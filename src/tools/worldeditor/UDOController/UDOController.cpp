#include "pch.hpp"
#include "UDOController.hpp"
#include "GeneralClass/CustomCollision.h"
#include "BLogicLib/BllHelp.h"

#include "Fly.hpp"

#include "worldeditor/editor/chunk_item_placer.hpp"
#include "common/string_utils.hpp"
#include "worldeditor/UDOController/UDOManager.h"


UDOController UDOController::s_instance_;

UDOController::UDOController() : 
canLoad_( false ), m_bHandle( false ), m_iPid( -1 ), m_bSuccess( true )
{
	TaskManager::instance().add( this, "UDOController", NULL );
}

UDOController::~UDOController()
{
}

UDOController &UDOController::instance()
{
	return s_instance_;
}

void UDOController::getLinkObjects( std::vector< UDOCameraNode > &vUdoCN, const std::string& firstGUID )
{
	m_objects = EditorChunkUserDataObject::getUserDataObjects();

	if ( m_objects.size() )
	{
		getLinkObject( vUdoCN, firstGUID );
	}
	
	m_objects.clear();
}

void UDOController::getLinkObject( std::vector< UDOCameraNode > &vUdoCN, const std::string& guid )
{
	for ( std::map<std::string, EditorChunkUserDataObject* >::const_iterator
		itr = m_objects.begin(); itr != m_objects.end(); itr++ )
	{
		std::string tmp = (itr->second)->pOwnSect()->readString( "guid" );
		if ( tmp == guid )
		{
			UDOCameraNode udoCN_;

			// 设置ID,PID值
			if( m_mapTemp.find( guid ) != m_mapTemp.end() )
			{
				udoCN_.id		   = m_mapTemp[ guid ].id;
				udoCN_.speed	   = m_mapTemp[ guid ].fSpeed;
				udoCN_.description = m_mapTemp[ guid ].description;
			}
			else
			{
				udoCN_.id		   = -1;
				udoCN_.speed	   = MIN_SPEED;
				udoCN_.description = "";
			}
			udoCN_.pid = m_iPid;
			
			udoCN_.transform = (itr->second)->pOwnSect()->readMatrix34( "transform" );
			udoCN_.guid = tmp;
			udoCN_.chunkID = (itr->second)->chunk()->identifier();
			
			std::string nextGUID = (itr->second)->pOwnSect()->readString( "properties/next/guid" );
			udoCN_.nextGUID = nextGUID;
			
			udoCN_.nextChunkID = (itr->second)->pOwnSect()->readString( "properties/next/chunkId" );
			
			std::string backGUID = (itr->second)->pOwnSect()->readString( "backLinks/link/guid" );
			udoCN_.backGUID = backGUID;
			
			udoCN_.backChunkID = (itr->second)->pOwnSect()->readString( "backLinks/link/chunkId" );
			
			if ( ( !nextGUID.empty() && m_objects.find( nextGUID ) == m_objects.end() ) ||
			     ( !backGUID.empty() && m_objects.find( backGUID ) == m_objects.end() ) )
			{
				m_bSuccess = false;
			}

			vUdoCN.push_back( udoCN_ );
			
			if ( nextGUID.empty() )
			{
				return;
			}
			
			getLinkObject( vUdoCN, nextGUID );
		}
	}
}

void UDOController::saveUdoData()
{
	std::vector< UDOCameraNode > vUdoNodes;

	// 获取数据
	getLinkObjects( vUdoNodes, m_strGuid );

	// 节点未加载完成，不进行保存
	if ( !m_bSuccess )
	{
		MessageBox( NULL, _T( "节点未加载完成，无法进行保存！" ), _T( "提示" ), 0 );
		m_bSuccess = true;
		
		return;
	}
	
	// 保存到数据库
	saveToDB( m_iPid, vUdoNodes );
}

