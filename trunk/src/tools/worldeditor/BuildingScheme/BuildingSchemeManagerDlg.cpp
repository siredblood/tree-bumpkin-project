// BuildingManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pch.hpp"
#include "BuildingSchemeManagerDlg.h"
#include "buildingSchemeManager.h"
#include "MessageRecord.h"

// BuildingManagerDlg 对话框

BuildingSchemeManagerDlg* BuildingSchemeManagerDlg::mInstance=NULL;

IMPLEMENT_DYNAMIC(BuildingSchemeManagerDlg, CDialog)

BuildingSchemeManagerDlg::BuildingSchemeManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BuildingSchemeManagerDlg::IDD, pParent)
{

}

BuildingSchemeManagerDlg::~BuildingSchemeManagerDlg()
{
}

void BuildingSchemeManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);

}


BEGIN_MESSAGE_MAP(BuildingSchemeManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &BuildingSchemeManagerDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORTCTRL, &BuildingSchemeManagerDlg::OnReportItemDBClick)
END_MESSAGE_MAP()


// BuildingManagerDlg 消息处理程序

BOOL BuildingSchemeManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndReportCtrl.AddColumn(new CXTPReportColumn(0, _T("√"), 30, FALSE));
	CXTPReportColumn *pColumn = m_wndReportCtrl.AddColumn(new CXTPReportColumn(1, _T("方案"), 30, TRUE));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(2, _T("原模型"), 50, TRUE));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(3, _T("替换模型"), 50, TRUE));

	pColumn->SetVisible(FALSE);

	m_wndReportCtrl.ShowGroupBy();
	m_wndReportCtrl.GetColumns()->GetGroupsOrder()->Add(m_wndReportCtrl.GetColumns()->GetAt(1));

	m_wndReportCtrl.Populate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BuildingSchemeManagerDlg* BuildingSchemeManagerDlg::getInstance()
{
	if(mInstance==NULL)
	{
		mInstance = new BuildingSchemeManagerDlg;
		mInstance->Create(IDD);
	}
	return mInstance;
}

void BuildingSchemeManagerDlg::showResult()
{
	m_wndReportCtrl.GetRecords()->RemoveAll();
	std::map<CString, std::map<CString, CString>> vAllScheme = BuildingSchemeManager::getInstance()->getAllScheme();
	
	std::map<CString, std::map<CString, CString>>::iterator iter;

	std::map<CString, CString> list;
	CString strScheme, strOldModel,strNewModel;

	for(iter=vAllScheme.begin(); iter!=vAllScheme.end(); iter++)
	{
		strScheme = iter->first;
		list = iter->second;
		for(std::map<CString, CString>::iterator childiter=list.begin(); childiter!=list.end(); childiter++ )
		{
			strOldModel = childiter->first;
			strNewModel = childiter->second;
			m_wndReportCtrl.AddRecord(new CMessageRecord(FALSE, strScheme,strOldModel,strNewModel));
		}
	}
	m_wndReportCtrl.Populate();
}

void BuildingSchemeManagerDlg::OnBnClickedButton1()
{
	if (MessageBox("您确定要删除吗？","删除警告",MB_OKCANCEL)!=IDOK)
		return;

	int iCount = m_wndReportCtrl.GetRecords()->GetCount();
	for(int i=0; i<iCount; i++)
	{
		if( m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(0)->IsChecked() )
		{
			CString strScheme = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(1)->GetCaption(0);
			CString strOldModel = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(2)->GetCaption(0);
			
			BuildingSchemeManager::getInstance()->deleteScheme(strScheme, strOldModel);
		}
	}

	showResult();
}

void BuildingSchemeManagerDlg::OnReportItemDBClick( NMHDR * pNotifyStruct, LRESULT * result )
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (pItemNotify->pRow)
	{
		int iSelRow = pItemNotify->pRow->GetIndex();
		if(pItemNotify->pRow->GetRecord())
		{
			CString strModel = pItemNotify->pRow->GetRecord()->GetItem(2)->GetCaption(0);

			BuildingSchemeManager::getInstance()->locateToModel(strModel);
		}

	}
}
