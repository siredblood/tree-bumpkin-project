#pragma once

#include <memory>
#include "resource.h"

class CDlgBuildingPropertyMgr : public CXTResizeDialog
{
public:
	CDlgBuildingPropertyMgr(CWnd* pParent = NULL);
	~CDlgBuildingPropertyMgr(void);
	
	static CDlgBuildingPropertyMgr &Instance();

	enum { IDD = IDD_DLG_PROPERTY_MANAGE };
	DECLARE_DYNAMIC(CDlgBuildingPropertyMgr)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
private:
	void UpdateReport();
	
private:
	static std::auto_ptr<CDlgBuildingPropertyMgr> s_pInstance;
	
	int m_iSelRow;
	
public:
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnClose();
	
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReflesh();	
	afx_msg void OnGotoTarget();
	afx_msg void OnModify();
	afx_msg void OnDelete();
	afx_msg void OnGetAll();
	afx_msg void OnCancelAll();
	afx_msg void OnOK();

	CXTPButton m_rbtnAll;
	CXTPButton m_rbtnCancle;
	CXTPReportFilterEditControl m_edtFilterEdit;

	CXTPOfficeBorder<CXTPReportControl,false>	m_wndProGridView;	//报表控件
	CXTPButton m_button1;
	CXTPButton m_button2;
	CXTPButton m_button3;
	CXTPButton m_button4;
};
