// BaseInputDlg.cpp : ʵ���ļ�
//

#include "pch.hpp"
#include "BaseInputDlg.h"


// CBaseInputDlg �Ի���

IMPLEMENT_DYNAMIC(CBaseInputDlg, CDialog)

CBaseInputDlg::CBaseInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBaseInputDlg::IDD, pParent)
{

}

CBaseInputDlg::~CBaseInputDlg()
{
}

void CBaseInputDlg::DoDataExchange(CDataExchange* pDX)
{
CDialog::DoDataExchange(pDX);
DDX_Control(pDX, IDC_EDIT_INPUT, m_edtInput);
DDX_Control(pDX, IDC_STATIC_NAME, m_stName);
DDX_Control(pDX, IDOK, m_btnOK);
}


BEGIN_MESSAGE_MAP(CBaseInputDlg, CDialog)
END_MESSAGE_MAP()


// CBaseInputDlg ��Ϣ�������

BOOL CBaseInputDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edtInput.SetUseVisualStyle(TRUE);
	//m_btnOK.SetTheme(xtpButtonThemeOffice2003);
	m_btnOK.SetUseVisualStyle( TRUE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
