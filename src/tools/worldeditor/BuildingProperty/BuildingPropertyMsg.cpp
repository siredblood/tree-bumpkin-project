#include "pch.hpp"

#include "BuildingPropertyMsg.h"
#include "worldeditor/GeneralClass/CustomCollision.h"
#include "romp/geometrics.hpp"


CBuildingPropertyMsg CBuildingPropertyMsg::s_instance;

CBuildingPropertyMsg::CBuildingPropertyMsg()
	:m_bDraw(false), m_bBuilding(false)
{
	TaskManager::instance().add( this, "CBuildingPropertyMsg", NULL );
	m_ChineseFont.InitFont(12, 24, "隶书");
}

CBuildingPropertyMsg::~CBuildingPropertyMsg()
{
}

CBuildingPropertyMsg &CBuildingPropertyMsg::Instance()
{
	return s_instance;
}

void CBuildingPropertyMsg::tick( float dTime )
{

}

void CBuildingPropertyMsg::draw()
{
	if(!m_bDraw||!m_bBuilding) return;

	float fWinHeight = Moo::rc().screenHeight();
	float fWinWidth = Moo::rc().screenWidth();
	POINT pt = WorldManager::instance().currentCursorPosition();
	Vector2 vBottom, vTop((float)pt.x+16, (float)pt.y);

	if(vTop.y-BG_HEIGHT/2<0){// 顶端超出
		vTop.y = 0;
		vBottom.y = vTop.y + BG_HEIGHT;
	}else if(vTop.y+BG_HEIGHT/2>fWinHeight){// 底端超出
		vBottom.y = fWinHeight;
		vTop.y = vBottom.y - BG_HEIGHT;
	}else{// 正常范围
		vTop.y -= BG_HEIGHT / 2;
		vBottom.y = vTop.y + BG_HEIGHT;
	}
	if(vTop.x+BG_WITHD>fWinWidth){
		vTop.x -= 16;
		vBottom.x = vTop.x;
		vTop.x -= BG_WITHD;
	}else{
		vBottom.x = vTop.x + BG_WITHD;
	}

	if(m_texBackground==NULL){
		CString strTexName;
		strTexName.Format("%s\\建筑属性背景.jpg",g_strExeFullPath);
		m_texBackground = Moo::TextureManager::instance()->get(
			strTexName.GetBuffer(0),
			false,						// allowAnimation
			false						// mustExist
		);
	}
	if(m_texBackground!=NULL)
		Geometrics::drawTexRect( vTop, vBottom, m_texBackground, true);

	int xpx=(int)vTop.x + 16;
	int ypx=(int)vTop.y + 30;
	m_ChineseFont.DrawChineseText(m_strTitle, xpx, ypx, 
		0xb4ff0000, CChineseFont::eLeftFlush, false);
	ypx += 36;
	for(size_t i=0; i<m_vMessage.size(); ++i){
		m_ChineseFont.DrawChineseText(m_vMessage[i], xpx, ypx, 
			0xb4ff0000, CChineseFont::eLeftFlush, false);
		ypx += 30;
	}
	for(size_t i=0; i<m_vMemo.size(); ++i){
		m_ChineseFont.DrawChineseText(m_vMemo[i], xpx, ypx, 
			0xb4ff0000, CChineseFont::eLeftFlush, false);
		ypx += 28;
	}
}

void CBuildingPropertyMsg::setDraw(bool bDraw)
{
	m_bDraw = bDraw;
}

bool CBuildingPropertyMsg::isDraw()
{
	return m_bDraw;
}

void CBuildingPropertyMsg::handleMouseEvent( const MouseEvent & event )
{
	if(!m_bDraw) return;

	POINT pt = WorldManager::instance().currentCursorPosition();
	Vector3 worldRay = WorldManager::instance().getWorldRay(pt);

	Vector3 start =  Moo::rc().invView().applyToOrigin();
	Vector3 extent = start + worldRay * Moo::rc().camera().farPlane();

	CustomCollision sc;
	float fRet = ChunkManager::instance().cameraSpace()->collide( start, extent, sc );

	ChunkItemPtr pItem = sc.getCollideObstacle();
	if(pItem==NULL){
		m_bBuilding = false;
		return;
	}
	std::string strGuid = pItem->edGUID();
	// 同一个建筑
	if(m_strGuid==strGuid)
		return;

	m_vMessage.clear();

	m_strGuid = strGuid;
	// 是否记录建筑
	LinkedStringMap mapProperty;
	if(CDBBuildingProperty::Query(strGuid, mapProperty)){
		int i=0;
		for(LinkedStringMap::reverse_iterator itr=mapProperty.rbegin(); 
			itr!=mapProperty.rend(); ++itr, ++i)
		{
			if(i<3) continue;// 从第三个开始显示
			if(i==3){
				m_strTitle = (*itr).second;
				continue;
			}
			if((*itr).first=="说明"){
				std::string msg = (*itr).first + "：" + (*itr).second;
				conver(msg, m_vMemo, 12);
				continue;
			}else{
				m_vMessage.push_back((*itr).first + "：" + (*itr).second);
			}

		}
		m_bBuilding = true;
	}else{
		m_bBuilding = false;
	}
}

void CBuildingPropertyMsg::conver(const std::string &s, std::vector<std::string> &vMsg, int sublen)
{
	vMsg.clear();
	std::wstring wstr = string2wstring(s);
	size_t len = wstr.size();
	size_t i=0, j=0;
	while(i<len){
		j = i + sublen;
		if(j>len){
			vMsg.push_back(wstring2string(wstr.substr(i, len-i)));
		}else{
			vMsg.push_back(wstring2string(wstr.substr(i, sublen)));
		}
		i = j;
	}
}

std::wstring CBuildingPropertyMsg::string2wstring(const std::string& s){
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str(); 
	size_t _Dsize = s.size() + 1; 
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest; 
	delete []_Dest; 
	setlocale(LC_ALL, "C"); 
	return result;
}

std::string CBuildingPropertyMsg::wstring2string(const std::wstring& ws){  
	std::string curLocale = setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, "chs"); 
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	std::string result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());  return result;
}