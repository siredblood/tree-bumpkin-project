// CDlgBuildingProperty.cpp : 实现文件
//

#include "pch.hpp"
#include "DlgBuildingProperty.h"
#include "DBBuildingProperty.h"
#include "../Dialogs/PropertyItem.h"
#include "GeneralClass/Common.h"


// CDlgBuildingProperty

std::auto_ptr<CDlgBuildingProperty> CDlgBuildingProperty::s_pInstance;

IMPLEMENT_DYNAMIC(CDlgBuildingProperty, CXTResizeDialog)

CDlgBuildingProperty::CDlgBuildingProperty(CWnd* pParent /*=NULL*/)
: CXTResizeDialog(CDlgBuildingProperty::IDD, pParent)
{

}

CDlgBuildingProperty::~CDlgBuildingProperty()
{
}

CDlgBuildingProperty &CDlgBuildingProperty::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgBuildingProperty> pDlg( new CDlgBuildingProperty() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgBuildingProperty::IDD );
	}else{
		s_pInstance->resetPropertyGrid();
	}

	return *s_pInstance;
}

void CDlgBuildingProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROPERTY_HOLDER, m_propertyGrid);
}

BEGIN_MESSAGE_MAP(CDlgBuildingProperty, CXTResizeDialog)
	ON_MESSAGE(XTPWM_PROPERTYGRID_NOTIFY, &CDlgBuildingProperty::OnGridNotify)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL CDlgBuildingProperty::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	SetResize(IDC_PROPERTY_HOLDER, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);

	this->SetWindowText("建筑属性");

	CRect rc;
	m_propertyGrid.GetWindowRect(&rc);
	ScreenToClient(&rc);
	m_wndGridGeneral.Create(rc, this, ID_GRID);
	m_wndGridGeneral.SetTheme(xtpGridThemeOffice2003);

	resetPropertyGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgBuildingProperty::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	// 用于销毁对象
	std::auto_ptr<CDlgBuildingProperty> pDlg( s_pInstance );
}

void CDlgBuildingProperty::resetPropertyGrid()
{
	std::vector<ChunkItemPtr> vSeleItems = WorldManager::instance().selectedItems();
	if(vSeleItems.size()!=1)
		return;

	ChunkItemPtr pModel = *vSeleItems.begin();
	m_strGuid = pModel->edGUID();

	BoundingBox box;
	Matrix mat = pModel->chunk()->transform();
	mat.preMultiply(pModel->edTransform());
	pModel->edSelectedBox( box );
	box.transformBy( mat );
	Vector3 pos = box.centre() + Vector3(0, box.height()/2.0f + 15.0f, 0);

	LinkedStringMap mapProperty;

	// 查询
	if(!CDBBuildingProperty::Query(m_strGuid, mapProperty)){
		if(mapProperty.empty()) return;

		for(LinkedStringMap::iterator itr=mapProperty.begin(); 
			itr!=mapProperty.end(); ++itr)
		{
			if((*itr).first=="编号"){
				(*itr).second = "-1";
			}else if((*itr).first=="GUID"){
				(*itr).second = m_strGuid;
			}else if((*itr).first=="坐标"){
				(*itr).second = ConvertVec3ToStr(pos).GetBuffer();
			}
		}
	}
	
	m_wndGridGeneral.ResetContent();
	//绑定类型信息
	CXTPPropertyGridItem *pCategoryApplication = m_wndGridGeneral.AddCategory("属性信息");
	CXTPPropertyGridItem *pItem = NULL;

	// 倒叙访问
	for(LinkedStringMap::reverse_iterator citr=mapProperty.rbegin();
		citr!=mapProperty.rend(); ++citr)
	{
		if((*citr).first=="编号"){
			m_pGridItemId = pCategoryApplication->AddChildItem(new CXTPPropertyGridItem((*citr).first.c_str(),
				(*citr).second.c_str()));
			m_pGridItemId->SetReadOnly();
			continue;
		}
		pItem = pCategoryApplication->AddChildItem(new CXTPPropertyGridItem((*citr).first.c_str(),
			(*citr).second.c_str()));
		if((*citr).first=="GUID"||(*citr).first=="坐标"){
			pItem->SetReadOnly();
		}
	}
	//保存按钮
	CXTPPropertyGridItem *pButton = new CCustomItemButtonGV(_T("保    存"), TRUE, FALSE);
	pButton->SetID(ID_BTN_SAVE);
	pCategoryApplication->AddChildItem(pButton);

	pCategoryApplication->Expand();
}

LRESULT CDlgBuildingProperty::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_PGN_ITEMVALUE_CHANGED){//响应指定事件
		CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;
		if (pItem){
			int id = pItem->GetID();

			if (id==ID_BTN_SAVE){
				CXTPPropertyGridItems *pRecords = m_wndGridGeneral.GetCategories();//获取整个网格记录
				CXTPPropertyGridItem *pRecord = pRecords->GetAt(0);// 获取单条报表记录
				CXTPPropertyGridItems *pChildRecords = pRecord->GetChilds();//获得子记录
				int count = pChildRecords->GetCount();
				bool bIsSave = true;

				CString strVal;
				LinkedStringMap mapProperty;
				std::string strField,strValue;

				for(int i=0, j=0; i<count; ++i, j+=3){
					strField = pChildRecords->GetAt(i)->GetCaption().GetBuffer(0);
					if(strField=="") continue;// 排除保存按钮
					strValue = pChildRecords->GetAt(i)->GetValue().GetBuffer(0);					
					mapProperty.insert(std::make_pair<std::string, std::string>(strField, strValue));

				}
				if(bIsSave)//可以保存了
				{
					if(CDBBuildingProperty::Save(mapProperty)){
						AfxMessageBox("保存成功");
						mapProperty.clear();
						CDBBuildingProperty::Query(m_strGuid, mapProperty);
						for(LinkedStringMap::reverse_iterator itr=mapProperty.rbegin(); 
							itr!=mapProperty.rend(); ++itr)
						{
							if((*itr).first=="编号"){
								m_pGridItemId->SetValue((*itr).second.c_str());
								break;;
							}
						}
					}else{
						AfxMessageBox("保存失败");
					}
				}//end save
			}//end save button
		} //end pItem
	} //end ptr
	return 0;
}