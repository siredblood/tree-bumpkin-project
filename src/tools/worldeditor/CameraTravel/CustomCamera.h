//
//	自定义的摄像机操作
//	处理移动到目标、漫游到目标、环绕目标运动
//

#ifndef __CUSTOMCAMERA_H__
#define __CUSTOMCAMERA_H__

#include "worldeditor/BaseFramework/ITask.hpp"

enum CustomState
{
	eNONE,
	eROAM,	//漫游
	eAROUND		//环绕
};

class CCustomCamera : public ITask
{
	public:
		CCustomCamera(void);
		~CCustomCamera(void);
		
		virtual void init();
		virtual void fini();
		virtual void tick( float dTime );
		virtual void draw();
		void handleKeyEvent( const KeyEvent & event );	//按键响应事件
		void handleMouseEvent( const MouseEvent & event );	//鼠标响应
		
		static CCustomCamera & Instance();
		
		//void SetTarget(Vector3 tarpos, float fDistance);	//设置目标
		
		void TeleportToTar(Vector3 tarpos, float fDistance);	//移动到目标
		void TeleportCamera(Vector3 pos, Vector3 dir);			//移动摄像机到指定位置和方向
		void RoamToTar(Vector3 tarpos, float fDistance);		//漫游到目标
		void AroundTar(Vector3 tarpos, float fDistance);		//环绕目标
		bool IsRoamToTar();		//是否正在漫游
		bool IsAroundTar();		//是否整体环绕
		void StopRoamToTar();	//停止漫游
		void StopAroundTar();	//停止环绕
		
		Vector3 GetCameraPos();		//获取摄像机坐标
		
		
	private:
		void RoamCamera();		//漫游
		void AroundCamera();	//环绕
		
	private:
		static CCustomCamera instance;
		Vector3 m_tarpos;	//目标点
		float m_fDistance;	//距离
		unsigned long m_ulState;	//操作类型
		Vector3 m_offset;
		
		float m_fPerYaw;	//漫游到目的时每帧转动的Yaw值
		float m_fPerPitch;	//漫游到目的时每帧转动的Pitch值
		float m_fPerDis;	//漫游到目的时每帧移动的距离
		Vector3 m_RoamDir;	//移动方向
		std::vector<Vector3> m_vRoamPoints;	//漫游时经过的中间点
		
		float m_fPitch;		//环绕目标时的倾斜值
		
		float m_fAroundSpeed;	//转速
		Vector3 m_lastdir;		//之前的方向
		bool m_bSpeedup;	//加速
		bool m_bSpeeddown;	//减速
		bool m_bMoveUp;		//上移
		bool m_bMoveDown;	//下移
		bool m_bMoveForward;	//前移
		bool m_bMoveBack;		//后移
};
	
#endif