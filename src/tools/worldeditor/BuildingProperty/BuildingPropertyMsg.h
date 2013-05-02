/************************************************************************/
/* 建筑属性信息显示                                                     */
/************************************************************************/
#ifndef _BUILDING_PROPERTY_MSG_H_
#define _BUILDING_PROPERTY_MSG_H_

#include "mark/ChineseFont.h"
#include "worldeditor/BaseFramework/ITask.hpp"
#include "DBBuildingProperty.h"

class CBuildingPropertyMsg : public ITask
{
private:
	CBuildingPropertyMsg();

public:
	static CBuildingPropertyMsg &Instance();
	~CBuildingPropertyMsg();

public:
	const static int BG_WITHD = 350;
	const static int BG_HEIGHT = 350;

	void tick( float dTime );
	void draw();

	void handleMouseEvent( const MouseEvent & event );

	void setDraw(bool bDraw);	//设置是否绘制
	bool isDraw();				//获取是否绘制

private:
	// string转为wstring
	std::wstring string2wstring(const std::string& s);
	// wstring转为string
	std::string wstring2string(const std::wstring& ws);
	// 按照sublen长度分割字符串，中文和其他字符混合一起可能会出现对齐问题
	void conver(const std::string &s, std::vector<std::string> &vMsg, int sublen);

private:
	static CBuildingPropertyMsg s_instance;

	bool m_bDraw;
	bool m_bBuilding;
	CChineseFont m_ChineseFont;
	std::string m_strGuid;
	//LinkedStringMap m_mapProperty;
	Moo::BaseTexturePtr m_texBackground;// 背景贴图
	std::string m_strTitle;	// 标题
	std::vector<std::string> m_vMessage; // 输出信息，不含说明信息
	std::vector<std::string> m_vMemo;	// 输出说明信息
};

#endif