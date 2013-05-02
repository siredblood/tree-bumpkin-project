#pragma once
#include "resource.h"
#include <map>

// CDlgBuildingProperty

class CDlgBuildingProperty : public CXTResizeDialog
{
	DECLARE_DYNAMIC(CDlgBuildingProperty)

public:
	CDlgBuildingProperty(CWnd* pParent = NULL);   // ��׼���캯��
	static std::auto_ptr<CDlgBuildingProperty> s_pInstance;

public:
	virtual ~CDlgBuildingProperty();

	// �Ի�������
	enum { IDD = IDD_DLG_PROPERTY };

public:
	static CDlgBuildingProperty &Instance();

private:
	void resetPropertyGrid();

	CStatic m_propertyGrid;
	CXTPPropertyGrid m_wndGridGeneral;
	std::string m_strGuid;
	CXTPPropertyGridItem *m_pGridItemId;

public:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnGridNotify(WPARAM, LPARAM);
	afx_msg void OnClose();
};


