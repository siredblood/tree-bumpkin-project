#pragma once
#include "resource.h"
#include <memory>
#include <atlimage.h>

// CDlgApartmentDiagram �Ի���

class CDlgApartmentDiagram : public CXTPDialogBase<CXTResizeDialog>
{
	DECLARE_DYNAMIC(CDlgApartmentDiagram)

private:
	CDlgApartmentDiagram(CWnd* pParent = NULL);   // ��׼���캯��
	static std::auto_ptr<CDlgApartmentDiagram> s_pInstance;

public:
	virtual ~CDlgApartmentDiagram();

// �Ի�������
	enum { IDD = IDD_DLG_APARTMENT_DIAGRAM };

	static CDlgApartmentDiagram &Instance();

	// ��ϢID
#define ID_AD_FIRST				3001
#define ID_AD_NEXT				3002
#define ID_AD_PREV				3003
#define ID_AD_LAST				3004
#define ID_AD_ADD				3005
#define ID_AD_DEL				3006
#define ID_AD_ALL				3007

protected:
	CRect		m_rcBorders;							//������������
	BOOL		m_bInRepositionControls, m_bInitDone;	//��������ʼ�����
	CImage		m_imgDiagram;			// ͼƬ����
	CString		m_strDiagramPath;		// ͼƬ·��
	CXTPStatusBar m_wndStatusBar;
	CXTPControlListBox* pListBox;

protected:
	// ����ͼƬ
	void loadDiagram();
	// ���¶Ի������
	void updateDialogTitle();
	// �����б�
	void resetDiagramList();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ���ÿؼ����
	void SetControlStyle();
	// ����������
	void RepositionControls( );
};
