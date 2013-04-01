#include "Duty.h"

CDuty::CDuty(void)
{
	m_strAdress = "";
	m_strDate = "";
	m_strID = "";
	m_strPliceID = "";
	m_strTime = "";
	m_strAudit="";
	m_strRemark = "";
}

CDuty::~CDuty(void)
{
}


BOOL CDuty::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat= "", strValuesFormat= "", strSQL= "";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (编号,警力ID,执勤地点,执勤日期,执勤班次,观众数,备注)";
		strValuesFormat = "(执勤表序列.NextVal,'" + m_strPliceID + "','"
			+ m_strAdress + "'," + "to_date('" + m_strDate + "','dd/mm/yyyy'),'"
			+ m_strTime + "','"+m_strAudit+"','" + m_strRemark + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(警力ID,执勤地点,执勤日期,执勤班次,观众数,备注)";
		strValuesFormat = "('" + m_strPliceID + "','"+ m_strAdress 
			+ "','" + m_strDate + "','" + m_strTime + "','"+m_strAudit+"','" + m_strRemark + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO 执勤表 " + strColumnsFormat + " Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDuty::Load(_bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的执勤编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL = "SELECT 编号,警力ID,执勤地点,执勤日期,执勤班次,观众数,备注 FROM 执勤表 WHERE 编号 = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if(!pRecordSet->adoEOF)//如果记录集中有记录
		{
			bFlag = TRUE;
			_variant_t var;
			m_strID = bstrID;
			var=pRecordSet->GetCollect("警力ID");
			m_strPliceID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("执勤地点");
			m_strAdress = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("执勤日期");
			m_strDate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("执勤班次");
			m_strTime = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("观众数");
			m_strAudit = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("备注");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CDuty::Update()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要更新记录！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strSQL = "UPDATE 执勤表 SET 警力ID = '" + m_strPliceID + "',执勤地点 = '"
			+ m_strAdress + "',执勤日期 = " + "to_date('" + m_strDate 
			+ "','yyyy/mm/dd')" + ",执勤班次 = '" + m_strTime + "',观众数='"+m_strAudit+"',备注 = '" 
			+ m_strRemark + "' WHERE 编号 = " + m_strID;
		break;
	case AccessType:
	case SqlServerType:
		strSQL = "UPDATE 执勤表 SET 警力ID = '" + m_strPliceID + "',执勤地点 = '"
			+ m_strAdress + "',执勤日期 = '" + m_strDate + "',执勤班次 = '" 
			+ m_strTime + "',观众数='"+m_strAudit+"',备注 = '" 	+ m_strRemark + "' WHERE 编号 = " 
			+ m_strID;
		break;
	default:
		return FALSE;
	}
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDuty::Delete()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除的记录！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 执勤表 WHERE 编号 = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDuty::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除的记录！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "DELETE FROM 执勤表 WHERE 编号 IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CDuty::QueryAllDuty()
{
	return QueryDutyByCondit("");
}

void CDuty::QueryAllDuty(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllDuty();
	if (Rcst==NULL)
		return ;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit( Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CDuty::QueryDutyByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "SELECT  编号,警力ID,执勤地点,执勤日期,执勤班次,观众数,备注  FROM 执勤表 WHERE 1=1 " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CDuty::QueryDutyByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryDutyByCondit(bstrWhere);
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}
//查询记录
_RecordsetPtr CDuty::QueryDutyRcst(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	_bstr_t strSqlwhere=GetWhereSql(strBeginDate,strEndDate,strdutyTimes,strAddress);
	return QueryDutyByCondit( strSqlwhere );
}
//警力GUID获取
_RecordsetPtr CDuty::QueryRCSTPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="select 警力ID  from  执勤表   where 1=1 ";
	strSQL+=GetWhereSql(strBeginDate,strEndDate,strdutyTimes,strAddress);
	strSQL+="  GROUP BY  警力ID";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

//警力部署控件GUID
vector<string> CDuty::QueryVectorPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	vector<string> polctlGUID;
	_RecordsetPtr rst=QueryRCSTPolCtlGUID(strBeginDate,strEndDate,strdutyTimes,strAddress);
	if (rst!=NULL)
	{
		string polid;
		while(!rst->adoEOF)
		{
			polid=(char *)((_bstr_t)rst->GetCollect("警力ID"));
			polctlGUID.push_back(polid);
			rst->MoveNext();
		}
		rst->Close();
		rst.Release();
	}
	return polctlGUID;
}
//统计警力
long CDuty::SumDutyPol(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	long lRst=0;
	_RecordsetPtr Rst=QueryRCSTPolCtlGUID(strBeginDate,strEndDate,strdutyTimes,strAddress);
	if (Rst!=NULL)
		lRst=Rst->GetRecordCount();
	return lRst;
}
//统计记录数
long CDuty::SumDutyRecords(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	long lRst=0;
	_RecordsetPtr Rst=QueryDutyRcst(strBeginDate,strEndDate,strdutyTimes,strAddress);
	if (Rst!=NULL)
		lRst=Rst->GetRecordCount();
	return lRst;
}
_bstr_t CDuty::GetWhereSql(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress)
{
	_bstr_t strSQL="";
	if (strdutyTimes.length()>0)
	{
		strSQL+="  and  执勤班次='"+strdutyTimes+"'";
	}
	if (strAddress.length()>0)
	{
		strSQL+="  and  执勤地点 like '%" + strAddress + "%'";
	}
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		if (strBeginDate.length()>0 && strEndDate.length()>0)
		{
			strSQL+="  and 执勤日期 BETWEEN #"+ strBeginDate+"#  AND  #"+strEndDate+"#";
		}
		else if (strBeginDate.length()>0)
		{
			strSQL+="  and 执勤日期=#"+ strBeginDate+"#";
		}
		else if (strEndDate.length()>0)
		{
			strSQL+="  and 执勤日期=#"+strEndDate+"#";
		}
		break;
	case SqlServerType:
		if (strBeginDate.length()>0 && strEndDate.length()>0)
		{
			strSQL+="  and 执勤日期 BETWEEN '"+ strBeginDate+"'  AND  '"+strEndDate+"'";
		}
		else if (strBeginDate.length()>0)
		{
			strSQL+="  and 执勤日期='"+ strBeginDate+"'";
		}
		else if (strEndDate.length()>0)
		{
			strSQL+="  and 执勤日期='"+strEndDate+"'";
		}
		break;
	case OracleType:
		if (strBeginDate.length()>0 && strEndDate.length()>0)
		{
			strSQL+="  and 执勤日期 BETWEEN  to_date('" + strBeginDate + "','dd/mm/yyyy')  AND  to_date('" + strEndDate + "','dd/mm/yyyy')";
		}
		else if (strBeginDate.length()>0)
		{
			strSQL+="  and 执勤日期=to_date('" + strBeginDate + "','dd/mm/yyyy')";
		}
		else if (strEndDate.length()>0)
		{
			strSQL+="  and 执勤日期=to_date('" + strEndDate + "','dd/mm/yyyy')";
		}
		break;
	default:
		strSQL= "";
	}
	return strSQL;
}
bool CDuty::CheckCollision(_bstr_t strId,_bstr_t strPolId,_bstr_t strDate,_bstr_t strDutyTimes)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return true;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤表"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤表业务表！"),_T("提示"),0);
		return true;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="select  编号  from  执勤表   where 警力ID='"+strPolId+"' and 执勤班次='"+strDutyTimes+"'  ";
	if (strId.length()>0)
		strSQL+="   and 编号<>"+strId;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		strSQL="  and 执勤日期=#" + strDate + "#";
		break;
	case SqlServerType:
		strSQL=" and 执勤日期='" +strDate+" '";
		break;
	case OracleType:
		strSQL=" and 执勤日期=to_date('" + strDate + "','dd/mm/yyyy')";
		break;
	default :
		return true;
	}

	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

