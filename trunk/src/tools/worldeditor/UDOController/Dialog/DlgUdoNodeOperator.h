#pragma once
#include "worldeditor/Dialogs/BaseOperationDlg.h"

class CDlgUdoNodeOperator :
	public CBaseOperationDlg
{
public:
	CDlgUdoNodeOperator(void);
	~CDlgUdoNodeOperator(void);

	// 获取操作数据
	void GetOperateData( CString &strOpertor, CString &strData );

private:
	CString		m_strOperator;	// 操作
	CString		m_strData;		// 数据

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
