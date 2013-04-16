#include "pch.hpp"
//#include "app.hpp"
#include "CustomCamera.h"
#include "chunk/chunk_manager.hpp"
#include "math.h"
#include "worldeditor/misc/world_editor_camera.hpp"
#include "GeneralClass/Common.h"
#include "romp/geometrics.hpp"

#include "BuildingScheme/AddBuildingSchemeDlg.h"
#include "BuildingScheme/buildingSchemeManager.h"
#include "BuildingScheme/BuildingSchemeManagerDlg.h"

#define  SECTION  100

CCustomCamera CCustomCamera::instance;

CCustomCamera::CCustomCamera(void)
{
	BW_GUARD;
	
	TaskManager::instance().add( this, "CCustomCamera", NULL );
	
	m_ulState = eNONE;
	m_offset = Vector3(0,0,0); 
	m_fAroundSpeed = 0.02f;
	m_bMoveBack = false; 
	m_bMoveForward = false;
	m_bMoveDown = false;
	m_bMoveUp = false;
	m_bSpeeddown = false;
	m_bSpeedup = false;
}

CCustomCamera::~CCustomCamera(void)
{
}

CCustomCamera &CCustomCamera::Instance()
{
	return instance;
}

void CCustomCamera::init()
{
}

void CCustomCamera::fini()
{
}

void CCustomCamera::tick( float dTime )
{
	if(m_ulState==eNONE)
		return;
		
	if(m_ulState==eAROUND)
	{
		if(m_bSpeedup)
		{
			if(m_fAroundSpeed<1)
				m_fAroundSpeed+=0.001f;
		}
		if(m_bSpeeddown)
		{
			if(m_fAroundSpeed>=0.001f)
				m_fAroundSpeed-= 0.001f;
		} 
		if( m_bMoveForward )
		{
			if(m_fDistance>0)
				m_fDistance -= 0.5f;
		}
		if( m_bMoveBack )
		{
			m_fDistance += 0.5f;
		}
		if( m_bMoveUp )
		{
			m_tarpos += Vector3(0, 0.5, 0);
		}
		if( m_bMoveDown )
		{
			m_tarpos -= Vector3(0, 0.5, 0);
		}
	}
	
	switch ( m_ulState )
	{
		case eROAM:
			break;
		case eAROUND:
			AroundCamera();
			break;
	}
}

void CCustomCamera::draw()
{
}

