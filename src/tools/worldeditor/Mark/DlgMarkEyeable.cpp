#include "pch.hpp"
#include "DlgMarkEyeable.h"
#include "DlgMarkInput.h"
#include "MarkManage.h"

std::auto_ptr<CDlgMarkEyeable> CDlgMarkEyeable::s_pInstance;

CDlgMarkEyeable::CDlgMarkEyeable(void)
{
}

CDlgMarkEyeable::~CDlgMarkEyeable(void)
{
}

CDlgMarkEyeable &CDlgMarkEyeable::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgMarkEyeable> pDlg( new CDlgMarkEyeable() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgMarkEyeable::IDD );
	}

	return *s_pInstance;
}

BEGIN_MESSAGE_MAP(CDlgMarkEyeable, CBaseInputDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CDlgMarkEyeable::OnBnClickedOk)
END_MESSAGE_MAP()

void CDlgMarkEyeable::OnClose()
{
	//CBaseInputDlg::OnClose();
	DestroyWindow();
	std::auto_ptr<CDlgMarkEyeable>	pDlg( s_pInstance );
}

BOOL CDlgMarkEyeable::OnInitDialog()
{
	CBaseInputDlg::OnInitDialog();

	m_stName.SetWindowText("可视距离");
	this->SetWindowText("可视距离");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgMarkEyeable::OnBnClickedOk()
{
	CString  strMark;
	m_edtInput.GetWindowText( strMark );

	if(strMark=="")
	{
		strMark = "300";
	}

	CDlgMarkEyeable::Instance().m_markdata.fViewDist = float(::atof(strMark.GetBuffer(0)));
	//CString strOutPut;
	//strOutPut.Format("GUID:%s\nPOS:%s\nTYPE:%s\nDIS:%f",m_markdata.strGUID.c_str(),m_markdata.strCreateTime.c_str(),\
	//	m_markdata.strType.c_str(),m_markdata.fViewDist);
	//strOutPut.Format("DIS:%f",CMarkInputDlg::Instance()->m_markdata.fViewDist);
	//strOutPut.Format("GUID:%s",CDlgMarkEyeable::Instance()->m_markdata.strGUID.c_str());
	//AfxMessageBox(strOutPut);

	CMarkManage::Instance().AddMarkMessage( CDlgMarkEyeable::Instance().m_markdata /*strMark.GetBuffer(0), pos, "1", (*p)->edGUID()*/);

	OnClose();
}
