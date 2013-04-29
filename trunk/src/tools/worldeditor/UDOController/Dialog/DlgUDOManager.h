#pragma once

#include "worldeditor/Dialogs/BaseReportDlg.h"
#include <memory>
#include "worldeditor/UDOController/UDOHeader.hpp"

class CDlgUDOManager : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDlgUDOManager)

public:
	~CDlgUDOManager();
	
	static CDlgUDOManager &Instance();

	void InitControl();
	void UpdateReport();	//更新列表
	void EditUpdate();		//编辑更新

	// 获取选中对象
	void GetSelectedItems( std::vector<UDOCamera> &vItems );

private:

	enum 
	{
		COLUMN_ID,
		COLUMN_NAME,
		COLUMN_SPEED,
		COLUMN_NODEID
	}; 
	
	CDlgUDOManager();
	static std::auto_ptr<CDlgUDOManager> s_pInstance;
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();

	afx_msg void OnClose();
	afx_msg void OnBeginTravel();
	//afx_msg void OnShowOrHidePath();
	afx_msg void OnCreatPath();
	afx_msg void OnDeletePath();
	afx_msg void OnEditPathNode();	
	afx_msg void OnNMReturnReport(NMHDR *pNMHDR, LRESULT *pResult);

	virtual void OnOK();
	virtual void OnCancel();
		
	CXTPReportControl				m_wndProGridView;
	CXTPReportFilterEditControl		m_edtFilterEdit;

	CXTPButton				m_button1;
	CXTPButton				m_button2;
	CXTPButton				m_button3;
	CXTPButton				m_button4;
	CXTPButton				m_button5;
	CXTPButton				m_button6;
	CXTPButton				m_button7;
};
