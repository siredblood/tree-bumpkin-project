#include "pch.hpp"
#include "CustomWorldCamera.h"
#include "GeneralClass/Common.h"
#include "CustomCamera.h"
#include "GeneralClass/CustomCollision.h"
#include "worldeditor/world/world_manager.hpp"

CCustomWorldCamera CCustomWorldCamera::instance;

CCustomWorldCamera::CCustomWorldCamera(void)
{
	TaskManager::instance().add( this, "CCustomWorldCamera", NULL );
	
	m_CameraType = CCustomWorldCamera::CT_KeyBoard;
	m_bHaveViewCentre = false;
	m_bFlyingToCentre = false;
	m_bMoveBack =false;
	m_bMoveForward = false;
	m_bTurnLeft = false;
	m_bTurnRight = false;
	m_bTurnDown = false;
	m_bTurnUp = false;
	m_bSpeedUp = false;
	m_bSlowdown = false;
	m_fTAMSpeed = 0.05f;
	
	m_AxisYawLeft = KeyEvent::KEY_JOY9;
	m_AxisYawRight = KeyEvent::KEY_JOY14;
	m_AxisPithDown = KeyEvent::KEY_JOY8;
	m_AxisPithUp = KeyEvent::KEY_JOY10;
	m_AxisAddSpeed = KeyEvent::KEY_JOY13;
	m_AxisReduceSpeed = KeyEvent::KEY_JOY5;
	
	m_fAxisYawSpeed = 0.02f;
	m_fAxisPitchSpeed = 0.02f;
	m_fAxisMoveSpeed = 1.0f;
	
	m_fAxisKeyValue = 0.0f;
	
	m_bAxisMoveUD = false;
	m_bAxisMoveLR = false;
}

CCustomWorldCamera::~CCustomWorldCamera(void)
{
	m_pFollowItem = NULL;
}

CCustomWorldCamera &CCustomWorldCamera::Instance()
{
	return instance;
}

void CCustomWorldCamera::SetCameraType( Camera_Type cameraType )
{
	m_CameraType = cameraType;
	if( m_CameraType==CT_Mouse )
	{

		Vector3 worldRay = Moo::rc().invView().applyToUnitAxisVector(2);
		Vector3 camerapos =  Moo::rc().invView().applyToOrigin();
		Vector3 start =  camerapos;
		Vector3 extent = start + worldRay * Moo::rc().camera().farPlane();

		CustomCollision sc;
		float fRet = ChunkManager::instance().cameraSpace()->collide( start, extent, sc );
		if(fRet>0)
			m_ViewCentre = start + worldRay * fRet ;
		else
		{
			m_ViewCentre = start + worldRay * 50.0f;
		}
		
		m_fDisToCentre = (m_ViewCentre - camerapos).length();
		m_fPitch_ = worldRay.pitch();
		m_fYaw_ = worldRay.yaw();
	}
	else
	{
		m_bFollowing = false;
	}
}

CCustomWorldCamera::Camera_Type CCustomWorldCamera::GetCameraType()
{
	return m_CameraType;
}

void CCustomWorldCamera::SetCameraViewCentre(Vector3 pos)
{
	if(m_bFollowing)
		return;
	m_ViewCentre = pos;
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	m_fDisToCentre = (camerapos-m_ViewCentre).length();
	m_bHaveViewCentre = true;
}

