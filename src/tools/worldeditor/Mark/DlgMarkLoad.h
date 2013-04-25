#pragma once

#include "resource.h"
// CDlgMarkLoad 对话框

class CDlgMarkLoad : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDlgMarkLoad)

private:
	CDlgMarkLoad(CWnd* pParent = NULL);   // 标准构造函数
	static std::auto_ptr<CDlgMarkLoad>	s_pInstance;

public:
	virtual ~CDlgMarkLoad();
	static CDlgMarkLoad &Instance();

// 对话框数据
	enum { IDD = IDD_DLG_MARK_LOAD };

// 报表
	enum
	{
		COLUMN_CHECK,
		COLUMN_ID,
		COLUMN_GUID,
		COLUMN_NAME,
		COLUMN_CREATOR,
		COLUMN_CREATE_TIME,
		COLUMN_TYPE,
		COLUMN_POSITION,
		COLUMN_VIEW_DISTANCE
	};

#define STRING_CHECK			"√"
#define STRING_ID				"编号"
#define STRING_GUID				"GUID"
#define STRING_NAME				"名称"
#define STRING_CREATOR			"创建者"
#define	STRING_CREATE_TIME		"创建时间"
#define STRING_TYPE				"类型"
#define STRING_POSITION			"位置"
#define STRING_VIEW_DISTANCE	"可视距离"

public:
	// 初始化控件
	void InitControl();

	// 绑定到列头
	void BindToHeader();

	// 绑定到报表
	void BindToReport( CString strCondit = "" );

private:
	//控件变量
	CXTPReportControl	m_wndReportCtrl;
	CComboBox			m_cmbFileds;
	CEdit				m_strValue;
	CXTPButton			m_btnSelect;
	CXTPButton			m_btnLoad;
	CXTPButton			m_btnRefresh;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnFilter();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedRbtnTangall();
	afx_msg void OnBnClickedRbtnTangcancel();
};
