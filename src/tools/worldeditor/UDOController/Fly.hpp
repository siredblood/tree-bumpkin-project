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
	 *	绘制节点文字
	 */
	void draw();
	
	void handleKeyEvent( const KeyEvent & event );
	
	// 设置是否开始飞行
	void setFly( bool fly );
	bool isFlying();

	// 设置是否暂停飞行
	void setPause( bool pause );
	bool isPause();
	
	//void setTmpRot( const std::vector< ChunkItemPtr >& ptr );

	// 设置飞行数据
	void setFlyData( const std::vector< FlyData > &vFlyData, float fSpeed, bool bDiffer );

private:
	void initFly();

	std::vector< FlyData >		m_vFlyData;
	bool		m_bFly;			// 飞行标记
	bool		m_bPause;		// 暂停标记
	bool		m_bDiffer;		// 是否不同速度
	float		m_fSpeed;		// 路径相同的速度
	float		dt_;			// 飞行频率
	uint		destId;			// 路径节点ID
	float		t;				// 
	
	CChineseFont m_ChineseFont; // 中文绘制
	
	
};

#endif // Fly_h__