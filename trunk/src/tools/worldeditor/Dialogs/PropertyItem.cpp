#include "pch.hpp"
#include "PropertyItem.h"

//////////////////////////////////////////////////////////////////////////
//源文件实现（重写）
BEGIN_MESSAGE_MAP(CInplaceButtonGV, CXTButton)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

void CInplaceButtonGV::OnClicked()
{
	m_pItem->m_bValue = !m_pItem->m_bValue;
	m_pItem->OnValueChanged(m_pItem->GetValue());
	SetChecked(m_pItem->m_bValue);
}

BOOL CInplaceButtonGV::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));
	return TRUE;
}

CCustomItemButtonGV::CCustomItemButtonGV(CString strCaption, BOOL bFullRowButton, BOOL bValue)
: CXTPPropertyGridItem(bFullRowButton? _T(""): strCaption)
{
	m_wndButton.m_pItem = this;
	m_nFlags = 0;
	m_bValue = bValue;
	m_strButtonText = strCaption;
	m_bFullRowButton = bFullRowButton;

	m_wndFont.CreateFont(13, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Tahoma"));
}

BOOL CCustomItemButtonGV::GetBool()
{
	return m_bValue;
}
void CCustomItemButtonGV::SetBool(BOOL bValue)
{
	m_bValue = bValue;

	if (m_wndButton.GetSafeHwnd())
		m_wndButton.SetCheck(bValue);
}

BOOL CCustomItemButtonGV::IsValueChanged()
{
	return !m_bValue;
}

void CCustomItemButtonGV::CreateButton()
{
	if (IsVisible())
	{	
		CRect rc;
		if (m_bFullRowButton)
		{		
			rc = GetItemRect();
			rc.DeflateRect( m_nIndent * 18, 0, 0, 1);
		} else
		{
			rc = GetValueRect();
		}


		if (!m_wndButton.m_hWnd)
		{
			m_wndButton.Create(m_strButtonText, WS_CHILD|BS_FLAT|BS_NOTIFY|WS_VISIBLE|BS_OWNERDRAW, rc, (CWnd*)m_pGrid, 100);
			m_wndButton.SetFont(&m_wndFont);
			//m_wndButton.SetTheme(new CXTButtonThemeOffice2003(TRUE));//主题冲突了
		}
		if (m_wndButton.GetChecked() != m_bValue) m_wndButton.SetChecked(m_bValue);
		m_wndButton.MoveWindow(rc);
		m_wndButton.Invalidate(FALSE);
	}
	else
	{
		m_wndButton.DestroyWindow();
	}
}


void CCustomItemButtonGV::SetVisible(BOOL bVisible)
{
	CXTPPropertyGridItem::SetVisible(bVisible);
	CreateButton();
}

void CCustomItemButtonGV::OnIndexChanged()
{
	CreateButton();	
}

BOOL CCustomItemButtonGV::OnDrawItemValue(CDC& /*dc*/, CRect /*rcValue*/)
{
	CreateButton();
	return FALSE;
}
