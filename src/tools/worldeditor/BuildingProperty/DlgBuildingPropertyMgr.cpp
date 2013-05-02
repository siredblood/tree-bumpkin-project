#include "pch.hpp"
#include "DlgBuildingPropertyMgr.h"
#include "GeneralClass/Common.h"
#include "CameraTravel/CustomWorldCamera.h"
//#include "worldeditor/Dialogs/MessageRecord.h"
#include "BuildingScheme/MessageRecord.h"
#include "BuildingPropertyMgr.h"

std::auto_ptr<CDlgBuildingPropertyMgr> CDlgBuildingPropertyMgr::s_pInstance;

IMPLEMENT_DYNAMIC(CDlgBuildingPropertyMgr, CXTResizeDialog)

CDlgBuildingPropertyMgr::CDlgBuildingPropertyMgr(CWnd* pParent /*=NULL*/)
: CXTResizeDialog(CDlgBuildingPropertyMgr::IDD, pParent)
{
}

CDlgBuildingPropertyMgr::~CDlgBuildingPropertyMgr(void)
{
}

CDlgBuildingPropertyMgr &CDlgBuildingPropertyMgr::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgBuildingPropertyMgr> pDlg( new CDlgBuildingPropertyMgr() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgBuildingPropertyMgr::IDD );
	}

	return *s_pInstance;
}

BEGIN_MESSAGE_MAP(CDlgBuildingPropertyMgr, CXTResizeDialog)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_MULTIPROGRIDVIEW, &CDlgBuildingPropertyMgr::OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_MULTIPROGRIDVIEW, &CDlgBuildingPropertyMgr::OnReportItemDBClick)
	ON_BN_CLICKED(IDC_BUTTON_1, &CDlgBuildingPropertyMgr::OnReflesh)
	ON_BN_CLICKED(IDC_BUTTON_2, &CDlgBuildingPropertyMgr::OnGotoTarget)
	ON_BN_CLICKED(IDC_BUTTON_3, &CDlgBuildingPropertyMgr::OnModify)
	ON_BN_CLICKED(IDC_BUTTON_4, &CDlgBuildingPropertyMgr::OnDelete)
	ON_BN_CLICKED(IDC_RBTN_GETALL, &CDlgBuildingPropertyMgr::OnGetAll)
	ON_BN_CLICKED(IDC_RBTN_CANCELALL, &CDlgBuildingPropertyMgr::OnCancelAll)
END_MESSAGE_MAP()

void CDlgBuildingPropertyMgr::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MULTIPROGRIDVIEW, m_wndProGridView);
	DDX_Control(pDX, IDC_BUTTON_1, m_button1);
	DDX_Control(pDX, IDC_BUTTON_2, m_button2);
	DDX_Control(pDX, IDC_BUTTON_3, m_button3);
	DDX_Control(pDX, IDC_BUTTON_4, m_button4);
	DDX_Control(pDX, IDC_RBTN_GETALL, m_rbtnAll);
	DDX_Control(pDX, IDC_RBTN_CANCELALL, m_rbtnCancle);
}

