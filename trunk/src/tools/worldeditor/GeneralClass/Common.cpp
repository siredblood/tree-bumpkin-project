#include "pch.hpp"
#include "GeneralClass/CustomCollision.h"
#include "world/editor_chunk.hpp"

Moo::Colour ConverStrToColorRGB(char *szColor)
{
	Moo::Colour ulColor;
	int r,g,b;
	
	sscanf(szColor, "%d;%d;%d", &r, &g, &b);
	ulColor = D3DCOLOR_XRGB(r,g,b);
	
	return ulColor; 
}

Moo::Colour ConverStrToColorARGB(char *szColor)
{
	Moo::Colour ulColor;
	int a,r,g,b;
	
	sscanf(szColor, "%d;%d;%d;%d", &a, &r, &g, &b);

	ulColor = D3DCOLOR_ARGB(a,r,g,b);

	return ulColor; 
}

CString ConverColorRGBToStr( Moo::Colour ulColor )
{
	CString strColor;
	strColor.Format("%d;%d;%d", int(ulColor.r*255), int(ulColor.g*255), int(ulColor.b*255) );
	
	return strColor;
}

CString ConverColorARGBToStr( Moo::Colour ulColor )
{
	CString strColor;
	strColor.Format("%d;%d;%d;%d", int(ulColor.a*255), int(ulColor.r*255), int(ulColor.g*255), int(ulColor.b*255) );

	return strColor;
}

Vector3 ConvertStrToVec3(char *szPos)
{
	Vector3 pos;
	float x=0.0f, y=0.0f, z=0.0f;
	
	sscanf(szPos, "%f,%f,%f", &x,&y,&z);
	
	pos = Vector3(x,y,z);

	return pos;
}

CString ConvertVec3ToStr(Vector3 pos)
{
	CString strPos;
	
	strPos.Format("%.4f,%.4f,%.4f", pos.x, pos.y, pos.z);
	
	return strPos;
}

Vector2 ConvertVec3ToScreenPt(Vector3 pos)
{
	Matrix viewProj = Moo::rc().view();
	viewProj.postMultiply( Moo::rc().projection() );  
	Vector3 projectedPos = viewProj.applyPoint(pos);  
	float halfx = Moo::rc().halfScreenWidth();
	float halfy = Moo::rc().halfScreenHeight();
	float fx = projectedPos.x * halfx + halfx;
	float fy = halfy - projectedPos.y * halfy;
	
	Vector2 ScreenPt = Vector2( fx, fy );
	
	return ScreenPt;
}

void CancelSeleteItem(ChunkItemPtr item)
{
	std::vector<ChunkItemPtr> vSelectedItems = WorldManager::instance().selectedItems();
	std::vector<ChunkItemPtr>::iterator p = vSelectedItems.begin();
	int iSize = vSelectedItems.size();
	for(int i=0; i<iSize; i++)
	{
		if( (*p)== item )
		{
			vSelectedItems.erase( p );
			break;
		}
	}

	WorldManager::instance().setSelection( vSelectedItems );
}

bool IsPositionInView(Vector3 pos)
{
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);//App::instance().getWorldRay();
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	Vector3 tarDir = pos - camerapos;
	float fLen = tarDir.length();
	tarDir.normalise();

	float fDotRes = cameradir.dotProduct( tarDir );	
	if(fDotRes>0)
	{
		float fFarPlane = Moo::rc().camera().farPlane();
		if(fLen>fFarPlane)
			return false;
		else
			return true;
	}
	else	
		return false;
}

bool IsPositionCanSee(Vector3 pos)
{
	Vector3 start =  Moo::rc().invView().applyToOrigin();
	CustomCollision sc;
	float fRet = ChunkManager::instance().cameraSpace()->collide( start, pos, sc );
	if(fRet<0)
		return true;
	else
		return false;
}

//判断点是否在直线上
bool IsPointInLine(Vector3 LinePt1, Vector3 LinePt2, Vector3 newPt)
{
	float fLineLen, fDisToPt1, fDisToPt2;
	fLineLen = (LinePt2-LinePt1).length();
	fDisToPt1 = (newPt-LinePt1).length();
	fDisToPt2 = (newPt-LinePt2).length();
	//点在线的中间，点在线的左边，点在线的右边
	if( /*fabs(fDisToPt1+fDisToPt2-fLineLen)<0.0001 || fabs(fDisToPt1+fLineLen-fDisToPt2)<0.0001 ||*/
	   fabs(fLineLen+fDisToPt2-fDisToPt1)<0.0001 )
	   return true;
	else
		return false;
}

bool IsStringInVector( std::string sText, std::vector<CString> &vTextVector )
{
	bool bMatch = false;
	CString strText = sText.c_str();
	int iSize = vTextVector.size();
	for(int i=0; i<iSize; i++)
	{
		if(vTextVector[i]==strText)
		{
			bMatch = true;
			break;
		}
	}
	return bMatch;
}

void CalculatePolygonMinMaxBound(std::vector<Vector3> &vBound, Vector3 &MinPt, Vector3 &MaxPt)
{
	int iSize = vBound.size();
	if(iSize==0)
		return;
	MinPt = vBound[0];
	MaxPt = vBound[0];
	for(int i=1; i<iSize; i++)
	{
		if(vBound[i].x<MinPt.x)
			MinPt.x = vBound[i].x;
		if(vBound[i].z<MinPt.z)
			MinPt.z = vBound[i].z;
		if(vBound[i].y<MinPt.y)
			MinPt.y = vBound[i].y;

		if(vBound[i].x>MaxPt.x)
			MaxPt.x = vBound[i].x;
		if(vBound[i].z>MaxPt.z)
			MaxPt.z = vBound[i].z;
		if(vBound[i].y>MaxPt.y)
			MaxPt.y = vBound[i].y;
	}
}

