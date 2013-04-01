//
//	自定义的世界浏览摄像机
//	处理鼠标操作浏览（双击飞行到目标，鼠标键盘操作环绕物体运动）

#pragma once
#include "input/input.hpp"
#include "chunk/chunk_item.hpp"
#include "worldeditor/BaseFramework/ITask.hpp"

class CCustomWorldCamera : public ITask
{
public:
	CCustomWorldCamera(void);
	~CCustomWorldCamera(void);
	
	//摄像机操作方式
	enum Camera_Type
	{
		CT_KeyBoard,
		CT_Mouse
	};
	
	static CCustomWorldCamera &Instance();
	
	void SetCameraType( Camera_Type cameraType );
	
	CCustomWorldCamera::Camera_Type GetCameraType();
	
	void handleKeyEvent( const KeyEvent & event );
	
	void handleMouseEvent( const MouseEvent & event );
	
	bool handleAxisEvent( const AxisEvent & event);		//增加控制杆响应
	
	void tick( float dTime );
	
	void SetCameraViewCentre(Vector3 pos);	//设置
	
	void FlyToCentre();		//飞到目标点
	void StopFlyToCentre();	//停止飞往目标
	
	bool IsFlyingToCentre();	//是否正飞往目标
	
	void TeleportToTar( ChunkItemPtr &item );	//移动到目标
	void TeleportToTar(Vector3 tarpos, float fDistance);	//移动到目标
	void RoamToTar(Vector3 tarpos, float fDistance);		//漫游到目标
	void AroundTar(Vector3 tarpos, float fDistance);		//环绕目标
	bool IsRoamToTar();		//是否正在漫游
	bool IsAroundTar();		//是否整体环绕
	void StopRoamToTar();	//停止漫游
	void StopAroundTar();	//停止环绕
	
	void TeleportCamera( Vector3 pos, Vector3 dir );		//移动摄像机
	void TeleportCamera( Matrix mat );
	
	void PathTravel(float fSpeed, std::vector<Vector3> vPathNodes, bool bLoopTravel = false );	//路径浏览
	bool IsPathTraveling();		//是否正在浏览路径
	bool IsPausedTraveling();	//是否暂停了浏览
	void PausedPathTravel();	//暂停浏览
	void ContinuePathTravel();	//继续浏览
	void StopPathTravel();		//停止浏览
	
	void FollowObject(ChunkItemPtr pItem);	// 跟踪对象
	void StopFollow();						//停止跟踪
	bool IsFollowing();						//是否跟踪
	ChunkItemPtr GetFollowObject();			//返回跟踪的对象
	
	void ReleaseFollowObj();				//释放跟踪对象
	
	void SetAxisKey(KeyEvent::Key YawLeft, KeyEvent::Key YawRight, KeyEvent::Key PithDown, 
					KeyEvent::Key PithUp, KeyEvent::Key AddSpeed, KeyEvent::Key ReduceSpeed);	//设置旋转按钮
	
	void SetAxisSpeed(float fYawSpeed, float fPitchSpeed, float fMoveSpeed);	//设置速度
	
	void GetAxisKey(KeyEvent::Key &YawLeft, KeyEvent::Key &YawRight, KeyEvent::Key &PithDown, 
					KeyEvent::Key &PithUp, KeyEvent::Key &AddSpeed, KeyEvent::Key &ReduceSpeed);
					
	void GetAxisSpeed(float &fYawSpeed, float &fPitchSpeed, float &fMoveSpeed);

private:
	void CameraNotUnderground();	//控制摄像机不陷到地底
	void handleAxisKeyEvent(const KeyEvent & event);	//处理操作杆的按键响应
	void handleAxisRotate();
	
private:
	static CCustomWorldCamera instance;
	
	Camera_Type m_CameraType;	//默认为键盘操作
	
	Vector3 m_ViewCentre;	//摄像机围绕的中心点
	
	bool m_bHaveViewCentre;	//是否有中心点
	
	bool m_bFlyingToCentre;	//是否在飞往中心
	
	float m_fDisToCentre;	//离中心点的距离
	
	float m_fYaw_;
	float m_fPitch_;
	
	float m_fTAMSpeed;		//旋转和移动速度
	
	bool m_bMoveForward ;	//前移动
	bool m_bMoveBack;		//后移动
	bool m_bTurnLeft;		//左旋
	bool m_bTurnRight;		//右旋
	bool m_bTurnDown;		//下旋
	bool m_bTurnUp;			//上旋
	bool m_bSpeedUp;		//加速
	bool m_bSlowdown;		//减速
	
	ChunkItemPtr m_pFollowItem;	//跟踪的对象
	bool m_bFollowing;	//是否在跟踪
	
	//默认的转向按钮
	KeyEvent::Key m_AxisYawLeft;
	KeyEvent::Key m_AxisYawRight;
	KeyEvent::Key m_AxisPithDown;
	KeyEvent::Key m_AxisPithUp;
	KeyEvent::Key m_AxisAddSpeed;
	KeyEvent::Key m_AxisReduceSpeed;
	
	float m_fAxisYawSpeed;
	float m_fAxisPitchSpeed;
	float m_fAxisMoveSpeed;
	
	float m_fAxisKeyValue;	//力度
	
	bool m_bAxisMoveUD;
	bool m_bAxisMoveLR;
	
	bool m_bAxisLeftYaw;
	bool m_bAxisRightYaw;
	bool m_bAxisDownPitch;
	bool m_bAxisUpPitch;
	bool m_bAxisAddSpeed;
	bool m_bAxisReduceSpeed;
};
