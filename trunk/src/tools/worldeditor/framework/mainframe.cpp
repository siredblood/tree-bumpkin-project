#include "pch.hpp"
#include "worldeditor/framework/mainframe.hpp"
#include "worldeditor/framework/world_editor_app.hpp"
#include "worldeditor/world/world_manager.hpp"
#include "worldeditor/scripting/we_python_adapter.hpp"
#include "worldeditor/gui/pages/page_properties.hpp"
#include "worldeditor/gui/pages/panel_manager.hpp"
#include "worldeditor/gui/dialogs/splash_dialog.hpp"
#include "common/file_dialog.hpp"
#include "pyscript/script.hpp"
#include "appmgr/options.hpp"
#include "controls/show_cursor_helper.hpp"
#include "guimanager/gui_manager.hpp"
#include "common/user_messages.hpp"
#include "common/property_list.hpp"
#include "cstdmf/debug.hpp"

//////////////////////////////////////////////////////////////////////////

//engine
#include "world_editor_view.hpp"
#include "resmgr/zip_file_system.hpp"
#include "worldeditor/misc/selection_filter.hpp"
#include "appmgr/options.hpp"
#include "romp/enviro_minder.hpp"
#include "romp/time_of_day.hpp"
#include "romp/fog_controller.hpp"

//数据库
#include "BLogicLib/BllHelper.h"

//公共类
#include "worldeditor/GeneralClass/common_public.hpp"
#include "worldeditor/GeneralClass/CustomCollision.h"
#include "worldeditor/GeneralClass/Common.h"

//摄像头等操作
#include "CameraTravel/CustomCamera.h"
#include "CameraTravel/CustomWorldCamera.h"

//模型操作
#include "worldeditor/GeneralClass/HideAndShowObject.h"

// 标注
#include "worldeditor/mark/DlgMarkInput.h"
#include "worldeditor/mark/DlgMarkManage.h"
#include "worldeditor/mark/MarkManage.h"
#include "worldeditor/mark/DlgMarkLoad.h"
#include "worldeditor/ApartmentDiagram/DlgApartmentDiagram.h"
// 户型图
#include "worldeditor/ApartmentDiagram/ApartmentDiagramMgr.h"
//建筑替换方案
#include "BuildingScheme/AddBuildingSchemeDlg.h"
#include "BuildingScheme/buildingSchemeManager.h"
#include "BuildingScheme/BuildingSchemeManagerDlg.h"
//新路径浏览
#include "worldeditor/UDOController/Dialog/DlgUDOManager.h"
#include "worldeditor/UDOController/Fly.hpp"

DECLARE_DEBUG_COMPONENT2( "WorldEditor2", 0 )

//自定义ID
#define ID_ITEM_GO 10001
#define ID_POPUP_CLOSE (-1)

static const int c_menuPaneWidth = 307;

// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, /*CFrameWnd*/CXTPFrameWnd)