BOOL UDOController::saveToDB( int pid, const std::vector< UDOCameraNode >& nodes )
{
	if( nodes.empty() )
		return TRUE;

	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough_Nodes"))
	{
		MessageBox(NULL, _T("数据库中不存在FlyThrough_Nodes表")  ,_T("提示"),0);
		return FALSE;
	}
	float fSpeed;
	CString strSql;
	std::vector< UDOCameraNode >::const_iterator cItr;
	std::vector< _bstr_t > vSql;
	
	//先删除数据库中当前节点的内容
	strSql.Format( "delete from [FlyThrough_Nodes] where [pid]=%d", pid );
	BOOL bRes = theBllApp.m_pDB->ExcuteSql( strSql.GetBuffer(0), adCmdText );

	for( cItr = nodes.begin(); cItr!=nodes.end(); ++cItr )
	{
		std::string strTransform = StringUtils::matrixToString( (*cItr).transform );
		fSpeed = (*cItr).speed > MIN_SPEED ? (*cItr).speed : MIN_SPEED;
		
		strSql.Format( "INSERT INTO FlyThrough_Nodes (pid, transform, guid, chunkID, nextGUID, \
					   nextChunkID, backGUID, backChunkID, speed, description) Values (%d,'%s','%s','%s','%s',\
					   '%s','%s','%s',%.2f,'%s')", pid, strTransform.c_str(), (*cItr).guid.c_str(), (*cItr).chunkID.c_str(), 
					   (*cItr).nextGUID.c_str(), (*cItr).nextChunkID.c_str(), (*cItr).backGUID.c_str(), 
					   (*cItr).backChunkID.c_str(), fSpeed, (*cItr).description.c_str() );
					   
		//if( (*cItr).id < 0 )
		//{
		//	strSql.Format( "INSERT INTO FlyThrough_Nodes (pid, transform, guid, chunkID, nextGUID, \
		//				   nextChunkID, backGUID, backChunkID, speed) Values (%d,'%s','%s','%s','%s',\
		//				   '%s','%s','%s',%.2f)", pid, strTransform.c_str(), (*cItr).guid.c_str(), (*cItr).chunkID.c_str(), 
		//				   (*cItr).nextGUID.c_str(), (*cItr).nextChunkID.c_str(), (*cItr).backGUID.c_str(), 
		//				   (*cItr).backChunkID.c_str(), fSpeed );
		//}
		//else
		//{
		//	strSql.Format( "UPDATE [FlyThrough_Nodes] SET [pid]=%d,[transform]='%s',[guid]='%s',\
		//				   [chunkID]='%s',[nextGUID]='%s',[nextChunkID]='%s',[backGUID]='%s',\
		//				   [backChunkID]='%s',[speed]=%.2f WHERE [id]=%d", pid, strTransform.c_str(), 
		//				   (*cItr).guid.c_str(), (*cItr).chunkID.c_str(), (*cItr).nextGUID.c_str(), 
		//				   (*cItr).nextChunkID.c_str(), (*cItr).backGUID.c_str(), 
		//				   (*cItr).backChunkID.c_str(), fSpeed, (*cItr).id );
		//}
		
		vSql.push_back( strSql.GetBuffer() );
	}

	return theBllApp.m_pDB->ExcuteTrans( vSql, adCmdText );
}

