#include "pch.hpp"
#include "DlgUDONode.h"
#include "BLogicLib/BllHelper.h"
#include "worldeditor/gui/Customs/BaseDlg/MessageRecord.h"
#include "worldeditor/CameraTravel/CustomWorldCamera.h"
#include "worldeditor/UDOController/UDOController.hpp"
#include "worldeditor/UDOController/Dialog/DlgUDOManager.h"
#include "worldeditor/GeneralClass/common_public.hpp"
#include "worldeditor/misc/world_editor_camera.hpp"
#include "worldeditor/UDOController/UDOManager.h"
#include "worldeditor/UDOController/Dialog/DlgUdoNodeOperator.h"
#include "worldeditor/GeneralClass/Common.h"
#include "GeneralClass/CustomCollision.h"
#include "worldeditor/CameraTravel/CustomCamera.h"


std::auto_ptr<CDlgUDONode> CDlgUDONode::s_pInstance;

namespace
{
	const LPCTSTR STRING_ID			 = "编号";
	const LPCTSTR STRING_GUID		 = "GUID";
	const LPCTSTR STRING_POSITION	 = "位置";
	const LPCTSTR STRING_ROTATE		 = "旋转";
	const LPCTSTR STRING_SPEED		 = "速度";
	const LPCTSTR STRING_DESCRIPTION = "描述";
}

CDlgUDONode::CDlgUDONode()
{
	m_iSelRow = -1;
	m_iPid = -1;
}

CDlgUDONode::~CDlgUDONode()
{
}

CDlgUDONode &CDlgUDONode::Instance()
{
	if( s_pInstance.get() == NULL )
	{
		std::auto_ptr<CDlgUDONode> pDlg( new CDlgUDONode() );
		s_pInstance = pDlg;
		s_pInstance->Create( IDD_DLG_REPORT_4 );
	}

	return *s_pInstance;
}

void CDlgUDONode::DoDataExchange(CDataExchange* pDX)
{
	CXTPResizeDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPORTCTRL, m_wndReportCtrl);
	DDX_Control(pDX, IDC_BUTTON1, m_btnSave );
	DDX_Control(pDX, IDC_BUTTON2, m_btnDelete );
	DDX_Control(pDX, IDC_BUTTON3, m_btnUnify );
}

BEGIN_MESSAGE_MAP(CDlgUDONode, CXTPResizeDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgUDONode::OnBtnSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgUDONode::OnBtnDelete)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlgUDONode::OnBtnUnify)
	ON_NOTIFY(NM_CLICK, IDC_REPORTCTRL, &CDlgUDONode::OnReportItemClick)
	ON_NOTIFY(NM_DBLCLK, IDC_REPORTCTRL, &CDlgUDONode::OnReportItemDBClick)
END_MESSAGE_MAP()