BEGIN_MESSAGE_MAP(MainFrame, /*CFrameWnd*/CXTPFrameWnd)
	ON_WM_CREATE()

	// Global help commands
	ON_COMMAND(ID_HELP_FINDER, /*CFrameWnd*/CXTPFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_WM_SIZE()
	ON_MESSAGE( WM_ENTERSIZEMOVE, OnEnterSizeMove)
	ON_MESSAGE( WM_EXITSIZEMOVE, OnExitSizeMove)
	ON_WM_CLOSE()
	ON_COMMAND_RANGE(GUI_COMMAND_START, GUI_COMMAND_END, OnGUIManagerCommand)
	ON_WM_EXITMENULOOP()
	ON_NOTIFY_RANGE( TBN_HOTITEMCHANGE, 0, 0xffffffff, OnToolbarHotItemChange  )
	ON_WM_SYSCOLORCHANGE()

	ON_COMMAND(ID_EXITSYSTEM, &MainFrame::OnExitSystem)
	ON_WM_GETMINMAXINFO()

	ON_MESSAGE(UM_FULLSCREEN, &MainFrame::OnFullScreen)

	ON_COMMAND(ID_BUTTON_LABELADD, &MainFrame::OnAddmark)
	ON_COMMAND(ID_BUTTON_LABELHIDE, &MainFrame::OnShoworhidemark)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_LABELHIDE, &MainFrame::OnUpdateShoworhidemark)
	ON_COMMAND(ID_BUTTON_LABELSET, &MainFrame::OnMarkmanage)
	ON_COMMAND(ID_BUTTON_LABELGET, &MainFrame::OnReloadmark)

	ON_COMMAND(ID_BUTTON_DIAGRAMVIEW, &MainFrame::OnViewDiagram)
	//方案替换
	ON_COMMAND(ID_BUTTON_ADDBUILDINGSCHEME, &MainFrame::OnAddBuildingScheme)
	ON_COMMAND(ID_BUTTON_DELETEBUILDINGSCHEME, &MainFrame::OnDeleteBuildingScheme)
	ON_COMMAND(ID_BUTTON_BUILDINGSCHEMEMANAGER, &MainFrame::OnBuildingSchemeManager)
	ON_COMMAND(ID_BUTTON_EXECUTEBUILDINGSCHEME, &MainFrame::OnExecuteBuildingScheme)
	//路径浏览
	ON_COMMAND(ID_BUTTON_PATHSET, &MainFrame::OnCtPathtravel)
	ON_COMMAND(ID_BUTTON_PAUSENAV, &MainFrame::OnPausedPathTravel)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PAUSENAV, &MainFrame::OnUpdatePausedPathTravel)
	ON_COMMAND(ID_BUTTON_STOP, &MainFrame::OnStopPathTravel)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_STOP, &MainFrame::OnUpdateStopPathTravel)

	
	END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	//ID_INDICATOR_MEMORYLOAD,
	//ID_INDICATOR_FRAMERATE,
};


// MainFrame construction/destruction

MainFrame::MainFrame()
: pScriptObject_(NULL)
, resizing_( false )
, triangles_( "" )
, initialised_( false )
, GUI::ActionMaker<MainFrame>( "doSaveSelectionAsPrefab", &MainFrame::saveSelectionAsPrefab )
, GUI::ActionMaker<MainFrame, 1>( "doShowToolbar", &MainFrame::showToolbar )
, GUI::ActionMaker<MainFrame, 2>( "doHideToolbar", &MainFrame::hideToolbar )
, GUI::UpdaterMaker<MainFrame>( "updateToolbar", &MainFrame::updateToolbar )
, GUI::ActionMaker<MainFrame, 3>( "doShowStatusBar", &MainFrame::showStatusBar )
, GUI::ActionMaker<MainFrame, 4>( "doHideStatusBar", &MainFrame::hideStatusBar )
, GUI::UpdaterMaker<MainFrame, 1>( "updateStatusBar", &MainFrame::updateStatusBar )
, GUI::ActionMaker<MainFrame, 5>( "doShowPlayerPreview", &MainFrame::showPlayerPreview )
, GUI::ActionMaker<MainFrame, 6>( "doHidePlayerPreview", &MainFrame::hidePlayerPreview )
, GUI::UpdaterMaker<MainFrame, 2>( "updatePlayerPreview", &MainFrame::updatePlayerPreview )
, GUI::UpdaterMaker<MainFrame, 3>( "updateToolMode", &MainFrame::updateToolMode )
{
	m_bAutoMenuEnable = FALSE;

	//皮肤样式路径
	TCHAR szStylesPath[_MAX_PATH];
	VERIFY(::GetModuleFileName(
		AfxGetApp()->m_hInstance, szStylesPath, _MAX_PATH));		

	m_strStylesPath = szStylesPath;
	int nIndex  = m_strStylesPath.ReverseFind(_T('\\'));
	if (nIndex > 0) {
		m_strStylesPath = m_strStylesPath.Left(nIndex);
	}
	else {
		m_strStylesPath.Empty();
	}
	m_strStylesPath += _T("\\Styles\\");
	XTPSkinManager()->LoadSkin(m_strStylesPath + _T("Office2007.cjstyles"));
	m_bFullScreen = FALSE;
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLong( m_hWnd, GWL_STYLE, GetStyle() & ~FWS_ADDTOTITLE );
	if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;
	
	CXTPCommandBars* pCommandBars = GetCommandBars();
	m_wndStatusBar.SetCommandBars(pCommandBars);

	// To Set theme for individual CommandBars
	pCommandBars->SetTheme( xtpThemeRibbon );

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle( xtpToolTipResource );
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->ShowImage( TRUE, 0 );
	pToolTipContext->SetMargin(CRect(2, 2, 2, 2));
	pToolTipContext->SetMaxTipWidth(180);
	pToolTipContext->SetFont( pCommandBars->GetPaintManager()->GetIconFont() );
	pToolTipContext->SetDelayTime( TTDT_INITIAL, 900 );

	// Create ToolBar
	pCommandBars->GetPaintManager()->m_bAutoResizeIcons = TRUE;

	pCommandBars->GetCommandBarsOptions()->bToolBarAccelTips = TRUE;

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	LoadIcons();
	
	//工具栏
	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	// 初始化工具条
	InitStatusBar();

	//隐藏框架
	OnFrameTheme();

	//设置风格
	OnOptionsStyle();

	//设置框架标题
	SetWindowText("3D-WorldViewer");

	//PostMessage(UM_FULLSCREEN);

	return 0;
}

