// BaseReportDlg.cpp : 实现文件
//

#include "pch.hpp"
#include "BaseReportDlg.h"
#include "worldeditor/framework/world_editor_app.hpp"


// CBaseReportDlg 对话框

IMPLEMENT_DYNAMIC(CBaseReportDlg, CDialogSampleDlgBase)

CBaseReportDlg::CBaseReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogSampleDlgBase(CBaseReportDlg::IDD, pParent)
{

}

CBaseReportDlg::~CBaseReportDlg()
{
}

void CBaseReportDlg::DoDataExchange(CDataExchange* pDX)
{
CDialogSampleDlgBase::DoDataExchange(pDX);
DDX_Control(pDX, IDC_MULTIPROGRIDVIEW, m_wndProGridView);
DDX_Control(pDX, IDC_BUTTON_1, m_button1);
DDX_Control(pDX, IDC_BUTTON_2, m_button2);
DDX_Control(pDX, IDC_BUTTON_3, m_button3);
DDX_Control(pDX, IDC_BUTTON_4, m_button4);
DDX_Control(pDX, IDC_BUTTON_5, m_button5);
DDX_Control(pDX, IDC_BUTTON_6, m_button6);
DDX_Control(pDX, IDC_BUTTON_7, m_button7);
DDX_Control(pDX, IDC_RBTN_GETALL, m_rbtnAll);
DDX_Control(pDX, IDC_RBTN_CANCELALL, m_rbtnCancle);
}


BEGIN_MESSAGE_MAP(CBaseReportDlg, CDialogSampleDlgBase)
	ON_BN_CLICKED(IDC_RBTN_GETALL, &CBaseReportDlg::OnGetAll)
	ON_BN_CLICKED(IDC_RBTN_CANCELALL, &CBaseReportDlg::OnCancelAll)
END_MESSAGE_MAP()


// CBaseReportDlg 消息处理程序

BOOL CBaseReportDlg::OnInitDialog()
{
	CXTPDialogBase<CXTResizeDialog>::OnInitDialog();


	XTThemeManager()->SetTheme(xtThemeOffice2003);
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);

	//m_button1.SetTheme(xtpButtonThemeOffice2003);
	//m_button2.SetTheme(xtpButtonThemeOffice2003);
	//m_button3.SetTheme(xtpButtonThemeOffice2003);
	//m_button4.SetTheme(xtpButtonThemeOffice2003);
	//m_button5.SetTheme(xtpButtonThemeOffice2003);
	//m_button6.SetTheme(xtpButtonThemeOffice2003);
	m_button1.SetUseVisualStyle(TRUE);
	m_button2.SetUseVisualStyle(TRUE);
	m_button3.SetUseVisualStyle(TRUE);
	m_button4.SetUseVisualStyle(TRUE);
	m_button5.SetUseVisualStyle(TRUE);
	m_button6.SetUseVisualStyle(TRUE);
	m_button7.SetUseVisualStyle(TRUE);
	//m_button1.SetUseVisualStyle(FALSE);
	//m_button2.SetUseVisualStyle(FALSE);
	//m_button3.SetUseVisualStyle(FALSE);
	//m_button4.SetUseVisualStyle(FALSE);
	//m_button5.SetUseVisualStyle(FALSE);
	//m_button6.SetUseVisualStyle(FALSE);
	//m_button7.SetUseVisualStyle(FALSE);

	m_rbtnAll.SetUseVisualStyle(TRUE);
	m_rbtnCancle.SetUseVisualStyle(TRUE);
	
	//报表初始化
	m_wndProGridView.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndProGridView.GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2003);
	m_wndProGridView.AllowEdit( TRUE );
	m_wndProGridView.EditOnClick(FALSE);

	SetResize(IDC_MULTIPROGRIDVIEW, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_1, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_2, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_3, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_4, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_5, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_6, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_7, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);

	SetResize(IDC_RBTN_GETALL, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_RBTN_CANCELALL, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	
	//////////////////////////////////////////////////////////////////////////
	SetResize(IDC_STI_LIANGTYPE3, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_EDIT_FILTER, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	//////////////////////////////////////////////////////////////////////////

	if (m_edtFilterEdit.GetSafeHwnd() == NULL)
	{
		m_edtFilterEdit.SubclassDlgItem(IDC_EDIT_FILTER, this);
		m_wndProGridView.GetColumns()->GetReportHeader()->SetFilterEditCtrl(&m_edtFilterEdit);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBaseReportDlg::OnGetAll()
{
	for ( int i = 0; i < m_wndProGridView.GetRecords()->GetCount(); i++ )
	{
		m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(TRUE);
	}
	m_wndProGridView.Populate();
}

void CBaseReportDlg::OnCancelAll()
{
	for ( int i = 0; i < m_wndProGridView.GetRecords()->GetCount(); i++ )
	{
		m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(FALSE);
	}
	m_wndProGridView.Populate();
}

void CBaseReportDlg::OnOK()
{

}