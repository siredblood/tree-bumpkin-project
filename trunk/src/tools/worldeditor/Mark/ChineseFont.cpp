#include "pch.hpp"
//#include "app.hpp"
#include "ChineseFont.h"
#include "romp/geometrics.hpp"

CChineseFont::CChineseFont(void)
{
}

CChineseFont::~CChineseFont(void)
{
}

void CChineseFont::InitFont(int FontWidth, int FontHeight, std::string strFontName)
{
	ZeroMemory(&lf, sizeof(D3DXFONT_DESCA));
	lf.Height = FontHeight;
	lf.Width = FontWidth;
	lf.Weight = 500;
	lf.Italic = false;
	lf.OutputPrecision = 0;
	lf.PitchAndFamily = 0;
	lf.Quality = 0;
	lf.CharSet = DEFAULT_CHARSET ;
	strcpy( lf.FaceName , strFontName.c_str() );
	
	m_iFontWidth = FontWidth;
	m_iFontHeight = FontHeight;
}

void CChineseFont::DrawChineseText( const std::string& strText, int x, int y, unsigned long ulColor, 
								   SHOWFORMAT ulFlush, bool bDrawBottom)
{

	D3DXCreateFontIndirect(Moo::rc().device(), &lf, &m_pD3DFont); 
	RECT rect;
	int iTextSize = strText.size();
	switch (ulFlush)
	{
	case eCenterFlush:
		rect.left = x - iTextSize * m_iFontWidth/2;
		rect.right = x + iTextSize * m_iFontWidth/2;
		rect.top = y - m_iFontHeight/2;
		rect.bottom = y + m_iFontHeight/2;
		break;
	case eLeftFlush:
		rect.left = x;
		rect.right = x + iTextSize * m_iFontWidth;
		rect.top = y;
		rect.bottom = y + m_iFontHeight;
		break;
	}
	if(bDrawBottom)
	{
		Vector2 LeftTop, RightBottom;
		LeftTop.x = (float)rect.left-20;
		LeftTop.y = (float)rect.top-10;
		RightBottom.x = (float)rect.right + 20;
		RightBottom.y = (float)rect.bottom + 40;
		Geometrics::drawRect(LeftTop, RightBottom, 0xff0000ff);
		Vector2 TrianCen, TrianP1, TrianP2;
		TrianCen.x = (LeftTop.x + RightBottom.x )/2.0f;
		TrianCen.y = RightBottom.y + 15.0f;
		float fWidth = (RightBottom.x - LeftTop.x) / 8.0f;
		TrianP1.x = TrianCen.x - fWidth;
		TrianP1.y = RightBottom.y;
		TrianP2.x = TrianCen.x + fWidth;
		TrianP2.y = RightBottom.y;
		Geometrics::drawTriangle( TrianP1, TrianP2, TrianCen, 0xB40000ff);

		//if(handDrawnMap_==NULL)
		//{
		//	CString strTexName;
		//	strTexName.Format("%s\\biaozhu.dds",g_strExeFullPath);
		//	handDrawnMap_ = Moo::TextureManager::instance()->get(
		//		strTexName.GetBuffer(0),
		//		false,						// allowAnimation
		//		false						// mustExist
		//		);
		//}
		//if(handDrawnMap_!=NULL)
		//	Geometrics::drawTexRect( LeftTop, RightBottom, handDrawnMap_, true );
	}

	m_pD3DFont->DrawText(
		NULL,
		strText.c_str(), 
		-1,					// size of string or -1 indicates null terminating string
		&rect,				// rectangle text is to be formatted to in windows coords
		DT_TOP | DT_LEFT,	// draw in the top left corner of the viewport
		ulColor				// black text
		);
	m_pD3DFont->Release();		 
}