void MainFrame::updateStatusBar( bool forceRedraw /*= false*/ )
{
	BOOL redrawPanels = forceRedraw ? TRUE : FALSE;

	// update the status bar
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_MEMORYLOAD),
		WorldManager::instance().getStatusMessage( 1 ).c_str());
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_FRAMERATE),
		WorldManager::instance().getStatusMessage( 2 ).c_str()); // Always redraw
}

void MainFrame::frameUpdate( bool forceRedraw /*= false*/ )
{
	// update controls on child windows
	PanelManager::instance().updateControls();

	updateStatusBar( forceRedraw );
	// update the scene tab
	//TODO : put back in when page scene is working correctly
	//PageScene::instance().update();

	// remove the focus if over the 3d pane and selection filter not being used
	// (as selection filter drops over the 3d view)
	if (WorldManager::instance().cursorOverGraphicsWnd() &&
		GetCapture() == NULL //&&
		//		!m_wndToolBar2.selectionFilter_.GetDroppedState() &&
		//		!m_wndToolBar2.coordFilter_.GetDroppedState()
		)
	{
		// TODO: this is a bit of a hack on selected item, 
		// they should be able to look after themselves
		if (PropertyItem::selectedItem())
			PropertyItem::selectedItem()->loseFocus();

		//SetFocus();
	}
}

/**
* Engine: 建立窗体
*/
BOOL MainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	BOOL result = /*CFrameWnd*/CXTPFrameWnd::OnCreateClient(lpcs, pContext);

	initialised_ = ( result != 0 );

	return result;
}

void MainFrame::OnSize(UINT nType, int cx, int cy)
{
	if (!initialised_)
		return;

	CXTPFrameWnd::OnSize(nType, cx, cy);
}

LRESULT MainFrame::OnEnterSizeMove(WPARAM, LPARAM)
{
	// Set the resizing_ flag to true, so the view knows that we are resizing
	// and that it shouldn't change the Moo mode.
	resizing_ = true;
	return 0;
}

LRESULT MainFrame::OnExitSizeMove(WPARAM, LPARAM)
{
	// Set the resizing_ flag back to false, so the view knows that it has to
	// change the Moo mode on the next repaint.
	resizing_ = false;
	// And send the repaint message to the view.
	::InvalidateRect( WorldManager::instance().hwndGraphics(), NULL, TRUE );
	::UpdateWindow( WorldManager::instance().hwndGraphics() );
	return 0;
}

BOOL MainFrame::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// capture the alt key and stop the menu bar from gaining focus
	if (wParam == SC_KEYMENU)
		return 1;

	return /*CFrameWnd*/CXTPFrameWnd::OnWndMsg(message, wParam, lParam, pResult);
}

void MainFrame::GetMessageString(UINT nID, CString& rMessage) const
{
	if (nID == AFX_IDS_IDLEMESSAGE)
	{
		rMessage.Empty();
		return;
	}

	return /*CFrameWnd*/CXTPFrameWnd::GetMessageString(nID, rMessage);
}

