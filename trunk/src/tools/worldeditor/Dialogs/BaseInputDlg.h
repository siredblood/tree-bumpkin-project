#pragma once
#include "worldeditor/resource.h"
#include "afxwin.h"

// CBaseInputDlg �Ի���

class CBaseInputDlg : public CDialog
{
	DECLARE_DYNAMIC(CBaseInputDlg)

public:
	CBaseInputDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBaseInputDlg();

// �Ի�������
	enum { IDD = IDD_BASEINPUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CXTPEdit m_edtInput;
	CStatic m_stName;
	CXTPButton m_btnOK;
	virtual BOOL OnInitDialog();
};
