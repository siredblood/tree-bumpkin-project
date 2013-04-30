//
//	绘制三维坐标系
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
	
	void SetDraw(bool bDrawDir);	//设置是否绘制
	bool IsDraw();					//获取是否绘制
	
	void SetDrowPosition(POSITION position);	//设置绘制位置
	POSITION GetDrawPosition();					//获取绘制位置
	
private:
	static CNavigationMap instance;
	
	CChineseFont m_ChineseFont;
	
	bool m_bDrawDir;
	
	POSITION m_Position;	//绘制的位置，默认在右下角

	Moo::BaseTexturePtr handDrawnMap_;

	Moo::BaseTexturePtr m_pLogoMap;

	float m_fNavWidth;	//导航图宽度
	float m_fMapWidth;	//地图长度x
	float m_fMapDepth;	//地图深度z
	
	Vector2 m_LeftTop;
	Vector2 m_RightDown;
	Vector2 m_center;
};