BOOL MainFrame::PreTranslateMessage(MSG* pMsg)
{
	UINT msg = pMsg->message;

	if( msg == WM_KEYDOWN )
	{
		TCHAR vkey = static_cast< TCHAR>(pMsg->wParam);
		if( vkey ==	VK_F8 )
		{
			// 状态栏
			if( m_wndStatusBar.IsWindowVisible() )
			{
				m_wndStatusBar.ShowWindow( SW_HIDE );

				// 隐藏菜单和工具栏
				CXTPCommandBars* pCommandBars = GetCommandBars();
				int i, iCounts;
				iCounts = pCommandBars->GetCount();
				for( i=0; i<iCounts; ++i )
				{
					if( pCommandBars->GetAt( i )->IsWindowVisible() )
						pCommandBars->ToggleVisible( i );
				}
			}
			else
			{
				m_wndStatusBar.ShowWindow( SW_SHOW );

				// 显示菜单和工具栏
				CXTPCommandBars* pCommandBars = GetCommandBars();
				int i, iCounts;
				iCounts = pCommandBars->GetCount();
				for( i=0; i<iCounts; ++i )
				{
					if( !pCommandBars->GetAt( i )->IsWindowVisible() )
						pCommandBars->ToggleVisible( i );
				}
			}
		}
	}

	if (msg == WM_SYSKEYDOWN) 
	{
		bool bAlt = (HIWORD(pMsg->lParam) & KF_ALTDOWN) == KF_ALTDOWN;
		
		TCHAR vkey = static_cast< TCHAR>(pMsg->wParam);
		bool bTab = GetKeyState(VK_TAB) > 0;
		bool bControl = GetKeyState(VK_CONTROL) > 0;

		if ( bAlt && !bTab && !bControl )
			return TRUE;
	}

	return /*CFrameWnd*/CXTPFrameWnd::PreTranslateMessage(pMsg);
}

// ----------------------------------------------------------------------------
LRESULT MainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return /*CFrameWnd*/CXTPFrameWnd::DefWindowProc(message, wParam, lParam);
}

void MainFrame::OnGUIManagerCommand(UINT nID)
{
	GUI::Manager::instance().act( nID );
}

bool MainFrame::saveSelectionAsPrefab( GUI::ItemPtr item )
{
	if (!WorldEditorApp::instance().pythonAdapter()->canSavePrefab())
	{
		WorldManager::instance().addCommentaryMsg( L("WORLDEDITOR/GUI/MAINFRAME/PREFAB_WARNING") );
		return false;
	}
	// open a save as dialog
	// szFilters is a text string that includes two file name filters:
	// "*.my" for "MyType Files" and "*.*' for "All Files."
	char szFilters[]=
		"Prefab Files (*.prefab)|*.prefab|All Files (*.*)|*.*||";

	ShowCursorHelper scopedShowCursor( true );

	// Create an Open dialog; the default file name extension is ".prefab".
	BWFileDialog fileDlg(FALSE, "prefab", "*.prefab",
		OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilters, this);

	CString path = "object/";
	CString prefabStr;
	prefabStr.LoadString(IDS_PAGE_PREFAB_CAPTION);
	path += prefabStr;
	path += '/';
	std::string initialDir = Options::getOptionString( (LPCTSTR)( path + "directory" ) ).c_str();
	if (initialDir.empty())
		initialDir = BWResource::getDefaultPath() + "/";
	std::replace(initialDir.begin(), initialDir.end(), '/', '\\');
	fileDlg.m_ofn.lpstrInitialDir = initialDir.c_str();

	// Display the file dialog. When user clicks OK, fileDlg.DoModal() 
	// returns IDOK.
	if( fileDlg.DoModal() != IDOK )
		return true;

	CString pathName = fileDlg.GetPathName();

	WorldEditorApp::instance().pythonAdapter()->saveSelectionPrefab( pathName.GetBuffer() );
	return true;
}

bool MainFrame::showToolbar( GUI::ItemPtr item )
{
	return BaseMainFrame::showToolbar( item );
}

bool MainFrame::hideToolbar( GUI::ItemPtr item )
{
	return BaseMainFrame::hideToolbar( item );
}

unsigned int MainFrame::updateToolbar( GUI::ItemPtr item )
{
	return BaseMainFrame::updateToolbar( item );
}

bool MainFrame::showStatusBar( GUI::ItemPtr item )
{
	ShowControlBar( &m_wndStatusBar, TRUE, FALSE );
	return true;
}

bool MainFrame::hideStatusBar( GUI::ItemPtr item )
{
	ShowControlBar( &m_wndStatusBar, FALSE, FALSE );
	return true;
}

unsigned int MainFrame::updateStatusBar( GUI::ItemPtr item )
{
	return ~m_wndStatusBar.GetStyle() & WS_VISIBLE;
}