BOOL CDlgBuildingPropertyMgr::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();
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

	SetResize(IDC_RBTN_GETALL, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_RBTN_CANCELALL, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	SetResize(IDC_STI_LIANGTYPE3, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_EDIT_FILTER, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	//////////////////////////////////////////////////////////////////////////

	if (m_edtFilterEdit.GetSafeHwnd() == NULL)
	{
		m_edtFilterEdit.SubclassDlgItem(IDC_EDIT_FILTER, this);
		m_wndProGridView.GetColumns()->GetReportHeader()->SetFilterEditCtrl(&m_edtFilterEdit);
	}

	this->SetWindowText( "属性管理" );
	
	m_button1.SetWindowText("刷新");
	m_button2.SetWindowText("定位");
	m_button3.SetWindowText("修改");
	m_button4.SetWindowText("删除");
	
	m_wndProGridView.AddColumn( new CXTPReportColumn(0, "√", 20) );
	std::vector<std::string> vColumns;
	CBuildingPropertyMgr::Instance().GetColumns(vColumns);
	for(size_t i=0; i<vColumns.size(); i++){
		m_wndProGridView.AddColumn( new CXTPReportColumn(i+1, vColumns[i].c_str(), 100) );
	}
	
	for(size_t i=0; i<vColumns.size()+1; i++)
	{
		m_wndProGridView.GetColumns()->GetAt(i)->SetAllowDrag( false );
		m_wndProGridView.GetColumns()->GetAt(i)->SetSortable( false );
		if(i>3)
			m_wndProGridView.GetColumns()->GetAt(i)->GetEditOptions()->m_bAllowEdit = true;
		else
			m_wndProGridView.GetColumns()->GetAt(i)->GetEditOptions()->m_bAllowEdit = false;
	}
	
	//更新列表
	UpdateReport();
	
	m_iSelRow = -1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgBuildingPropertyMgr::OnClose()
{
	DestroyWindow();
	std::auto_ptr<CDlgBuildingPropertyMgr>	pDlg( s_pInstance );
	//CXTResizeDialog::OnClose();
}

void CDlgBuildingPropertyMgr::UpdateReport()
{
	//m_wndProGridView.ResetContent();
	m_wndProGridView.GetRecords()->RemoveAll();
	std::vector<LinkedStringMap> vProperties;
	CBuildingPropertyMgr::Instance().Load(vProperties);
	for(size_t i=0; i<vProperties.size(); i++)
	{

		CXTPReportRecord* pRecord = m_wndProGridView.AddRecord(new CXTPReportRecord());
		pRecord->AddItem( new CMessageRecordItemCheck(FALSE) );
		// 倒叙访问
		for(LinkedStringMap::reverse_iterator citr=vProperties[i].rbegin();
			citr!=vProperties[i].rend(); ++citr)
		{
			pRecord->AddItem( new CXTPReportRecordItemText((*citr).second.c_str()) );
		}
	}
	
	m_wndProGridView.Populate();
	m_wndProGridView.AllowEdit(FALSE);
	
	//RefreshTotalRecordMsg();
}

void CDlgBuildingPropertyMgr::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
	{
		m_iSelRow = -1;
		return;
	}

	m_iSelRow = pItemNotify->pRow->GetIndex();
}

void CDlgBuildingPropertyMgr::OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (pItemNotify->pRow)
	{
		int iSelRow = pItemNotify->pRow->GetIndex();
		CString strGuid = pItemNotify->pRow->GetRecord()->GetItem(2)->GetCaption(0);//找到第3列(GUID)的记录
		CString strPos = pItemNotify->pRow->GetRecord()->GetItem(3)->GetCaption(0);//找到第4列(POS)的记录
		Vector3 dir = Moo::rc().invView().applyToUnitAxisVector(2);
		Vector3 vPos = ConvertStrToVec3(strPos.GetBuffer(0));
		Vector3 tarpos = vPos - dir * 5.f;
		CCustomWorldCamera::Instance().TeleportCamera( tarpos, dir );
	}
}

void CDlgBuildingPropertyMgr::OnReflesh()
{
	UpdateReport();
}

void CDlgBuildingPropertyMgr::OnGotoTarget()
{
	if(m_iSelRow==-1)
		return;
	
	Vector3 dir = Moo::rc().invView().applyToUnitAxisVector(2);
	//找到第4列(POS)的记录
	CString strPos = m_wndProGridView.GetRecords()->GetAt(m_iSelRow)->GetItem(3)->GetCaption(0);
	Vector3 vPos = ConvertStrToVec3(strPos.GetBuffer(0));
	Vector3 tarpos = vPos - dir * 5.0f;
	
	CCustomWorldCamera::Instance().TeleportCamera( tarpos, dir );
}

