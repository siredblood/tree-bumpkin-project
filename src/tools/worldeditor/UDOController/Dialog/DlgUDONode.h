#pragma once

#include <memory>


class CDlgUDONode : public CXTPResizeDialog
{
public:
	~CDlgUDONode();
	
	static CDlgUDONode &Instance();
	void SetPID( int pid );
	
	//更新列表
	void UpdateReport();	

	// 设置统一高度
	void SetUnifyHeight( float fHeight );
	void SetUnifyOffset( Vector3 vOffset );

private:
	enum 
	{
		COLUMN_ID,
		COLUMN_GUID,
		COLUMN_POSITION,
		COLUMN_ROTATE,
		COLUMN_SPEED,
		COLUMN_DESCRIPTION
	}; 
	
	CDlgUDONode();
	
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnUnify();
	afx_msg void OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result);

	virtual void OnOK();
	virtual void OnCancel();
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	
	static std::auto_ptr<CDlgUDONode> s_pInstance;
	
	int			m_iSelRow;
	int			m_iPid;

	CXTPReportControl	m_wndReportCtrl;
	CXTPButton			m_btnSave;
	CXTPButton			m_btnDelete;
	CXTPButton			m_btnUnify;
};
