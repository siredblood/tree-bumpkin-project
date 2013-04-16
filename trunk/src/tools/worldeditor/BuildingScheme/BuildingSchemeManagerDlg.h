#pragma once
#include "resource.h"
#include "ReportControl/XTPReportControl.h"

// BuildingManagerDlg �Ի���

class BuildingSchemeManagerDlg : public CDialog
{
	DECLARE_DYNAMIC(BuildingSchemeManagerDlg)

public:
	BuildingSchemeManagerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BuildingSchemeManagerDlg();

// �Ի�������
	enum { IDD = IDD_SCHEMEMANAGER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	CXTPReportControl m_wndReportCtrl;

	static BuildingSchemeManagerDlg* mInstance;

public:
	virtual BOOL OnInitDialog();

	static BuildingSchemeManagerDlg* getInstance();
	/*====================================
	˵������ʾ���
	������
	���أ�
	====================================*/
	void showResult();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result);
};