bool MainFrame::showPlayerPreview( GUI::ItemPtr item )
{
	WorldManager::instance().setPlayerPreviewMode( true );
	return true;
}

bool MainFrame::hidePlayerPreview( GUI::ItemPtr item )
{
	WorldManager::instance().setPlayerPreviewMode( false );
	return true;
}

unsigned int MainFrame::updatePlayerPreview( GUI::ItemPtr item )
{
	return !WorldManager::instance().isInPlayerPreviewMode();
}

unsigned int MainFrame::updateToolMode( GUI::ItemPtr item )
{
	if ( PanelManager::pInstance() == NULL )
		return 1;

	return (PanelManager::instance().currentTool() == (*item)["toolMode"]) ? 1 : 0;
}

void MainFrame::OnClose()
{
	if (WorldManager::instance().canClose( L("WORLDEDITOR/GUI/MAINFRAME/CAN_CLOSE_EXIT") ))
	{
		// this can take a while, specially if the ThumbnailManager is waiting
		// for a big model to load, but it's the safest way

		PanelManager::instance().onClose();

		/*CFrameWnd*/CXTPFrameWnd::OnClose();
	}
}

void MainFrame::OnExitMenuLoop( BOOL bIsTrackPopupMenu )
{
	SetMessageText( "" );
}

void MainFrame::OnToolbarHotItemChange( UINT id, NMHDR* pNotifyStruct, LRESULT* result )
{
	*result = 0;
	std::string s;
	LPNMTBHOTITEM hotitem = (LPNMTBHOTITEM)pNotifyStruct;
	GUI::ItemPtr item = GUI::Manager::instance().findByCommandID( hotitem->idNew );
	if( item )
	{
		s = item->description();
		while( s.find( '&' ) != s.npos )
		{
			s.erase( s.begin() + s.find( '&' ) );
		}
	}
	SetMessageText( s.c_str() );
}

void MainFrame::OnSysColorChange()
{
	/*CFrameWnd*/CXTPFrameWnd::OnSysColorChange();
	for( unsigned int i = 0; i < numToolbars_; ++i )
		toolbars_[ i ].SendMessage( WM_SYSCOLORCHANGE, 0, 0 );
}

/************************************************************************/
/* 自定义                                                               */
/************************************************************************/

void MainFrame::OnExitSystem()
{
	OnClose();
}

void MainFrame::InitStatusBar()
{
	// 内存
	CXTPStatusBarPane* pMemoryPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_MEMORYLOAD, 3);
	m_wndStatusBar.SetPaneWidth(0, 200);
	pMemoryPane->SetText(_T(""));

	// FPS值
	CXTPStatusBarPane* pFPSPane = m_wndStatusBar.AddIndicator(ID_INDICATOR_FRAMERATE, 4);
	m_wndStatusBar.SetPaneWidth(1, 80);
	pFPSPane->SetText(_T(""));

}

//设置风格
void MainFrame::OnOptionsStyle()
{
	GetCommandBars()->SetTheme(xtpThemeRibbon);

	HMODULE hModule = AfxGetInstanceHandle();
	hModule = LoadLibrary(_T("Windows7.dll"));

	LPCTSTR lpszIniFile = 0;
	lpszIniFile = _T("WINDOWS7BLUE.INI"); 

	((CXTPOffice2007Theme*)GetCommandBars()->GetPaintManager())->SetImageHandle(hModule, lpszIniFile);
}

//隐藏原框架
void MainFrame::OnFrameTheme()
{
	//ShowWindow(SW_NORMAL);
	//CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	//CXTPWindowRect rc(this);
	//rc.top += (pRibbonBar->IsFrameThemeEnabled() ? -1 : +1) * GetSystemMetrics(SM_CYCAPTION);
	//MoveWindow(rc);

	//pRibbonBar->EnableFrameTheme(!pRibbonBar->IsFrameThemeEnabled());

}