void CChineseFont::DrawChineseText(Vector3 MarkPos, std::string strText, int x, int y, unsigned long ulColor, 
									SHOWFORMAT ulFlush, bool bDrawBottom)
{
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	float fLen = (camerapos - MarkPos ).length();
	////如果距离超过300米就不显示
	//Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	//float fLen = (camerapos - pos ).length();
	//if (fLen>200)
	//	continue;


	D3DXCreateFontIndirect(Moo::rc().device(), &lf, &m_pD3DFont); 
	RECT rect;
	int iTextSize = strText.size();
	switch (ulFlush)
	{
		case eCenterFlush:
			rect.left = x - iTextSize * m_iFontWidth/2;
			rect.right = x + iTextSize * m_iFontWidth/2;
			rect.top = y - m_iFontHeight/2;
			rect.bottom = y + m_iFontHeight/2;
			break;
		case eLeftFlush:
			rect.left = x;
			rect.right = x + iTextSize * m_iFontWidth;
			rect.top = y;
			rect.bottom = y + m_iFontHeight;
			break;
	}
	if(bDrawBottom)
	{
		Vector2 LeftTop, RightBottom;
		LeftTop.x = (float)rect.left-20;
		LeftTop.y = (float)rect.top-10;
		RightBottom.x = (float)rect.right+20;
		RightBottom.y = (float)rect.bottom+10;
		Geometrics::drawRect(LeftTop, RightBottom, 0x80BCEAEA);
		Vector2 TrianCen, TrianP1, TrianP2;
		TrianCen.x = (LeftTop.x + RightBottom.x )/2.0f;
		TrianCen.y = RightBottom.y + 15.0f;
		float fWidth = (RightBottom.x - LeftTop.x) / 8.0f;
		TrianP1.x = TrianCen.x - fWidth;
		TrianP1.y = RightBottom.y;
		TrianP2.x = TrianCen.x + fWidth;
		TrianP2.y = RightBottom.y;
		Geometrics::drawTriangle( TrianP1, TrianP2, TrianCen, 0x80BCEAEA);
	}
	
	
	m_pD3DFont->DrawText(
		NULL,
		strText.c_str(), 
		-1,					// size of string or -1 indicates null terminating string
		&rect,				// rectangle text is to be formatted to in windows coords
		DT_TOP | DT_LEFT,	// draw in the top left corner of the viewport
		ulColor				// black text
	);
	m_pD3DFont->Release();		 
}

void CChineseFont::DrawChineseText(std::string strText, CRect rc, unsigned long ulColor, UINT uiFormat)
{
	D3DXCreateFontIndirect(Moo::rc().device(), &lf, &m_pD3DFont); 
	m_pD3DFont->DrawText(
		NULL,
		strText.c_str(), 
		-1,					// size of string or -1 indicates null terminating string
		&rc,				// rectangle text is to be formatted to in windows coords
		uiFormat,		// draw in the top left corner of the viewport
		ulColor				// black text
		);
	m_pD3DFont->Release();		 
}

void CChineseFont::DrawChineseText( std::string tmp, std::string strText, int x, int y, unsigned long ulColor, SHOWFORMAT ulFlush/*=eCenterFlush*/ )
{
	tmp = "";
	D3DXCreateFontIndirect(Moo::rc().device(), &lf, &m_pD3DFont); 
	RECT rect;
	int iTextSize = strText.size();
	switch (ulFlush)
	{
	case eCenterFlush:
		rect.left = x - iTextSize * m_iFontWidth/2;
		rect.right = x + iTextSize * m_iFontWidth/2;
		rect.top = y - m_iFontHeight/2;
		rect.bottom = y + m_iFontHeight/2;
		break;
	case eLeftFlush:
		rect.left = x;
		rect.right = x + iTextSize * m_iFontWidth;
		rect.top = y;
		rect.bottom = y + m_iFontHeight;
		break;
	}

	Vector2 LeftTop, RightBottom;
	//LeftTop.x = (float)rect.left-20;
	//LeftTop.y = (float)rect.top-10;
	//RightBottom.x = (float)rect.right + 20;
	//RightBottom.y = (float)rect.bottom + 40;

	LeftTop.x = (float)rect.left - 10;
	LeftTop.y = (float)rect.top - 10;

	RightBottom.x = (float)rect.right + 10;
	RightBottom.y = (float)rect.bottom + 40;

	//Geometrics::drawRect(LeftTop, RightBottom, 0xff0000ff);
	//Vector2 TrianCen, TrianP1, TrianP2;
	//TrianCen.x = (LeftTop.x + RightBottom.x )/2.0f;
	//TrianCen.y = RightBottom.y + 15.0f;
	//float fWidth = (RightBottom.x - LeftTop.x) / 8.0f;
	//TrianP1.x = TrianCen.x - fWidth;
	//TrianP1.y = RightBottom.y;
	//TrianP2.x = TrianCen.x + fWidth;
	//TrianP2.y = RightBottom.y;
	//Geometrics::drawTriangle( TrianP1, TrianP2, TrianCe n, 0xB40000ff);

	if(handDrawnMap_==NULL)
	{
		CString strTexName;
		strTexName.Format("%s\\biaozhu.dds",g_strExeFullPath);
		handDrawnMap_ = Moo::TextureManager::instance()->get(
			strTexName.GetBuffer(0),
			false,						// allowAnimation
			false						// mustExist
			);
	}
	if(handDrawnMap_!=NULL)
	Geometrics::drawTexRect( LeftTop, RightBottom, handDrawnMap_, true );

	m_pD3DFont->DrawText(
		 NULL,
		 strText.c_str(), 
		 -1,				// size of string or -1 indicates null terminating string
		 &rect,				// rectangle text is to be formatted to in windows coords
		 DT_TOP | DT_LEFT,	// draw in the top left corner of the viewport
		 ulColor			// black text
	);
	m_pD3DFont->Release();	
}

