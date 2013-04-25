// DlgMarkLoad.cpp : 实现文件
//

#include "pch.hpp"
#include "DlgMarkLoad.h"
#include "MarkManage.h"
#include "GeneralClass/Common.h"
#include "BLogicLib/BllHelper.h"
//#include "worldeditor/Dialogs/MessageRecord.h"
#include "BuildingScheme/MessageRecord.h"


std::auto_ptr<CDlgMarkLoad> CDlgMarkLoad::s_pInstance;

// CDlgMarkLoad 对话框

IMPLEMENT_DYNAMIC(CDlgMarkLoad, CXTPResizeDialog)

CDlgMarkLoad::CDlgMarkLoad(CWnd* pParent /*=NULL*/)
	: CXTPResizeDialog(CDlgMarkLoad::IDD, pParent)
{

}

CDlgMarkLoad::~CDlgMarkLoad()
{
}

CDlgMarkLoad &CDlgMarkLoad::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgMarkLoad> pDlg( new CDlgMarkLoad() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgMarkLoad::IDD );
	}

	return *s_pInstance;
}

void CDlgMarkLoad::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TANG_LINELIST, m_wndReportCtrl);
	DDX_Control(pDX, IDC_CMB_TANGFIELDS, m_cmbFileds);
	DDX_Control(pDX, IDC_EDT_TANGCONDITION, m_strValue);
	DDX_Control(pDX, IDC_BTN_TANGSELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BTN_TANGLOADLINE, m_btnLoad);
	DDX_Control(pDX, IDC_BTN_REFRESHLINE, m_btnRefresh);
}


BEGIN_MESSAGE_MAP(CDlgMarkLoad, CXTPResizeDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_TANGSELECT, &CDlgMarkLoad::OnBnClickedBtnFilter)
	ON_BN_CLICKED(IDC_BTN_TANGLOADLINE, &CDlgMarkLoad::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_REFRESHLINE, &CDlgMarkLoad::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_RBTN_TANGALL, &CDlgMarkLoad::OnBnClickedRbtnTangall)
	ON_BN_CLICKED(IDC_RBTN_TANGCANCEL, &CDlgMarkLoad::OnBnClickedRbtnTangcancel)
END_MESSAGE_MAP()


// CDlgMarkLoad 消息处理程序

BOOL CDlgMarkLoad::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitControl();
	BindToHeader();
	BindToReport();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgMarkLoad::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CXTPResizeDialog::OnOK();
}

void CDlgMarkLoad::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CXTPResizeDialog::OnCancel();
}

void CDlgMarkLoad::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CXTPResizeDialog::OnClose();
	DestroyWindow();
	std::auto_ptr<CDlgMarkLoad>	pDlg( s_pInstance );
}

void CDlgMarkLoad::InitControl()
{
	m_wndReportCtrl.GetReportHeader()->AllowColumnRemove(FALSE);//防止组被拖走
	m_wndReportCtrl.GetReportHeader()->AllowColumnReorder(FALSE);//防止表头移动
	m_wndReportCtrl.GetReportHeader()->AllowColumnSort(FALSE);//禁止记录项排序
	m_wndReportCtrl.GetPaintManager()->m_clrHeaderRowsDivider = RGB(255,0,0);
	m_wndReportCtrl.GetPaintManager()->m_clrFooterRowsDivider = RGB(0,0,255);
	m_wndReportCtrl.GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2003);
	m_wndReportCtrl.GetPaintManager()->SetGridStyle(TRUE, xtpReportGridLargeDots);

	m_wndReportCtrl.FocusSubItems(TRUE);	

	SetResize(IDC_RBTN_TANGALL, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_RBTN_TANGCANCEL, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_TANG_LINELIST, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_CMB_TANGFIELDS, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_EDT_TANGCONDITION, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BTN_TANGSELECT, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BTN_TANGLOADLINE, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BTN_REFRESHLINE, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);

	this->SetWindowText("加载标注");
}

void CDlgMarkLoad::OnBnClickedBtnFilter()
{
	CString strCondit, strItem, strValue;
	GetDlgItem( IDC_CMB_TANGFIELDS )->GetWindowText( strItem );
	GetDlgItem( IDC_EDT_TANGCONDITION )->GetWindowText( strValue );
	strCondit = "and 所属目标='" + g_strImportantTarget + "' and "+ strItem + " like '%" + strValue + "%'";

	this->BindToReport( strCondit );
}