Vector3 CalculatePolygonCentre(std::vector<Vector3> &vPolygon)
{
	Vector3 MinPt, MaxPt;
	CalculatePolygonMinMaxBound( vPolygon, MinPt, MaxPt);
	return (MinPt+MaxPt)/2.0f;
}

void CalculatePolygonMinMaxCentre(std::vector<Vector3> &vBound, Vector3 &MinPt, Vector3 &MaxPt, Vector3 &Centre)
{
	CalculatePolygonMinMaxBound( vBound, MinPt, MaxPt);
	Centre = (MinPt+MaxPt)/2.0f;
}

//生成bezier曲线点
float bezier(std::vector<float> p, float t)
{
	int i,r;
	int n = p.size() - 1;
	std::vector<float> q;
	q = p;
	for(r=1;r<=n;r++)
	{        
		for(i=0;i<=n-r;i++)
		{       
			q[i]=(1-t)*q[i]+t*q[i+1];
		}
	}

	return(q[0]);

}

CString GetNowTime()
{
	CString strTime;
	COleDateTime time = COleDateTime::GetCurrentTime();
	strTime.Format( "%d-%.2d-%.2d %.2d:%.2d:%.2d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), 
				   time.GetMinute(), time.GetSecond() );
				   
	return strTime;
}

int timeToInt( const std::string & value )
{
	std::string strHour;
	std::string strMin;

	int nIdx = value.find_first_of( ':' );
	strHour = value.substr( 0, nIdx );
	strMin = value.substr( nIdx + 1 );

	int nHour = atoi( strHour.c_str() );
	int nMin = atoi( strMin.c_str() );

	if( nHour > 23 )
	{
		nHour = 23;
	}

	if( nMin > 59 )
	{
		nMin = 59;
	}

	return nHour * 60 + nMin;

}

/**
* \brief Convert an integer into a string, like 08:30
* \param nValue
* \return the string, like 08:30
* \see timeToInt
*/
std::string intToTime( int nValue )
{
	int nHour = nValue / 60;
	int nMin = nValue % 60;

	if( nHour == 24 && nMin == 0 )
		{
		nHour = 0;
		}

	std::string fmt;
	fmt += nHour >= 10 ? "%d:" : "0%d:";
	fmt += nMin >= 10 ? "%d" : "0%d";

	char szTime[128] = { 0 };

	int nlen = sprintf( szTime, fmt.c_str(), nHour, nMin );
	szTime[nlen] = '\0';

	return std::string( szTime );
}

/*===============================================================/
*	检测文件夹是否存在，如果不存在，就创建一个
*	参数:
*		CStrig strFolderPath	- 文件夹路径，可以绝对也可以是相对
*	返回值:
*		布尔值			- 文件夹存在或创建成功返回TRUE
不存在但创建失败返回FALSE
*	调用函数:
*		ErrorMessage()		- 自定义错误处理函数
===============================================================*/
BOOL CheckFolder( CString strFolderPath )
{
	BOOL bOK = FALSE;
	if( !CreateDirectory( strFolderPath, NULL ) )
	{
		bOK = TRUE;
	}
	else
	{
		DWORD dwCode = GetLastError();

		if( dwCode != 0 )
			MessageBox(NULL,"创建文件夹失败！","提示",MB_OK);
		//ErrorMessage( "CreateDirectory", dwCode );
	}

	return bOK;
}

void MoveItemToPos(ChunkItemPtr &item, Vector3 pos, Vector3 dir)
{
	Matrix oldMt = item->edTransform();
	Vector3 olddir = oldMt.applyToUnitAxisVector(2);

	Matrix posmt;
	posmt.setTranslate( pos );
	Matrix localPose;
	localPose.multiply( posmt, item->chunk()->transformInverse() );
	Matrix newPosemt;

	newPosemt = item->edTransform();
	newPosemt.translation( localPose.applyToOrigin() ); 

	Matrix rot/* = Matrix::identity*/;
	//rot.setRotate(dir.yaw(), dir.pitch(), 0.0f);
	//特意把yaw+PI，面向变反
	XPMatrixRotationYawPitchRoll( &rot, MATH_PI / 2 + (dir.yaw()-olddir.yaw()), 0.0, 0.f );
	newPosemt.preMultiply( rot ); 
	//newPosemt.invert();

	item->edTransform(newPosemt,false);
}

ChunkItemPtr findItem( CString strGuid )
{
	ChunkItemPtr pResultItem=NULL;
	std::vector<ChunkItemPtr> items;
	for( std::set<Chunk*>::iterator iter = EditorChunkCache::chunks_.begin();
		iter != EditorChunkCache::chunks_.end(); ++iter )
	{

		items = EditorChunkCache::instance( **iter ).staticItems();
		for(std::vector<ChunkItemPtr>::iterator itrItems = items.begin(); itrItems != items.end(); ++itrItems)
		{
			std::string strTMP = (*itrItems)->edGUID();
			if( !strTMP.compare( strGuid.GetBuffer() ) )
			{
				pResultItem = *itrItems;
				break;
			}
		}
		if(pResultItem!=NULL)
			break;
	}
	return pResultItem;
}
