// BaseOperationDlg.cpp : ʵ���ļ�
//

#include "pch.hpp"
#include "worldeditor/framework/world_editor_app.hpp"
#include "BaseOperationDlg.h"


// CBaseOperationDlg �Ի���

IMPLEMENT_DYNAMIC(CBaseOperationDlg, CDialog)

CBaseOperationDlg::CBaseOperationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseOperationDlg::IDD, pParent)
{

}

CBaseOperationDlg::~CBaseOperationDlg()
{
}

void CBaseOperationDlg::DoDataExchange(CDataExchange* pDX)
{
CDialog::DoDataExchange(pDX);
DDX_Control(pDX, IDC_COMBO_TYPE, m_combox);
DDX_Control(pDX, IDC_EDIT_VALUE, m_editbox);
DDX_Control(pDX, IDOK, m_btnOK);
DDX_Control(pDX, IDCANCEL, m_btnExit);
	}


BEGIN_MESSAGE_MAP(CBaseOperationDlg, CDialog)
END_MESSAGE_MAP()


// CBaseOperationDlg ��Ϣ�������

BOOL CBaseOperationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_btnOK.SetTheme(xtpButtonThemeOffice2003);
	//m_btnExit.SetTheme(xtpButtonThemeOffice2003);
	m_btnExit.SetUseVisualStyle( TRUE );
	m_btnOK.SetUseVisualStyle( TRUE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
