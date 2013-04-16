#pragma once
#include "resource.h"
#include "afxwin.h"
#include <Controls/ListBox/XTPEditListBox.h>

// AddBuildingSchemeDlg 对话框
struct REPLACEMODEL
{
	int index;
	CString strModelName;
	CString strModelPath;
};

class AddBuildingSchemeDlg : public CDialog
{
	DECLARE_DYNAMIC(AddBuildingSchemeDlg)

public:
	AddBuildingSchemeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddBuildingSchemeDlg();

// 对话框数据
	enum { IDD = IDD_BUILDSCHEME_DIALOG };

	virtual BOOL OnInitDialog();

	static AddBuildingSchemeDlg* getInstance();
	/*====================================
	说明：传入选中模型
	参数：
	返回：
	====================================*/
	void setSelectedModel(std::string strGUID);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	afx_msg void OnNewItem();	//
	afx_msg void OnDeleteItem(); //
	afx_msg void OnLbnSelchangeListScheme();
private:
	/*====================================
	说明：加载替换模型列表
	参数：
	返回：
	====================================*/
	void loadReplaceList();	//
	/*====================================
	说明：遍历模型列表data\\clientRes\\models
	参数：
	返回：
	====================================*/
	void getAllModelList(CString strPath, std::vector<REPLACEMODEL>& vModelList);
public:
	CEdit m_edtScheme;
	CEdit m_edtOriginal;
	CEdit m_edtReplace;
	CXTPEditListBox m_lstScheme;
	CListCtrl m_lstReplace;

	CString m_strOriginalScheme;
	CString m_strSelectedScheme;

	std::vector<REPLACEMODEL> m_vReplaceModel;

private:
	static AddBuildingSchemeDlg* m_instance;

public:
	
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnItemchangedListReplace(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChangedListReplace(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListReplace(NMHDR *pNMHDR, LRESULT *pResult);
};
