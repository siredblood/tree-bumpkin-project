#include "pch.hpp"
#include "NavigationMap.h"
#include "romp/geometrics.hpp"
#include "GeneralClass/CustomCollision.h"
CNavigationMap CNavigationMap::instance;

CNavigationMap::CNavigationMap(void)
{
	TaskManager::instance().add( this, "CNavigationMap", NULL );
	
	m_bDrawDir = true;
	m_ChineseFont.InitFont(20, 30, "¡• È");
	
	m_Position = eRightTop;

	m_fNavWidth = 100;
	m_fMapWidth = -1;
	m_fMapDepth = -1;
}

CNavigationMap::~CNavigationMap(void)
{
}

CNavigationMap &CNavigationMap::Instance()
{
	return instance;
}

void CNavigationMap::draw()
{
	if(!m_bDrawDir)
		return;
	
	float fWinHeight = Moo::rc().screenHeight();
	float fWinWidth = Moo::rc().screenWidth();
	Matrix cameraMatrix  = Moo::rc().view();
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	if(m_fMapWidth<0)
	{
		BoundingBox spaceBB(ChunkManager::instance().cameraSpace()->gridBounds());
		const Vector3& minB = spaceBB.minBounds();
		const Vector3& maxB = spaceBB.maxBounds();
		INFO_MSG("%f,%f,%f\n", spaceBB.width(), spaceBB.height(), spaceBB.depth());
		m_fMapWidth = spaceBB.width();
		m_fMapDepth = spaceBB.depth();
	}
	float xratio = camerapos.x / m_fMapWidth;
	float zratio = camerapos.z / m_fMapDepth;
	
	INFO_MSG("camera: %f,%f\n", camerapos.x, camerapos.z);
	INFO_MSG("%f,%f\n", xratio, zratio);

	Vector2 centerpt, xzpos,xfpos,zzpos,zfpos, ypos;// = Vector2( 40, 40 );
	Vector2 NothPt, SouthPt, EastPt, WestPt;
	
	switch( m_Position )
	{
		case eLeftTop:
			centerpt = Vector2(m_fNavWidth, m_fNavWidth );
			break;
		case eLeftDown:
			centerpt = Vector2(m_fNavWidth, fWinHeight- m_fNavWidth);
			break;
		case eRightTop:
			centerpt = Vector2(fWinWidth-m_fNavWidth, m_fNavWidth);
			break;
		case eRightDown:
			centerpt = Vector2(fWinWidth-m_fNavWidth, fWinHeight-m_fNavWidth);
			break;
		case eCenter:
			centerpt = Vector2(fWinWidth/2, fWinHeight/2);
			break;
	};

	Vector2 LeftTop, RightBottom;
	LeftTop = centerpt - Vector2(m_fNavWidth,m_fNavWidth);
	RightBottom = centerpt + Vector2(m_fNavWidth,m_fNavWidth);
	if(handDrawnMap_==NULL)
	{
		CString strTexName;
		strTexName.Format("%s\\µº∫ΩÕº.jpg",g_strExeFullPath);
		handDrawnMap_ = Moo::TextureManager::instance()->get(
			strTexName.GetBuffer(0),
			false,						// allowAnimation
			false						// mustExist
			);
	}
	if(handDrawnMap_!=NULL)
		Geometrics::drawTexRect( LeftTop, RightBottom, handDrawnMap_, true);

	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 rightdir, leftdir;
	cameradir.x = -cameradir.x;
	rightdir.setPitchYaw( (-cameradir).pitch(), (-cameradir).yaw()+MATH_PI/4.0f );
	leftdir.setPitchYaw( (-cameradir).pitch(), (-cameradir).yaw()-MATH_PI/4.0f );
	rightdir.normalise();
	leftdir.normalise();
	Vector2 dir = Vector2( cameradir.x, cameradir.z);
	Vector2 rdir = Vector2( rightdir.x, rightdir.z );
	Vector2 ldir = Vector2( leftdir.x, leftdir.z );
	dir.normalise();
	rdir.normalise();
	ldir.normalise();

	Vector2 arrowpos = Vector2(centerpt.x + m_fNavWidth*2*xratio, centerpt.y - m_fNavWidth*2*zratio);
	zzpos = arrowpos - dir * 10.0;
	Vector2 rmpos,lmpos;
	rmpos = arrowpos - rdir * 10.0f;
	lmpos = arrowpos - ldir * 10.0f;

	Geometrics::drawTriangle(arrowpos, zzpos, rmpos, 0xb4ff0000 );
	Geometrics::drawTriangle(arrowpos, lmpos, zzpos, 0xb4ff0000 );

	m_ChineseFont.DrawChineseText("N", int(centerpt.x), int(centerpt.y - m_fNavWidth+10), 
		0xb4ff0000, CChineseFont::eCenterFlush, false);
}

void CNavigationMap::SetDraw(bool bDrawDir)
{
	m_bDrawDir = bDrawDir;
}

bool CNavigationMap::IsDraw()
{
	return m_bDrawDir;
}

void CNavigationMap::SetDrowPosition(POSITION position)
{
	m_Position = position;
}

CNavigationMap::POSITION CNavigationMap::GetDrawPosition()
{
	return m_Position;
}