void CCustomWorldCamera::handleKeyEvent( const KeyEvent & event )
{
	//INFO_MSG("handleKeyEvent");
	switch (event.key())
	{	
		case KeyEvent::KEY_JOY0:
			INFO_MSG("KEY_JOY0\n");
			break;
		case KeyEvent::KEY_JOY1:
			INFO_MSG("KEY_JOY1\n");
			break;
		case KeyEvent::KEY_JOY2:
			INFO_MSG("KEY_JOY2\n");
			break;
		case KeyEvent::KEY_JOY3:
			INFO_MSG("KEY_JOY3\n");
			break;
		case KeyEvent::KEY_JOY4:
			INFO_MSG("KEY_JOY4\n");
			break;
		case KeyEvent::KEY_JOY5:
			INFO_MSG("KEY_JOY5\n");
			break;
		case KeyEvent::KEY_JOY6:
			INFO_MSG("KEY_JOY6\n");
			break;
		case KeyEvent::KEY_JOY7:
			INFO_MSG("KEY_JOY7\n");
			break;
		case KeyEvent::KEY_JOY8:
			INFO_MSG("KEY_JOY8\n");
			break;
		case KeyEvent::KEY_JOY9:
			INFO_MSG("KEY_JOY9\n");
			break;
		case KeyEvent::KEY_JOY10:
			INFO_MSG("KEY_JOY10\n");
			break;
		case KeyEvent::KEY_JOY11:
			INFO_MSG("KEY_JOY11\n");
			break;
		case KeyEvent::KEY_JOY12:
			INFO_MSG("KEY_JOY12\n");
			break;
		case KeyEvent::KEY_JOY13:
			INFO_MSG("KEY_JOY13\n");
			break;
		case KeyEvent::KEY_JOY14:
			INFO_MSG("KEY_JOY14\n");
			break;
		case KeyEvent::KEY_JOY15:
			INFO_MSG("KEY_JOY15\n");
			break;
		case KeyEvent::KEY_JOY16:
			INFO_MSG("KEY_JOY16\n");
			break;
		case KeyEvent::KEY_JOY17:
			INFO_MSG("KEY_JOY17\n");
			break;
		case KeyEvent::KEY_JOY18:
			INFO_MSG("KEY_JOY18\n");
			break;
		case KeyEvent::KEY_JOY19:
			INFO_MSG("KEY_JOY19\n");
			break;
		case KeyEvent::KEY_JOY20:
			INFO_MSG("KEY_JOY20\n");
			break;
		case KeyEvent::KEY_JOY21:
			INFO_MSG("KEY_JOY21\n");
			break;
		case KeyEvent::KEY_JOY22:
			INFO_MSG("KEY_JOY22\n");
			break;
		case KeyEvent::KEY_JOY23:
			INFO_MSG("KEY_JOY23\n");
			break;
		case KeyEvent::KEY_JOY24:
			INFO_MSG("KEY_JOY24\n");
			break;
		case KeyEvent::KEY_JOY25:
			INFO_MSG("KEY_JOY25\n");
			break;
		case KeyEvent::KEY_JOY26:
			INFO_MSG("KEY_JOY26\n");
			break;
		case KeyEvent::KEY_JOY27:
			INFO_MSG("KEY_JOY27\n");
			break;
		case KeyEvent::KEY_JOY28:
			INFO_MSG("KEY_JOY28\n");
			break;
		case KeyEvent::KEY_JOY29:
			INFO_MSG("KEY_JOY29\n");
			break;
		case KeyEvent::KEY_JOY30:
			INFO_MSG("KEY_JOY30\n");
			break;
		case KeyEvent::KEY_JOY31:
			INFO_MSG("KEY_JOY31\n");
			break;
		case KeyEvent::KEY_JOYALUP:
			INFO_MSG("KEY_JOYALUP\n");
			break;
		case KeyEvent::KEY_JOYALDOWN:
			INFO_MSG("KEY_JOYALDOWN\n");
			break;
		case KeyEvent::KEY_JOYALLEFT:
			INFO_MSG("KEY_JOYALLEFT\n");
			break;
		case KeyEvent::KEY_JOYALRIGHT:
			INFO_MSG("KEY_JOYALRIGHT\n");
			break;
		case KeyEvent::KEY_JOYARUP:
			INFO_MSG("KEY_JOYARUP\n");
			break;
		case KeyEvent::KEY_JOYARDOWN:
			INFO_MSG("KEY_JOYARDOWN\n");
			break;
		case KeyEvent::KEY_JOYARLEFT:
			INFO_MSG("KEY_JOYARLEFT\n");
			break;
		case KeyEvent::KEY_JOYARRIGHT:
			INFO_MSG("KEY_JOYARRIGHT\n");
			break;
		case KeyEvent::KEY_DEBUG:
			INFO_MSG("KEY_DEBUG\n");
			break;
	}

	handleAxisKeyEvent( event );
	
	if( m_bFlyingToCentre && event.key()==KeyEvent::KEY_ESCAPE && event.isKeyDown())
	{
		StopFlyToCentre();
	}
	
	if(m_CameraType!=CT_Mouse)
		return;
	
	if( m_bFlyingToCentre || CCustomCamera::Instance().IsAroundTar() || CCustomCamera::Instance().IsRoamToTar())
	{
		return;
	}	
	switch (event.key())
	{
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
		case KeyEvent::KEY_A:
			if(event.isKeyDown())
				m_bTurnLeft = true;
			if( event.isKeyUp() )
				m_bTurnLeft = false;
				
			break;
		case KeyEvent::KEY_D:
			if(event.isKeyDown())
				m_bTurnRight = true;
			if( event.isKeyUp() )
				m_bTurnRight = false;
			break;
		case KeyEvent::KEY_Z:
			if(event.isKeyDown())
				m_bTurnDown = true;
			if( event.isKeyUp() )
				m_bTurnDown = false;
			break;
		case KeyEvent::KEY_X:
			if(event.isKeyDown())
				m_bTurnUp = true;
			if( event.isKeyUp() )
				m_bTurnUp = false;
			break;
			
		case KeyEvent::KEY_EQUALS:
		case KeyEvent::KEY_ADD:
			if( event.isKeyDown() )
				m_bSpeedUp = true;
			if( event.isKeyUp() )
				m_bSpeedUp = false;
			break;
		case KeyEvent::KEY_MINUS:
		case KeyEvent::KEY_NUMPADMINUS:
			if( event.isKeyDown() )
				m_bSlowdown = true;
			if( event.isKeyUp() )
				m_bSlowdown = false;
			break;
			
		default:
			break;
	}
}

