// CDlgBuildingProperty.cpp : ʵ���ļ�
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

	this->SetWindowText("��������");

	CRect rc;
	m_propertyGrid.GetWindowRect(&rc);
	ScreenToClient(&rc);
	m_wndGridGeneral.Create(rc, this, ID_GRID);
	m_wndGridGeneral.SetTheme(xtpGridThemeOffice2003);

	resetPropertyGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgBuildingProperty::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	// �������ٶ���
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

	// ��ѯ
	if(!CDBBuildingProperty::Query(m_strGuid, mapProperty)){
		if(mapProperty.empty()) return;

		for(LinkedStringMap::iterator itr=mapProperty.begin(); 
			itr!=mapProperty.end(); ++itr)
		{
			if((*itr).first=="���"){
				(*itr).second = "-1";
			}else if((*itr).first=="GUID"){
				(*itr).second = m_strGuid;
			}else if((*itr).first=="����"){
				(*itr).second = ConvertVec3ToStr(pos).GetBuffer();
			}
		}
	}
	
	m_wndGridGeneral.ResetContent();
	//��������Ϣ
	CXTPPropertyGridItem *pCategoryApplication = m_wndGridGeneral.AddCategory("������Ϣ");
	CXTPPropertyGridItem *pItem = NULL;

	// �������
	for(LinkedStringMap::reverse_iterator citr=mapProperty.rbegin();
		citr!=mapProperty.rend(); ++citr)
	{
		if((*citr).first=="���"){
			m_pGridItemId = pCategoryApplication->AddChildItem(new CXTPPropertyGridItem((*citr).first.c_str(),
				(*citr).second.c_str()));
			m_pGridItemId->SetReadOnly();
			continue;
		}
		pItem = pCategoryApplication->AddChildItem(new CXTPPropertyGridItem((*citr).first.c_str(),
			(*citr).second.c_str()));
		if((*citr).first=="GUID"||(*citr).first=="����"){
			pItem->SetReadOnly();
		}
	}
	//���水ť
	CXTPPropertyGridItem *pButton = new CCustomItemButtonGV(_T("��    ��"), TRUE, FALSE);
	pButton->SetID(ID_BTN_SAVE);
	pCategoryApplication->AddChildItem(pButton);

	pCategoryApplication->Expand();
}

LRESULT CDlgBuildingProperty::OnGridNotify(WPARAM wParam, LPARAM lParam)
{
	if (wParam == XTP_PGN_ITEMVALUE_CHANGED){//��Ӧָ���¼�
		CXTPPropertyGridItem* pItem = (CXTPPropertyGridItem*)lParam;
		if (pItem){
			int id = pItem->GetID();

			if (id==ID_BTN_SAVE){
				CXTPPropertyGridItems *pRecords = m_wndGridGeneral.GetCategories();//��ȡ���������¼
				CXTPPropertyGridItem *pRecord = pRecords->GetAt(0);// ��ȡ���������¼
				CXTPPropertyGridItems *pChildRecords = pRecord->GetChilds();//����Ӽ�¼
				int count = pChildRecords->GetCount();
				bool bIsSave = true;

				CString strVal;
				LinkedStringMap mapProperty;
				std::string strField,strValue;

				for(int i=0, j=0; i<count; ++i, j+=3){
					strField = pChildRecords->GetAt(i)->GetCaption().GetBuffer(0);
					if(strField=="") continue;// �ų����水ť
					strValue = pChildRecords->GetAt(i)->GetValue().GetBuffer(0);					
					mapProperty.insert(std::make_pair<std::string, std::string>(strField, strValue));

				}
				if(bIsSave)//���Ա�����
				{
					if(CDBBuildingProperty::Save(mapProperty)){
						AfxMessageBox("����ɹ�");
						mapProperty.clear();
						CDBBuildingProperty::Query(m_strGuid, mapProperty);
						for(LinkedStringMap::reverse_iterator itr=mapProperty.rbegin(); 
							itr!=mapProperty.rend(); ++itr)
						{
							if((*itr).first=="���"){
								m_pGridItemId->SetValue((*itr).second.c_str());
								break;;
							}
						}
					}else{
						AfxMessageBox("����ʧ��");
					}
				}//end save
			}//end save button
		} //end pItem
	} //end ptr
	return 0;
}