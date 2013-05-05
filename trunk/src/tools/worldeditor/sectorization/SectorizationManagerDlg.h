#pragma once
#include "resource.h"
#include "afxwin.h"

// SectorizationManagerDlg �Ի���

class SectorizationManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(SectorizationManagerDlg)

public:
	SectorizationManagerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SectorizationManagerDlg();

// �Ի�������
	enum { IDD = IDD_SECTORIZATIONMANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CXTPReportControl m_wndReportCtrl;

	static SectorizationManagerDlg* mInstance;

	CButton m_btnAdd;
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButton3();

	static SectorizationManagerDlg* getInstance();

	void showResult();
	
	CButton m_btnDelete;
};