BOOL CDlgUDONode::OnInitDialog()
{
	CXTPResizeDialog::OnInitDialog();

	this->SetWindowText( "节点编辑" );

	GetDlgItem( IDC_BUTTON4 )->ShowWindow( SW_HIDE );

	m_btnSave.SetWindowText("保存");
	m_btnDelete.SetWindowText("删除");
	m_btnUnify.SetWindowText("坐标运算");

	m_wndReportCtrl.ModifyStyle(0, WS_CLIPCHILDREN|WS_CLIPSIBLINGS|WS_TABSTOP);
	m_wndReportCtrl.SetMultipleSelection( TRUE );
	m_wndReportCtrl.GetPaintManager()->SetColumnStyle(xtpReportColumnOffice2003);

	CXTPReportColumn *pColumnGuid = NULL;
	m_wndReportCtrl.AddColumn( new CXTPReportColumn( COLUMN_ID, STRING_ID, 25 ) );
	pColumnGuid = m_wndReportCtrl.AddColumn( new CXTPReportColumn(COLUMN_GUID, STRING_GUID, 80 ) );
	m_wndReportCtrl.AddColumn( new CXTPReportColumn( COLUMN_POSITION, STRING_POSITION, 80 ) );
	m_wndReportCtrl.AddColumn( new CXTPReportColumn( COLUMN_ROTATE, STRING_ROTATE, 40 ) );
	m_wndReportCtrl.AddColumn( new CXTPReportColumn( COLUMN_SPEED, STRING_SPEED, 25 ) );
	m_wndReportCtrl.AddColumn( new CXTPReportColumn( COLUMN_DESCRIPTION, STRING_DESCRIPTION, 80 ) );

	// GUID隐藏
	pColumnGuid->SetVisible( FALSE );

	for( int i = COLUMN_ID; i <= COLUMN_SPEED; i++ )
	{
		m_wndReportCtrl.GetColumns()->GetAt(i)->SetAllowDrag( FALSE );
		m_wndReportCtrl.GetColumns()->GetAt(i)->SetSortable( FALSE );
		m_wndReportCtrl.GetColumns()->GetAt(i)->GetEditOptions()->m_bAllowEdit = FALSE;
	}
	m_wndReportCtrl.GetColumns()->GetAt(COLUMN_SPEED)->GetEditOptions()->m_bAllowEdit = TRUE;
	m_wndReportCtrl.AllowEdit( TRUE );

	m_wndReportCtrl.Populate();

	SetResize( IDC_REPORTCTRL, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT );
	SetResize( IDC_BUTTON1, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT );
	SetResize( IDC_BUTTON2, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT );
	SetResize( IDC_BUTTON3, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT );
	SetResize( IDC_BUTTON4, SZ_BOTTOM_RIGHT, SZ_BOTTOM_RIGHT );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgUDONode::SetPID( int pid )
{
	m_iPid = pid;

	UpdateReport();
}

void CDlgUDONode::UpdateReport()
{
	m_wndReportCtrl.ResetContent();

	std::vector< UDOCameraNode > vUdoNodes;
	std::vector< UDOCameraNode >::iterator itr;

	// 读取数据库
	UDOController::instance().loadFromDB( m_iPid, vUdoNodes );

	for( itr = vUdoNodes.begin(); itr != vUdoNodes.end(); ++itr )
	{
		Chunk *pChunk = ChunkManager::instance().findChunkByName( 
			(*itr).chunkID, WorldManager::instance().chunkDirMapping() );

		Matrix tmpMatrix;
		tmpMatrix.multiply( (*itr).transform, pChunk->transformInverse() );
		Matrix itemMatrix = pChunk->transform();
		itemMatrix.preMultiply( tmpMatrix );
		Vector3 vPos = itemMatrix.applyToOrigin();
		Vector3 vDir = itemMatrix.applyToUnitAxisVector( 2 );

		CString strPos, strDir;
		strPos.Format( "%.3f,%.3f,%.3f", vPos.x, vPos.y, vPos.z ); 
		strDir.Format( "%.3f,%.3f,%.3f", vDir.x, vDir.y, vDir.z );

		CXTPReportRecord* pRecord = m_wndReportCtrl.AddRecord( new CXTPReportRecord() );
		pRecord->AddItem( new CXTPReportRecordItemNumber( (*itr).id ) );
		pRecord->AddItem( new CXTPReportRecordItemText( (*itr).guid.c_str() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( strPos.GetBuffer() ) );
		pRecord->AddItem( new CXTPReportRecordItemText( strDir.GetBuffer() ) );
		pRecord->AddItem( new CXTPReportRecordItemNumber( (*itr).speed, "%.2f" ) );
		pRecord->AddItem( new CXTPReportRecordItemText( (*itr).description.c_str() ) );
		
	}

	m_wndReportCtrl.Populate();
}

void CDlgUDONode::OnClose()
{
	//关闭后台加载
	UDOController::instance().stopLoading();
	if( MessageBox( "是否保存节点？", "提示", MB_YESNO ) == IDYES )
	{	
		//保存
		OnBtnSave();
	}

	CDlgUDOManager::Instance().UpdateReport();
	CDlgUDOManager::Instance().ShowWindow( SW_SHOW );

	UDOController::instance().clearUdo();

	// 销毁窗体
	DestroyWindow();
	std::auto_ptr<CDlgUDONode> pDlg( s_pInstance );

	//CBaseReportDlg::OnClose();
}

void CDlgUDONode::OnBtnSave()
{
	CXTPReportRecords *pRecords = m_wndReportCtrl.GetRecords();
	int iCounts = pRecords->GetCount();
	//  先保存已有节点的数据，主要是保存速度
	if( iCounts > 0 )
	{
		CXTPReportRecord *pRecord;
		std::map< std::string, TempStruct > mapSpeed;
		for( int i=0; i<iCounts; ++i )
		{
			TempStruct ts;
			
			pRecord = pRecords->GetAt( i );
			std::string strGuid = pRecord->GetItem( COLUMN_GUID )->GetCaption( 0 ).GetBuffer( 0 );
			CString strSpeed = pRecord->GetItem( COLUMN_SPEED )->GetCaption( 0 );
			float fSpeed = (float)::atof( strSpeed );
			
			ts.id		   = -1;
			ts.fSpeed	   = fSpeed;
			ts.description = pRecord->GetItem( COLUMN_DESCRIPTION )->GetCaption( 0 ).GetBuffer( 0 );
			
			mapSpeed.insert( std::make_pair( strGuid, ts ) );
		}
		UDOController::instance().updateSpeed( mapSpeed );
	}

	UDOController::instance().saveUdoData();
	UpdateReport();

	// 再把所有节点显示出来，同时还要更新FlyThrough表
	pRecords = m_wndReportCtrl.GetRecords();
	if( pRecords->GetCount() > 0 )
	{
		std::string strGuid = pRecords->GetAt( 0 )->GetItem( COLUMN_GUID )->GetCaption( 0 ).GetBuffer( 0 );
		int id = UDOController::instance().getID( strGuid );

		UDOCamera udoCamera;
		CUDOManager::Instance().GetUdoCamera( m_iPid, udoCamera );
		udoCamera.iNodeid = id; 
		CUDOManager::Instance().UpdateUdoCamera( udoCamera );
	}

	UpdateReport();
}

void CDlgUDONode::OnBtnDelete()
{
	CXTPReportSelectedRows *pSelRows = m_wndReportCtrl.GetSelectedRows();
	if( pSelRows->GetCount() != 1 )
		return ;

	if( MessageBox( "删除后将不能恢复，是否确定删除节点？", "警告", MB_YESNO ) == IDYES )
	{
		std::string strGuid
			= pSelRows->GetAt( 0 )->GetRecord()->GetItem( COLUMN_GUID )->GetCaption( 0 ).GetBuffer( 0 );

		UDOController::instance().delUdo( strGuid );
	}

	UpdateReport();
}

void CDlgUDONode::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (!pItemNotify->pRow || !pItemNotify->pColumn)
	{
		m_iSelRow = -1;
		return;
	}

	m_iSelRow = pItemNotify->pRow->GetIndex();
}

void CDlgUDONode::OnReportItemDBClick(NMHDR * pNotifyStruct, LRESULT * result)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;

	if (pItemNotify->pRow)
	{
		int iSelRow = pItemNotify->pRow->GetIndex();
		if( iSelRow==-1 )
			return;

		CXTPReportRecord *pRecord = pItemNotify->pRow->GetRecord();

		CString strPos = pRecord->GetItem( COLUMN_POSITION )->GetCaption( 0 );
		CString strDir = pRecord->GetItem( COLUMN_ROTATE )->GetCaption( 0 );
		Vector3 vPos = ConvertStrToVec3( strPos.GetBuffer() );
		Vector3 vDir = ConvertStrToVec3( strDir.GetBuffer() );
		vDir.normalise();
		vPos += vDir * 1.2f;

		CCustomCamera::Instance().TeleportCamera( vPos, -vDir );
		
	}
}