BOOL UDOController::loadFromDB( int pid, std::vector< UDOCameraNode >& nodes )
{
	nodes.clear();
	m_mapTemp.clear();

	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return TRUE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough_Nodes"))
	{
		MessageBox(NULL, _T("数据库中不存在FlyThrough_Nodes表")  ,_T("提示"),0);
		return TRUE;
	}

	CString strSql;
	_RecordsetPtr pRecordSet;
	
	strSql.Format( "select * from FlyThrough_Nodes where [pid]=%d", pid );
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes( strSql.GetBuffer(0), adCmdText );

	if( pRecordSet == NULL )
		return FALSE;

	while( !pRecordSet->adoEOF )//如果记录集中有记录
	{
		UDOCameraNode node;
		_variant_t var;

		var = pRecordSet->GetCollect("id");
		node.id = ( var.vt==VT_NULL ? -1 : var.intVal );

		var = pRecordSet->GetCollect("pid");
		node.pid = ( var.vt==VT_NULL ? -1 : var.intVal );
		
		var = pRecordSet->GetCollect("guid");
		node.guid = (_bstr_t)( var.vt==VT_NULL ? "" : var );
		StringUtils::replace( node.guid, " ", "" );

		var = pRecordSet->GetCollect("chunkID");
		node.chunkID = (_bstr_t)( var.vt == VT_NULL ? "" : var );
		StringUtils::replace( node.chunkID, " ", "" );
		
		var = pRecordSet->GetCollect("transform");
		std::string strTransform = (_bstr_t)( var.vt==VT_NULL ? "" : var );
		
		
		//////////////////////////////////////////////////////////////////////////
		//变换矩阵
		Matrix tmpTransform;
		tmpTransform.setIdentity();	//important
		StringUtils::matrixFromString( strTransform, tmpTransform );
		
		//转换矩阵
		Chunk *pChunk = ChunkManager::instance().findChunkByName( 
				node.chunkID, WorldManager::instance().chunkDirMapping() );
		Matrix m = pChunk->transform();
		m.preMultiply( tmpTransform );
		node.transform = m;
		//////////////////////////////////////////////////////////////////////////
		
		var = pRecordSet->GetCollect("nextGUID");
		node.nextGUID = (_bstr_t)( var.vt==VT_NULL ? "" : var );
		StringUtils::replace( node.nextGUID, " ", "" );

		var = pRecordSet->GetCollect("nextChunkID");
		node.nextChunkID = (_bstr_t)( var.vt==VT_NULL ? "" : var );
		StringUtils::replace( node.nextChunkID, " ", "" );

		var = pRecordSet->GetCollect("backGUID");
		node.backGUID = (_bstr_t)( var.vt==VT_NULL ? "" : var );
		StringUtils::replace( node.backGUID, " ", "" );

		var = pRecordSet->GetCollect("backChunkID");
		node.backChunkID = (_bstr_t)( var.vt==VT_NULL ? "" : var );
		StringUtils::replace( node.backChunkID, " ", "" );

		var = pRecordSet->GetCollect("speed");
		std::string str = (_bstr_t)( var.vt==VT_NULL ? "0.1" : var );
		node.speed = (float)atof( str.c_str() );
		
		var = pRecordSet->GetCollect( "description" );
		node.description  = (_bstr_t)( var.vt == VT_NULL ? "" : var );
		StringUtils::replace( node.description, " ", "" );

		nodes.push_back( node );

		// 保存临时数据
		TempStruct tmp;
		tmp.id			= node.id;
		tmp.fSpeed		= node.speed;
		tmp.description = node.description;
		m_mapTemp.insert( std::make_pair(node.guid, tmp) );

		pRecordSet->MoveNext();
	}
	pRecordSet->Close();
	pRecordSet.Release();

	return TRUE;
}

BOOL UDOController::delNodeFromDB( int id )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough_Nodes"))
	{
		MessageBox(NULL, _T("数据库中不存在FlyThrough_Nodes表")  ,_T("提示"),0);
		return FALSE;
	}

	CString strSql;
	strSql.Format( "delete from [FlyThrough_Nodes] where [id]=%d", id );

	return theBllApp.m_pDB->ExcuteSql( strSql.GetBuffer(0), adCmdText );
}

BOOL UDOController::delNodesFromDB( int pid )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough_Nodes"))
	{
		MessageBox(NULL, _T("数据库中不存在FlyThrough_Nodes表")  ,_T("提示"),0);
		return FALSE;
	}

	CString strSql;
	strSql.Format( "delete from [FlyThrough_Nodes] where [pid]=%d", pid );

	BOOL bRes = theBllApp.m_pDB->ExcuteSql( strSql.GetBuffer(0), adCmdText );

	// 是否是当前编辑的节点，是的话就删除场景的UDO对象
	if( bRes && m_iPid == pid )
		clearUdo();

	return bRes;
}

void UDOController::makeUdoFromDB( int pid, int firstid )
{
	loadFromDB( pid, dbNodes_ );

	m_strGuid = getGuid( firstid );

	if( m_strGuid.empty() )// 没有记录
		return;

	if( dbNodes_.empty() )
		return;

	m_objects = EditorChunkUserDataObject::getUserDataObjects();
	for( std::vector< UDOCameraNode >::iterator rItr = dbNodes_.begin(); 
		rItr != dbNodes_.end(); ++rItr )
	{
		//////////////////////////////////////////////////////////////////////////
		//删除重复的
		std::map<std::string, EditorChunkUserDataObject* >::iterator iter = 
			m_objects.find( (*rItr).guid );
		if ( iter != m_objects.end() )
		{
			( iter->second )->edPreDelete();
			( iter->second )->chunk()->delStaticItem( iter->second );
		}	
		//////////////////////////////////////////////////////////////////////////
		
		ChunkItemPtr item = ChunkItemPlacer::createUDOChunkItem(
			(*rItr).transform, (*rItr).guid, (*rItr).chunkID, (*rItr).nextGUID, 
			(*rItr).nextChunkID, (*rItr).backGUID, (*rItr).backChunkID );
			
		//加载不成功，chunk未加载或其他原因,放入后台加载线程。
		//判断条件：1.地形是否已载入 2.节点窗体是否打开
		if ( item == NULL ) 
		{
			nodes_.insert( &*rItr );
			canLoad_ = true;
		}
	}
}

