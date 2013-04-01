//
//	�Զ�������������
//	�����ƶ���Ŀ�ꡢ���ε�Ŀ�ꡢ����Ŀ���˶�
//

#ifndef __CUSTOMCAMERA_H__
#define __CUSTOMCAMERA_H__

#include "worldeditor/BaseFramework/ITask.hpp"

enum CustomState
{
	eNONE,
	eROAM,	//����
	eAROUND		//����
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
		void handleKeyEvent( const KeyEvent & event );	//������Ӧ�¼�
		void handleMouseEvent( const MouseEvent & event );	//�����Ӧ
		
		static CCustomCamera & Instance();
		
		//void SetTarget(Vector3 tarpos, float fDistance);	//����Ŀ��
		
		void TeleportToTar(Vector3 tarpos, float fDistance);	//�ƶ���Ŀ��
		void TeleportCamera(Vector3 pos, Vector3 dir);			//�ƶ��������ָ��λ�úͷ���
		void RoamToTar(Vector3 tarpos, float fDistance);		//���ε�Ŀ��
		void AroundTar(Vector3 tarpos, float fDistance);		//����Ŀ��
		bool IsRoamToTar();		//�Ƿ���������
		bool IsAroundTar();		//�Ƿ����廷��
		void StopRoamToTar();	//ֹͣ����
		void StopAroundTar();	//ֹͣ����
		
		Vector3 GetCameraPos();		//��ȡ���������
		
		
	private:
		void RoamCamera();		//����
		void AroundCamera();	//����
		
	private:
		static CCustomCamera instance;
		Vector3 m_tarpos;	//Ŀ���
		float m_fDistance;	//����
		unsigned long m_ulState;	//��������
		Vector3 m_offset;
		
		float m_fPerYaw;	//���ε�Ŀ��ʱÿ֡ת����Yawֵ
		float m_fPerPitch;	//���ε�Ŀ��ʱÿ֡ת����Pitchֵ
		float m_fPerDis;	//���ε�Ŀ��ʱÿ֡�ƶ��ľ���
		Vector3 m_RoamDir;	//�ƶ�����
		std::vector<Vector3> m_vRoamPoints;	//����ʱ�������м��
		
		float m_fPitch;		//����Ŀ��ʱ����бֵ
		
		float m_fAroundSpeed;	//ת��
		Vector3 m_lastdir;		//֮ǰ�ķ���
		bool m_bSpeedup;	//����
		bool m_bSpeeddown;	//����
		bool m_bMoveUp;		//����
		bool m_bMoveDown;	//����
		bool m_bMoveForward;	//ǰ��
		bool m_bMoveBack;		//����
};
	
#endif