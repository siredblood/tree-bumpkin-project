#include "pch.hpp"
//#include "app.hpp"
#include "MarkObject.h"
#include "MarkManage.h"
#include "worldeditor/world/world_manager.hpp"
#include "worldeditor/Editor/chunk_item_placer.hpp"
#include "GeneralClass/Common.h"

static const int FontWidth = 10;
static const int FontHeight = 30;

CMarkObject CMarkObject::instance;

CMarkObject &CMarkObject::Instance()
{
	return instance;
}

CMarkObject::CMarkObject(void)
{
	BW_GUARD;
	
	TaskManager::instance().add( this, "CMarkObject", NULL );
	
	m_bDraw = false;
}

CMarkObject::~CMarkObject(void)
{
	BW_GUARD;

	m_vAllMarkIcon.clear();
}

void CMarkObject::init()
{
	m_ChineseFont.InitFont(FontWidth, FontHeight, "黑体");
}

void CMarkObject::fini()
{
	BW_GUARD;
	int iMarkSize = m_vAllMarkIcon.size();
	for(int i=0; i<iMarkSize; i++)
	{
		if(m_vAllMarkIcon[i]!=NULL)
		{
			CancelSeleteItem( m_vAllMarkIcon[i] );
			m_vAllMarkIcon[i]->chunk()->delStaticItem( m_vAllMarkIcon[i] );
		}
	}
	m_vAllMarkIcon.clear();
}

void CMarkObject::tick( float dTime )
{
	//把标注按远到近排序
	SortByDis();

	m_LastDir = Moo::rc().invView().applyToUnitAxisVector(2);
	m_LastPos = Moo::rc().invView().applyToOrigin();
	
	std::vector<ChunkItemPtr> vSelItems = WorldManager::instance().selectedItems();
	int iSelSize = vSelItems.size();
	if(iSelSize==0)
		return;
		
	std::vector<ChunkItemPtr>::iterator p;
	std::string strGUID;
	int iIndex=-1;
	Vector3 pos;
	Matrix mat;
	//Matrix newMat;
	BoundingBox box;
	
	for(p=vSelItems.begin(); p!=vSelItems.end(); p++)
	{
		if( (*p)==NULL )
			continue;

		strGUID = (*p)->edGUID();
		if( CheckExistByGUID(strGUID, iIndex) )
		{
			mat = (*p)->chunk()->transform();
			mat.preMultiply((*p)->edTransform());
			//pos = mat.applyToOrigin();
			(*p)->edSelectedBox( box );
			box.transformBy( mat );
			//pos.y = pos.y + box.height() + 5.0f;
			if( m_vMarkData[iIndex].strType=="0" )
				pos = box.centre() + Vector3(0, box.height()/2.0f, 0);
			else
				pos = box.centre() + Vector3(0, box.height()/2.0f, 0);
			ModifyMark( strGUID, pos);
		}
	}
}

void CMarkObject::draw()
{
	if(!m_bDraw)
		return;

	int iSize = m_vMarkData.size();
	int x, y;

	Vector3 pos;
	std::string strText, strGUID, strType;
	int iScreenWidth = (int)Moo::rc().screenWidth();
	int iScreenHeight = (int)Moo::rc().screenHeight();
	int ffwidth=0,ffhight=0;
	
	
	for( int i=0; i<iSize; i++) 
	{
		pos = m_vMarkData[i].pos; //m_vDrawPos[i];

		Conver3DTo2D(pos, x, y);
		////INFO_MSG("%d,%d\n", x, y);
		
		if(!IsPositionInView(pos) )
			continue;
			
		if(x<0 || x> iScreenWidth || y<0 || y>iScreenHeight)
			continue;

		//如果距离超过可视范围就不显示
		Vector3 camerapos = Moo::rc().invView().applyToOrigin();
		float fLen = (camerapos - pos ).length();
		//INFO_MSG("%d:%f\n",i,m_vMarkData[i].fViewDist);
		float fviewdist=m_vMarkData[i].fViewDist;
		if (fLen>fviewdist)
			continue;
			
		strText = m_vMarkData[i].strText;	//m_vDrawText[i];

		//m_ChineseFont.DrawChineseText( "", strText, x, y, 0xffffffff, CChineseFont::eCenterFlush );

		m_ChineseFont.DrawChineseText( strText, x, y, 0xffffffff, 10.f, CChineseFont::eCenterFlush, true );
	
		strGUID = m_vMarkData[i].strGUID;
		strType = m_vMarkData[i].strType;
		if(strType=="0")	//如果是任意位置标注，并且还没有添加对象
		{
			if(!m_vMarkData[i].bHaveObject)
			{
				ChunkItemPtr pMarkitem = ChunkItemPlacer::createDBChunkItem( MARK_MODEL,
					strGUID, pos.x,pos.y-5,pos.z,0.0,0.0,0.0,1.0,1.0,1.0 );
				if(pMarkitem!=NULL) 
				{
					BoundingBox box;
					Matrix mat = pMarkitem->chunk()->transform();
					mat.preMultiply(pMarkitem->edTransform());
					pMarkitem->edSelectedBox( box );
					box.transformBy( mat );
					Vector3 centre = box.centre();
					float fBottom = (centre - mat.applyToOrigin()).length() - box.height()/2;

					Vector3 pos = m_vMarkData[i].pos - Vector3(0, box.height() + fBottom + 1.0f, 0);
					MoveItemToPos(pMarkitem, pos, Vector3(0,0,0) );

					m_vMarkData[i].strGUID = pMarkitem->edGUID();
					m_vMarkData[i].bHaveObject = true;
					m_vAllMarkIcon.push_back(pMarkitem);
				}
			}
			
		}
	}	
}