void UDOController::handleMouseEvent( const MouseEvent & event )
{
	if( !m_bHandle )
		return;
	
	POINT pt = WorldManager::instance().currentCursorPosition();
	Vector3 worldRay = WorldManager::instance().getWorldRay(pt);

	Vector3 start =  Moo::rc().invView().applyToOrigin();
	Vector3 extent = start + worldRay * Moo::rc().camera().farPlane();

	CustomCollision sc;
	float fRet = ChunkManager::instance().cameraSpace()->collide( start, extent, sc );

	Vector3 vMousePt = start + worldRay * sc.getCollideDist() ;

	INFO_MSG("%f,%f,%f\n", vMousePt.x, vMousePt.y, vMousePt.z);

	Matrix transform;
	transform.setIdentity();
	transform[ 3 ] = vMousePt;

	ChunkItemPtr pItem = ChunkItemPlacer::createUDOChunkItem( transform );
	if(pItem==NULL)
		INFO_MSG("新建对象为空\n");
	m_strGuid = pItem->edGUID();

	setHandle( false );
}

void UDOController::delUdo( const std::string &guid )
{
	std::vector< UDOCameraNode > vUdo;
	getUdoData( vUdo );
	std::vector< UDOCameraNode >::iterator itr, itrTmp;
	for( itr=vUdo.begin(); itr!=vUdo.end(); ++itr )
	{
		if( guid == itr->guid )
			break;
	}
	if( itr == vUdo.end() )
		return;

	if( itr == vUdo.begin() )// 第一个节点
	{
		CString strSql;
		std::vector<_bstr_t> vSql;
		UDOCamera udoCamera;
		CUDOManager::Instance().GetUdoCamera( itr->pid, udoCamera );
		if( vUdo.size() != 1 )// 多于一个节点
		{
			itrTmp = itr + 1;
			udoCamera.iNodeid = itrTmp->id;
		}
		else
			udoCamera.iNodeid = -1;
		CUDOManager::Instance().UpdateUdoCamera( udoCamera );
	}
	else
	{
		if( ( itr + 1 ) == vUdo.end() ) // 最后一个
		{
			itrTmp = itr - 1;
			itrTmp->nextGUID = "";
			itrTmp->nextChunkID = "";
		}
		else
		{
			itrTmp = itr - 1;
			itrTmp->nextGUID = itr->nextGUID;
			itrTmp->nextChunkID = itr->nextChunkID;
		}
	}
	delNodeFromDB( itr->id );
	vUdo.erase( itr );

	int firstid = ( vUdo.empty() ? -1 : vUdo.begin()->id );
	saveToDB( m_iPid, vUdo );

	// 删除所有节点
	clearUdo();

	makeUdoFromDB( m_iPid, firstid );
}

void UDOController::getUdoData( std::vector< UDOCameraNode > &vUdo )
{
	getLinkObjects( vUdo, m_strGuid );
}

void UDOController::clearUdo()
{
	m_objects = EditorChunkUserDataObject::getUserDataObjects();
	std::map<std::string, EditorChunkUserDataObject* >::iterator itrObj;
	
	for( itrObj=m_objects.begin(); itrObj!=m_objects.end(); ++itrObj )
	{
		( itrObj->second )->edPreDelete();
		( itrObj->second )->chunk()->delStaticItem( itrObj->second );
	}
	
	m_objects.clear();
}

void UDOController::Fly( const UDOCamera &udoCamera, bool bDiffer )
{ 
	std::vector<UDOCameraNode> vUdoCN; 
	std::vector< FlyData > vFlyData;

	loadFromDB( udoCamera.id, vUdoCN );
	if( vUdoCN.empty() )
		return;

	std::vector<UDOCameraNode>::iterator itr;
	for( itr = vUdoCN.begin(); itr != vUdoCN.end(); ++itr )
	{
		Chunk *pChunk = ChunkManager::instance().findChunkByName( 
			(*itr).chunkID, WorldManager::instance().chunkDirMapping() );

		Matrix tmpMatrix;
		tmpMatrix.multiply( (*itr).transform, pChunk->transformInverse() );

		Matrix itemMatrix = pChunk->transform();
		itemMatrix.preMultiply( tmpMatrix );

		Vector3 pos = itemMatrix.applyToOrigin();

		Vector3 rot;
		rot.x = itemMatrix.yaw();
		rot.y = itemMatrix.pitch();
		rot.z = itemMatrix.roll();

		FlyData flyData;
		flyData.pos         = pos;
		flyData.rot			= rot;
		flyData.speed		= (*itr).speed;
		flyData.description = (*itr).description;

		vFlyData.push_back( flyData );

		if( itr == vUdoCN.begin() )
		{
			vFlyData.push_back( flyData );
		}
		if( (itr + 1) == vUdoCN.end() )
		{
			vFlyData.push_back( flyData );
		}
	}

	Fly::instance().setFlyData( vFlyData, udoCamera.fSpeed, bDiffer );
	Fly::instance().setFly( true );
}