void CDlgUDONode::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CXTPResizeDialog::OnOK();
}

void CDlgUDONode::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CXTPResizeDialog::OnCancel();
}

void CDlgUDONode::OnBtnUnify()
{
	CDlgUdoNodeOperator dlg;
	if( dlg.DoModal() == IDOK )
	{
		CString strOperator, strValue;
		dlg.GetOperateData( strOperator, strValue );
		if( strOperator.Find( "高度" ) != -1 )
		{
			float fHeight = 0.0f;
			fHeight = (float)atof( strValue.GetBuffer() );
			SetUnifyHeight( fHeight );
		}
		else if( strOperator.Find( "偏移" ) != -1 )
		{
			Vector3 vOffset = ConvertStrToVec3( strValue.GetBuffer() );
			SetUnifyOffset( vOffset );
		}
	}
}


/**
 *	统一偏移选定节点高度
 */
void CDlgUDONode::SetUnifyHeight( float fHeight )
{
	CXTPReportSelectedRows *pRows = m_wndReportCtrl.GetSelectedRows();
	int iCount = pRows->GetCount();

	std::map<std::string, EditorChunkUserDataObject* > objects;
	objects = EditorChunkUserDataObject::getUserDataObjects();

	for( int i=0; i<iCount; ++i )
	{
		CXTPReportRecord *pRecord = pRows->GetAt( i )->GetRecord();
		std::string strGuid = pRecord->GetItem( COLUMN_GUID )->GetCaption( 0 ).GetBuffer( 0 );
		if( objects.find( strGuid ) != objects.end() )
		{
			EditorChunkUserDataObject *pObject = objects[strGuid];
			Matrix oldMt = pObject->chunk()->transform();
			oldMt.preMultiply( pObject->edTransform() );
			Vector3 vPos = oldMt.applyToOrigin();
			Vector3 vDir = oldMt.applyToUnitAxisVector( 2 );
			vPos.y = fHeight;
			
			Matrix posmt;
			posmt.setTranslate( vPos );
			Matrix localPose;
			localPose.multiply( posmt, pObject->chunk()->transformInverse() );
			Matrix newPosemt;

			newPosemt = pObject->edTransform();
			newPosemt.translation( localPose.applyToOrigin() ); 

			Matrix rot;
			rot.setRotate( vDir.yaw(), vDir.pitch(), 0.0f );
			newPosemt.preMultiply( rot ); 

			pObject->edTransform( newPosemt, false );
		}
	}
}

