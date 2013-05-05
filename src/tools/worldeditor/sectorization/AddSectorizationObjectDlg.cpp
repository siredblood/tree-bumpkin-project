// AddSectorizationObjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pch.hpp"
#include "AddSectorizationObjectDlg.h"
#include "SectorizationManager.h"

// AddSectorizationObjectDlg 对话框

AddSectorizationObjectDlg* AddSectorizationObjectDlg::mInstance = NULL;

IMPLEMENT_DYNAMIC(AddSectorizationObjectDlg, CDialog)

AddSectorizationObjectDlg::AddSectorizationObjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddSectorizationObjectDlg::IDD, pParent)
{

}

AddSectorizationObjectDlg::~AddSectorizationObjectDlg()
{
}

void AddSectorizationObjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cmbSectorization);
}


BEGIN_MESSAGE_MAP(AddSectorizationObjectDlg, CDialog)
	ON_BN_CLICKED(IDOK, &AddSectorizationObjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// AddSectorizationObjectDlg 消息处理程序

AddSectorizationObjectDlg* AddSectorizationObjectDlg::getInstance()
{
	if(mInstance==NULL)
	{
		mInstance = new AddSectorizationObjectDlg;
		mInstance->Create(IDD);
	}
	return mInstance;
}

void AddSectorizationObjectDlg::setSelectGuids( std::vector<CString> vGuids )
{
	m_cmbSectorization.Clear();
	std::vector<SECTORIZATIONDATA> vData = SectorizationManager::getInstance()->getSectorizationData();
	std::vector<SECTORIZATIONDATA>::iterator itr = vData.begin();
	for(; itr!=vData.end(); itr++)
	{
		m_cmbSectorization.AddString(itr->strName);
	}
	m_vGuids = vGuids;
}

void AddSectorizationObjectDlg::OnBnClickedOk()
{
	int iCur = m_cmbSectorization.GetCurSel();
	if(iCur<0)
		return;

	CString strName;
	m_cmbSectorization.GetLBText(iCur, strName);

	int isize = m_vGuids.size();
	for(int i=0; i<isize; i++)
	{
		SectorizationManager::getInstance()->addSectorizationObject(strName, m_vGuids[i]);
	}

	OnOK();
}
