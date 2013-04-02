#ifndef CVS_INFO_DIALOG_HPP
#define CVS_INFO_DIALOG_HPP


#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/resource.h"
#include "worldeditor/misc/cvswrapper.hpp"


class CVSInfoDialog : public CDialog, public CVSLog
{
public:
	CVSInfoDialog( const std::string& title );
	~CVSInfoDialog();

	virtual void add( const std::string& msg );

// Dialog Data
	enum { IDD = IDD_MODELESS_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	std::string title_;

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};


#endif // CVS_INFO_DIALOG_HPP