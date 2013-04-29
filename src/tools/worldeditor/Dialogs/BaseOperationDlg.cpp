// BaseOperationDlg.cpp : 实现文件
//

#include "pch.hpp"
#include "worldeditor/framework/world_editor_app.hpp"
#include "BaseOperationDlg.h"


// CBaseOperationDlg 对话框

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


// CBaseOperationDlg 消息处理程序

BOOL CBaseOperationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//m_btnOK.SetTheme(xtpButtonThemeOffice2003);
	//m_btnExit.SetTheme(xtpButtonThemeOffice2003);
	m_btnExit.SetUseVisualStyle( TRUE );
	m_btnOK.SetUseVisualStyle( TRUE );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
