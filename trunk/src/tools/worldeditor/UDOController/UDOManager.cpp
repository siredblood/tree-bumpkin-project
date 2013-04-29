#include "pch.hpp"
#include "UDOManager.h"
#include "BLogicLib/BllHelp.h"


CUDOManager CUDOManager::s_instance;

CUDOManager::CUDOManager()
{
	;
}

CUDOManager::~CUDOManager()
{
	;
}

CUDOManager &CUDOManager::Instance()
{
	return s_instance;
}

void CUDOManager::AddUdoCamera( const UDOCamera &udoCamera )
{
	if( !Save( udoCamera ) )
	{
		MessageBox( NULL, "���ݿ���Ӽ�¼ʧ��", "��ʾ", MB_OK );
		return;
	}
	if( !Load( m_vUdoCamera ) )
	{
		MessageBox( NULL, "��ȡ���ݿ��¼ʧ��", "��ʾ", MB_OK );
		return;
	}
}

void CUDOManager::UpdateUdoCamera( const UDOCamera &udoCamera )
{
	if( !Save( udoCamera ) )
	{
		CString strError;
		strError.Format( "���ݿ���Ϊ%d�ļ�¼����ʧ��", udoCamera.id );
		MessageBox( NULL, strError, "��ʾ", MB_OK );
		return;
	}

	if( !Load( m_vUdoCamera ) )
	{
		MessageBox( NULL, "��ȡ���ݿ��¼ʧ��", "��ʾ", MB_OK );
		return;
	}
}

void CUDOManager::DelUdoCamera( int id )
{
	if( !Delete( id ) )
	{
		MessageBox( NULL, "ɾ�����ݿ��¼ʧ��", "��ʾ", MB_OK );
		return;
	}
	if( !Load( m_vUdoCamera ) )
	{
		MessageBox( NULL, "��ȡ���ݿ��¼ʧ��", "��ʾ", MB_OK );
		return;
	}
}

void CUDOManager::GetUdoCamera( int id, UDOCamera &udoCamera )
{
	std::vector<UDOCamera>::iterator itr;
	for( itr=m_vUdoCamera.begin(); itr!=m_vUdoCamera.end(); ++itr)
	{
		if( id == itr->id )
		{
			udoCamera = (*itr);
			break;
		}
	}
}

void CUDOManager::GetAllUdoCamera( std::vector<UDOCamera> &vUdoCamera )
{
	if( m_vUdoCamera.empty() )
	{
		if( !Load( m_vUdoCamera ) )
		{
			MessageBox( NULL, "��ȡ���ݿ��¼ʧ��", "��ʾ", MB_OK );
			return;
		}
	}

	vUdoCamera = m_vUdoCamera;
}

//////////////////////////////////////////////////////////////////////////
BOOL CUDOManager::Load( std::vector<UDOCamera> &vUdoCamera )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough"))
	{
		MessageBox(NULL, _T("���ݿ��в�����FlyThrough��")  ,_T("��ʾ"),0);
		return FALSE;
	}

	vUdoCamera.clear();

	CString strSql;
	_RecordsetPtr pRecordSet;

	strSql = "select * from FlyThrough";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes( strSql.GetBuffer(0), adCmdText );

	if( pRecordSet != NULL )
	{
		while( !pRecordSet->adoEOF )//�����¼�����м�¼
		{
			_variant_t var;
			UDOCamera udoCamera;

			var = pRecordSet->GetCollect("id");
			udoCamera.id = ( var.vt==VT_NULL ? -1 : var.intVal );
			var = pRecordSet->GetCollect("name");
			udoCamera.strName = (_bstr_t)( var.vt==VT_NULL ? "" : var );
			var = pRecordSet->GetCollect("speed");
			std::string str = (_bstr_t)( var.vt==VT_NULL ? "" : var );
			udoCamera.fSpeed = (float)atof( str.c_str() );
			var = pRecordSet->GetCollect("nodeid");
			udoCamera.iNodeid = ( var.vt==VT_NULL ? -1 : var.intVal );

			vUdoCamera.push_back( udoCamera );
			pRecordSet->MoveNext();
		}
		pRecordSet->Close();
		pRecordSet.Release();

		return TRUE;
	}
	else 
		return FALSE;
}

BOOL CUDOManager::Save( const UDOCamera &udoCamera )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough"))
	{
		MessageBox(NULL, _T("���ݿ��в�����FlyThrough��")  ,_T("��ʾ"),0);
		return FALSE;
	}

	CString strSql;
	_RecordsetPtr pRecordSet;

	if( udoCamera.id < 0 )
	{
		strSql.Format( "insert into [FlyThrough]([name],[speed],[nodeid]) values ('%s',%.2f,%d)", 
			udoCamera.strName.c_str(), udoCamera.fSpeed, udoCamera.iNodeid );
	}
	else
	{
		strSql.Format( "update [FlyThrough] set [name]='%s',[speed]=%.2f,[nodeid]=%d where [id]=%d", 
			udoCamera.strName.c_str(), udoCamera.fSpeed, udoCamera.iNodeid, udoCamera.id );
	}

	//INFO_MSG("%s\r\n", strSql);

	return theBllApp.m_pDB->ExcuteSql( strSql.GetBuffer(), adCmdText );
}

BOOL CUDOManager::Delete( int id )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("FlyThrough"))
	{
		MessageBox(NULL, _T("���ݿ��в�����FlyThrough��")  ,_T("��ʾ"),0);
		return FALSE;
	}

	std::vector<_bstr_t> vSql;
	CString strSql;
	// ɾ����ǰ·����¼
	strSql.Format( "delete from FlyThrough where [id]=%d", id );
	vSql.push_back( strSql.GetBuffer() );
	// ɾ����ǰ·�����нڵ�
	strSql.Format( "delete from FlyThrough_Nodes where [pid]=%d", id );
	vSql.push_back( strSql.GetBuffer() );

	return theBllApp.m_pDB->ExcuteTrans( vSql, adCmdText );
}
