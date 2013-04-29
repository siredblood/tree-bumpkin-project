// AddBuildingSchemeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "pch.hpp"
#include "AddBuildingSchemeDlg.h"
#include <atlimage.h>
#include "buildingSchemeManager.h"

// AddBuildingSchemeDlg 对话框
AddBuildingSchemeDlg* AddBuildingSchemeDlg::m_instance=NULL;

IMPLEMENT_DYNAMIC(AddBuildingSchemeDlg, CDialog)

AddBuildingSchemeDlg::AddBuildingSchemeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddBuildingSchemeDlg::IDD, pParent)
{
	m_strOriginalScheme = "";
}

AddBuildingSchemeDlg::~AddBuildingSchemeDlg()
{
}

AddBuildingSchemeDlg* AddBuildingSchemeDlg::getInstance()
{
	if(m_instance==NULL)
	{
		m_instance = new AddBuildingSchemeDlg;
		m_instance->Create(IDD_BUILDSCHEME_DIALOG);
	}
	return m_instance;
}

void AddBuildingSchemeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SCHEME, m_edtScheme);
	DDX_Control(pDX, IDC_EDIT_ORIGINAL, m_edtOriginal);
	DDX_Control(pDX, IDC_EDIT_REPLACE, m_edtReplace);
	DDX_Control(pDX, IDC_LIST_SCHEME, m_lstScheme);
	DDX_Control(pDX, IDC_LIST_REPLACE, m_lstReplace);
}


BEGIN_MESSAGE_MAP(AddBuildingSchemeDlg, CDialog)
	ON_WM_CREATE()
	ON_LBN_XTP_NEWITEM(IDC_LIST_SCHEME, OnNewItem)
	ON_LBN_XTP_DELETEITEM(IDC_LIST_SCHEME, OnDeleteItem)
	ON_LBN_SELCHANGE(IDC_LIST_SCHEME, &AddBuildingSchemeDlg::OnLbnSelchangeListScheme)
	ON_BN_CLICKED(IDOK, &AddBuildingSchemeDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REPLACE, &AddBuildingSchemeDlg::OnLvnItemchangedListReplace)
	ON_NOTIFY(NM_THEMECHANGED, IDC_LIST_REPLACE, &AddBuildingSchemeDlg::OnNMThemeChangedListReplace)
	ON_NOTIFY(NM_CLICK, IDC_LIST_REPLACE, &AddBuildingSchemeDlg::OnNMClickListReplace)
END_MESSAGE_MAP()

// AddBuildingSchemeDlg 消息处理程序

BOOL AddBuildingSchemeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	loadReplaceList();

	m_lstScheme.SetListEditStyle(_T("操作:"),LBS_XTP_HIDE_UP_DOWN);
	m_lstScheme.Initialize();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int AddBuildingSchemeDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	//loadReplaceList();

	return 0;
}


void AddBuildingSchemeDlg::loadReplaceList()
{
	
	INFO_MSG("加载替换模型\n");
	CString strImageName, strImagePath;
	//std::vector<REPLACEMODEL> vModelList;
	getAllModelList("data\\clientRes\\models", m_vReplaceModel);
	int isize = m_vReplaceModel.size();
	if(isize==0)
		return;

	CImageList  imagelist;
	if (!imagelist.Create (128, 128, ILC_COLOR32|ILC_MASK, 0, 1))
		return;

	for(int i=0; i<isize; i++)
	{
		strImageName = m_vReplaceModel[i].strModelName + ".thumbnail.jpg";
		strImagePath = m_vReplaceModel[i].strModelPath + "\\" +  strImageName;
		//INFO_MSG("图片："+strImageName + "\n");
		//INFO_MSG("路径：" +strImagePath + "\n");
		CImage image;// = new CImage;
		image.Load( strImagePath.GetBuffer() );
		//image->Detach();
		//if(image==NULL)
		//	INFO_MSG("image is null\n");
		//HBITMAP hBitmap=image.Detach(); 
		//CBitmap bmp; 
		//bmp.Attach(hBitmap);
		CBitmap pBitmap ;//= CBitmap::FromHandle( image.operator HBITMAP()  );
		//pBitmap->DeleteObject();
		pBitmap.Attach(image.operator HBITMAP());
		//if(pBitmap==NULL)
		//	INFO_MSG("pBitmap is null\n");
		imagelist.Add(&pBitmap, RGB(0,0,0)/*GetSysColor(COLOR_3DFACE)*/);
	}
	
	//m_lstReplace.SetExtendedStyle(m_lstReplace.GetExtendedStyle()| LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT); 

	m_lstReplace.SetImageList(&imagelist, LVSIL_NORMAL);

	for(int i=0; i<isize; i++)
	{
		m_lstReplace.InsertItem( m_lstReplace.GetItemCount(), m_vReplaceModel[i].strModelName, i);
	}

	imagelist.Detach();
}

