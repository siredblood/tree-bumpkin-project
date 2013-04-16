#pragma once
#include "resource.h"
#include "ReportControl/XTPReportControl.h"

// BuildingManagerDlg 对话框

class BuildingSchemeManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(BuildingSchemeManagerDlg)

public:
	BuildingSchemeManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~BuildingSchemeManagerDlg();

// 对话框数据
	enum { IDD = IDD_SCHEMEMANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	CXTPReportControl m_wndReportCtrl;

	static BuildingSchemeManagerDlg* mInstance;

public:
	virtual BOOL OnInitDialog();

	static BuildingSchemeManagerDlg* getInstance();
	/*====================================
	说明：显示结果
	参数：
	返回：
	====================================*/
	void showResult();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result);
};
