#ifndef WORLD_EDITOR_VIEW_HPP
#define WORLD_EDITOR_VIEW_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include <atltime.h>
#include "imm.h"
#pragma comment(lib,"Imm32.lib")

class WorldEditorView : public CView
{
protected: 
	DECLARE_DYNCREATE(WorldEditorView)

	WorldEditorView();

public:
	virtual ~WorldEditorView();

	WorldEditorDoc* GetDocument() const;

	virtual void OnDraw(CDC* pDC); 
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	afx_msg void OnPaint();	
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	afx_msg BOOL OnSetCursor( CWnd*, UINT, UINT );
	DECLARE_MESSAGE_MAP()

private:
	CRect		lastRect_;
	CTime  m_LastClickTime;
	DWORD  m_lastTickTime;
	CPoint	m_MousePt;
	
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	};


#endif // WORLD_EDITOR_VIEW_HPP
