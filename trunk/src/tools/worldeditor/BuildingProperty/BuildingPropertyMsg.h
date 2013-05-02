/************************************************************************/
/* ����������Ϣ��ʾ                                                     */
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

	void setDraw(bool bDraw);	//�����Ƿ����
	bool isDraw();				//��ȡ�Ƿ����

private:
	// stringתΪwstring
	std::wstring string2wstring(const std::string& s);
	// wstringתΪstring
	std::string wstring2string(const std::wstring& ws);
	// ����sublen���ȷָ��ַ��������ĺ������ַ����һ����ܻ���ֶ�������
	void conver(const std::string &s, std::vector<std::string> &vMsg, int sublen);

private:
	static CBuildingPropertyMsg s_instance;

	bool m_bDraw;
	bool m_bBuilding;
	CChineseFont m_ChineseFont;
	std::string m_strGuid;
	//LinkedStringMap m_mapProperty;
	Moo::BaseTexturePtr m_texBackground;// ������ͼ
	std::string m_strTitle;	// ����
	std::vector<std::string> m_vMessage; // �����Ϣ������˵����Ϣ
	std::vector<std::string> m_vMemo;	// ���˵����Ϣ
};

#endif