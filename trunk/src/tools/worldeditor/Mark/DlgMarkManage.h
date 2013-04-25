#pragma once

#include <memory>
#include "mark\MarkObject.h"
#include "resource.h"

class CDlgMarkManage : public CXTResizeDialog
{
public:
	CDlgMarkManage(CWnd* pParent = NULL);
	~CDlgMarkManage(void);
	
	static CDlgMarkManage &Instance();

	enum { IDD = IDD_DLG_MARK_MANAGE };
	DECLARE_DYNAMIC(CDlgMarkManage)

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
private:
	void UpdateReport();
	
private:
	static std::auto_ptr<CDlgMarkManage> s_pInstance;
	std::vector<MARKDATA> m_vAllMarkData;
	
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

	CXTPOfficeBorder<CXTPReportControl,false>	m_wndProGridView;	//����ؼ�
	CXTPButton m_button1;
	CXTPButton m_button2;
	CXTPButton m_button3;
	CXTPButton m_button4;
};