void CCustomCamera::handleKeyEvent( const KeyEvent & event )
{
	switch (event.key())
	{
	case KeyEvent::KEY_1:	//给对象添加方案
		{
			if( event.isKeyDown() )
			{
				std::vector<ChunkItemPtr> vSelItems = WorldManager::instance().selectedItems();
				if(vSelItems.size()==1)
				{
					std::string strGuid = vSelItems[0]->edGUID();
					AddBuildingSchemeDlg::getInstance()->ShowWindow(SW_SHOW);
					AddBuildingSchemeDlg::getInstance()->setSelectedModel(strGuid);
				}
			}
			
		}
		break;
	case KeyEvent::KEY_2:	//执行方案
		{
			if( event.isKeyDown() )
			{
				std::vector<CString> vAllSchemeName = BuildingSchemeManager::getInstance()->getAllSchemeName();
				if(vAllSchemeName.size()>0)
					BuildingSchemeManager::getInstance()->executeScheme(vAllSchemeName[0] );
			}
			
		}
		break;
	case KeyEvent::KEY_3:	//删除对象的方案
		{
			if( event.isKeyDown() )
			{
				std::vector<ChunkItemPtr> vSelItems = WorldManager::instance().selectedItems();
				int isize = vSelItems.size();
				for(int i=0; i<isize; i++)
				{
					std::string strGuid = vSelItems[i]->edGUID();
					BuildingSchemeManager::getInstance()->deleteSchemeByModel( strGuid.c_str() );
				}
			}
		}
		break;
	case KeyEvent::KEY_4:
		{
			if( event.isKeyDown() )
			{
				BuildingSchemeManagerDlg::getInstance()->ShowWindow(SW_SHOW);
				BuildingSchemeManagerDlg::getInstance()->showResult();
			}
		}
		break;
	}

	if(m_ulState!=eAROUND)
		return;
		
	switch (event.key())
	{
	case KeyEvent::KEY_EQUALS:
	case KeyEvent::KEY_ADD:
		if( event.isKeyDown() )
			m_bSpeedup = true;
		if( event.isKeyUp() )
			m_bSpeedup = false;
		break;
	case KeyEvent::KEY_MINUS:
	case KeyEvent::KEY_NUMPADMINUS:
		if( event.isKeyDown() )
			m_bSpeeddown = true;
		if( event.isKeyUp() )
			m_bSpeeddown = false;
		break;
	case KeyEvent::KEY_Z:
		//m_tarpos += Vector3(0, 0.5, 0);
		if( event.isKeyDown() )
			m_bMoveUp = true;
		if( event.isKeyUp() )
			m_bMoveUp = false;
		break;
	case KeyEvent::KEY_X:
		//m_tarpos -= Vector3(0,0.5,0);
		if( event.isKeyDown() )
			m_bMoveDown = true;
		if( event.isKeyUp() )
			m_bMoveDown = false;
		break;
	case KeyEvent::KEY_W:
		if(event.isKeyDown())
			m_bMoveForward = true;
		if( event.isKeyUp() )
			m_bMoveForward = false;
		break;
	case KeyEvent::KEY_S:
		if(event.isKeyDown())
			m_bMoveBack = true;
		if( event.isKeyUp() )
			m_bMoveBack = false;
		break;

	
		
	default:
		break;
	}
}

void CCustomCamera::handleMouseEvent( const MouseEvent & event )
{
	if(m_ulState!=eAROUND)
		return;
		
	//if( event.dx()>0 && m_fDistance> fabs(event.dz()/50.0f) )
	m_fDistance -= event.dz()/50.0f;
	//else
	if( m_fDistance<0.01f)
		m_fDistance = 0.01f;
	
	if( InputDevices::isKeyDown( KeyEvent::KEY_RIGHTMOUSE ) )
	{

		float deltaPitch = event.dy() / 100.0f;
		//deltaPitch *= event.dz() ? -1.0f : 1.0f;

		m_fPitch += deltaPitch;
		if( m_fPitch< -MATH_PI/2.0f)
			m_fPitch = -MATH_PI/2.0f + 0.0001f;
		if( m_fPitch>MATH_PI/2.0f)
			m_fPitch = MATH_PI/2.0f - 0.0001f;
	}
}
	
bool CCustomCamera::IsRoamToTar()
{
	return m_ulState==eROAM ? true : false;
}

bool CCustomCamera::IsAroundTar()
{
	return m_ulState==eAROUND ? true : false;
}

void CCustomCamera::StopAroundTar()
{
	m_ulState = eNONE;
}

void CCustomCamera::StopRoamToTar()
{
	m_ulState = eNONE;
}

void CCustomCamera::TeleportToTar(Vector3 tarpos, float fDistance)
{
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);//App::instance().getWorldRay();
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();

	Vector3 dir = tarpos - camerapos;
	dir.normalise();
	dir.y = 0;
	
	Vector3 newpos = tarpos - dir * fDistance + Vector3(0,fDistance/2,0);
	dir = tarpos - newpos;
	dir.normalise();

	TeleportCamera( newpos, dir );
}