void CChineseFont::DrawChineseText( std::string strText, int x, int y, unsigned long ulColor, float fDistance/*=-1*/, SHOWFORMAT ulFlush/*=eCenterFlush*/, bool bDrawBottom /*= false*/ )
{
	int iFontWidth, iFontHeight;
	int iIncreaseWidth, iIncreaseBottom;
	bool bDrawText = true;
	
	if(fDistance>0)
	{
		iFontHeight = m_iFontHeight - (int)fDistance/100;
		iFontWidth = m_iFontWidth - (int)fDistance/100;
		
		if(iFontHeight<=0)	//当字体大小为0时就不再绘制文字
		{
			iFontHeight = 0;
			bDrawText = false;
		}
		if(iFontWidth<=0)
		{
			iFontWidth = 0;
			bDrawText = false;
		}
		
		lf.Height = iFontHeight;
		lf.Width = iFontWidth;
		
		iIncreaseWidth = 20 - (int)fDistance/50;
		iIncreaseBottom = 40 - (int)fDistance/50;
		if(iIncreaseWidth<0)
			iIncreaseWidth = 0;
		if(iIncreaseBottom<0)
			iIncreaseBottom = 0;
	}
	else
	{
		lf.Height = m_iFontHeight;
		lf.Width = m_iFontWidth;
		iFontHeight = lf.Height;
		iFontWidth = lf.Width;
	}

	
	D3DXCreateFontIndirect(Moo::rc().device(), &lf, &m_pD3DFont); 
	RECT rect;
	int iTextSize = strText.size();
	switch (ulFlush)
	{
		case eCenterFlush:
			rect.left = x - iTextSize * iFontWidth/2;
			rect.right = x + iTextSize * iFontWidth/2 + 20;
			rect.top = y - iFontHeight/2;
			rect.bottom = y + iFontHeight/2;
			break;
		case eLeftFlush:
			rect.left = x;
			rect.right = x + iTextSize * iFontWidth;
			rect.top = y;
			rect.bottom = y + iFontHeight;
			break;
	}
	if(bDrawBottom && bDrawText)
	{
		Vector2 LeftTop, RightBottom;
		LeftTop.x = (float)rect.left - iIncreaseWidth - 10;
		LeftTop.y = (float)rect.top - iIncreaseWidth/4;
		RightBottom.x = (float)rect.right + iIncreaseWidth - 10;
		RightBottom.y = (float)rect.bottom + iIncreaseBottom;
		//Geometrics::drawRect(LeftTop, RightBottom, 0x80ff0000);/*0x80BCEAEA*/
		//Vector2 TrianCen, TrianP1, TrianP2;
		//TrianCen.x = (LeftTop.x + RightBottom.x )/2.0f;
		//TrianCen.y = RightBottom.y + 15.0f;
		//float fWidth = (RightBottom.x - LeftTop.x) / 8.0f;
		//TrianP1.x = TrianCen.x - fWidth;
		//TrianP1.y = RightBottom.y;
		//TrianP2.x = TrianCen.x + fWidth;
		//TrianP2.y = RightBottom.y;
		//Geometrics::drawTriangle( TrianP1, TrianP2, TrianCen, 0x80ff0000);/*0x80BCEAEA*/
		
		if(handDrawnMap_==NULL)
		{
			CString strTexName;
			strTexName.Format("%s\\biaozhu.dds",g_strExeFullPath);
			handDrawnMap_ = Moo::TextureManager::instance()->get(
				strTexName.GetBuffer(0),
				false,						// allowAnimation
				false						// mustExist
			);
		}
		if(handDrawnMap_!=NULL)
			Geometrics::drawTexRect( LeftTop, RightBottom, handDrawnMap_, true );
	}
	
	if( bDrawText )
		m_pD3DFont->DrawText(
			NULL,
			strText.c_str(), 
			-1,					// size of string or -1 indicates null terminating string
			&rect,				// rectangle text is to be formatted to in windows coords
			DT_TOP | DT_LEFT,	// draw in the top left corner of the viewport
			ulColor				// black text
		);
	m_pD3DFont->Release();
}