//工具栏
BOOL MainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach( ::GetMenu(m_hWnd) );
	SetMenu(NULL);

	CXTPRibbonBar* pRibbonBar = ( CXTPRibbonBar* )pCommandBars->Add( _T("The Ribbon"),
		xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar) );
	if ( !pRibbonBar )
	{
		return FALSE;
	}
	pRibbonBar->EnableDocking(0);

	//常用工具
	CXTPRibbonTab* pTabImportTool = pRibbonBar->AddTab( ID_TAB_IMPORTTOOL );

	CXTPRibbonGroup* pGroupLabel= pTabImportTool->AddGroup( ID_GROUP_LABEL );			//标注
	pGroupLabel->Add( xtpControlButton, ID_BUTTON_LABELGET );							//加载标注
	pGroupLabel->Add( xtpControlButton, ID_BUTTON_LABELADD	);							//添加标注
	pGroupLabel->Add( xtpControlButton, ID_BUTTON_LABELHIDE );							//显示/隐藏标注
	pGroupLabel->Add( xtpControlButton, ID_BUTTON_LABELSET );							//标注管理

	CXTPRibbonGroup* pGroupDiagram = pTabImportTool->AddGroup( ID_GROUP_DIAGRAM );	//户型图
	pGroupDiagram->SetControlsCentering();
	pGroupDiagram->Add( xtpControlButton, ID_BUTTON_DIAGRAMVIEW );					//加载户型图

	//////////////////////////////////////////////////////////////////////////
	//建筑替换方案
	CXTPRibbonGroup* pGroupBuildingScheme= pTabImportTool->AddGroup( ID_GROUP_BUILDINGSCHEME);
	pGroupBuildingScheme->Add( xtpControlButton, ID_BUTTON_ADDBUILDINGSCHEME);
	pGroupBuildingScheme->Add( xtpControlButton, ID_BUTTON_DELETEBUILDINGSCHEME);	
	pGroupBuildingScheme->Add( xtpControlButton, ID_BUTTON_BUILDINGSCHEMEMANAGER);	
	pGroupBuildingScheme->Add( xtpControlButton, ID_BUTTON_EXECUTEBUILDINGSCHEME);	
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//路径浏览
	CXTPRibbonGroup* pGroupPathScan = pTabImportTool->AddGroup( ID_GROUP_PATHSCAN );	//增加路径浏览组
	pGroupPathScan->SetControlsCentering();

	pGroupPathScan->Add( xtpControlButton, ID_BUTTON_PATHSET );							//路径管理
	pGroupPathScan->Add( xtpControlButton, ID_BUTTON_PAUSENAV );						//浏览暂停或继续
	pGroupPathScan->Add( xtpControlButton, ID_BUTTON_STOP );							//浏览停止
	//////////////////////////////////////////////////////////////////////////
	// 帮助
	CXTPRibbonTab* pTabHelpTool = pRibbonBar->AddTab( ID_TAB_HELPTOOL );

	CXTPRibbonGroup* pGroupHelp= pTabHelpTool->AddGroup( ID_GROUP_HELP );			//帮助

	pRibbonBar->ShowQuickAccess(FALSE);
	pRibbonBar->EnableFrameTheme();
	return TRUE;
}

//图标绑定工具栏
void MainFrame::LoadIcons()
{	
	CXTPCommandBars* pCommandBars = GetCommandBars();

	//加载标注
	UINT uiGroupLabelGet[] = { ID_BUTTON_LABELGET };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_LABELGET, uiGroupLabelGet, 
		_countof(uiGroupLabelGet), CSize(32, 32) );

	//标注管理
	UINT uiGroupLabelSet[] = { ID_BUTTON_LABELSET };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_LABELSET, uiGroupLabelSet, 
		_countof(uiGroupLabelSet), CSize(32, 32) );

	//添加标注
	UINT uiGroupLabelAdd[] = { ID_BUTTON_LABELADD };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_LABELADD, uiGroupLabelAdd, 
		_countof(uiGroupLabelAdd), CSize(32, 32) );

	//显示隐藏标注
	UINT uiGroupLabelHide[] = { ID_BUTTON_LABELHIDE };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_LABELHIDE, uiGroupLabelHide, 
		_countof(uiGroupLabelHide), CSize(32, 32) );

	// 查看户型图
	UINT uiGroupDiagramView[] = { ID_BUTTON_DIAGRAMVIEW };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_DIAGRAMVIEW, uiGroupDiagramView, 
		_countof(uiGroupDiagramView), CSize(32, 32) );

	UINT uiGroupPathset[] = { ID_BUTTON_PATHSET };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_PATH, uiGroupPathset, 
		_countof(uiGroupPathset), CSize(32, 32) );

	UINT uiGroupPathPause[] = { ID_BUTTON_PAUSENAV };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_PAUSE, uiGroupPathPause, 
		_countof(uiGroupPathPause), CSize(32, 32) );

	UINT uiGroupPathStop[] = { ID_BUTTON_STOP };
	pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_STOP, uiGroupPathStop, 
		_countof(uiGroupPathStop), CSize(32, 32) );


}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(cs.hMenu!=NULL)
	{
		::DestroyMenu(cs.hMenu);      // delete menu if loaded
		cs.hMenu = NULL;              // no menu for this window
	}

	return __super::PreCreateWindow(cs);
}