void CCustomWorldCamera::handleMouseEvent( const MouseEvent & event )
{
	if(m_CameraType!=CT_Mouse)
		return;
	
	if( m_bFlyingToCentre || CCustomCamera::Instance().IsAroundTar() || CCustomCamera::Instance().IsRoamToTar())
		return;
		
	m_fDisToCentre -= event.dz()/50.0f;
	if( m_fDisToCentre<0.01f)
		m_fDisToCentre = 0.01f;

	if( InputDevices::isKeyDown( KeyEvent::KEY_RIGHTMOUSE ) )
	{
		float deltaPitch = event.dy() / 100.0f;
		//deltaPitch *= event.dz() ? -1.0f : 1.0f;

		m_fPitch_ += deltaPitch;
		if( m_fPitch_< -MATH_PI/2.0f)
			m_fPitch_ = -MATH_PI/2.0f + 0.01f;
		if( m_fPitch_>MATH_PI/2.0f)
			m_fPitch_ = MATH_PI/2.0f - 0.01f;
	//}
	//if( InputDevices::isKeyDown( KeyEvent::KEY_LEFTMOUSE ) )
	//{
		float deltaYaw = event.dx() / 100.0f;
		m_fYaw_ += deltaYaw;
	}
}

bool CCustomWorldCamera::handleAxisEvent(const AxisEvent & event)
{
	if (event.axis() == AxisEvent::AXIS_LX || event.axis() == AxisEvent::AXIS_LY)
	{
		m_fAxisKeyValue = event.value();
	}

	return true;
}

