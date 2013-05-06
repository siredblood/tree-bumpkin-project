#include "pch.hpp"
#include "SectorizationDatabase.h"
#include "DataBaseLib/DBHelper.h"
#include "GeneralClass/Common.h"

SectorizationDatabase::SectorizationDatabase()
{

}

SectorizationDatabase::~SectorizationDatabase()
{

}

void SectorizationDatabase::loadSectorization( std::vector<SECTORIZATIONDATA>& vData )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("功能分区"))
	{
		MessageBox(NULL,_T("数据库中不存在功能分区业务表！"),_T("提示"),0);
		return;
	}

	SECTORIZATIONDATA data;

	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT * FROM 功能分区";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		while(!pRecordSet->adoEOF)
		{
			CString strName = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("名称");
			CString strPos = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("视角位置");
			CString strDir = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("视角方向");
			Vector3 pos = ConvertStrToVec3( strPos.GetBuffer(0) );
			Vector3 dir = ConvertStrToVec3( strDir.GetBuffer(0) );
			data.strName = strName;
			data.viewpos = pos;
			data.viewdir = dir;
			data.vGuids.clear();
			_bstr_t strSubSql = "SELECT * FROM 功能分区对象 WHERE 所属分区='" + strName + "'";
			_RecordsetPtr pSubRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSubSql,adCmdText);
			if(pSubRecordSet!=NULL)
			{
				while(!pSubRecordSet->adoEOF)
				{
					CString strGUID = (LPCSTR)(_bstr_t)pSubRecordSet->GetCollect("对象");
					data.vGuids.push_back(strGUID);
					pSubRecordSet->MoveNext();
				}
				pSubRecordSet->Close();
				pSubRecordSet.Release();
			}
			vData.push_back(data);

			pRecordSet->MoveNext();
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	

}

BOOL SectorizationDatabase::addSectorization( CString strName, Vector3 viewpos, Vector3 viewdir )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("功能分区"))
	{
		MessageBox(NULL,_T("数据库中不存在功能分区业务表！"),_T("提示"),0);
		return FALSE;
	}
	CString strpos = ConvertVec3ToStr(viewpos);
	CString strdir = ConvertVec3ToStr(viewdir);

	_bstr_t strSQL;
	strSQL = "INSERT INTO 功能分区(名称,视角位置,视角方向) values('" + strName +"','" + strpos
		+"','" + strdir + "')";

	//INFO_MSG(strSQL);
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::editSectorization( CString strName, Vector3 viewpos, Vector3 viewdir )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("功能分区"))
	{
		MessageBox(NULL,_T("数据库中不存在功能分区业务表！"),_T("提示"),0);
		return FALSE;
	}
	CString strpos = ConvertVec3ToStr(viewpos);
	CString strdir = ConvertVec3ToStr(viewdir);
	
	_bstr_t strSQL;
	strSQL = "UPDATE 功能分区 SET 视角位置 ='" + strpos + "', 视角方向='" + strdir + "' WHERE 名称='" + strName + "'";
	//INFO_MSG(strSQL);

	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::addSectorizationObject( CString strName, CString strGuid )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("功能分区对象"))
	{
		MessageBox(NULL,_T("数据库中不存在功能分区对象业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "INSERT INTO 功能分区对象(所属分区,对象) values('" + strName +"','" + strGuid + "')";

	//INFO_MSG(strSQL);
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::deleteSectorization( CString strName )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("功能分区"))
	{
		MessageBox(NULL,_T("数据库中不存在功能分区对象业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 功能分区 WHERE 名称='" + strName + "'";
	theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);

	strSQL = "DELETE FROM 功能分区对象 WHERE 所属分区='" + strName + "'";

	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL SectorizationDatabase::deleteSectorizationObject( CString strName, CString strGuid )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("功能分区对象"))
	{
		MessageBox(NULL,_T("数据库中不存在功能分区对象业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 功能分区对象 WHERE 所属分区='" + strName + "' AND 对象='" + strGuid + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}