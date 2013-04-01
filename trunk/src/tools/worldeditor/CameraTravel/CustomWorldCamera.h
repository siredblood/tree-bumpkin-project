//
//	�Զ����������������
//	���������������˫�����е�Ŀ�꣬�����̲������������˶���

#pragma once
#include "input/input.hpp"
#include "chunk/chunk_item.hpp"
#include "worldeditor/BaseFramework/ITask.hpp"

class CCustomWorldCamera : public ITask
{
public:
	CCustomWorldCamera(void);
	~CCustomWorldCamera(void);
	
	//�����������ʽ
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
	
	bool handleAxisEvent( const AxisEvent & event);		//���ӿ��Ƹ���Ӧ
	
	void tick( float dTime );
	
	void SetCameraViewCentre(Vector3 pos);	//����
	
	void FlyToCentre();		//�ɵ�Ŀ���
	void StopFlyToCentre();	//ֹͣ����Ŀ��
	
	bool IsFlyingToCentre();	//�Ƿ�������Ŀ��
	
	void TeleportToTar( ChunkItemPtr &item );	//�ƶ���Ŀ��
	void TeleportToTar(Vector3 tarpos, float fDistance);	//�ƶ���Ŀ��
	void RoamToTar(Vector3 tarpos, float fDistance);		//���ε�Ŀ��
	void AroundTar(Vector3 tarpos, float fDistance);		//����Ŀ��
	bool IsRoamToTar();		//�Ƿ���������
	bool IsAroundTar();		//�Ƿ����廷��
	void StopRoamToTar();	//ֹͣ����
	void StopAroundTar();	//ֹͣ����
	
	void TeleportCamera( Vector3 pos, Vector3 dir );		//�ƶ������
	void TeleportCamera( Matrix mat );
	
	void PathTravel(float fSpeed, std::vector<Vector3> vPathNodes, bool bLoopTravel = false );	//·�����
	bool IsPathTraveling();		//�Ƿ��������·��
	bool IsPausedTraveling();	//�Ƿ���ͣ�����
	void PausedPathTravel();	//��ͣ���
	void ContinuePathTravel();	//�������
	void StopPathTravel();		//ֹͣ���
	
	void FollowObject(ChunkItemPtr pItem);	// ���ٶ���
	void StopFollow();						//ֹͣ����
	bool IsFollowing();						//�Ƿ����
	ChunkItemPtr GetFollowObject();			//���ظ��ٵĶ���
	
	void ReleaseFollowObj();				//�ͷŸ��ٶ���
	
	void SetAxisKey(KeyEvent::Key YawLeft, KeyEvent::Key YawRight, KeyEvent::Key PithDown, 
					KeyEvent::Key PithUp, KeyEvent::Key AddSpeed, KeyEvent::Key ReduceSpeed);	//������ת��ť
	
	void SetAxisSpeed(float fYawSpeed, float fPitchSpeed, float fMoveSpeed);	//�����ٶ�
	
	void GetAxisKey(KeyEvent::Key &YawLeft, KeyEvent::Key &YawRight, KeyEvent::Key &PithDown, 
					KeyEvent::Key &PithUp, KeyEvent::Key &AddSpeed, KeyEvent::Key &ReduceSpeed);
					
	void GetAxisSpeed(float &fYawSpeed, float &fPitchSpeed, float &fMoveSpeed);

private:
	void CameraNotUnderground();	//������������ݵ��ص�
	void handleAxisKeyEvent(const KeyEvent & event);	//��������˵İ�����Ӧ
	void handleAxisRotate();
	
private:
	static CCustomWorldCamera instance;
	
	Camera_Type m_CameraType;	//Ĭ��Ϊ���̲���
	
	Vector3 m_ViewCentre;	//�����Χ�Ƶ����ĵ�
	
	bool m_bHaveViewCentre;	//�Ƿ������ĵ�
	
	bool m_bFlyingToCentre;	//�Ƿ��ڷ�������
	
	float m_fDisToCentre;	//�����ĵ�ľ���
	
	float m_fYaw_;
	float m_fPitch_;
	
	float m_fTAMSpeed;		//��ת���ƶ��ٶ�
	
	bool m_bMoveForward ;	//ǰ�ƶ�
	bool m_bMoveBack;		//���ƶ�
	bool m_bTurnLeft;		//����
	bool m_bTurnRight;		//����
	bool m_bTurnDown;		//����
	bool m_bTurnUp;			//����
	bool m_bSpeedUp;		//����
	bool m_bSlowdown;		//����
	
	ChunkItemPtr m_pFollowItem;	//���ٵĶ���
	bool m_bFollowing;	//�Ƿ��ڸ���
	
	//Ĭ�ϵ�ת��ť
	KeyEvent::Key m_AxisYawLeft;
	KeyEvent::Key m_AxisYawRight;
	KeyEvent::Key m_AxisPithDown;
	KeyEvent::Key m_AxisPithUp;
	KeyEvent::Key m_AxisAddSpeed;
	KeyEvent::Key m_AxisReduceSpeed;
	
	float m_fAxisYawSpeed;
	float m_fAxisPitchSpeed;
	float m_fAxisMoveSpeed;
	
	float m_fAxisKeyValue;	//����
	
	bool m_bAxisMoveUD;
	bool m_bAxisMoveLR;
	
	bool m_bAxisLeftYaw;
	bool m_bAxisRightYaw;
	bool m_bAxisDownPitch;
	bool m_bAxisUpPitch;
	bool m_bAxisAddSpeed;
	bool m_bAxisReduceSpeed;
};