void CMarkObject::AddDrawMessage(MARKDATA markdata)
{
	if(markdata.strType=="0")
	{
		m_vMarkData.push_back(markdata);
	}
	else
	{
		int index = -1;
		if(CheckExistByGUID(markdata.strGUID,index))
		{	
			m_vMarkData[index] = markdata;
		}
		else
		{
			m_vMarkData.push_back(markdata);
		}

	}
}
void CMarkObject::DeleteMark(std::string strGUID)
{
	int index=-1;
	if (CheckExistByGUID(strGUID,index))
	{
		
		std::string strItemGuid;
		std::string strGUID = m_vMarkData[index].strGUID;
		std::vector<ChunkItemPtr>::iterator p;
		for(p=m_vAllMarkIcon.begin(); p!=m_vAllMarkIcon.end(); p++)
		{
			strItemGuid = (*p)->edGUID();
			if(strItemGuid==strGUID)
			{
				CancelSeleteItem((*p));
				(*p)->chunk()->delStaticItem( (*p) );
				m_vAllMarkIcon.erase(p);
				break;
			}
		}
		DeleteMark(index);
	}
}
//清除场景中所有标注
void CMarkObject::ClearAllMark()
{
	std::string strItemGuid, strGUID;
	std::vector<ChunkItemPtr>::iterator p;
	
	int iSize = m_vMarkData.size();
	for(int i=0; i<iSize; i++)
	{
		
		strGUID = m_vMarkData[i].strGUID;
		
		for(p=m_vAllMarkIcon.begin(); p!=m_vAllMarkIcon.end(); p++)
		{
			strItemGuid = (*p)->edGUID();
			if(strItemGuid==strGUID)
			{
				CancelSeleteItem((*p));
				(*p)->chunk()->delStaticItem( (*p) );
				m_vAllMarkIcon.erase(p);
				break;
			}
		}
	}
	m_vMarkData.clear();
}
void CMarkObject::SetDrawMessage(std::vector<MARKDATA> vMarkdata)
{
	m_vMarkData = vMarkdata;
}

std::vector<MARKDATA> CMarkObject::GetDrawMessage( )
{
	return m_vMarkData;
}

void CMarkObject::ShowMark(bool bDraw)
{
	m_bDraw = bDraw;
	ShowMarkModel(bDraw);
}

bool CMarkObject::IsShowMark()
{
	return m_bDraw;
}

void CMarkObject::Conver3DTo2D(Vector3 pos, int &x, int &y)
{

	Matrix viewProj = Moo::rc().view();
	viewProj.postMultiply( Moo::rc().projection() );  
	Vector3 projectedPos = viewProj.applyPoint(pos);  
	float halfx = Moo::rc().halfScreenWidth();
	float halfy = Moo::rc().halfScreenHeight();
	float fx = projectedPos.x * halfx + halfx;
	float fy = halfy - projectedPos.y * halfy;
	x = int(fx);
	y = int(fy);
}

bool CMarkObject::IsPositionInView(Vector3 pos)
{
	//POINT pt = WorldManager::instance().currentCursorPosition();
	
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);//App::instance().getWorldRay();
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	Vector3 tarDir = pos - camerapos;
	float fLen = tarDir.length();
	tarDir.normalise();
	
	float fDotRes = cameradir.dotProduct( tarDir );	
	if(fDotRes>0)
	{
		if(fLen>Moo::rc().camera().farPlane())
			return false;
		else
			return true;
	}
	else	
		return false;
}

