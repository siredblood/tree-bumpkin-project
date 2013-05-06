#include "pch.hpp"
#include "buildingSchemeDatabase.h"
#include "DataBaseLib/DBHelper.h"

BuildingSchemeDatabase::BuildingSchemeDatabase()
{

}

BuildingSchemeDatabase::~BuildingSchemeDatabase()
{

}

void BuildingSchemeDatabase::loadScheme( std::map<CString, std::map<CString, CString>> &vScheme )
{
	INFO_MSG("loadScheme\n");
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("建筑替换方案"))
	{
		MessageBox(NULL,_T("数据库中不存在建筑替换方案业务表！"),_T("提示"),0);
		return;
	}

	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT * FROM 建筑替换方案";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		while(!pRecordSet->adoEOF)
		{
			CString strName = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("方案名称");
			CString strBeReplace = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("原模型");
			CString strNewModel = (LPCSTR)(_bstr_t)pRecordSet->GetCollect("替换模型");

			//INFO_MSG("%s,%s,%s\n", strName,strBeReplace,strNewModel);
			std::map<CString, std::map<CString, CString>>::iterator itr = vScheme.find(strName);
			if(itr==vScheme.end())
			{
				//INFO_MSG("不存在\n");
				std::map<CString, CString> list;
				list.insert( std::pair<CString, CString>(strBeReplace, strNewModel) );
				vScheme.insert( std::pair<CString, std::map<CString, CString>>(strName, list) );
			}
			else
			{
				itr->second.insert( std::pair<CString, CString>(strBeReplace, strNewModel) );
			}
			pRecordSet->MoveNext();
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
}

BOOL BuildingSchemeDatabase::addScheme( CString strScheme, CString strBeReplacedModel, CString strNewModel )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("建筑替换方案"))
	{
		MessageBox(NULL,_T("数据库中不存在建筑替换方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "INSERT INTO 建筑替换方案(方案名称,原模型,替换模型) values('" + strScheme +"','" + strBeReplacedModel
		+"','" + strNewModel + "')";
	
	//INFO_MSG(strSQL);
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL BuildingSchemeDatabase::deleteScheme( CString strScheme )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("建筑替换方案"))
	{
		MessageBox(NULL,_T("数据库中不存在建筑替换方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 建筑替换方案 WHERE 方案名称='" + strScheme + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL BuildingSchemeDatabase::deleteScheme( CString strScheme, CString strBeReplacedModel )
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("建筑替换方案"))
	{
		MessageBox(NULL,_T("数据库中不存在建筑替换方案业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 建筑替换方案 WHERE 方案名称='" + strScheme + "' and 原模型='" + strBeReplacedModel + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}
