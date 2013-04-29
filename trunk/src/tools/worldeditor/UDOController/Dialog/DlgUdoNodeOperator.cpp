#include "pch.hpp"
#include "DlgUdoNodeOperator.h"
#include "GeneralClass/Common.h"

CDlgUdoNodeOperator::CDlgUdoNodeOperator(void)
{
}

CDlgUdoNodeOperator::~CDlgUdoNodeOperator(void)
{
}

BEGIN_MESSAGE_MAP(CDlgUdoNodeOperator, CBaseOperationDlg)
	ON_BN_CLICKED(IDOK, &CDlgUdoNodeOperator::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CDlgUdoNodeOperator::OnInitDialog()
{
	CBaseOperationDlg::OnInitDialog();

	m_combox.InsertString(0, "ͳһ�߶�");
	m_combox.InsertString(1, "ͳһƫ��");

	m_combox.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgUdoNodeOperator::OnBnClickedOk()
{
	m_editbox.GetWindowText( m_strData );
	m_combox.GetLBText( m_combox.GetCurSel(), m_strOperator );

	CBaseOperationDlg::OnOK();
}

void CDlgUdoNodeOperator::GetOperateData( CString &strOpertor, CString &strData )
{
	strOpertor = m_strOperator;
	strData = m_strData;
}