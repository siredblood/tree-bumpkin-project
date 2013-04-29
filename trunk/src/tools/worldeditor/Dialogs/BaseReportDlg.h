#pragma once
#include "afxwin.h"
#include "worldeditor/resource.h"

// CBaseReportDlg 对话框
#define CDialogSampleDlgBase CXTPDialogBase<CXTResizeDialog>
class CBaseReportDlg : public CDialogSampleDlgBase
{
	DECLARE_DYNAMIC(CBaseReportDlg)

public:
	CBaseReportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBaseReportDlg();

// 对话框数据
	enum { IDD = IDD_BASEREPORT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CXTPOfficeBorder<CXTPReportControl,false>	m_wndProGridView;	//报表控件
	CXTPButton m_button1;
	CXTPButton m_button2;
	CXTPButton m_button3;
	CXTPButton m_button4;
	CXTPButton m_button5;
	CXTPButton m_button6;
	CXTPButton m_button7;

	CXTPButton m_rbtnAll;
	CXTPButton m_rbtnCancle;
	CXTPReportFilterEditControl m_edtFilterEdit;

	virtual BOOL OnInitDialog();
	afx_msg void OnGetAll();
	afx_msg void OnCancelAll();
	afx_msg void OnOK();
};