void AddBuildingSchemeDlg::getAllModelList( CString strPath, std::vector<REPLACEMODEL>& vModelList )
{
	REPLACEMODEL model;

	_finddata_t FileInfo;
	CString strfind = strPath + "\\*";
	long Handle = _findfirst(strfind.GetBuffer(), &FileInfo);

	if (Handle == -1L)
		return;

	do{
		INFO_MSG(FileInfo.name);
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)    
		{
			//这个语句很重要
			if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
			{
				CString newPath = strPath + "\\" + FileInfo.name;
				getAllModelList(newPath, vModelList);
			}
		}
		else  
		{
			CString strFileName = FileInfo.name;
			if(strFileName.Find(".model")>=0)
			{
				int index = vModelList.size();
				int pos = strFileName.Find(".");
				CString strName = strFileName.Mid(0, pos);
				model.index = index;
				model.strModelName = strName;
				model.strModelPath = strPath;
				INFO_MSG(strName + "\n");
				INFO_MSG(model.strModelPath + "\n");
				vModelList.push_back(model);
			}
			
		}
	}while (_findnext(Handle, &FileInfo) == 0);

	_findclose(Handle);

}

void AddBuildingSchemeDlg::OnNewItem()
{
	
}

void AddBuildingSchemeDlg::OnDeleteItem()
{
	INFO_MSG("delete\n");
	int iIndex = m_lstScheme.GetCurSel();
	if(iIndex==-1)
		return;
	
	BuildingSchemeManager::getInstance()->deleteScheme(m_strSelectedScheme);

	m_lstScheme.GetText(iIndex, m_strSelectedScheme);
	INFO_MSG(m_strSelectedScheme + "\n");
	m_edtScheme.SetWindowText(m_strSelectedScheme);
}

void AddBuildingSchemeDlg::setSelectedModel( std::string strGUID )
{
	m_strOriginalScheme = "";
	m_edtScheme.SetWindowText("");
	m_edtReplace.SetWindowText("");

	m_edtOriginal.SetWindowText(strGUID.c_str() );
	//查找所属方案和替换模型
	std::map<CString, std::map<CString, CString>> vAllScheme = BuildingSchemeManager::getInstance()->getAllScheme();
	
	//std::map<CString, CString> vReplaceList;
	std::map<CString, std::map<CString, CString>>::iterator itr;
	for(itr=vAllScheme.begin(); itr!=vAllScheme.end(); itr++)
	{
		std::map<CString, CString>::iterator childitr = itr->second.find( strGUID.c_str() );
		if(childitr!=itr->second.end())
		{
			m_strOriginalScheme = itr->first;
			m_edtScheme.SetWindowText( itr->first );
			m_edtReplace.SetWindowText( childitr->second );
			break;
		}
	}

	int iCount = m_lstScheme.GetCount();
	for(int i=iCount-1; i>=0; i--)
		m_lstScheme.DeleteString(i);
	std::vector<CString> vAllSchemeName = BuildingSchemeManager::getInstance()->getAllSchemeName();
	int isize = vAllSchemeName.size();
	for(int i=0; i<isize; i++)
	{
		m_lstScheme.AddString(vAllSchemeName[i]);
	}
}


void AddBuildingSchemeDlg::OnLbnSelchangeListScheme()
{
	INFO_MSG("Selchange\n");
	m_strSelectedScheme = "";
	int iIndex = m_lstScheme.GetCurSel();
	if(iIndex==-1)
		return;

	m_lstScheme.GetText(iIndex, m_strSelectedScheme);
	INFO_MSG(m_strSelectedScheme + "\n");
	m_edtScheme.SetWindowText( m_strSelectedScheme );
}

void AddBuildingSchemeDlg::OnBnClickedOk()
{
	CString strScheme, strNewModel, strOldModel;
	m_edtScheme.GetWindowText( strScheme );
	m_edtOriginal.GetWindowText(strOldModel);
	m_edtReplace.GetWindowText(strNewModel);

	if(strScheme!="" && strNewModel!="")
	{
		BuildingSchemeManager::getInstance()->deleteScheme(m_strOriginalScheme, strOldModel);
		BuildingSchemeManager::getInstance()->addScheme(strScheme, strOldModel, strNewModel);
	}
	else
	{
		MessageBox("信息不全","提示", MB_OK);
		return;
	}
	OnOK();
}

void AddBuildingSchemeDlg::OnLvnItemchangedListReplace(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

void AddBuildingSchemeDlg::OnNMThemeChangedListReplace(NMHDR *pNMHDR, LRESULT *pResult)
{

	*pResult = 0;
}

void AddBuildingSchemeDlg::OnNMClickListReplace(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	//str.Format(_T("Item index: %d,SubItem:%d"), pNMListView->iItem,
	//	pNMListView->iSubItem);

	int index = pNMListView->iItem;
	if(index==-1)
		return;

	CString str = m_lstReplace.GetItemText(index, pNMListView->iSubItem);
	
	CString strPath = m_vReplaceModel[index].strModelPath;
	CString strName = m_vReplaceModel[index].strModelName;
	
	strPath = strPath + "\\" + strName + ".model";
	m_edtReplace.SetWindowText( strPath );

	*pResult = 0;
}
