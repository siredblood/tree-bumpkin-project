#pragma once
#include "resource.h"

// SectorizationObjManagerDlg �Ի���

class SectorizationObjManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(SectorizationObjManagerDlg)

public:
	SectorizationObjManagerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SectorizationObjManagerDlg();

// �Ի�������
	enum { IDD = IDD_SECTORIZATIONOBJECTMANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CXTPReportControl m_wndReportCtrl;
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void OnBnClickedButton1();

private:
	void showResult();
};