bool CMarkObject::CheckExistByPosition(Vector3 pos, int &index, std::string &strText)
{
	bool bExist = false;
	int iSize = m_vMarkData.size();	//m_vDrawPos.size();
	float fLen;
	Vector3 itempos;
	for(int i=0; i<iSize; i++)
	{
		itempos = m_vMarkData[i].pos;	//m_vDrawPos[i];
		fLen = (pos-itempos).length();
		if(fLen<1.0E-6)
		{
			index = i;
			strText = m_vMarkData[i].strText;	//m_vDrawText[i];
			bExist = true;
			break;
		}
	}
	
	return bExist;
}

bool CMarkObject::CheckExistbyText( std::string strText )
{
	bool bExist = false;
	int iSize =	m_vMarkData.size();	//m_vDrawText.size();
	for(int i=0; i<iSize; i++)
	{
		if( strText==m_vMarkData[i].strText /*m_vDrawText[i]*/ )
		{
			bExist = true;
			break;
		}
	}
	
	return bExist;
}

void CMarkObject::DeleteMark(int index)
{
	std::vector<MARKDATA>::iterator p = m_vMarkData.begin();
	for(int i=0; i<index; i++)
	{
		p++;
	}
	m_vMarkData.erase(p);
}

//void CMarkObject::DeleteMark(Vector3 pos)
//{
//	int iSize = m_vMarkData.size();	//m_vDrawPos.size();
//	float fLen;
//	int index=-1;
//	Vector3 itempos;
//	for(int i=0; i<iSize; i++)
//	{
//		itempos = m_vMarkData[i].pos;	//m_vDrawPos[i];
//		fLen = (pos-itempos).length();
//		if(fLen<1.0E-6)
//		{
//			index = i;
//			break;
//		}
//	}
//	if(index!=-1)
//	{
//		std::string strName = m_vMarkData[index].strText;	//m_vDrawText[index];
//		DeleteMark(index);
//		
//		////INFO_MSG("%d, %s\n", index, strName.c_str());
//		CMarkManage::Instance().DeleteMarkByName( strName );
//	}
//
//}
 //根据GUID判断是否有标注
bool CMarkObject::CheckExistByGUID(std::string strGUID ,int &iindex)
{
	bool bExist = false;
	int iSize =	m_vMarkData.size();	//m_vDrawText.size();
	for(int i=0; i<iSize; i++)
	{
		if( strGUID==m_vMarkData[i].strGUID /*m_vDrawText[i]*/ )
		{
			iindex=i;
			bExist = true;
			break;
		}
	}
	return bExist;
}

int CMarkObject::ModifyMark(std::string strGUID, Vector3 pos)
{
	int iIndex=-1;
	if(CheckExistByGUID(strGUID, iIndex))
	{
		m_vMarkData[iIndex].pos = pos;
	}
	return iIndex;
}

int CMarkObject::ModifyMark(std::string strGUID, std::string strText)
{
	int iIndex=-1;
	if(CheckExistByGUID(strGUID, iIndex))
	{
		m_vMarkData[iIndex].strText = strText;
	}
	return iIndex;
}
int CMarkObject::ModifyMark(std::string strGUID, std::string strText,float fviewDist)
{
	int iIndex=-1;
	if(CheckExistByGUID(strGUID, iIndex))
	{
		m_vMarkData[iIndex].strText = strText;
		m_vMarkData[iIndex].fViewDist = fviewDist;
	}
	return iIndex;
}

//MARKDATA CMarkObject::GetMark(int index){
//	return m_vMarkData.at(index);
//}

void CMarkObject::SortByDis()
{
	int iSize = m_vMarkData.size();
	if( iSize==0 )
		return;
	
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	
	if( almostEqual(m_LastDir,cameradir) && almostEqual(m_LastPos, camerapos) )
	{
		return;
	}
	std::vector<float> vDistance;
	float /*fDis,*/ fDis1, fDis2;
	MARKDATA TempMark;
	
	//排序
	for(int i=0; i<iSize; i++)
	{
		for(int j=0; j<iSize-1-i; j++)
		{
			fDis1 = (camerapos-m_vMarkData[j].pos).length();
			fDis2 = (camerapos-m_vMarkData[j+1].pos).length();
			if(fDis1<fDis2)
			{
				TempMark = m_vMarkData[j];
				m_vMarkData[j] = m_vMarkData[j+1];
				m_vMarkData[j+1] = TempMark;
			}
		}
	}
}

void CMarkObject::ShowMarkModel( bool bType )
{
	int iSize = m_vAllMarkIcon.size();
	for( int i=0; i < iSize; i++ )
	{
		CancelSeleteItem( m_vAllMarkIcon[i] );
		m_vAllMarkIcon[i]->edSetShouldDraw( bType );
	}
}