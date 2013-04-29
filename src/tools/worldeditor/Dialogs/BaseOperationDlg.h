#pragma once
#include "afxwin.h"
#include "worldeditor/resource.h"

// CBaseOperationDlg 对话框

class CBaseOperationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseOperationDlg)

public:
	CBaseOperationDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseOperationDlg();

// 对话框数据
	enum { IDD = IDD_BASEOPERATION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combox;
	CEdit m_editbox;
	virtual BOOL OnInitDialog();
	CXTPButton m_btnOK;
	CXTPButton m_btnExit;
};
