#pragma once
#include "worldeditor/Dialogs/BaseOperationDlg.h"

class CDlgUdoNodeOperator :
	public CBaseOperationDlg
{
public:
	CDlgUdoNodeOperator(void);
	~CDlgUdoNodeOperator(void);

	// ��ȡ��������
	void GetOperateData( CString &strOpertor, CString &strData );

private:
	CString		m_strOperator;	// ����
	CString		m_strData;		// ����

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
