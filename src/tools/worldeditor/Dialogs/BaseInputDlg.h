#pragma once
#include "worldeditor/resource.h"
#include "afxwin.h"

// CBaseInputDlg 对话框

class CBaseInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseInputDlg)

public:
	CBaseInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseInputDlg();

// 对话框数据
	enum { IDD = IDD_BASEINPUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXTPEdit m_edtInput;
	CStatic m_stName;
	CXTPButton m_btnOK;
	virtual BOOL OnInitDialog();
};
