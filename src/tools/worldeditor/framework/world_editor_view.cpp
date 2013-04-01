#include "pch.hpp"
#include "worldeditor/framework/world_editor_view.hpp"
#include "worldeditor/framework/world_editor_app.hpp"
#include "worldeditor/framework/world_editor_doc.hpp"
#include "worldeditor/framework/mainframe.hpp"
#include "worldeditor/world/world_manager.hpp"
#include "appmgr/app.hpp"
#include "appmgr/module_manager.hpp"
#include "common/cooperative_moo.hpp"
#include "input/input.hpp"
#include "CameraTravel/CustomWorldCamera.h"
#include "mainframe.hpp"

IMPLEMENT_DYNCREATE(WorldEditorView, CView)


BEGIN_MESSAGE_MAP(WorldEditorView, CView)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


WorldEditorView::WorldEditorView() :
	lastRect_( 0, 0, 0, 0 )
{
}


WorldEditorView::~WorldEditorView()
{
}


BOOL WorldEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Change style to no background to avoid flicker in the 3D view:
	cs.lpszClass = AfxRegisterWndClass(
		CS_OWNDC | CS_HREDRAW | CS_VREDRAW, ::LoadCursor(NULL, IDC_ARROW), 0 );
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}


void WorldEditorView::OnDraw(CDC* /*pDC*/)
{
}


WorldEditorDoc* WorldEditorView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(WorldEditorDoc)));
	return (WorldEditorDoc*)m_pDocument;
}


void WorldEditorView::OnPaint()
{
	CView::OnPaint();

	CRect rect;
	GetClientRect( &rect );

	if 
	( 
		WorldEditorApp::instance().mfApp() 
		&&
		ModuleManager::instance().currentModule() 
	)
	{
		if ( CooperativeMoo::beginOnPaint() )
		{		
			// Change mode when a paint message is received and the size of the
			// window is different than last stored size:
			if 
			( 
				lastRect_ != rect 
				&&
				Moo::rc().device() 
				&& 
				Moo::rc().windowed() 
				&&
				rect.Width() && rect.Height() 
				&&
				!((MainFrame*)WorldEditorApp::instance().mainWnd())->resizing() 
			)
			{
				CWaitCursor wait;
				Moo::rc().changeMode(Moo::rc().modeIndex(), Moo::rc().windowed(), true);
				lastRect_ = rect;
			}
			WorldEditorApp::instance().mfApp()->updateFrame( false );
			CooperativeMoo::endOnPaint();
		}
	}
	else
	{
		CWindowDC dc( this );
		dc.FillSolidRect( rect, ::GetSysColor( COLOR_BTNFACE ) );
	}
}


void WorldEditorView::OnActivateView
(
	BOOL		bActivate, 
	CView		*pActivateView, 
	CView		*pDeactiveView
)
{
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	
	//输入法控制，关
	HIMC hImc = ImmGetContext(m_hWnd);
	ImmSetOpenStatus(hImc,false);
	ImmReleaseContext(m_hWnd,hImc);
	hImc=NULL;
}


BOOL WorldEditorView::OnSetCursor(CWnd *wnd, UINT, UINT)
{
	::SetCursor( WorldManager::instance().cursor() );
	return TRUE;
}

void WorldEditorView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar=='K')
	{
		bool bTraveling = CCustomWorldCamera::Instance().IsPathTraveling();
		if(!bTraveling)
			return;
		bool bPausedTravel = CCustomWorldCamera::Instance().IsPausedTraveling();
		if(bPausedTravel)
			CCustomWorldCamera::Instance().ContinuePathTravel();
		else
			CCustomWorldCamera::Instance().PausedPathTravel();
	}
	if(nChar=='L')
	{
		bool bTraveling = CCustomWorldCamera::Instance().IsPathTraveling();
		if(!bTraveling)
			return;
		CCustomWorldCamera::Instance().StopPathTravel();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void WorldEditorView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

	//输入法控制，开
	HIMC hImc = ImmGetContext(m_hWnd);
	ImmSetOpenStatus(hImc,true);
	ImmReleaseContext(m_hWnd,hImc);
	hImc=NULL;
}

void WorldEditorView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	//输入法控制，关
	HIMC hImc = ImmGetContext(m_hWnd);
	ImmSetOpenStatus(hImc,false);
	ImmReleaseContext(m_hWnd,hImc);
	hImc=NULL;
}
