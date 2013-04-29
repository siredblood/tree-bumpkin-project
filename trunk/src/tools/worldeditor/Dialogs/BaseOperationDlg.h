#pragma once
#include "afxwin.h"
#include "worldeditor/resource.h"

// CBaseOperationDlg �Ի���

class CBaseOperationDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseOperationDlg)

public:
	CBaseOperationDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseOperationDlg();

// �Ի�������
	enum { IDD = IDD_BASEOPERATION_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combox;
	CEdit m_editbox;
	virtual BOOL OnInitDialog();
	CXTPButton m_btnOK;
	CXTPButton m_btnExit;
};