//////////////////////////////////////////////////////////////////////////

CDutyTime::CDutyTime()
{

}

CDutyTime::~CDutyTime()
{

}


BOOL CDutyTime::Add(_bstr_t strTime,_bstr_t strRemark)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤班次"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤班次业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat= "", strValuesFormat= "", strSQL;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (编号,执勤时间,备注)";
		strValuesFormat = "(执勤班次序列.NextVal,'" + strTime + "','"
			+ strRemark + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(执勤时间,备注)";
		strValuesFormat = "('" + strTime + "','"
			+ strRemark + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO 执勤班次 " + strColumnsFormat + "  Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDutyTime::Update(_bstr_t strID, _bstr_t strTime, _bstr_t strRemark)
{
	if (strID.length()<=0)
	{
		MessageBox(NULL,_T("修改编号不能为空！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤班次"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤班次业务表！"),_T("提示"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "UPDATE 执勤班次 SET 执勤时间 = '" + strTime
		+ "',备注 = '" + strRemark + "' WHERE 编号 = "+ strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CDutyTime::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除的记录编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤班次"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤班次业务表！"),_T("提示"),0);
		return FALSE;
	}

	_bstr_t strSQL;
	strSQL = "DELETE FROM 执勤班次 WHERE 编号 IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

//得到所以班次
std::vector<string> CDutyTime::QueryTimes()
{
	vector<string> v;
	_RecordsetPtr rcst=QueryDutyTimeByCondit("");
	if (rcst!=NULL&&!rcst->adoEOF)
	{
		string temp;
		while(!rcst->adoEOF)
		{
			temp=(char *)((_bstr_t)rcst->GetCollect("执勤时间"));
			v.push_back(temp);
			rcst->MoveNext();
		}
	}
	return v;

}

_RecordsetPtr CDutyTime::QueryAllDutyTime()
{
	return QueryDutyTimeByCondit("");
}

void CDutyTime::QueryAllDutyTime(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllDutyTime();
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CDutyTime::QueryDutyTimeByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("执勤班次"))
	{
		MessageBox(NULL,_T("数据库中不存在该执勤班次业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL = "SELECT 编号,执勤时间,备注  FROM 执勤班次 WHERE 1=1 " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CDutyTime::QueryDutyTimeByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryDutyTimeByCondit(bstrWhere);
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}