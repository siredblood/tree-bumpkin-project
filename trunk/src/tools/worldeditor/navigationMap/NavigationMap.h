//
//	������ά����ϵ
//
//

#include "mark/ChineseFont.h"
#include "worldeditor/BaseFramework/ITask.hpp"

#pragma once

class CNavigationMap : public ITask
{
public:
	CNavigationMap(void);
	~CNavigationMap(void);
	
	enum POSITION
	{
		eLeftTop,
		eLeftDown,
		eRightTop,
		eRightDown,
		eCenter
	};
	
	static CNavigationMap &Instance();
	
	void draw();

	void handleKeyEvent( const KeyEvent & event );
	
	void SetDraw(bool bDrawDir);	//�����Ƿ����
	bool IsDraw();					//��ȡ�Ƿ����
	
	void SetDrowPosition(POSITION position);	//���û���λ��
	POSITION GetDrawPosition();					//��ȡ����λ��
	
private:
	static CNavigationMap instance;
	
	CChineseFont m_ChineseFont;
	
	bool m_bDrawDir;
	
	POSITION m_Position;	//���Ƶ�λ�ã�Ĭ�������½�

	Moo::BaseTexturePtr handDrawnMap_;

	Moo::BaseTexturePtr m_pLogoMap;

	float m_fNavWidth;	//����ͼ���
	float m_fMapWidth;	//��ͼ����x
	float m_fMapDepth;	//��ͼ���z
	
	Vector2 m_LeftTop;
	Vector2 m_RightDown;
	Vector2 m_center;
};
