#ifndef ME_MAINFRAME_HPP
#define ME_MAINFRAME_HPP

#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "guimanager/gui_functor_cpp.hpp"
#include "common/base_mainframe.hpp"


// MainFrame
class MainFrame : public /*CFrameWnd*/BaseMainFrame,
	GUI::ActionMaker<MainFrame>, // save prefab
	GUI::ActionMaker<MainFrame, 1>, // show toolbar
	GUI::ActionMaker<MainFrame, 2>, // hide toolbar
	GUI::ActionMaker<MainFrame, 3>, // show status bar
	GUI::ActionMaker<MainFrame, 4>, // hide status bar
	GUI::ActionMaker<MainFrame, 5>, // show player preview
	GUI::ActionMaker<MainFrame, 6>, // hide player preview
	GUI::UpdaterMaker<MainFrame>, // update show toolbar
	GUI::UpdaterMaker<MainFrame, 1>, // update show status bar
	GUI::UpdaterMaker<MainFrame, 2>, // update player preview
	GUI::UpdaterMaker<MainFrame, 3> // update tool mode
{
protected: 
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

public:
	/**
	* 系统原有
	*/
	virtual ~MainFrame();

	void updateStatusBar( bool forceRedraw = false );
	void frameUpdate( bool forceRedraw = false );
	bool resizing() const { return resizing_; }

	virtual void GetMessageString(UINT nID, CString& rMessage) const;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	/**
	* 系统原有
	*/
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	std::string GetActionName(UINT nID);

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	bool saveSelectionAsPrefab( GUI::ItemPtr item );

	bool showToolbar( GUI::ItemPtr item );
	bool hideToolbar( GUI::ItemPtr item );
	unsigned int updateToolbar( GUI::ItemPtr item );

	bool showStatusBar( GUI::ItemPtr item );
	bool hideStatusBar( GUI::ItemPtr item );
	unsigned int updateStatusBar( GUI::ItemPtr item );

	bool showPlayerPreview( GUI::ItemPtr item );
	bool hidePlayerPreview( GUI::ItemPtr item );
	unsigned int updatePlayerPreview( GUI::ItemPtr item );
	unsigned int updateToolMode( GUI::ItemPtr item );

	

public:
	/**
	* 公开方法声明
	*/
	// 初始化状态条
	void InitStatusBar();

	//设置主题风格
	void OnOptionsStyle();

	//重画系统按钮
	void OnFrameTheme();

	//设置图标
	BOOL CreateRibbonBar();

	//工具栏图标设置
	void LoadIcons();

private:

	/**
	 * 私有控件声明
	 */
	CString m_strStylesPath;//皮肤样式路径

	CXTPStatusBar	m_wndStatusBar;		// 状态栏

	//全屏
#define UM_FULLSCREEN WM_USER+1
private:
	WINDOWPLACEMENT m_OldWndPlacement; //用来保存原窗口位置 
	BOOL m_bFullScreen; //全屏显示标志 
	CRect m_FullScreenRect; //表示全屏显示时的窗口位置
public:
	void beginFullScreen();
	void endFullScreen();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg LRESULT OnFullScreen(WPARAM wParam = 0, LPARAM lParam = 0);
private:
	/**
	* 成员变量声明
	*/
	typedef struct _object PyObject;

	PyObject		*pScriptObject_;
	bool			resizing_;
	CString			triangles_;	
	bool			initialised_;
public:
	/**
	* 消息
	*/
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnEnterSizeMove (WPARAM, LPARAM);
	afx_msg LRESULT OnExitSizeMove (WPARAM, LPARAM);
	afx_msg void OnClose();
	afx_msg void OnGUIManagerCommand(UINT nID);
	afx_msg void OnExitMenuLoop( BOOL bIsTrackPopupMenu );
	afx_msg void OnToolbarHotItemChange( UINT id, NMHDR * pNotifyStruct, LRESULT * result );
	afx_msg void OnSysColorChange();
	
	//**************************标注**************************//
	afx_msg void OnAddmark();
	afx_msg void OnShoworhidemark();
	afx_msg void OnUpdateShoworhidemark(CCmdUI *pCmdUI);
	afx_msg void OnMarkmanage();
	afx_msg void OnReloadmark();
	//**************************标注**************************//

	//**************************户型图**************************//
	afx_msg void OnViewDiagram();
	//**************************户型图**************************//
	//////////////////////////////////////////////////////////////////////////
	//建筑替换方案
	afx_msg void OnAddBuildingScheme();
	afx_msg void OnBuildingSchemeManager();
	afx_msg void OnDeleteBuildingScheme();
	afx_msg void OnExecuteBuildingScheme();
	//////////////////////////////////////////////////////////////////////////
	//**************************路径浏览**************************//
	afx_msg void OnCtPathtravel();
	afx_msg void OnPausedPathTravel();
	afx_msg void OnUpdatePausedPathTravel(CCmdUI *pCmdUI);
	afx_msg void OnStopPathTravel();
	afx_msg void OnUpdateStopPathTravel(CCmdUI *pCmdUI);
	//**************************路径浏览**************************//

	//**************************建筑属性**************************//
	afx_msg void OnBuildingProperty();
	afx_msg void OnBuildingPropertyMgr();
	afx_msg void OnBuildingPropertyShowHide();
	afx_msg void OnUpdateBuildingPropertyShowHide(CCmdUI *pCmdUI);
	//**************************建筑属性**************************//

	//弹出窗体里的控件相应事件
	//afx_msg LRESULT OnPopupNotify(WPARAM wParam, LPARAM lParam);

	//退出系统
	afx_msg void OnExitSystem();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};


#endif // ME_MAINFRAME_HPP
