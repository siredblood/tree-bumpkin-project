#pragma once
#include "resource.h"
#include <memory>
#include <atlimage.h>

// CDlgApartmentDiagram 对话框

class CDlgApartmentDiagram : public CXTPDialogBase<CXTResizeDialog>
{
	DECLARE_DYNAMIC(CDlgApartmentDiagram)

private:
	CDlgApartmentDiagram(CWnd* pParent = NULL);   // 标准构造函数
	static std::auto_ptr<CDlgApartmentDiagram> s_pInstance;

public:
	virtual ~CDlgApartmentDiagram();

// 对话框数据
	enum { IDD = IDD_DLG_APARTMENT_DIAGRAM };

	static CDlgApartmentDiagram &Instance();

	// 消息ID
#define ID_AD_FIRST				3001
#define ID_AD_NEXT				3002
#define ID_AD_PREV				3003
#define ID_AD_LAST				3004
#define ID_AD_ADD				3005
#define ID_AD_DEL				3006
#define ID_AD_ALL				3007

protected:
	CRect		m_rcBorders;							//调整工具栏用
	BOOL		m_bInRepositionControls, m_bInitDone;	//工具栏初始化标记
	CImage		m_imgDiagram;			// 图片对象
	CString		m_strDiagramPath;		// 图片路径
	CXTPStatusBar m_wndStatusBar;
	CXTPControlListBox* pListBox;

protected:
	// 载入图片
	void loadDiagram();
	// 更新对话框标题
	void updateDialogTitle();
	// 更新列表
	void resetDiagramList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnKickIdle(WPARAM wp, LPARAM lCount);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnPaint();

	afx_msg void OnBnClickedFirst();
	afx_msg void OnUpdateFirst(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedNext();
	afx_msg void OnUpdateNext(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedPrev();
	afx_msg void OnUpdatePrev(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedLast();
	afx_msg void OnUpdateLast(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedAdd();
	afx_msg void OnUpdateAdd(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedDel();
	afx_msg void OnUpdateDel(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedAll();

public:
	void updateCommandBar();
	// 设置控件风格
	void SetControlStyle();
	// 调整工具栏
	void RepositionControls( );
};