void CDlgBuildingPropertyMgr::OnDelete()
{
	CString strBtnName;
	m_button4.GetWindowText( strBtnName );
	if(strBtnName=="取消")
	{
		UpdateReport();
		m_button3.SetWindowText("修改");
		m_button4.SetWindowText("删除");
		m_button1.EnableWindow(TRUE);
		m_button2.EnableWindow(TRUE);
	}
	else
	{
		
		if (MessageBox("您确定要删除此属性吗？","删除警告",MB_OKCANCEL)!=IDOK)
			return;
		std::vector<std::string> vIds;
		CXTPReportRecords *pRecords = m_wndProGridView.GetRecords();
		int iRecount = pRecords->GetCount();
		for(int i=0; i<iRecount; i++)
		{
			if( pRecords->GetAt(i)->GetItem(0)->IsChecked() )
			{
				CString strId = pRecords->GetAt(i)->GetItem(1)->GetCaption(0);
				vIds.push_back(strId.GetBuffer(0));
			}
		}
		if(CBuildingPropertyMgr::Instance().Delete(vIds)){
			AfxMessageBox("删除成功");
		}else{
			AfxMessageBox("删除失败");
		}
		
		UpdateReport();
	}
}

void CDlgBuildingPropertyMgr::OnModify()
{
	CString strBtnName;
	m_button3.GetWindowText( strBtnName );
	if(strBtnName=="修改")
	{
		bool bIsCheck = false;
		int iRc=m_wndProGridView.GetRecords()->GetCount();

		m_wndProGridView.AllowEdit(TRUE);
		for (int i=0;i<iRc;i++)
		{
			if (m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->IsChecked())
			{
				m_wndProGridView.GetRecords()->GetAt(i)->SetEditable(TRUE);
				bIsCheck=true;
			}
			else
				m_wndProGridView.GetRecords()->GetAt(i)->SetEditable(FALSE);
		}
		if (!bIsCheck)
		{
			int iCurSel = m_iSelRow;
			UpdateReport();
			if(iCurSel!=-1)
			{
				CXTPReportRows *pRows =  m_wndProGridView.GetRows();
				pRows->GetAt(iCurSel)->SetSelected(true);
				m_wndProGridView.SetFocusedRow(pRows->GetAt(iCurSel));
				m_iSelRow = iCurSel;
			}

			//m_wndProGridView.GetColumns()->GetAt(0)->GetEditOptions()->m_bAllowEdit = true;
			return;
		}	
		m_button3.SetWindowText("保存");
		m_button4.SetWindowText("取消");
		m_button1.EnableWindow(FALSE);
		m_button2.EnableWindow(FALSE);
		
	}else{

		CXTPReportRows *pRows =  m_wndProGridView.GetRows();
		CXTPReportRecord *pRecord = NULL;
		int iRowCount = pRows->GetCount();
		std::vector<LinkedStringMap> vProperties;

		std::vector<std::string> vColumns;
		for(int i=1; i<m_wndProGridView.GetColumns()->GetCount(); i++){
			CString strCol = m_wndProGridView.GetColumns()->GetAt(i)->GetCaption();
			vColumns.push_back(strCol.GetBuffer());
		}

		for(int i=0; i<iRowCount; i++)
		{
			pRecord = pRows->GetAt(i)->GetRecord();
			if(pRecord->GetItem(0)->IsChecked())
			{
				LinkedStringMap mapProperty;
				for(size_t j=0; j<vColumns.size(); ++j){
					CString strVal = pRecord->GetItem(j+1)->GetCaption(0);
					mapProperty.insert(std::make_pair<std::string, std::string>(vColumns[j], strVal.GetBuffer(0)));
				}
				vProperties.push_back(mapProperty);
			}
		}

		if(vProperties.size()>0){
			if(CBuildingPropertyMgr::Instance().Save(vProperties)){
				AfxMessageBox("保存成功");
			}else{
				AfxMessageBox("保存失败");
			}
		}

		UpdateReport();
		
		m_button3.SetWindowText("修改");
		m_button4.SetWindowText("删除");
		m_button1.EnableWindow(TRUE);
		m_button2.EnableWindow(TRUE);
	}

}

void CDlgBuildingPropertyMgr::OnGetAll()
{
	for ( int i = 0; i < m_wndProGridView.GetRecords()->GetCount(); i++ )
	{
		m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(TRUE);
	}
	m_wndProGridView.Populate();
}

void CDlgBuildingPropertyMgr::OnCancelAll()
{
	for ( int i = 0; i < m_wndProGridView.GetRecords()->GetCount(); i++ )
	{
		m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(FALSE);
	}
	m_wndProGridView.Populate();
}

void CDlgBuildingPropertyMgr::OnOK()
{

}