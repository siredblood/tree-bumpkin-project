// SectorizationObjManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pch.hpp"
#include "SectorizationObjManagerDlg.h"
#include "SectorizationManager.h"
#include "BuildingScheme/MessageRecord.h"

// SectorizationObjManagerDlg 对话框

IMPLEMENT_DYNAMIC(SectorizationObjManagerDlg, CDialog)

SectorizationObjManagerDlg::SectorizationObjManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SectorizationObjManagerDlg::IDD, pParent)
{

}

SectorizationObjManagerDlg::~SectorizationObjManagerDlg()
{
}

void SectorizationObjManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
}


BEGIN_MESSAGE_MAP(SectorizationObjManagerDlg, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORTCTRL, &SectorizationObjManagerDlg::OnReportItemDBClick)
	ON_BN_CLICKED(IDC_BUTTON1, &SectorizationObjManagerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// SectorizationObjManagerDlg 消息处理程序

BOOL SectorizationObjManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndReportCtrl.AddColumn(new CXTPReportColumn(0, _T("√"), 30, FALSE));
	CXTPReportColumn *pColumn = m_wndReportCtrl.AddColumn(new CXTPReportColumn(1, _T("分区"), 30, TRUE));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(2, _T("对象"), 50, TRUE));

	pColumn->SetVisible(FALSE);

	m_wndReportCtrl.ShowGroupBy();
	m_wndReportCtrl.GetColumns()->GetGroupsOrder()->Add(pColumn);

	m_wndReportCtrl.Populate();

	showResult();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void SectorizationObjManagerDlg::OnBnClickedButton1()
{
	if (MessageBox("您确定要删除吗？","删除警告",MB_OKCANCEL)!=IDOK)
		return;

	int iCount = m_wndReportCtrl.GetRecords()->GetCount();
	for(int i=0; i<iCount; i++)
	{
		if( m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(0)->IsChecked() )
		{
			CString strName = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(1)->GetCaption(0);
			CString strModel = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(2)->GetCaption(0);

			SectorizationManager::getInstance()->deleteSectorizationObject(strName, strModel);
		}
	}

	showResult();
}

void SectorizationObjManagerDlg::OnReportItemDBClick( NMHDR * pNotifyStruct, LRESULT * result )
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (pItemNotify->pRow)
	{
		int iSelRow = pItemNotify->pRow->GetIndex();
		if(pItemNotify->pRow->GetRecord())
		{
			CString strModel = pItemNotify->pRow->GetRecord()->GetItem(2)->GetCaption(0);

			SectorizationManager::getInstance()->locateToModel(strModel);
		}
		
	}
}

void SectorizationObjManagerDlg::showResult()
{
	m_wndReportCtrl.GetRecords()->RemoveAll();
	std::vector<SECTORIZATIONDATA> vData = SectorizationManager::getInstance()->getSectorizationData();
	std::vector<SECTORIZATIONDATA>::iterator itr = vData.begin();
	for(; itr!=vData.end(); itr++)
	{
		std::vector<CString>::iterator subitr = itr->vGuids.begin();
		for(; subitr!=itr->vGuids.end(); subitr++)
		{
			CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord( new CXTPReportRecord() );
			pRecord->AddItem( new CMessageRecordItemCheck(FALSE) );
			pRecord->AddItem( new CXTPReportRecordItemText( itr->strName ) );
			pRecord->AddItem( new CXTPReportRecordItemText( *subitr ) );
		}
	}
	m_wndReportCtrl.Populate();
}