void UDOController::updateSpeed( const std::map<std::string, TempStruct> &mapSpeed )
{
	std::map<std::string, TempStruct>::const_iterator cItr;
	for( cItr = mapSpeed.begin(); cItr != mapSpeed.end(); ++cItr )
	{
		if( m_mapTemp.find( (*cItr).first ) != m_mapTemp.end() )
		{
			m_mapTemp[(*cItr).first].fSpeed		 = (*cItr).second.fSpeed;
			m_mapTemp[(*cItr).first].description = (*cItr).second.description;
		}
		else
		{
			TempStruct tmp;
			tmp.id = -1;
			tmp.fSpeed = ( (*cItr).second.fSpeed < MIN_SPEED ? MIN_SPEED : (*cItr).second.fSpeed );
			tmp.description = (*cItr).second.description;
			
			m_mapTemp.insert( std::make_pair( (*cItr).first, tmp ) );
		}
	}
}

void UDOController::setPID( int pid )
{
	m_iPid = pid;
}

int UDOController::getID( const std::string &strGuid )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough_Nodes"))
	{
		MessageBox(NULL, _T("数据库中不存在FlyThrough_Nodes表")  ,_T("提示"),0);
		return FALSE;
	}

	int id = -1;
	CString strSql;
	strSql.Format( "select * from [FlyThrough_Nodes] where [guid]='%s'", strGuid.c_str() );
	
	_RecordsetPtr pRecordSet = theBllApp.m_pDB->ExcuteSqlRes( strSql.GetBuffer(0), adCmdText );

	if( pRecordSet != NULL && !pRecordSet->adoEOF )
	{
		_variant_t var;
		var = pRecordSet->GetCollect("id");
		// 保存第一个GUID
		id = ( var.vt==VT_NULL ? -1 : var.intVal );
	}

	return id;
}

std::string UDOController::getGuid( int id )
{
	CString strSql;
	strSql.Format( "select * from [FlyThrough_Nodes] where [id]=%d", id );
	_RecordsetPtr pRecordSet = theBllApp.m_pDB->ExcuteSqlRes( strSql.GetBuffer(), adCmdText );

	std::string strGuid = "";
	if( pRecordSet != NULL && !pRecordSet->adoEOF )
	{
		_variant_t var;
		var = pRecordSet->GetCollect("guid");
		// 保存第一个GUID
		strGuid = (_bstr_t)( var.vt==VT_NULL ? "" : var );
	}

	return strGuid;
}

bool UDOController::isUdoExist( int id )
{
	std::string strGuid = getGuid( id );
	if( strGuid.empty() )
		return false;

	m_objects = EditorChunkUserDataObject::getUserDataObjects();
	for ( std::map<std::string, EditorChunkUserDataObject* >::iterator
		itr = m_objects.begin(); itr != m_objects.end(); itr++ )
	{
		if( strGuid == itr->first )
		{
			m_objects.clear();
			return true;
		}
	}
	m_objects.clear();
	
	return false;
}

void UDOController::tick( float dTime )
{	
	if ( !canLoad_ || nodes_.empty() )
		return;
			
	std::set< UDOCameraNode* >::iterator rItr;
	for ( rItr = nodes_.begin(); rItr != nodes_.end(); rItr++ )
	{
		ChunkItemPtr item = ChunkItemPlacer::createUDOChunkItem(
			(*rItr)->transform, (*rItr)->guid, (*rItr)->chunkID, (*rItr)->nextGUID, 
			(*rItr)->nextChunkID, (*rItr)->backGUID, (*rItr)->backChunkID );
		
		//加载成功	
		if ( item != NULL )
		{
			nodes_.erase( rItr );
			rItr = nodes_.begin();
		}
	}
}

/**
 *	停止后台加载
 */
void UDOController::stopLoading()
{	
	setCanLoad( false );
	nodes_.clear();
}