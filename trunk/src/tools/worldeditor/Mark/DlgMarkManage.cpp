#include "pch.hpp"
#include "DlgMarkManage.h"
#include "mark/MarkObject.h"
#include "mark/MarkManage.h"
#include "GeneralClass/Common.h"
#include "CameraTravel/CustomWorldCamera.h"
//#include "worldeditor/Dialogs/MessageRecord.h"
#include "BuildingScheme/MessageRecord.h"

std::auto_ptr<CDlgMarkManage> CDlgMarkManage::s_pInstance;

IMPLEMENT_DYNAMIC(CDlgMarkManage, CXTResizeDialog)

CDlgMarkManage::CDlgMarkManage(CWnd* pParent /*=NULL*/)
: CXTResizeDialog(CDlgMarkManage::IDD, pParent)
{
}

CDlgMarkManage::~CDlgMarkManage(void)
{
}

CDlgMarkManage &CDlgMarkManage::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgMarkManage> pDlg( new CDlgMarkManage() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgMarkManage::IDD );
	}

	return *s_pInstance;
}

BEGIN_MESSAGE_MAP(CDlgMarkManage, CXTResizeDialog)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_MULTIPROGRIDVIEW, &CDlgMarkManage::OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_MULTIPROGRIDVIEW, &CDlgMarkManage::OnReportItemDBClick)
	ON_BN_CLICKED(IDC_BUTTON_1, &CDlgMarkManage::OnReflesh)
	ON_BN_CLICKED(IDC_BUTTON_2, &CDlgMarkManage::OnGotoTarget)
	ON_BN_CLICKED(IDC_BUTTON_3, &CDlgMarkManage::OnModify)
	ON_BN_CLICKED(IDC_BUTTON_4, &CDlgMarkManage::OnDelete)
	ON_BN_CLICKED(IDC_RBTN_GETALL, &CDlgMarkManage::OnGetAll)
	ON_BN_CLICKED(IDC_RBTN_CANCELALL, &CDlgMarkManage::OnCancelAll)
END_MESSAGE_MAP()

void CDlgMarkManage::DoDataExchange(CDataExchange* pDX)
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

BOOL CDlgMarkManage::OnInitDialog()
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

	this->SetWindowText( "标注管理" );
	
	m_button1.SetWindowText("刷新");
	m_button2.SetWindowText("定位");
	m_button3.SetWindowText("修改");
	m_button4.SetWindowText("删除");
	
	m_wndProGridView.AddColumn( new CXTPReportColumn(0, "√", 20) );
	m_wndProGridView.AddColumn( new CXTPReportColumn(1, "编号", 50));
	m_wndProGridView.AddColumn( new CXTPReportColumn(2, "GUID", 100));
	m_wndProGridView.AddColumn( new CXTPReportColumn(3, "标注", 150));
	m_wndProGridView.AddColumn( new CXTPReportColumn(4, "位置", 100));
	m_wndProGridView.AddColumn( new CXTPReportColumn(5, "创建者", 80));
	m_wndProGridView.AddColumn( new CXTPReportColumn(6, "创建时间", 100));
	m_wndProGridView.AddColumn( new CXTPReportColumn(7, "可视距离", 50));
	
	for(int i=0; i<8; i++)
	{
		m_wndProGridView.GetColumns()->GetAt(i)->SetAllowDrag( false );
		m_wndProGridView.GetColumns()->GetAt(i)->SetSortable( false );
		if(i==0 || i==3 || i==7)
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

void CDlgMarkManage::OnClose()
{
	DestroyWindow();
	std::auto_ptr<CDlgMarkManage>	pDlg( s_pInstance );
	//CXTResizeDialog::OnClose();
}

void CDlgMarkManage::UpdateReport()
{
	//m_wndProGridView.ResetContent();
	m_wndProGridView.GetRecords()->RemoveAll();
	m_vAllMarkData = CMarkObject::Instance().GetDrawMessage();
	int iSize = m_vAllMarkData.size();
	MARKDATA markitem;
	CString strPos;
	for(int i=0; i<iSize; i++)
	{
		markitem = m_vAllMarkData[i];
		CXTPReportRecord* pRecord = m_wndProGridView.AddRecord(new CXTPReportRecord());
		pRecord->AddItem( new CMessageRecordItemCheck(FALSE) );
		pRecord->AddItem( new CXTPReportRecordItemNumber(i+1) );
		pRecord->AddItem( new CXTPReportRecordItemText(markitem.strGUID.c_str()) );
		pRecord->AddItem( new CXTPReportRecordItemText(markitem.strText.c_str()) );
		strPos  = ConvertVec3ToStr( markitem.pos );
		pRecord->AddItem( new CXTPReportRecordItemText(strPos) );
		pRecord->AddItem( new CXTPReportRecordItemText(markitem.strCreator.c_str()) );
		pRecord->AddItem( new CXTPReportRecordItemText(markitem.strCreateTime.c_str()) );
		pRecord->AddItem( new CXTPReportRecordItemNumber(markitem.fViewDist) );
	}
	
	m_wndProGridView.Populate();
	m_wndProGridView.AllowEdit(FALSE);
	
	//RefreshTotalRecordMsg();
}

void CDlgMarkManage::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
	{
		m_iSelRow = -1;
		return;
	}

	m_iSelRow = pItemNotify->pRow->GetIndex();
}

