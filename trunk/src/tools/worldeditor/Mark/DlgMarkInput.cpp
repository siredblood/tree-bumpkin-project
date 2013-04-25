#include "pch.hpp"
#include "DlgMarkInput.h"
#include "MarkManage.h"
#include "DlgMarkEyeable.h"
#include "worldeditor/world/world_manager.hpp"

std::auto_ptr<CDlgMarkInput> CDlgMarkInput::s_pInstance;

CDlgMarkInput::CDlgMarkInput(void)
{
}

CDlgMarkInput::~CDlgMarkInput(void)
{
}

CDlgMarkInput &CDlgMarkInput::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgMarkInput> pDlg( new CDlgMarkInput() );
		s_pInstance = pDlg;
		s_pInstance->Create( CDlgMarkInput::IDD );
	}

	return *s_pInstance;
}

BEGIN_MESSAGE_MAP(CDlgMarkInput, CBaseInputDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CDlgMarkInput::OnBnClickedOk)
END_MESSAGE_MAP()

void CDlgMarkInput::OnClose()
{
	//CBaseInputDlg::OnClose();
	DestroyWindow();
	std::auto_ptr<CDlgMarkInput> pDlg( s_pInstance );
}

//void CDlgMarkInput::SetMarkMsg(CString strGUID, Vector3 pos, int iType)
//{
//	m_strGUID = strGUID;
//	m_MarkPos = pos;
//	m_iMarkType = iType;
//}
	
void CDlgMarkInput::OnBnClickedOk()
{
	CString  strMark;
	m_edtInput.GetWindowText( strMark );
	
	if(strMark=="")
	{
		MessageBox("标注不能为空！","提示",MB_OK);
		return;
	}
	
	CString strTime;
	COleDateTime time = COleDateTime::GetCurrentTime();
	strTime.Format( "%d-%.2d-%.2d %.2d:%.2d:%.2d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), 
					time.GetMinute(), time.GetSecond() );
					
	std::vector<ChunkItemPtr> vSeleItems = WorldManager::instance().selectedItems();
	int iSelSize = vSeleItems.size();
	if(iSelSize>0)
	{
		Vector3 pos;
		Matrix mat;

		BoundingBox box;
		std::vector<ChunkItemPtr>::iterator p ;//= vSeleItems.begin();
		for(p=vSeleItems.begin(); p!=vSeleItems.end(); p++)
		{
			mat = (*p)->chunk()->transform();
			mat.preMultiply((*p)->edTransform());
			//pos = mat.applyToOrigin();
			(*p)->edSelectedBox( box );
			box.transformBy( mat );
			//pos.y = pos.y + box.height() + 5.0f;
			pos = box.centre() + Vector3(0, box.height()/2.0f + 15.0f, 0);
			
			CDlgMarkEyeable::Instance().m_markdata.pos = pos;
			CDlgMarkEyeable::Instance().m_markdata.bHaveObject = true;
			CDlgMarkEyeable::Instance().m_markdata.strText = strMark.GetBuffer(0);
			CDlgMarkEyeable::Instance().m_markdata.strGUID = (*p)->edGUID();
			CDlgMarkEyeable::Instance().m_markdata.strType = "1";
			CDlgMarkEyeable::Instance().m_markdata.strCreator = g_strSysUserName.GetBuffer(0);
			CDlgMarkEyeable::Instance().m_markdata.strCreateTime = strTime;
			CDlgMarkEyeable::Instance().m_markdata.fViewDist=300.0f;
			
			//CMarkManage::Instance().AddMarkMessage( m_markdata /*strMark.GetBuffer(0), pos, "1", (*p)->edGUID()*/);
		}
	}
	else
	{
		//POINT pt = WorldManager::instance().currentCursorPosition();
		//Vector3 worldRay = WorldManager::instance().getWorldRay(pt);
		Vector3 worldRay = Moo::rc().invView().applyToUnitAxisVector(2);
		Vector3 start =  Moo::rc().invView().applyToOrigin();
		Vector3 extent = start + worldRay * 10.0f;
		//extent.y -= 5.0f;
		
		//MARKDATA markdata;
		CDlgMarkEyeable::Instance().m_markdata.pos = extent;
		CDlgMarkEyeable::Instance().m_markdata.bHaveObject = false;
		CDlgMarkEyeable::Instance().m_markdata.strText = strMark.GetBuffer(0);
		CDlgMarkEyeable::Instance().m_markdata.strGUID = "";
		CDlgMarkEyeable::Instance().m_markdata.strType = "0";
		CDlgMarkEyeable::Instance().m_markdata.strCreator = g_strSysUserName.GetBuffer(0);
		CDlgMarkEyeable::Instance().m_markdata.strCreateTime = strTime;
		CDlgMarkEyeable::Instance().m_markdata.fViewDist=300.0f;
		
		//CMarkManage::Instance().AddMarkMessage( m_markdata/*strMark.GetBuffer(0), extent, "0", ""*/);
	}
	CMarkManage::Instance().AddMarkMessage( CDlgMarkEyeable::Instance().m_markdata );
	
	//添加标注即保存到数据库
	CMarkManage::Instance().SaveMarks();

	OnClose();
}

BOOL CDlgMarkInput::OnInitDialog()
{
	CBaseInputDlg::OnInitDialog();

	m_stName.SetWindowText("标注：");
	this->SetWindowText("标注");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
