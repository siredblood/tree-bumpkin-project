#include "ControlUser.h"

CControlUser::CControlUser(void)
{
}

CControlUser::~CControlUser(void)
{
}


BOOL CControlUser::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("监控用户"))
	{
		MessageBox(NULL,_T("数据库中不存在该监控用户业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat = "", strValuesFormat= "" , strSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (编号,服务器,用户名,密码)";
		strValuesFormat = "(监控用户序列.NextVal,'" + m_strServer + "','"+ m_strUserName +  "','" + m_strPassWord + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(服务器,用户名,密码)";
		strValuesFormat = "('" + m_strServer + "','" + m_strUserName +  "','" + m_strPassWord + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO 监控用户 " + strColumnsFormat + " Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CControlUser::Load(_bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载监控用户编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("监控用户"))
	{
		MessageBox(NULL,_T("数据库中不存在该监控用户业务表！"),_T("提示"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT 编号,服务器,用户名,密码 FROM 监控用户 WHERE 编号 = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);

	if(pRecordSet!=NULL)//如果记录集中有记录
	{
		if (!pRecordSet->adoEOF)
		{
			bFlag = TRUE;
			_variant_t var;
			m_strID = bstrID;
			var=pRecordSet->GetCollect("服务器");
			m_strServer = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("用户名");
			m_strUserName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("密码");
			m_strPassWord = (_bstr_t)(var.vt==1?"":var);
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}


BOOL CControlUser::Update()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要更新监控用户！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("监控用户"))
	{
		MessageBox(NULL,_T("数据库中不存在该监控用户业务表！"),_T("提示"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "UPDATE 监控用户 SET 服务器 = '" + m_strServer + "',用户名 = '"
		+ m_strUserName + "',密码 = '" + m_strPassWord+ "' WHERE 编号 = " 
		+ m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CControlUser::Delete()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除监控用户编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("监控用户"))
	{
		MessageBox(NULL,_T("数据库中不存在该监控用户业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 监控用户 WHERE 编号 = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CControlUser::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除监控用户编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("监控用户"))
	{
		MessageBox(NULL,_T("数据库中不存在该监控用户业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 监控用户 WHERE 编号 IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CControlUser::QueryAllUser()
{
	return QueryUserByCondit("");
}
vector<string> CControlUser::GetAllUserName()
{
	vector<string> v;
	string strTemp;
	_RecordsetPtr Rcst=QueryAllUser();
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			strTemp=(char *)((_bstr_t)Rcst->GetCollect("用户名"));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	return v;
}

void CControlUser::QueryAllUser(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllUser();
	if ( Rcst == NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CControlUser::QueryUserByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("监控用户"))
	{
		MessageBox(NULL,_T("数据库中不存在该监控用户业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL = "SELECT 编号,服务器,用户名,密码  FROM 监控用户 WHERE 1=1 " + STRWhere;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

void CControlUser::QueryUserByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryUserByCondit(bstrWhere);
	if (Rcst == NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}