void CDlgMarkLoad::OnBnClickedBtnLoad()
{
	CXTPReportRecords *pRecords = m_wndReportCtrl.GetRecords();
	int iCounts = pRecords->GetCount();
	CString strPos, strViewDis;
	for( int i=0; i<iCounts; ++i )
	{
		if( !pRecords->GetAt( i )->GetItem( COLUMN_CHECK)->IsChecked() )
			continue;

		MARKDATA markdata;
		markdata.strGUID = pRecords->GetAt( i )->GetItem( COLUMN_GUID )->GetCaption( 0 ).GetBuffer( 0 );
		markdata.strText = pRecords->GetAt( i )->GetItem( COLUMN_NAME )->GetCaption( 0 ).GetBuffer( 0 );
		markdata.strCreator = pRecords->GetAt( i )->GetItem( COLUMN_CREATOR )->GetCaption( 0 ).GetBuffer( 0 );
		markdata.strCreateTime = pRecords->GetAt( i )->GetItem( COLUMN_CREATE_TIME )->GetCaption( 0 ).GetBuffer( 0 );
		markdata.strType = pRecords->GetAt( i )->GetItem( COLUMN_TYPE )->GetCaption( 0 ).GetBuffer( 0 );
		strPos = pRecords->GetAt( i )->GetItem( COLUMN_POSITION )->GetCaption( 0 );
		strViewDis = pRecords->GetAt( i )->GetItem( COLUMN_VIEW_DISTANCE )->GetCaption( 0 );
		markdata.pos = ConvertStrToVec3( strPos.GetBuffer(0) );
		markdata.fViewDist = (float)atof( strViewDis.GetBuffer() );
		markdata.bHaveObject = false;

		CMarkManage::Instance().AddMarkMessage( markdata );
	}
}

void CDlgMarkLoad::OnBnClickedBtnRefresh()
{
	BindToReport();
}

void CDlgMarkLoad::BindToHeader()
{
	CXTPReportColumn* pColumnCheckBox;
	pColumnCheckBox = m_wndReportCtrl.AddColumn(
		new CXTPReportColumn( COLUMN_CHECK, STRING_CHECK, 30));		
	pColumnCheckBox->GetEditOptions()->m_bAllowEdit = TRUE;

	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_ID, STRING_ID, 30 ));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_GUID, STRING_GUID, 100 ));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_NAME, STRING_NAME, 100 ));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_CREATOR, STRING_CREATOR, 100 ));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_CREATE_TIME, STRING_CREATE_TIME, 100 ));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_TYPE, STRING_TYPE, 100));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_POSITION, STRING_POSITION, 100));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_VIEW_DISTANCE, STRING_VIEW_DISTANCE, 100));
	//m_wndReportCtrl.AddColumn(new CXTPReportColumn( COLUMN_HAVE_OBJECT, STRING_HAVE_OBJECT, 100));

	m_cmbFileds.InsertString( 0, STRING_GUID );
	m_cmbFileds.InsertString( 1, STRING_NAME );
	m_cmbFileds.InsertString( 2, STRING_CREATOR );
	m_cmbFileds.SetCurSel( 0 );
}

void CDlgMarkLoad::BindToReport( CString strCondit /* = */ )
{
	m_wndReportCtrl.ResetContent();

	CLableMarker lableMark;
	std::vector<LABLESTRUCT> dataLables;
	if( strCondit.IsEmpty() )
	{
		dataLables = lableMark.LoadLableMark( g_strImportantTarget.GetBuffer(0) );
	}
	else
	{
		lableMark.LoadMarks( strCondit.GetBuffer(), dataLables );
	}
	int index = 1;

	for ( std::vector <LABLESTRUCT>::iterator lable = dataLables.begin(); lable != dataLables.end(); lable++ )//加载信息标注
	{
		CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord( new CXTPReportRecord() );
		pRecord->AddItem( new CMessageRecordItemCheck(FALSE) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( index++ ) );
		pRecord->AddItem( new CXTPReportRecordItemText( lable->strGUID.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( lable->strText.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( lable->strCreator.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( lable->strCreatTime.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( lable->strType.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( lable->strPos.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( lable->fEyeable, "%.2f" ) );
	}

	m_wndReportCtrl.Populate();
}

void CDlgMarkLoad::OnBnClickedRbtnTangall()
{
	for (int i=0;i<m_wndReportCtrl.GetRecords()->GetCount();i++)
	{
		m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(TRUE);
	}
	m_wndReportCtrl.Populate();
}

void CDlgMarkLoad::OnBnClickedRbtnTangcancel()
{
	for (int i=0;i<m_wndReportCtrl.GetRecords()->GetCount();i++)
	{
		m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(FALSE);
	}
	m_wndReportCtrl.Populate();
}