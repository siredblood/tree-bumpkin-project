#pragma once
#include <memory>
#include <vector>
#include <string>
#include "resource.h"


// CDlgMusicMgr �Ի���

class CDlgMusicMgr : public CXTPResizeDialog
{
	DECLARE_DYNAMIC(CDlgMusicMgr)

private:
	CDlgMusicMgr(CWnd* pParent = NULL);   // ��׼���캯��
	static std::auto_ptr<CDlgMusicMgr> s_pInstance;

public:
	virtual ~CDlgMusicMgr();
	static CDlgMusicMgr &Instance();

	// ����״̬
	void updateState();

// �Ի�������
	enum { IDD = IDD_DLG_MUSIC_MGR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

protected:
	CXTPCheckListBox m_checkList;

protected:
	void InitCheckListBox();
	std::vector<std::string> getCheckedItems();

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPausecontinue();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedCheck();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnPrev();
};
