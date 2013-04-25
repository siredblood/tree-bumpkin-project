
//
//	�������
//
//
//

#ifndef _CHINESEFONT_H_
#define _CHINESEFONT_H_

#include <d3dx9core.h>

class CChineseFont
{
	public:
		CChineseFont(void);
		~CChineseFont(void);
		
		enum SHOWFORMAT
		{
			eLeftFlush,
			eCenterFlush
		};
		//static CChineseFont & Instance();
		void InitFont(int FontWidth, int FontHeight, std::string strFontName);	//��ʼ������
		void DrawChineseText( const std::string& strText, int x, int y, unsigned long ulColor, 
								SHOWFORMAT ulFlush=eCenterFlush, bool bDrawBottom = false);	//��������

		//�ع��������֣�Ĭ����ʾβ��
		void DrawChineseText( std::string tmp, std::string strText, int x, int y, unsigned long ulColor, 
			SHOWFORMAT ulFlush=eCenterFlush );

		void DrawChineseText(Vector3 MarkPos, std::string strText, int x, int y, unsigned long ulColor, 
			SHOWFORMAT ulFlush, bool bDrawBottom);
		void DrawChineseText(std::string strText, CRect rc, unsigned long ulColor, UINT uiFormat);	//��������

		void DrawChineseText(std::string strText, int x, int y, unsigned long ulColor, float fDistance=-1,
			SHOWFORMAT ulFlush=eCenterFlush, bool bDrawBottom = false);	//��������

		void DrawChineseTextNew(std::string strText, int x, int y, unsigned long ulColor, float fDistance=-1,
			SHOWFORMAT ulFlush=eCenterFlush, bool bDrawBottom = false);	//��������(����)
		
	private:
		//static CChineseFont instance;
		ID3DXFont* m_pD3DFont;
		D3DXFONT_DESCA lf;
		
		int m_iFontWidth;
		int m_iFontHeight;
		
		Moo::BaseTexturePtr handDrawnMap_;
};

#endif