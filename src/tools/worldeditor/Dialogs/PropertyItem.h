#pragma once

//////////////////////////////////////////////////////////////////////////
//按钮控件的实现
class CCustomItemButtonGV;//声明类

class CInplaceButtonGV : public CXTButton
{
public:
	DECLARE_MESSAGE_MAP()
protected:
	CCustomItemButtonGV* m_pItem;
	void OnClicked();
	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	friend class CCustomItemButtonGV;
};

class CCustomItemButtonGV : public CXTPPropertyGridItem
{
protected:

public:
	CCustomItemButtonGV(CString strCaption, BOOL bFullRowButton, BOOL bValue);

	BOOL GetBool();
	void SetBool(BOOL bValue);

protected:
	virtual BOOL IsValueChanged();
	virtual void SetVisible(BOOL bVisible);
	BOOL OnDrawItemValue(CDC& dc, CRect rcValue);
	virtual void OnIndexChanged();
	void CreateButton();


private:
	CInplaceButtonGV m_wndButton;
	BOOL m_bValue;
	CFont m_wndFont;
	CString m_strButtonText;
	BOOL m_bFullRowButton;

	friend class CInplaceButtonGV;
};

