#ifndef WAIT_DIALOG_HPP
#define WAIT_DIALOG_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/resource.h"
#include "common/resource_loader.hpp"


class WaitDlg : public CDialog, public ISplashVisibilityControl
{
	DECLARE_DYNAMIC(WaitDlg)

public:
// Dialog Data
	enum { IDD = IDD_WAITDLG };

	WaitDlg(CWnd* pParent = NULL);
	virtual ~WaitDlg();

	/*virtual*/ void setSplashVisible( bool visible );

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT nIDEvent);

	static WaitDlg* s_dlg_;
	static std::string lastString_;
	bool bShow_;

public:
	static bool isValid();
	static ISplashVisibilityControl* getSVC();
	static void show( const std::string& info );
	static void hide( int delay = 0 );
	static void overwriteTemp( const std::string& info, int delay );
};


#endif // WAIT_DIALOG_HPP