void MainFrame::beginFullScreen()
{
	GetWindowPlacement(&m_OldWndPlacement);//获取窗口位置
	CRect WindowRect;
	GetWindowRect(&WindowRect);//获取窗口大小
	CRect ClientRect;
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);//获取控制条窗口的大小
	ClientToScreen(&ClientRect);//转换为屏幕坐标
	//获取屏幕的分辨率
	int nFullWidth=GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
	//将除控制条外的客户区全屏显示到从(0,0)到(nFullWidth, nFullHeight)区域, 将(0,0)和(nFullWidth, nFullHeight)两个点外扩充原窗口和除控制条之外的客户区位置间的差值, 就得到全屏显示的窗口位置
	m_FullScreenRect.left=WindowRect.left-ClientRect.left;
	m_FullScreenRect.top=WindowRect.top-ClientRect.top;
	m_FullScreenRect.right=WindowRect.right-ClientRect.right+nFullWidth;
	m_FullScreenRect.bottom=WindowRect.bottom-ClientRect.bottom+nFullHeight;
	m_bFullScreen=TRUE; //设置全屏显示标志为 TRUE
	//进入全屏显示状态
	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	wndpl.flags=0;
	wndpl.showCmd=SW_SHOWNORMAL;
	wndpl.rcNormalPosition=m_FullScreenRect;
	SetWindowPlacement(&wndpl);
}

void MainFrame::endFullScreen()
{
	if(m_bFullScreen)
	{
		//退出全屏显示, 恢复原窗口显示
		ShowWindow(SW_HIDE);
		SetWindowPlacement(&m_OldWndPlacement);
	}
}

void MainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bFullScreen)
	{
		//全屏显示的大小
		lpMMI->ptMaxSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxSize.y=m_FullScreenRect.Height();
		//全屏显示的位置
		lpMMI->ptMaxPosition.x=m_FullScreenRect.Width();
		lpMMI->ptMaxPosition.y=m_FullScreenRect.Height();
		//最大的Track尺寸也要改变
		lpMMI->ptMaxTrackSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxTrackSize.y=m_FullScreenRect.Height();
	}
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

LRESULT MainFrame::OnFullScreen(WPARAM wParam, LPARAM lParam)
{
	beginFullScreen();
	return 0;
}

