#include "pch.hpp"
#include "DlgUDOManager.h"
#include "BLogicLib/BllHelper.h"
#include "worldeditor/gui/Customs/BaseDlg/MessageRecord.h"
#include "worldeditor/CameraTravel/CustomWorldCamera.h"
#include "worldeditor/UDOController/UDOManager.h"
#include "worldeditor/UDOController/UDOController.hpp"
#include "worldeditor/UDOController/Fly.hpp"
#include "worldeditor/UDOController/Dialog/DlgUDONode.h"

IMPLEMENT_DYNAMIC(CDlgUDOManager, CXTPResizeDialog)

std::auto_ptr<CDlgUDOManager> CDlgUDOManager::s_pInstance;

namespace
{
	const LPCTSTR STRING_ID		= "编号";
	const LPCTSTR STRING_NAME   = "名称";
	const LPCTSTR STRING_SPEED	= "速度";
	const LPCTSTR STRING_NODEID	= "节点ID";
}

CDlgUDOManager::CDlgUDOManager()
{
}

CDlgUDOManager::~CDlgUDOManager()
{

}

CDlgUDOManager &CDlgUDOManager::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgUDOManager> pDlg( new CDlgUDOManager() );
		s_pInstance = pDlg;
		s_pInstance->Create( IDD_BASEREPORT2_DLG );
	}

	return *s_pInstance;
}

void CDlgUDOManager::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MULTIPROGRIDVIEW, m_wndProGridView);
	DDX_Control(pDX, IDC_BUTTON_1, m_button1);
	DDX_Control(pDX, IDC_BUTTON_2, m_button2);
	DDX_Control(pDX, IDC_BUTTON_3, m_button3);
	DDX_Control(pDX, IDC_BUTTON_4, m_button4);
	DDX_Control(pDX, IDC_BUTTON_5, m_button5);
	DDX_Control(pDX, IDC_BUTTON_6, m_button6);
	DDX_Control(pDX, IDC_BUTTON_7, m_button7);
}

BEGIN_MESSAGE_MAP(CDlgUDOManager, CXTPResizeDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_4, &CDlgUDOManager::OnBeginTravel)
	ON_BN_CLICKED(IDC_BUTTON_3, &CDlgUDOManager::OnCreatPath)
	ON_BN_CLICKED(IDC_BUTTON_2, &CDlgUDOManager::OnDeletePath)
	ON_BN_CLICKED(IDC_BUTTON_1, &CDlgUDOManager::OnEditPathNode)
	ON_NOTIFY(XTP_NM_REPORT_PREVIEWKEYDOWN, IDC_MULTIPROGRIDVIEW, &CDlgUDOManager::OnNMReturnReport)
END_MESSAGE_MAP()


BOOL CDlgUDOManager::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	this->SetWindowText( "路径管理" );

	// 初始化控件
	InitControl();

	UpdateReport();

	return TRUE;
}

void CDlgUDOManager::OnClose()
{
	DestroyWindow();

	std::auto_ptr<CDlgUDOManager> pDlg( s_pInstance );

	//CBaseReportDlg::OnClose();
}