/**
 *	统一偏移选定节点坐标
 */
void CDlgUDONode::SetUnifyOffset( Vector3 vOffset )
{
	CXTPReportSelectedRows *pRows = m_wndReportCtrl.GetSelectedRows();
	int iCount = pRows->GetCount();

	std::map<std::string, EditorChunkUserDataObject* > objects;
	objects = EditorChunkUserDataObject::getUserDataObjects();

	for( int i=0; i<iCount; ++i )
	{
		CXTPReportRecord *pRecord = pRows->GetAt( i )->GetRecord();
		std::string strGuid = pRecord->GetItem( COLUMN_GUID )->GetCaption( 0 ).GetBuffer( 0 );
		if( objects.find( strGuid ) != objects.end() )
		{
			EditorChunkUserDataObject *pObject = objects[strGuid];
			Matrix oldMt = pObject->chunk()->transform();
			oldMt.preMultiply( pObject->edTransform() );
			Vector3 vPos = oldMt.applyToOrigin();
			Vector3 vDir = oldMt.applyToUnitAxisVector( 2 );
			vPos += vOffset;

			Matrix posmt;
			posmt.setTranslate( vPos );
			Matrix localPose;
			localPose.multiply( posmt, pObject->chunk()->transformInverse() );
			Matrix newPosemt;

			newPosemt = pObject->edTransform();
			newPosemt.translation( localPose.applyToOrigin() ); 

			Matrix rot;
			rot.setRotate( vDir.yaw(), vDir.pitch(), 0.0f );
			newPosemt.preMultiply( rot ); 

			pObject->edTransform( newPosemt, false );
		}
	}
}