void CCustomWorldCamera::handleAxisKeyEvent(const KeyEvent & event)
{
	
	if( m_CameraType==CT_Mouse && event.isKeyUp())
	{

			if(event.key()== m_AxisYawLeft)
				m_bTurnLeft = false;
			else if( event.key()== m_AxisYawRight )
				m_bTurnRight = false;
			else if( event.key() == m_AxisPithDown )
				m_bTurnDown = false;
			else if( event.key()== m_AxisPithUp)
				m_bTurnUp = false;
	}
	
	if(event.key()==m_AxisYawLeft)
	{
		if( event.isKeyDown() )
			m_bAxisLeftYaw = true;
		else
			m_bAxisLeftYaw = false;
	}
	
	if( event.key()==m_AxisYawRight )
	{
		if( event.isKeyDown() )
			m_bAxisRightYaw = true;
		else
			m_bAxisRightYaw = false;
	}
	
	if( event.key()==m_AxisPithDown )
	{
		if( event.isKeyDown() )
			m_bAxisDownPitch = true;
		else
			m_bAxisDownPitch = false;
	}
	
	if( event.key()==m_AxisPithUp )
	{
		if( event.isKeyDown() )
			m_bAxisUpPitch = true;
		else
			m_bAxisUpPitch = false;
	}
	
	if( event.key()==m_AxisAddSpeed )
	{
		if( event.isKeyDown() )
			m_bAxisAddSpeed = true;
		else
			m_bAxisAddSpeed = false;
	}
	
	if( event.key()==m_AxisReduceSpeed )
	{
		if(event.isKeyDown())
			m_bAxisReduceSpeed = true;
		else
			m_bAxisReduceSpeed = false;
	}
	
	if(event.key()==KeyEvent::KEY_JOYALDOWN || event.key()==KeyEvent::KEY_JOYALUP )
	{
		if( event.isKeyDown() )
			m_bAxisMoveUD = true;
		else 
			m_bAxisMoveUD = false;
	}
	if(event.key()==KeyEvent::KEY_JOYALLEFT || event.key()==KeyEvent::KEY_JOYALRIGHT )
	{
		if( event.isKeyDown() )
			m_bAxisMoveLR = true;
		else 
			m_bAxisMoveLR = false;
	}
}

void CCustomWorldCamera::handleAxisRotate()
{
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();

	//if(InputDevices::isKeyDown(m_AxisYawLeft))	//左转
	if( m_bAxisLeftYaw )
	{
		if(m_CameraType==CT_KeyBoard)
		{
			float fYaw = cameradir.yaw() - m_fAxisYawSpeed;

			Vector3 newDir;
			newDir.setPitchYaw(cameradir.pitch(), fYaw);

			TeleportCamera( camerapos, newDir );
			
			cameradir = newDir;
		}
		else
		{
			m_bTurnLeft = true;
		}
	}
	//else if(InputDevices::isKeyDown(m_AxisYawRight))	//右转
	else if( m_bAxisRightYaw )
	{
		if(m_CameraType==CT_KeyBoard)
		{
			float fYaw = cameradir.yaw()  + m_fAxisYawSpeed;

			Vector3 newDir;
			newDir.setPitchYaw(cameradir.pitch(), fYaw);

			TeleportCamera( camerapos, newDir );
			
			cameradir = newDir;
		}
		else
		{
			m_bTurnRight = true;
		}
	}
	//else if(InputDevices::isKeyDown(m_AxisPithDown))	//下倾
	else if( m_bAxisDownPitch )
	{
		if(m_CameraType==CT_KeyBoard)
		{
			float fPitch = cameradir.pitch() - m_fAxisYawSpeed;

			Vector3 newDir;
			newDir.setPitchYaw(fPitch, cameradir.yaw());

			TeleportCamera( camerapos, newDir );
			cameradir = newDir;
		}
		else
		{
			m_bTurnDown = true;
		}
	}
	//else if(InputDevices::isKeyDown(m_AxisPithUp))		//上倾
	else if( m_bAxisUpPitch )
	{
		if(m_CameraType==CT_KeyBoard)
		{
			float fPitch = cameradir.pitch() + m_fAxisYawSpeed;

			Vector3 newDir;
			newDir.setPitchYaw(fPitch, cameradir.yaw());

			TeleportCamera( camerapos, newDir );
			cameradir = newDir;
		}
		else
		{
			m_bTurnUp = true;
		}
	}
	//else if( InputDevices::isKeyDown(m_AxisAddSpeed) )
	else if( m_bAxisAddSpeed )
	{
		m_fAxisMoveSpeed += 0.02f;
	}
	//else if( InputDevices::isKeyDown(m_AxisReduceSpeed) )
	else if( m_bAxisReduceSpeed )
	{
		if(m_fAxisMoveSpeed>=0.02f)
		{
			m_fAxisMoveSpeed -= 0.02f;
		}
	}
	
	if( !InputDevices::joystick().isUsingKeyboard() )
	{
		if( m_bAxisMoveUD )	//前后走
		{
			//cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
			Vector3 newpos = camerapos + cameradir * m_fAxisKeyValue * m_fAxisMoveSpeed;
			TeleportCamera( newpos, cameradir );
		}
	
		if( m_bAxisMoveLR )	//左右走
		{
			Vector3 right = Moo::rc().invView().applyToUnitAxisVector(0);
			Vector3 newpos = camerapos + right * m_fAxisKeyValue * m_fAxisMoveSpeed;
			TeleportCamera( newpos, cameradir );
		}
	}

}