void CDlgUDOManager::UpdateReport()
{
	m_wndProGridView.ResetContent();

	std::vector<UDOCamera> vUDOCamera;
	CUDOManager::Instance().GetAllUdoCamera( vUDOCamera );

	std::size_t iSize = vUDOCamera.size();
	for( std::size_t i=0; i<iSize; i++ )
	{
		UDOCamera &udoCamera = vUDOCamera[i];

		CXTPReportRecord* pRecord = m_wndProGridView.AddRecord( new CXTPReportRecord() );
		//pRecord->AddItem( new CMessageRecordItemCheck(FALSE) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( udoCamera.id ) );
		pRecord->AddItem( new CXTPReportRecordItemText( udoCamera.strName.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( udoCamera.fSpeed, "%.2f" ) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( udoCamera.iNodeid ) );
	}

	m_wndProGridView.Populate();
}

void CDlgUDOManager::OnBeginTravel()
{
	std::vector<UDOCamera> vItem;
	GetSelectedItems( vItem );
	if( vItem.size() != 1)
	{
		MessageBox( "请选择一条记录！", "提示", MB_OK );
		return;
	}

	if( vItem.begin()->iNodeid < 0 ) // 没有节点
		return;

	bool bDiffer;
	int iRes = MessageBox( "路径是否按照统一的速度浏览", "提示", MB_YESNO );
	if( iRes == IDYES )
		bDiffer = false;
	else if( iRes == IDNO )
		bDiffer = true;
	else
		return ;

	UDOController::instance().Fly( *vItem.begin(), bDiffer );

	this->ShowWindow( SW_SHOWMINIMIZED );
}

void CDlgUDOManager::OnCreatPath()
{
	CString strBtnName;
	m_button3.GetWindowText(strBtnName);
	if(strBtnName=="新建")
	{
		CXTPReportRecord* pRecord = m_wndProGridView.AddRecord( new CXTPReportRecord() );

		pRecord->AddItem( new CXTPReportRecordItemNumber( -1 ) );
		pRecord->AddItem( new CXTPReportRecordItemText( "" ) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( 2.0 ) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( -1 ) );
		m_button2.SetWindowText("取消");
		m_button3.SetWindowText("保存");
		m_button1.EnableWindow( FALSE );
		m_button4.EnableWindow( FALSE );
	}
	else
	{
		EditUpdate();	

		m_button3.SetWindowText("新建");
		m_button2.SetWindowText("删除");
		m_button1.EnableWindow( TRUE );
		m_button4.EnableWindow( TRUE );
	}

	m_wndProGridView.Populate();
}

void CDlgUDOManager::EditUpdate()
{
	CXTPReportRecords *pRecords =  m_wndProGridView.GetRecords();
	CXTPReportRecord *pRecord;

	CString strPathID, strName, strSpeed, strNodeid;
	double fSpeed;
	UDOCamera udoCamera;

	int iCount = pRecords->GetCount();
	for( int i=0; i<iCount; i++ )
	{
		pRecord = pRecords->GetAt(i);
		strPathID = pRecord->GetItem( COLUMN_ID )->GetCaption(0);
		strName = pRecord->GetItem( COLUMN_NAME )->GetCaption(0);
		strSpeed = pRecord->GetItem( COLUMN_SPEED )->GetCaption(0);
		strNodeid = pRecord->GetItem( COLUMN_NODEID )->GetCaption(0);
		udoCamera.id = atoi( strPathID.Trim() );
		udoCamera.strName = strName.Trim().GetBuffer(0);
		fSpeed = atof( strSpeed.Trim() );
		udoCamera.fSpeed = fSpeed < MIN_SPEED ? MIN_SPEED : (float)fSpeed; 
		udoCamera.iNodeid = atoi( strNodeid.Trim() );

		//修改数据库
		if( udoCamera.id < 0 )
			CUDOManager::Instance().AddUdoCamera( udoCamera );
		else
			CUDOManager::Instance().UpdateUdoCamera( udoCamera );
	}

	UpdateReport();
}

void CDlgUDOManager::OnDeletePath()
{
	CString strOperation;
	m_button2.GetWindowText(strOperation);
	if(strOperation=="取消")
	{
		m_button3.SetWindowText( "新建" );
		m_button2.SetWindowText( "删除" );
		m_button1.EnableWindow( TRUE );
		m_button4.EnableWindow( TRUE );
	}
	else
	{
		std::vector<UDOCamera> vItem;
		GetSelectedItems( vItem );
		if( !vItem.empty() )
		{
			if( MessageBox("删除后不能再恢复，确定删除吗？","提示", MB_YESNO)==IDYES)
			{
				for( std::size_t j=0; j<vItem.size(); ++j )
				{
					CUDOManager::Instance().DelUdoCamera( vItem[j].id );
					UDOController::instance().delNodesFromDB( vItem[j].iNodeid );
				}
			}
		}
		else
			MessageBox( "请选择记录", "提示", MB_OK );
	}
	UpdateReport();
}

void CDlgUDOManager::OnEditPathNode()
{
	std::vector<UDOCamera> vItem;
	GetSelectedItems( vItem );
	if( vItem.size() != 1 )
	{
		MessageBox( "请选择一条记录", "提示", MB_OK );
		return ;
	}
	// 清空场景所有UDO对象，只支持一条路径编辑
	UDOController::instance().clearUdo();

	// 获取节点的父ID
	UDOCamera udoCamera;
	CUDOManager::Instance().GetUdoCamera( vItem.begin()->id, udoCamera );

	if( udoCamera.iNodeid < 0 )// 没有子节点
	{
		::MessageBox( NULL, "当前节点为空，请在三维场景点击鼠标左键放置第一个节点", "提示", MB_OK );

		UDOController::instance().setPID( udoCamera.id );
		UDOController::instance().setHandle( true );

		CDlgUDONode::Instance().SetPID( udoCamera.id );
		CDlgUDONode::Instance().ShowWindow( SW_SHOW );
	}
	else
	{
		UDOController::instance().setPID( udoCamera.id );
		UDOController::instance().makeUdoFromDB( udoCamera.id, udoCamera.iNodeid );

		CDlgUDONode::Instance().SetPID( udoCamera.id );
		CDlgUDONode::Instance().ShowWindow( SW_SHOW );
	}

	this->ShowWindow( SW_HIDE );
}

void CDlgUDOManager::OnOK()
{
	//CBaseReportDlg::OnOK();
}

void CDlgUDOManager::OnCancel()
{
	//CBaseReportDlg::OnCancel();
}

void CDlgUDOManager::GetSelectedItems( std::vector<UDOCamera> &vItems )
{
	CString strID, strPID, strName, strSpeed;
	float fSpeed;
	CXTPReportSelectedRows *pSelectedRows =  m_wndProGridView.GetSelectedRows();
	int iCounts = pSelectedRows->GetCount();

	for( int i=0; i<iCounts; ++i )
	{
		UDOCamera udoCamera;
		CXTPReportRecord *pRecord = pSelectedRows->GetAt( i )->GetRecord();

		strID = pRecord->GetItem(COLUMN_ID)->GetCaption(0);
		strPID = pRecord->GetItem(COLUMN_NODEID)->GetCaption(0);
		strName = pRecord->GetItem(COLUMN_NAME)->GetCaption(0);
		strSpeed = pRecord->GetItem(COLUMN_SPEED)->GetCaption(0);
		fSpeed = (float)atof( strSpeed.Trim() );
		udoCamera.id = atoi( strID.Trim() );
		udoCamera.strName = strName.Trim();
		udoCamera.fSpeed = fSpeed < 0.0f ? 0.0f : fSpeed;
		udoCamera.iNodeid = atoi( strPID.Trim() );

		vItems.push_back( udoCamera );
	}
}

void CDlgUDOManager::InitControl()
{
	XTThemeManager()->SetTheme(xtThemeOffice2003);
	CXTPPaintManager::SetTheme(xtpThemeOffice2003);

	m_button1.SetUseVisualStyle(TRUE);
	m_button2.SetUseVisualStyle(TRUE);
	m_button3.SetUseVisualStyle(TRUE);
	m_button4.SetUseVisualStyle(TRUE);
	m_button5.SetUseVisualStyle(TRUE);
	m_button6.SetUseVisualStyle(TRUE);
	m_button7.SetUseVisualStyle(TRUE);

	//报表初始化
	m_wndProGridView.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndProGridView.GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2003);
	m_wndProGridView.AllowEdit( TRUE );
	m_wndProGridView.EditOnClick(TRUE);

	SetResize(IDC_MULTIPROGRIDVIEW, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_1, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_2, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_3, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_4, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_5, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_6, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_BUTTON_7, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT);

	SetResize(IDC_STI_LIANGTYPE3, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_EDIT_FILTER, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	if (m_edtFilterEdit.GetSafeHwnd() == NULL)
	{
		m_edtFilterEdit.SubclassDlgItem(IDC_EDIT_FILTER, this);
		m_wndProGridView.GetColumns()->GetReportHeader()->SetFilterEditCtrl(&m_edtFilterEdit);
	}

	m_button4.SetWindowText("浏览");
	m_button3.SetWindowText("新建");
	m_button2.SetWindowText("删除");
	m_button1.SetWindowText("编辑节点");
	m_button5.ShowWindow( SW_HIDE );
	m_button6.ShowWindow( SW_HIDE );
	m_button7.ShowWindow( SW_HIDE );

	//m_wndProGridView.AddColumn( new CXTPReportColumn(COLUMN_CHECK, STRING_CHECK, 20) );
	m_wndProGridView.AddColumn( new CXTPReportColumn(COLUMN_ID, STRING_ID, 50) );
	m_wndProGridView.AddColumn( new CXTPReportColumn(COLUMN_NAME, STRING_NAME, 80) );
	m_wndProGridView.AddColumn( new CXTPReportColumn(COLUMN_SPEED, STRING_SPEED, 50) );
	CXTPReportColumn *pColumn = m_wndProGridView.AddColumn( new CXTPReportColumn(COLUMN_NODEID, STRING_NODEID, 50) );
	pColumn->SetVisible( FALSE );

	for( int i = COLUMN_ID; i <=COLUMN_NODEID; i++ )
	{
		m_wndProGridView.GetColumns()->GetAt(i)->SetAllowDrag( FALSE );
		m_wndProGridView.GetColumns()->GetAt(i)->SetSortable( FALSE );
	}
	m_wndProGridView.GetColumns()->GetAt(COLUMN_ID)->GetEditOptions()->m_bAllowEdit = FALSE;
	m_wndProGridView.AllowEdit(TRUE);
}

void CDlgUDOManager::OnNMReturnReport(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	NMKEY *pNMKey = ( NMKEY * )pNMHDR;
	if( pNMKey->nVKey == 13 )
	{
		// shit，要先更新报表数据
		m_wndProGridView.Populate();
		// 保存
		EditUpdate();
	}

	*pResult = 0;
}