/**
* 添加标注
*/
void MainFrame::OnAddmark()
{
	CDlgMarkInput::Instance().ShowWindow(SW_SHOW);
}
/**
* 隐藏显示标注
*/
void MainFrame::OnShoworhidemark()
{
	bool bShowMark = CMarkObject::Instance().IsShowMark();
	CMarkObject::Instance().ShowMark(!bShowMark);
}
/**
* 隐藏显示标注更新
*/
void MainFrame::OnUpdateShoworhidemark(CCmdUI *pCmdUI)
{
	//pCmdUI->SetCheck(CMarkObject::Instance().IsShowMark());

	CXTPCommandBars* pCommandBars = GetCommandBars();
	bool bShowMark = CMarkObject::Instance().IsShowMark();

	if ( !bShowMark )
	{
		//设置按钮为显示标注
		pCmdUI->SetText( "显示标注" );
		UINT uiGroupPauseNav[] = { ID_BUTTON_LABELHIDE };
		pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_LABELSHOW, uiGroupPauseNav,
			_countof(uiGroupPauseNav), CSize(32, 32) );
	}
	else
	{
		//设置按钮为隐藏标注
		pCmdUI->SetText( "隐藏标注" );
		UINT uiGroupPauseNav[] = { ID_BUTTON_LABELHIDE };
		pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_LABELHIDE, uiGroupPauseNav,
			_countof(uiGroupPauseNav), CSize(32, 32) );
	}
}
/**
* 标注管理
*/
void MainFrame::OnMarkmanage()
{
	CDlgMarkManage::Instance().ShowWindow( SW_SHOW );
}
/**
* 加载标注
*/
void MainFrame::OnReloadmark()
{
	CDlgMarkLoad::Instance().ShowWindow( SW_SHOW );
}
/**
* 查看户型图
*/
void MainFrame::OnViewDiagram()
{
	std::vector<ChunkItemPtr> vItems = WorldManager::instance().selectedItems();
	if(vItems.size()!=1){
		AfxMessageBox("请选择一个对象");
		return;
	}
	CApartmentDiagramMgr::Instance().setCurrentApartment(vItems[0]->edGUID());
	CDlgApartmentDiagram::Instance().ShowWindow(SW_SHOW);
}
/*
添加替换方案
*/
void MainFrame::OnAddBuildingScheme()
{
	std::vector<ChunkItemPtr> vSelItems = WorldManager::instance().selectedItems();
	if(vSelItems.size()==1)
	{
		std::string strGuid = vSelItems[0]->edGUID();
		AddBuildingSchemeDlg::getInstance()->ShowWindow(SW_SHOW);
		AddBuildingSchemeDlg::getInstance()->setSelectedModel(strGuid);
	}
}
/*
方案管理
*/
void MainFrame::OnBuildingSchemeManager()
{
	BuildingSchemeManagerDlg::getInstance()->ShowWindow(SW_SHOW);
	BuildingSchemeManagerDlg::getInstance()->showResult();
}
/*
删除建筑方案
*/
void MainFrame::OnDeleteBuildingScheme()
{
	if (MessageBox("您确定要删除吗？","删除警告",MB_OKCANCEL)!=IDOK)
		return;
	std::vector<ChunkItemPtr> vSelItems = WorldManager::instance().selectedItems();
	int isize = vSelItems.size();
	for(int i=0; i<isize; i++)
	{
		std::string strGuid = vSelItems[i]->edGUID();
		BuildingSchemeManager::getInstance()->deleteSchemeByModel( strGuid.c_str() );
	}
}
/*
执行替换方案
*/
void MainFrame::OnExecuteBuildingScheme()
{
	std::vector<CString> vAllSchemeName = BuildingSchemeManager::getInstance()->getAllSchemeName();
	int isize = vAllSchemeName.size();
	for(int i=0; i<isize; i++)
		BuildingSchemeManager::getInstance()->executeScheme(vAllSchemeName[i] );
}

void MainFrame::OnCtPathtravel()
{
	CDlgUDOManager::Instance().ShowWindow( SW_SHOW );
}

void MainFrame::OnPausedPathTravel()
{
	bool bTraveling = Fly::instance().isFlying();
	if ( !bTraveling )
		return;

	bool bPause = Fly::instance().isPause();
	Fly::instance().setPause( !bPause );
}

void MainFrame::OnUpdatePausedPathTravel( CCmdUI *pCmdUI )
{
	bool bTraveling = Fly::instance().isFlying();

	//图标管理
	CXTPCommandBars* pCommandBars = GetCommandBars();

	if ( bTraveling )
	{
		pCmdUI->Enable( TRUE );

		bool bPause = Fly::instance().isPause();

		if ( bPause )
		{
			pCmdUI->SetText( "继续浏览" );
			//继续浏览
			UINT uiGroupPauseNav[] = { ID_BUTTON_PAUSENAV };
			pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_CONTINUE, uiGroupPauseNav,
				_countof(uiGroupPauseNav), CSize(32, 32) );
		}
		else
		{
			//暂停浏览
			UINT uiGroupPauseNav[] = { ID_BUTTON_PAUSENAV };
			pCommandBars->GetImageManager()->SetIcons( IDR_BUTTON_PAUSE, uiGroupPauseNav,
				_countof(uiGroupPauseNav), CSize(32, 32) );
			pCmdUI->SetText( "暂停浏览" );
		}
	}
	else
	{
		pCmdUI->Enable( FALSE );
	}
}

void MainFrame::OnStopPathTravel()
{
	bool bTraveling = Fly::instance().isFlying();
	if ( !bTraveling )
		return;
	Fly::instance().setFly( false );
}

void MainFrame::OnUpdateStopPathTravel( CCmdUI *pCmdUI )
{
	bool bTraveling = Fly::instance().isFlying();
	pCmdUI->Enable( bTraveling );
}
