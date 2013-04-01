#ifndef WORLD_EDITOR_APP_HPP
#define WORLD_EDITOR_APP_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/resource.h"

class CAboutDlg : public CDialog
{
	CBitmap mBackground;
	CFont mFont;
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

class AppFunctor;
typedef SmartPointer<AppFunctor> AppFunctorPtr;


class WorldEditorApp : public CWinApp
{
public:
	static WorldEditorApp & instance() { return *s_instance_; }

	WorldEditorApp();
	~WorldEditorApp();

	CWnd* mainWnd() { return m_pMainWnd; }
	App* mfApp() { return s_mfApp; }

	virtual BOOL InitInstance();
	virtual int ExitInstance();

	virtual BOOL OnIdle(LONG lCount);

	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	WEPythonAdapter * pythonAdapter() const;

protected:
	DECLARE_MESSAGE_MAP()

	BOOL parseCommandLineMF();

private:
	static WorldEditorApp * s_instance_;
	App					  * s_mfApp;
	WEPythonAdapter		  * pPythonAdapter_;
	HANDLE					updateMailSlot_;
	AppFunctorPtr			pAppFunctor_;
	LPCTSTR					oldAppName_;
};


extern WorldEditorApp theApp;


#endif // WORLD_EDITOR_APP_HPP