void CCustomWorldCamera::tick( float dTime )
{
	//控制摄像机不陷到地底下
	//CameraNotUnderground();
	
	handleAxisRotate();
	
	if(m_CameraType!=CT_Mouse)
		return;
		
	//if( m_bFlyingToCentre )
	//{
	//	if(CFlyTravel::Instance().IsStopTravel())
	//	{
	//		m_bFlyingToCentre = false;
	//		//Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	//		//Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	//		//
	//		//m_fPitch_ = cameradir.pitch();
	//		//m_fYaw_ = cameradir.yaw();
	//		//
	//		//m_fDisToCentre = (camerapos-m_ViewCentre).length();
	//		SetCameraType( CT_Mouse );
	//	}
	//	
	//	return;
	//}
	
	if( CCustomCamera::Instance().IsAroundTar() || CCustomCamera::Instance().IsRoamToTar())
	{
		return;
	}
	
	
	if( m_bSpeedUp )
	{
		m_fTAMSpeed += 0.01f;
	}
	if( m_bSlowdown )
	{
		m_fTAMSpeed -= 0.01f;
		if( m_fTAMSpeed<0)
			m_fTAMSpeed = 0.01f;
	}
	if( m_bMoveForward )
	{
		if(m_fDisToCentre>0)
			m_fDisToCentre -= m_fTAMSpeed*50.0f;
		if(m_fDisToCentre<0)
			m_fDisToCentre = m_fTAMSpeed;
	}
	if( m_bMoveBack )
	{
		m_fDisToCentre += m_fTAMSpeed*50.0f;
	}
	
	if( m_bTurnLeft )
	{
		m_fYaw_ -= m_fTAMSpeed;
	}
	if( m_bTurnRight )
	{
		m_fYaw_ += m_fTAMSpeed;
	}
	if(m_bTurnDown)
	{
		m_fPitch_ -= m_fTAMSpeed;
		if( m_fPitch_<-MATH_PI/2.0f)
			m_fPitch_ = -MATH_PI/2.0f + 0.01f;
	}
	if( m_bTurnUp )
	{
		m_fPitch_ += m_fTAMSpeed;
		if( m_fPitch_> MATH_PI/2.0f)
			m_fPitch_ = MATH_PI/2.0f-0.01f;
	}
	
	Vector3 dir;
	dir.setPitchYaw(m_fPitch_, m_fYaw_ );

	if(m_bFollowing)
	{
		//Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
		Matrix mt = m_pFollowItem->chunk()->transform();
		mt.preMultiply( m_pFollowItem->edTransform() );
		//Vector3 pos = mt.applyToOrigin();
		m_ViewCentre = mt.applyToOrigin();
		//TeleportCamera( pos,cameradir);
		//return;
	}
	Vector3 newpos = m_ViewCentre - m_fDisToCentre * dir /*+ m_offset*/;

	CCustomCamera::Instance().TeleportCamera(newpos, dir);
}

