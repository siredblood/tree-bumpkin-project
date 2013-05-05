#pragma once
#include "resource.h"
#include "afxwin.h"

// SectorizationManagerDlg 对话框

class SectorizationManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(SectorizationManagerDlg)

public:
	SectorizationManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SectorizationManagerDlg();

// 对话框数据
	enum { IDD = IDD_SECTORIZATIONMANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CXTPReportControl m_wndReportCtrl;

	static SectorizationManagerDlg* mInstance;

	CButton m_btnAdd;
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButton3();

	static SectorizationManagerDlg* getInstance();

	void showResult();
	
	CButton m_btnDelete;
};
