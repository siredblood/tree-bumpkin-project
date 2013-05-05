#pragma once
#include "resource.h"
#include "afxwin.h"

// AddSectorizationObjectDlg �Ի���

class AddSectorizationObjectDlg : public CDialog
{
	DECLARE_DYNAMIC(AddSectorizationObjectDlg)

public:
	AddSectorizationObjectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AddSectorizationObjectDlg();

// �Ի�������
	enum { IDD = IDD_ADDSECTORIZATIONOBJECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	static AddSectorizationObjectDlg* mInstance;

	CComboBox m_cmbSectorization;

	std::vector<CString> m_vGuids;
public:
	static AddSectorizationObjectDlg* getInstance();

	void setSelectGuids( std::vector<CString> vGuids );

	afx_msg void OnBnClickedOk();
};
