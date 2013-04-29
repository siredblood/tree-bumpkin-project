#ifndef Fly_h__
#define Fly_h__

#include "worldeditor/BaseFramework/ITask.hpp"
#include "worldeditor/UDOController/UDOHeader.hpp"
#include "worldeditor/mark/ChineseFont.h"


class Fly : public Singleton< Fly >, public ITask
{
public:
	Fly();
	
	~Fly();
	
	inline void catMullRomSplines( Vector3& out, const Vector3& p0, const Vector3& p1,
									  const Vector3& p2, const Vector3& p3,
									  float t, float t2, float t3 );
									  
	void clampAngles( const Vector3& start, Vector3& end );
	
	void tick( float dTime );
	
	/**
	 *	���ƽڵ�����
	 */
	void draw();
	
	void handleKeyEvent( const KeyEvent & event );
	
	// �����Ƿ�ʼ����
	void setFly( bool fly );
	bool isFlying();

	// �����Ƿ���ͣ����
	void setPause( bool pause );
	bool isPause();
	
	//void setTmpRot( const std::vector< ChunkItemPtr >& ptr );

	// ���÷�������
	void setFlyData( const std::vector< FlyData > &vFlyData, float fSpeed, bool bDiffer );

private:
	void initFly();

	std::vector< FlyData >		m_vFlyData;
	bool		m_bFly;			// ���б��
	bool		m_bPause;		// ��ͣ���
	bool		m_bDiffer;		// �Ƿ�ͬ�ٶ�
	float		m_fSpeed;		// ·����ͬ���ٶ�
	float		dt_;			// ����Ƶ��
	uint		destId;			// ·���ڵ�ID
	float		t;				// 
	
	CChineseFont m_ChineseFont; // ���Ļ���
	
	
};

#endif // Fly_h__