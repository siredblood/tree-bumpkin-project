#pragma once

#include "resource.h"
// CDlgMarkLoad �Ի���

class CDlgMarkLoad : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDlgMarkLoad)

private:
	CDlgMarkLoad(CWnd* pParent = NULL);   // ��׼���캯��
	static std::auto_ptr<CDlgMarkLoad>	s_pInstance;

public:
	virtual ~CDlgMarkLoad();
	static CDlgMarkLoad &Instance();

// �Ի�������
	enum { IDD = IDD_DLG_MARK_LOAD };

// ����
	enum
	{
		COLUMN_CHECK,
		COLUMN_ID,
		COLUMN_GUID,
		COLUMN_NAME,
		COLUMN_CREATOR,
		COLUMN_CREATE_TIME,
		COLUMN_TYPE,
		COLUMN_POSITION,
		COLUMN_VIEW_DISTANCE
	};

#define STRING_CHECK			"��"
#define STRING_ID				"���"
#define STRING_GUID				"GUID"
#define STRING_NAME				"����"
#define STRING_CREATOR			"������"
#define	STRING_CREATE_TIME		"����ʱ��"
#define STRING_TYPE				"����"
#define STRING_POSITION			"λ��"
#define STRING_VIEW_DISTANCE	"���Ӿ���"

public:
	// ��ʼ���ؼ�
	void InitControl();

	// �󶨵���ͷ
	void BindToHeader();

	// �󶨵�����
	void BindToReport( CString strCondit = "" );

private:
	//�ؼ�����
	CXTPReportControl	m_wndReportCtrl;
	CComboBox			m_cmbFileds;
	CEdit				m_strValue;
	CXTPButton			m_btnSelect;
	CXTPButton			m_btnLoad;
	CXTPButton			m_btnRefresh;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnFilter();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedRbtnTangall();
	afx_msg void OnBnClickedRbtnTangcancel();
};
