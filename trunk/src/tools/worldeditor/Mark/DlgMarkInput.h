#pragma once
#include "worldeditor/Dialogs/BaseInputDlg.h"
#include "MarkObject.h"

class CDlgMarkInput :public CBaseInputDlg
{
public:
	CDlgMarkInput(void);
	~CDlgMarkInput(void);
	
	static CDlgMarkInput &Instance();
	
	//void SetMarkMsg(CString strGUID, Vector3 pos, int iType);
	
private:
	static std::auto_ptr<CDlgMarkInput>	s_pInstance;
	//Vector3 m_MarkPos;
	//int m_iMarkType;
	//CString m_strGUID;
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
public:
	MARKDATA m_markdata;
};