void CCustomWorldCamera::FlyToCentre()
{
	
	if(!m_bHaveViewCentre || m_bFollowing)
		return;
	
	CCustomCamera::Instance().RoamToTar( m_ViewCentre, 1.0f);
	m_bFlyingToCentre = true;
	
	//Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	//Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	//
	//std::vector<Vector3> vFlyPoints;
	//std::vector<float> vPtX, vPtZ;
	//Vector3 midPos;
	//Vector3 tardir, middir;
	//float fHeight, fTarLen;
	//tardir = m_ViewCentre - camerapos ;
	//fTarLen = tardir.length();
	//tardir.normalise();
	//float yaw = (tardir.yaw()+cameradir.yaw()) / 2.0f;
	//middir.setPitchYaw( cameradir.pitch(), yaw );
	//middir.normalise();

	//midPos = camerapos + middir * fTarLen/2.0f;

	//vPtX.push_back( camerapos.x );
	//vPtX.push_back( midPos.x );
	//vPtX.push_back( m_ViewCentre.x );

	//vPtZ.push_back( camerapos.z );
	//vPtZ.push_back( midPos.z );
	//vPtZ.push_back( m_ViewCentre.z );

	//fHeight = m_ViewCentre.y - camerapos.y;

	//int k = 10;
	//float fPerHeight = fHeight / (float)k;
	//float t, x, z, y;
	//Vector3 pt;

	//for(int i=0; i<=k; i++)
	//{   
	//	t = (float)i/k;
	//	x = bezier(vPtX,t);      
	//	z = bezier(vPtZ,t);
	//	y = camerapos.y + fPerHeight*(float)i;
	//	pt = Vector3(x,y,z);
	//	if( (pt-m_ViewCentre).length()>1 )
	//		vFlyPoints.push_back( pt );
	//}

	//CFlyTravel::Instance().SetTravelParam(4.0f, 10.0f, vFlyPoints);
	//CFlyTravel::Instance().SetControlDir( true );
	//CFlyTravel::Instance().SetAbsoluteHeight( false );	
	//CFlyTravel::Instance().StartTravel();
	//
	//m_bFlyingToCentre = true;
	//
	//vPtX.clear();
	//vPtZ.clear();
	//vFlyPoints.clear();
}

void CCustomWorldCamera::StopFlyToCentre()
{
	m_bFlyingToCentre = false;
}

bool CCustomWorldCamera::IsFlyingToCentre()
{
	return m_bFlyingToCentre;
}

void CCustomWorldCamera::TeleportToTar( ChunkItemPtr &item )
{
	Vector3 dir = Moo::rc().invView().applyToUnitAxisVector(2);
	Matrix mat = item->chunk()->transform();
	mat.preMultiply(item->edTransform());

	BoundingBox box;
	item->edSelectedBox(box);
	box.transformBy(mat);	

	float fWidth = box.width();
	float fDepth = box.depth();
	float fHeight = box.height();

	Vector3 itemCentre = box.centre();

	float fDistance = fWidth > fDepth ? fWidth + 5 : fDepth + 5;

	TeleportToTar( itemCentre, fDistance );
}

