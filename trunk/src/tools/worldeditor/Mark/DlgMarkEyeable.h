#pragma once
#include "worldeditor/Dialogs/BaseInputDlg.h"
#include "MarkObject.h"

class CDlgMarkEyeable :public CBaseInputDlg
{
public:
	CDlgMarkEyeable(void);
	~CDlgMarkEyeable(void);

	static CDlgMarkEyeable &Instance();

private:
	static std::auto_ptr<CDlgMarkEyeable> s_pInstance;

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
public:
	MARKDATA m_markdata;
};