void CDlgMarkManage::OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (pItemNotify->pRow)
	{
		int iSelRow = pItemNotify->pRow->GetIndex();
		CString strCompare = pItemNotify->pRow->GetRecord()->GetItem(2)->GetCaption(0);//找到第3列(GUID)的记录
		int iSizeData = m_vAllMarkData.size();
		Vector3 dir = Moo::rc().invView().applyToUnitAxisVector(2);
		Vector3 tarpos;
		for(int i = 0;i < iSizeData;++i)
		{
			if(!m_vAllMarkData[i].strGUID.compare(strCompare))
			{
				tarpos = m_vAllMarkData[i].pos - dir * 5.f;
				CCustomWorldCamera::Instance().TeleportCamera( tarpos, dir );
				break;
			}
		}
	}
}

void CDlgMarkManage::OnReflesh()
{
	UpdateReport();
}

void CDlgMarkManage::OnGotoTarget()
{
	if(m_iSelRow==-1)
		return;
	
	Vector3 dir = Moo::rc().invView().applyToUnitAxisVector(2);
	Vector3 tarpos = m_vAllMarkData[m_iSelRow].pos - dir * 5.0f;
	
	CCustomWorldCamera::Instance().TeleportCamera( tarpos, dir );
}

void CDlgMarkManage::OnDelete()
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
		
		if (MessageBox("您确定要删除此标注吗？","删除警告",MB_OKCANCEL)!=IDOK)
			return;
		//MARKDATA markdata;
		int iRecount = m_wndProGridView.GetRecords()->GetCount();
		for(int i=0; i<iRecount; i++)
		{
			if( m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->IsChecked() )
			{
				CMarkManage::Instance().DeleteMarkByGUID(m_vAllMarkData[i].strGUID);
				//CMarkObject::Instance().DeleteMark( markdata.strGUID );
			}
		}
		//markdata = m_vAllMarkData[m_iSelRow];
		//CMarkObject::Instance().DeleteMark( markdata.strGUID );
		
		UpdateReport();
	}
}

void CDlgMarkManage::OnModify()
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
		
	}
	else
	{
		CXTPReportRows *pRows =  m_wndProGridView.GetRows();
		CXTPReportRow *pItemRow;
		CXTPReportRecord *pRecord;
		CString strText, strGUID;
		float fViewDist=0.0f;
		int iRowCount = pRows->GetCount();
		int iMarkSize = m_vAllMarkData.size();

		std::vector<MARKDATA> vMarkData;
		for(int i=0; i<iRowCount; i++)
		{
			pItemRow = pRows->GetAt(i);
			pRecord = pItemRow->GetRecord();
			if(pRecord->GetItem(0)->IsChecked())
			{
				strGUID = pRecord->GetItem(2)->GetCaption(0);
				strText = pRecord->GetItem(3)->GetCaption(0);
				fViewDist=(float)atof(pRecord->GetItem(7)->GetCaption(0)) ;
				CMarkObject::Instance().ModifyMark( strGUID.GetBuffer(0), 
					strText.GetBuffer(0), fViewDist);
			}

		}
		CMarkManage::Instance().SaveMarks();

		UpdateReport();
		
		m_button3.SetWindowText("修改");
		m_button4.SetWindowText("删除");
		m_button1.EnableWindow(TRUE);
		m_button2.EnableWindow(TRUE);
	}

}

void CDlgMarkManage::OnGetAll()
{
	for ( int i = 0; i < m_wndProGridView.GetRecords()->GetCount(); i++ )
	{
		m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(TRUE);
	}
	m_wndProGridView.Populate();
}

void CDlgMarkManage::OnCancelAll()
{
	for ( int i = 0; i < m_wndProGridView.GetRecords()->GetCount(); i++ )
	{
		m_wndProGridView.GetRecords()->GetAt(i)->GetItem(0)->SetChecked(FALSE);
	}
	m_wndProGridView.Populate();
}

void CDlgMarkManage::OnOK()
{

}