void CCustomWorldCamera::TeleportToTar(Vector3 tarpos, float fDistance)
{
	if(m_bFollowing)
		return;
		
	if(m_CameraType==CT_Mouse)
	{
		m_ViewCentre = tarpos;
		m_fDisToCentre = fDistance;
	}
	else if(m_CameraType==CT_KeyBoard)
	{
		CCustomCamera::Instance().TeleportToTar( tarpos, fDistance );
	}
	
}

void CCustomWorldCamera::RoamToTar(Vector3 tarpos, float fDistance)
{
	if(m_bFollowing)
		return;
		
	switch(m_CameraType)
	{
	case CT_Mouse:
		m_ViewCentre = tarpos;
		m_fDisToCentre = fDistance;
		m_bFlyingToCentre = true;
		break;
	case CT_KeyBoard:
		break;
	default:
		break;
	}
	
	
	if(IsAroundTar())
		StopAroundTar();	
		
	CCustomCamera::Instance().RoamToTar( tarpos, fDistance );
}	

void CCustomWorldCamera::AroundTar(Vector3 tarpos, float fDistance)
{
	if(m_bFollowing)
		return;
		
	switch(m_CameraType)
	{
	case CT_Mouse:
		m_ViewCentre = tarpos;
		m_fDisToCentre = fDistance;
		
		break;
	case CT_KeyBoard:
		break;
	default:
		break;
	}
	
	if(IsRoamToTar())
		StopRoamToTar();
		
	CCustomCamera::Instance().AroundTar( tarpos, fDistance );
}

bool CCustomWorldCamera::IsAroundTar()
{
	return CCustomCamera::Instance().IsAroundTar();
}

bool CCustomWorldCamera::IsRoamToTar()
{
	return CCustomCamera::Instance().IsRoamToTar();
}

void CCustomWorldCamera::StopAroundTar()
{
	CCustomCamera::Instance().StopAroundTar();
	
	if(m_CameraType==CT_Mouse)
	{
		Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
		Vector3 camerapos = Moo::rc().invView().applyToOrigin();
		m_fDisToCentre = (camerapos-m_ViewCentre).length();
		m_fPitch_ = cameradir.pitch();
		m_fYaw_ = cameradir.yaw();
	}
}

void CCustomWorldCamera::StopRoamToTar()
{
	CCustomCamera::Instance().StopRoamToTar();
	if( m_CameraType==CT_Mouse )
	{
		Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
		Vector3 camerapos = Moo::rc().invView().applyToOrigin();
		m_fDisToCentre = (camerapos-m_ViewCentre).length();
		m_fPitch_ = cameradir.pitch();
		m_fYaw_ = cameradir.yaw();
	}
}

void CCustomWorldCamera::TeleportCamera( Matrix mat )
{
	Vector3 pos( mat.applyToOrigin() );
	Vector3 dir( mat.applyToUnitAxisVector(2) );
	TeleportCamera( pos, dir );
}

void CCustomWorldCamera::TeleportCamera( Vector3 pos, Vector3 dir )
{
	
	if(m_CameraType==CT_Mouse)
	{
		CustomCollision sc;
		Vector3 extent = pos + dir * Moo::rc().camera().farPlane();
		float fRet = ChunkManager::instance().cameraSpace()->collide( pos, extent, sc );
		if(fRet>0)
			m_ViewCentre = pos + dir * fRet ;
		else
			m_ViewCentre = pos + dir * 50.0f;

		m_fDisToCentre = (pos-m_ViewCentre).length();
		m_fPitch_ = dir.pitch();
		m_fYaw_ = dir.yaw(); 
	}
	else
	{
		CCustomCamera::Instance().TeleportCamera( pos, dir );
	}
	
}

void CCustomWorldCamera::PathTravel(float fSpeed, std::vector<Vector3> vPathNodes, bool bLoopTravel)
{

}

bool CCustomWorldCamera::IsPathTraveling()
{
	return false;
}

bool CCustomWorldCamera::IsPausedTraveling()
{
	return false;
}