void CCustomCamera::TeleportCamera(Vector3 pos, Vector3 dir)
{
	
	Matrix view_ = WorldEditorCamera::instance().currentCamera().view();
	Matrix oldView = view_;

	view_.invert();

	Vector3 lastpos( view_.applyToOrigin() );
	Vector3 lastdir( view_.applyToUnitAxisVector(2) );

	if (!almostEqual( pos.x, lastpos.x ) || !almostEqual( pos.y, lastpos.y ) || !almostEqual( pos.z, lastpos.z ) ||
		!almostEqual( dir.yaw(), lastdir.yaw() ) || !almostEqual( dir.pitch(), lastdir.pitch() ))
	{
		view_.setIdentity();

		Matrix rot;
		XPMatrixRotationYawPitchRoll( &rot, dir.yaw(), dir.pitch(), 0.f );

		view_.setTranslate( pos );
		view_.preMultiply( rot );

		view_.invert();
	}
	else
	{
		view_ = oldView;
	}

	WorldEditorCamera::instance().currentCamera().view( view_ );
}

void CCustomCamera::RoamToTar(Vector3 tarpos, float fDistance)
{

	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	
	//生成bezier曲线
	m_vRoamPoints.clear();
	std::vector<float> vPtX, vPtZ;
	Vector3 midPos;
	Vector3 tardir, middir;
	float fHeight, fTarLen;
	tardir = tarpos - camerapos ;
	fTarLen = tardir.length();
	tardir.normalise();
	float yaw = (tardir.yaw()+cameradir.yaw()) / 2.0f;
	middir.setPitchYaw( cameradir.pitch(), yaw );
	middir.normalise();
	
	midPos = camerapos + middir * fTarLen/2.0f;
	
	vPtX.push_back( camerapos.x );
	vPtX.push_back( midPos.x );
	vPtX.push_back( tarpos.x );
	
	vPtZ.push_back( camerapos.z );
	vPtZ.push_back( midPos.z );
	vPtZ.push_back( tarpos.z );
	
	fHeight = tarpos.y - camerapos.y;
	
	int k = 10;
	float fPerHeight = fHeight / (float)k;
	float t, x, z, y;
	Vector3 pt;
	
	for(int i=0; i<=k; i++)
	{   
		t = (float)i/k;
		x = bezier(vPtX,t);      
		z = bezier(vPtZ,t);
		y = camerapos.y + fPerHeight*(float)i;
		pt = Vector3(x,y,z);
		if( (pt-tarpos).length()>fDistance )
			m_vRoamPoints.push_back( pt );
	}
	
	m_ulState = eROAM;
}

void CCustomCamera::AroundTar(Vector3 tarpos, float fDistance)
{
	m_tarpos = tarpos;
	m_fDistance = fDistance;

	
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	
	cameradir.y = 0;
	m_lastdir = -cameradir;
	Vector3 newpos = tarpos - cameradir * fDistance;
	m_fPitch = cameradir.pitch();
	
	TeleportCamera(newpos, cameradir);
	
	m_ulState = eAROUND;
}

void CCustomCamera::RoamCamera()
{
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	
	float fLen = (camerapos - m_tarpos).length();
	if(fLen<m_fPerDis)
	{	
		m_ulState = eNONE;
		return;
	}
	Vector3 newpos = camerapos + m_RoamDir /*cameradir*/ * m_fPerDis;
	
	Vector3 dir;
	dir.setPitchYaw( cameradir.pitch()+m_fPerPitch, cameradir.yaw() + m_fPerYaw);
	dir.normalise();
	
	TeleportCamera(newpos, dir);
}

void CCustomCamera::AroundCamera()
{
	Vector3 newDir;

	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);

	float fLastYaw = m_lastdir.yaw();

	float fNewYaw = fLastYaw + m_fAroundSpeed;
	newDir.setPitchYaw(m_fPitch, fNewYaw );
	m_lastdir = newDir;
	Vector3 newpos = m_tarpos - m_fDistance * newDir /*+ m_offset*/;
	
	TeleportCamera(newpos, newDir);
}

Vector3 CCustomCamera::GetCameraPos()
{
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();

	return camerapos;
}