void CChineseFont::DrawChineseTextNew(std::string strText, int x, int y, unsigned long ulColor, float fDistance, SHOWFORMAT ulFlush, bool bDrawBottom)
{
	int iFontWidth, iFontHeight;
	int iIncreaseWidth, iIncreaseBottom;
	bool bDrawText = true;

	if(fDistance>0)
	{
		iFontHeight = m_iFontHeight - (int)fDistance/20;
		iFontWidth = m_iFontWidth - (int)fDistance/20;

		if(iFontHeight<=0)	//当字体大小为0时就不再绘制文字
		{
			iFontHeight = 0;
			bDrawText = false;
		}
		if(iFontWidth<=0)
		{
			iFontWidth = 0;
			bDrawText = false;
		}

		lf.Height = iFontHeight;
		lf.Width = iFontWidth;

		iIncreaseWidth = 20 - (int)fDistance/15;
		iIncreaseBottom = 10 - (int)fDistance/15;
		if(iIncreaseWidth<0)
			iIncreaseWidth = 0;
		if(iIncreaseBottom<0)
			iIncreaseBottom = 0;
	}
	else
	{
		lf.Height = m_iFontHeight;
		lf.Width = m_iFontWidth;
		iFontHeight = lf.Height;
		iFontWidth = lf.Width;
	}


	D3DXCreateFontIndirect(Moo::rc().device(), &lf, &m_pD3DFont); 
	RECT rect;
	int iTextSize = strText.size();
	switch (ulFlush)
	{
	case eCenterFlush:
		rect.left = x - iTextSize * iFontWidth/2;
		rect.right = x + iTextSize * iFontWidth/2 + 20;
		rect.top = y - iFontHeight/2;
		rect.bottom = y + iFontHeight/2;
		break;
	case eLeftFlush:
		rect.left = x;
		rect.right = x + iTextSize * iFontWidth;
		rect.top = y;
		rect.bottom = y + iFontHeight;
		break;
	}
	if(bDrawBottom && bDrawText)
	{
		Vector2 LeftTop, RightBottom;
		LeftTop.x = (float)rect.left - iIncreaseWidth - 10;
		LeftTop.y = (float)rect.top - iIncreaseWidth/4;
		RightBottom.x = (float)rect.right + iIncreaseWidth - 10;
		RightBottom.y = (float)rect.bottom + iIncreaseBottom;
		Geometrics::drawRect(LeftTop, RightBottom, 0x80C8C8C8);/*0x80BCEAEA*/
		Vector2 TrianCen, TrianP1, TrianP2;
		TrianCen.x = (LeftTop.x + RightBottom.x )/2.0f;
		TrianCen.y = RightBottom.y + 15.0f;
		float fWidth = (RightBottom.x - LeftTop.x) / 8.0f;
		TrianP1.x = TrianCen.x - fWidth;
		TrianP1.y = RightBottom.y;
		TrianP2.x = TrianCen.x + fWidth;
		TrianP2.y = RightBottom.y;
		Geometrics::drawTriangle( TrianP1, TrianP2, TrianCen, 0x80C8C8C8);/*0x80BCEAEA*/

		//if(handDrawnMap_==NULL)
		//{
		//	CString strTexName;
		//	strTexName.Format("%s\\biaozhu.dds",g_strExeFullPath);
		//	handDrawnMap_ = Moo::TextureManager::instance()->get(
		//		strTexName.GetBuffer(0),
		//		false,						// allowAnimation
		//		false						// mustExist
		//	);
		//}
		//if(handDrawnMap_!=NULL)
		//	Geometrics::drawTexRect( LeftTop, RightBottom, handDrawnMap_ );
	}

	if( bDrawText )
		m_pD3DFont->DrawText(
		NULL,
		strText.c_str(), 
		-1,					// size of string or -1 indicates null terminating string
		&rect,				// rectangle text is to be formatted to in windows coords
		DT_TOP | DT_LEFT,	// draw in the top left corner of the viewport
		ulColor				// black text
		);
	m_pD3DFont->Release();		 
}