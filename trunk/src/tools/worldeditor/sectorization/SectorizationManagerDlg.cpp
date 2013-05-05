// SectorizationManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pch.hpp"
#include "SectorizationManagerDlg.h"
#include "SectorizationManager.h"
#include "BuildingScheme/MessageRecord.h"
#include "GeneralClass/Common.h"

SectorizationManagerDlg* SectorizationManagerDlg::mInstance = NULL;

// SectorizationManagerDlg 对话框

IMPLEMENT_DYNAMIC(SectorizationManagerDlg, CDialog)

SectorizationManagerDlg::SectorizationManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SectorizationManagerDlg::IDD, pParent)
{

}

SectorizationManagerDlg::~SectorizationManagerDlg()
{
}

SectorizationManagerDlg* SectorizationManagerDlg::getInstance()
{
	if(mInstance==NULL)
	{
		mInstance = new SectorizationManagerDlg;
		mInstance->Create(IDD);
	}
	return mInstance;
}

void SectorizationManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	DDX_Control(pDX, IDC_BUTTON_DEL, m_btnDelete);
}


BEGIN_MESSAGE_MAP(SectorizationManagerDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &SectorizationManagerDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &SectorizationManagerDlg::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON3, &SectorizationManagerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// SectorizationManagerDlg 消息处理程序

BOOL SectorizationManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndReportCtrl.AddColumn(new CXTPReportColumn(0, _T("√"), 30, FALSE));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(1, _T("名称"), 30, TRUE));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(2, _T("视角坐标"), 50, TRUE));
	m_wndReportCtrl.AddColumn(new CXTPReportColumn(3, _T("视角方向"), 50, TRUE));

	m_wndReportCtrl.Populate();
	return TRUE;
}


void SectorizationManagerDlg::OnBnClickedButtonAdd()
{
	CString strBtnName;
	m_btnAdd.GetWindowText(strBtnName);
	if(strBtnName=="新建")
	{
		Vector3 camerapos = Moo::rc().invView().applyToOrigin();
		Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
		CString strpos = ConvertVec3ToStr(camerapos);
		CString strdir = ConvertVec3ToStr(cameradir);
		m_wndReportCtrl.AddRecord(new CMessageRecord(TRUE, "", strpos, strdir));

		int iRc= m_wndReportCtrl.GetRecords()->GetCount();

		m_wndReportCtrl.AllowEdit(TRUE);
		for (int i=0;i<iRc-1;i++)
		{
			m_wndReportCtrl.GetRecords()->GetAt(i)->SetEditable(FALSE);
		}
		m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->SetEditable(TRUE);

		m_btnAdd.SetWindowText("确定");
		m_btnDelete.EnableWindow(FALSE);
	}
	else
	{
		

		int iRc= m_wndReportCtrl.GetRecords()->GetCount();
		CString strName = m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->GetItem(1)->GetCaption(0);
		bool bSameName = false;
		for (int i=0;i<iRc-1;i++)
		{
			CString strOther = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(1)->GetCaption(0);
			if(strName==strOther)
			{
				bSameName = true;
			}
			//m_wndReportCtrl.GetRecords()->GetAt(i)->SetEditable(TRUE);
		}
		//m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->SetEditable(TRUE);
		//m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->GetItem(0)->SetChecked(FALSE);

		if(bSameName)
		{
			MessageBox("名字重复！","警告",MB_OK);
			return;
		}
		else
		{
			m_wndReportCtrl.AllowEdit(FALSE);
			for (int i=0;i<iRc;i++)
			{
				m_wndReportCtrl.GetRecords()->GetAt(i)->SetEditable(TRUE);
			}
			m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->GetItem(0)->SetChecked(FALSE);

			CString strName = m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->GetItem(1)->GetCaption(0);
			CString strPos = m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->GetItem(2)->GetCaption(0);
			CString strDir = m_wndReportCtrl.GetRecords()->GetAt(iRc-1)->GetItem(3)->GetCaption(0);

			Vector3 pos = ConvertStrToVec3( strPos.GetBuffer(0) );
			Vector3 dir = ConvertStrToVec3( strDir.GetBuffer(0) );

			SectorizationManager::getInstance()->addSectorization(strName, pos, dir);
			m_btnAdd.SetWindowText("新建");
			m_btnDelete.EnableWindow(TRUE);
		}
		
	}
	m_wndReportCtrl.Populate();
}

void SectorizationManagerDlg::OnBnClickedButtonDel()
{
	if (MessageBox("您确定要删除吗？","删除警告",MB_OKCANCEL)!=IDOK)
		return;

	int iCount = m_wndReportCtrl.GetRecords()->GetCount();
	for(int i=0; i<iCount; i++)
	{
		if( m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(0)->IsChecked() )
		{
			CString strName = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(1)->GetCaption(0);
			

			SectorizationManager::getInstance()->deleteSectorization(strName);
		}
	}

	showResult();
}

void SectorizationManagerDlg::OnBnClickedButton3()
{

	//当前视角
	Vector3 camerapos = Moo::rc().invView().applyToOrigin();
	Vector3 cameradir = Moo::rc().invView().applyToUnitAxisVector(2);
	CString strpos = ConvertVec3ToStr(camerapos);
	CString strdir = ConvertVec3ToStr(cameradir);

	int iCount = m_wndReportCtrl.GetRecords()->GetCount();
	for(int i=0; i<iCount; i++)
	{
		if( m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(0)->IsChecked() )
		{
			CString strName = m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(1)->GetCaption(0);
			m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(2)->SetCaption( strpos.GetBuffer(0) );
			m_wndReportCtrl.GetRecords()->GetAt(i)->GetItem(3)->SetCaption( strdir.GetBuffer(0) );

			SectorizationManager::getInstance()->editSectorizationViewport(strName, camerapos, cameradir);
		}
	}
	m_wndReportCtrl.Populate();
}

void SectorizationManagerDlg::showResult()
{
	m_wndReportCtrl.GetRecords()->RemoveAll();
	std::vector<SECTORIZATIONDATA> vData = SectorizationManager::getInstance()->getSectorizationData();

	std::vector<SECTORIZATIONDATA>::iterator itr = vData.begin();
	for(; itr!=vData.end(); itr++)
	{
		CString strpos = ConvertVec3ToStr( itr->viewpos );
		CString strdir = ConvertVec3ToStr( itr->viewdir );
		m_wndReportCtrl.AddRecord(new CMessageRecord(FALSE, itr->strName, strpos, strdir));
	}

	m_wndReportCtrl.Populate();
}


