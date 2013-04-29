#include "pch.hpp"
#include "Fly.hpp"
#include "worldeditor/misc/world_editor_camera.hpp"


BW_SINGLETON_STORAGE( Fly )
Fly s_t_;


//初始化测试坐标及方向
Fly::Fly() 
: m_bFly( false )
, m_bPause( false )
, m_bDiffer( false )
, m_fSpeed( 0.0f )
, dt_( 0.12f )
, destId( 1 )
, t( 1.f )
{
	TaskManager::instance().add( this, "Fly", NULL );
	
	m_ChineseFont.InitFont( 15, 30, "宋体" );
}

Fly::~Fly()
{}

//样条插值算法或直接调用D3D的D3DXVec3CatmullRom()函数
void Fly::catMullRomSplines( Vector3& out, 
								const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, 
								float t, float t2, float t3 )
{
	  out = 0.5 *((2 * p1) +
			(-p0 + p2) * t +
			(2*p0 - 5*p1 + 4*p2 - p3) * t2 +
			(-p0 + 3*p1- 3*p2 + p3) * t3 );
}

void Fly::clampAngles( const Vector3& start, Vector3& end )
{
	Vector3 rot = end - start;
	if (rot[0] <= -MATH_PI) end[0] += MATH_2PI; else if (rot[0] > MATH_PI) end[0] -= MATH_2PI;
	if (rot[1] <= -MATH_PI) end[1] += MATH_2PI; else if (rot[1] > MATH_PI) end[1] -= MATH_2PI;
	if (rot[2] <= -MATH_PI) end[2] += MATH_2PI; else if (rot[2] > MATH_PI) end[2] -= MATH_2PI;
}

void Fly::tick( float dTime )
{
	if ( !m_bFly )
		return;
		
	if( m_bPause )
		return;

	if( m_vFlyData.empty() )
		return;
		
	static Matrix transform;
	static Vector3 p0, p1, p2, p3;
	static Vector3 r0, r1, r2, r3;

	t += dTime * dt_;

	if ( t >= 1.f )
	{
		destId++;

		if ( destId >= m_vFlyData.size() - 1 )
		{
			destId = 1;
			m_bFly = false;
			m_bPause = false;
			return;
		}

		p0 = m_vFlyData[ destId - 2 ].pos;
		p1 = m_vFlyData[ destId - 1 ].pos;
		p2 = m_vFlyData[ destId + 0 ].pos;
		p3 = m_vFlyData[ destId + 1 ].pos;

		r0 = m_vFlyData[ destId - 2 ].rot;
		r1 = m_vFlyData[ destId - 1 ].rot;
		r2 = m_vFlyData[ destId + 0 ].rot;
		r3 = m_vFlyData[ destId + 1 ].rot;
		
		clampAngles( r0, r1 );
		clampAngles( r1, r2 );
		clampAngles( r2, r3 );

		// 是否统一速度飞行 dt_ = 0.1 = 100(m/s)

		//dt_ = fSpeed / ((p0 - p1).length() +
		//	2.f * (p1 - p2).length() +
		//	(p2 - p3).length());
		
		if ( m_bDiffer )
		{
			float fSpeed = m_vFlyData[ destId - 1 ].speed;
			dt_ = fSpeed * 0.1f;
		}
		
		t -= 1.f;
	}

	float t2 = t * t;
	float t3 = t * t2;

	Vector3 pos =	0.5 *((2 * p1) +
		(-p0 + p2) * t +
		(2*p0 - 5*p1 + 4*p2 - p3) * t2 +
		(-p0 + 3*p1- 3*p2 + p3) * t3 );
		
	//直接调用D3DX函数
	//D3DXVECTOR3 pos_;
	//D3DXVec3CatmullRom( &pos_, &D3DXVECTOR3( p0.x, p0.y, p0.z ),
	//	&D3DXVECTOR3( p1.x, p1.y, p1.z ),
	//	&D3DXVECTOR3( p2.x, p2.y, p2.z ),
	//	&D3DXVECTOR3( p3.x, p3.y, p3.z ), t );
	//	
	//Vector3 pos = Vector3( pos_.x, pos_.y, pos_.z );	

	Vector3 rot =	0.5 *((2 * r1) +
		(-r0 + r2) * t +
		(2*r0 - 5*r1 + 4*r2 - r3) * t2 +
		(-r0 + 3*r1- 3*r2 + r3) * t3 );

	////建立方向矩阵
	Matrix m = Matrix::identity;
	m.preRotateY( rot[0] );
	m.preRotateX( rot[1] );
	m.preRotateZ( rot[2] );

	//获取方向
	Vector3 dir = m.applyToUnitAxisVector( Z_AXIS );
	Vector3 up = m.applyToUnitAxisVector( Y_AXIS );

	transform.lookAt( pos, dir, up );
	
	WorldEditorCamera::instance().currentCamera().view( transform );
}

void Fly::setFly( bool fly ) 
{ 	
	m_bFly = fly; 
}

bool Fly::isFlying() 
{
	return m_bFly; 
}

void Fly::setPause( bool pause ) 
{ 
	m_bPause = pause; 
}

bool Fly::isPause() 
{ 
	return m_bPause; 
}

void Fly::setFlyData( const std::vector< FlyData > &vFlyData, float fSpeed, bool bDiffer )
{ 
	initFly();
	
	m_vFlyData = vFlyData; 
	
	if ( fSpeed > 8.f )
		m_fSpeed = 8.f;
	else if ( fSpeed < 0.1f )
		m_fSpeed = 0.1f;
	else
		m_fSpeed = fSpeed; 
		
	dt_ = m_fSpeed * 0.1f;
	
	m_bDiffer = bDiffer; 
}

void Fly::handleKeyEvent( const KeyEvent & event )
{
	if ( !m_bFly || m_bPause )
		return;
		
	if( event.isKeyDown() )
	{
		if( event.key() == KeyEvent::KEY_EQUALS || event.key() == KeyEvent::KEY_ADD )
		{
			if ( dt_ < 0.8f )
				dt_ += 0.01f;
		}
		else 
		if ( event.key() == KeyEvent::KEY_MINUS || event.key() == KeyEvent::KEY_NUMPADMINUS )
		{
			if ( dt_ > 0.01f )
				dt_ -= 0.01f;
		}
	}
}

void Fly::initFly()
{
	m_vFlyData.clear();
	
	m_bFly = true;
	m_bPause = false;
	
	destId = 1;
	t = 1.f;
}

/**
 *	简单绘制节点文字
 */
void Fly::draw()
{
	if ( !m_bFly )
		return;
		
	int	iWidth  = (int)Moo::rc().screenWidth();
	int	iHeigth = (int)Moo::rc().screenHeight();
		
	//绘制
	m_ChineseFont.DrawChineseText( m_vFlyData[ destId - 1 ].description, 50, iHeigth >> 2, 
		0xff0000ff, CChineseFont::eLeftFlush );
}