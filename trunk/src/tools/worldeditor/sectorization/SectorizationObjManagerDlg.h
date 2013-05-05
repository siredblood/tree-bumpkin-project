#pragma once
#include "resource.h"

// SectorizationObjManagerDlg 对话框

class SectorizationObjManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(SectorizationObjManagerDlg)

public:
	SectorizationObjManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SectorizationObjManagerDlg();

// 对话框数据
	enum { IDD = IDD_SECTORIZATIONOBJECTMANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CXTPReportControl m_wndReportCtrl;
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnBnClickedButton1();

private:
	void showResult();
};