void CCustomWorldCamera::PausedPathTravel()
{
	if(m_CameraType==CT_Mouse)
		SetCameraType( CT_Mouse );
	m_bFlyingToCentre = false;
}

void CCustomWorldCamera::ContinuePathTravel()
{
	m_bFlyingToCentre = true;
}

void CCustomWorldCamera::StopPathTravel()
{
	if(m_CameraType==CT_Mouse)
		SetCameraType( CT_Mouse );

	m_bFlyingToCentre = false;
}

void CCustomWorldCamera::FollowObject(ChunkItemPtr pItem)
{
	TeleportToTar( pItem );
	
	m_pFollowItem = pItem;
	m_bFollowing = true;
	SetCameraType( CT_Mouse );
}

void CCustomWorldCamera::StopFollow()
{
	m_bFollowing = false;
	m_pFollowItem = NULL;
}

bool CCustomWorldCamera::IsFollowing()
{
	return m_bFollowing;
}

void CCustomWorldCamera::ReleaseFollowObj()
{
	StopFollow();
	//m_pFollowItem = NULL;
}

ChunkItemPtr CCustomWorldCamera::GetFollowObject()
{
	return m_pFollowItem;
}

void CCustomWorldCamera::CameraNotUnderground()
{
	ClosestTerrainObstacle mc; 
	Vector3 CameraPos = Moo::rc().invView().applyToOrigin();
	Vector3 StartPos = CameraPos + Vector3(0,500,0);
	Vector3 EndPos = CameraPos;
	EndPos.y = -500.0f;
	
	float fRet = ChunkManager::instance().cameraSpace()->collide(StartPos, EndPos, mc );
	if( fRet>0 )
	{
		Vector3 TerrainPt = StartPos - Vector3(0,fRet,0);
		if( CameraPos.y<TerrainPt.y+0.5f)
		{
			Vector3 CameraDir = Moo::rc().invView().applyToUnitAxisVector(2);
			CameraPos.y = TerrainPt.y + 0.6f;
			TeleportCamera(CameraPos, CameraDir);
		}
	}

}

void CCustomWorldCamera::SetAxisKey(KeyEvent::Key YawLeft, KeyEvent::Key YawRight, KeyEvent::Key PithDown, 
									KeyEvent::Key PithUp, KeyEvent::Key AddSpeed, KeyEvent::Key ReduceSpeed)
{
	m_AxisYawLeft = YawLeft;
	m_AxisYawRight = YawRight;
	m_AxisPithDown = PithDown;
	m_AxisPithUp = PithUp;
	m_AxisAddSpeed = AddSpeed;
	m_AxisReduceSpeed = ReduceSpeed;
}

void CCustomWorldCamera::GetAxisKey(KeyEvent::Key &YawLeft, KeyEvent::Key &YawRight, KeyEvent::Key &PithDown, 
									KeyEvent::Key &PithUp, KeyEvent::Key &AddSpeed, KeyEvent::Key &ReduceSpeed)
{
	YawLeft = m_AxisYawLeft;
	YawRight = m_AxisYawRight;
	PithDown = m_AxisPithDown;
	PithUp = m_AxisPithUp;
	AddSpeed = m_AxisAddSpeed;
	ReduceSpeed = m_AxisReduceSpeed;
}

void CCustomWorldCamera::SetAxisSpeed(float fYawSpeed, float fPitchSpeed, float fMoveSpeed)
{
	m_fAxisYawSpeed = fYawSpeed;
	m_fAxisPitchSpeed = fPitchSpeed;
	m_fAxisMoveSpeed = fMoveSpeed;
}

void CCustomWorldCamera::GetAxisSpeed(float &fYawSpeed, float &fPitchSpeed, float &fMoveSpeed)
{
	fYawSpeed = m_fAxisYawSpeed;
	fPitchSpeed = m_fAxisPitchSpeed;
	fMoveSpeed = m_fAxisMoveSpeed;
}