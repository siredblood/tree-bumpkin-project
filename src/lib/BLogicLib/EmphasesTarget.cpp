#include "EmphasesTarget.h"

CEmphasesTarget CEmphasesTarget::instance;

CEmphasesTarget::CEmphasesTarget(void)
{
}

CEmphasesTarget::~CEmphasesTarget(void)
{
}

CEmphasesTarget & CEmphasesTarget::Instance()
{
	return instance;
}
BOOL CEmphasesTarget::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strColumnsFormat= "", strValuesFormat= "", strSQL="";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (编号,名称,类型,所属区域,地址,坐标,描述)";
		strValuesFormat = "(重点目标序列.NextVal,'" + m_strName + "','"
			+ m_strType +  "','" + m_strArea + "','"+m_strAddress+"','" + m_strCoordinate
			+  "','" + m_strRemark + "')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(名称,类型,所属区域,地址,坐标,描述)";
		strValuesFormat = "('" + m_strName + "','" + m_strType +  "','" 
			+ m_strArea +"','"+m_strAddress+"','" + m_strCoordinate +  "','" + m_strRemark + "')";
		break;
	default:
		break;
	}
	strSQL = "INSERT INTO  重点目标 "+strColumnsFormat+"  Values " + strValuesFormat;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CEmphasesTarget::Load(_bstr_t bstrID)
{
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载重点目标编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT 编号,名称,类型,所属区域,地址,坐标,描述 FROM 重点目标 WHERE 编号 = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if (!pRecordSet->adoEOF)
		{
			m_strID = bstrID;
			_variant_t var;
			var=pRecordSet->GetCollect("名称");
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("类型");
			m_strType = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("所属区域");
			m_strArea = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("地址");
			m_strAddress = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("坐标");
			m_strCoordinate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("描述");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			bFlag=TRUE;
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CEmphasesTarget::LoadByName(_bstr_t bstrName)
{
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载重点目标名称！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT 编号,名称,类型,所属区域,地址,坐标,描述 FROM 重点目标 WHERE 名称 = '" + bstrName+"'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if (!pRecordSet->adoEOF)
		{
			_variant_t var;
			var=pRecordSet->GetCollect("编号");
			m_strID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("名称");
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("类型");
			m_strType = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("所属区域");
			m_strArea = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("地址");
			m_strAddress = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("坐标");
			m_strCoordinate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("描述");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
			bFlag=TRUE;
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}
//检查重点目标名称是否存在
BOOL CEmphasesTarget::CheckNameExist(_bstr_t bstrName)
{
	if (bstrName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载重点目标名称！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT 编号,名称,类型,所属区域,地址,坐标,描述 FROM 重点目标 WHERE 名称 = '" + bstrName+"'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet==NULL)
		return FALSE;
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
		return TRUE;
	pRecordSet->Close();
	pRecordSet.Release();
	return FALSE;
}
//检查重点目标名称更新
BOOL CEmphasesTarget::NameValidate(_bstr_t bstrName,_bstr_t bstrID)
{
	if (bstrName.length()<=0 || bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载重点目标！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT 编号,名称,类型,所属区域,地址,坐标,描述 FROM 重点目标 WHERE 编号<>"+bstrID+" and  名称 = '" + bstrName+"'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
		return FALSE;
	pRecordSet->Close();
	pRecordSet.Release();
	return TRUE;
}
BOOL CEmphasesTarget::Update()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择更改重点目标编号！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "UPDATE 重点目标 SET 名称 = '" + m_strName + "',类型 = '"
		+ m_strType + "',地址='"+ m_strAddress +"',所属区域 = '" + m_strArea + "',坐标 = '"
		+ m_strCoordinate + "',描述 = '" + m_strRemark + 
		"' WHERE 编号 = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CEmphasesTarget::Delete()
{
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除重点目标！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 重点目标 WHERE 编号 = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}
//用名称实现删除
BOOL CEmphasesTarget::DeleteByName(_bstr_t strName)
{
	if (strName.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除重点目标！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 重点目标 WHERE strName = '" + strName+"'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CEmphasesTarget::Delete(_bstr_t strIDS)
{
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要删除重点目标！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 重点目标 WHERE 编号 IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CEmphasesTarget::QueryAllEmphTarg()
{
	return QueryEmphTargByCondit("");
}
std::vector<TARGETMODEL> CEmphasesTarget::QueryAllTarget()
{
	std::vector<TARGETMODEL> vModels;
	TARGETMODEL model;
	_RecordsetPtr pRecordSet=QueryEmphTargByCondit("");
	if (pRecordSet==NULL)
		return vModels;
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
	{
		_variant_t var;
		while(!pRecordSet->adoEOF)
		{
			var=pRecordSet->GetCollect("编号");
			model.m_strID =(char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("名称");
			model.m_strName = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("类型");
			model.m_strType = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("所属区域");
			model.m_strArea = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("地址");
			model.m_strAddress =(char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("坐标");
			model.m_strCoordinate = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			var=pRecordSet->GetCollect("描述");
			model.m_strRemark = (char *)((_bstr_t)(var.vt==1?"":var)) ;
			vModels.push_back(model);
			pRecordSet->MoveNext();
		}
	}
	pRecordSet->Close();
	pRecordSet.Release();
	return vModels;
}
vector<string> CEmphasesTarget::GetAllTargetName()
{
	vector<string> v;
	string strTemp;
	_RecordsetPtr Rcst=QueryAllEmphTarg();
	if (Rcst==NULL)
		return v;
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			strTemp= (char *)((_bstr_t)Rcst->GetCollect("名称"));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	Rcst->Close();
	Rcst.Release();
	return v;
}
//区域
std::vector<string> CEmphasesTarget::GetAreas()
{
	std::vector<string> v;
	string strTemp;
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select distinct 所属区域 from 重点目标",adCmdText);
	if (Rcst==NULL)
		return v;
	if (!Rcst->adoEOF)
	{
		_variant_t var;
		while(!Rcst->adoEOF)
		{
			var=Rcst->GetCollect("所属区域");
			strTemp = (char *)((_bstr_t)(var.vt==1?"":var));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	Rcst->Close();
	Rcst.Release();
	return v;
}
//区域重点目标
std::vector<string> CEmphasesTarget::GetTargetByArea(string strArea)
{
	std::vector<string> v;
	string strTemp;
	strTemp="select distinct 名称 from 重点目标  where 所属区域='"+strArea+"'";
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes(strTemp.c_str(),adCmdText);
	if (Rcst==NULL)
		return v;
	if (!Rcst->adoEOF)
	{
		_variant_t var;
		while(!Rcst->adoEOF)
		{
			var=Rcst->GetCollect("名称");
			strTemp = (char *)((_bstr_t)(var.vt==1?"":var));
			v.push_back(strTemp);
			Rcst->MoveNext();
		}
	}
	Rcst->Close();
	Rcst.Release();
	return v;
}

void CEmphasesTarget::QueryAllEmphTarg(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllEmphTarg();
	if (Rcst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CEmphasesTarget::QueryEmphTargByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标"))
	{
		MessageBox(NULL,_T("数据库中不存在该重点目标业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "SELECT 编号,名称,类型,所属区域,地址,坐标,描述 FROM 重点目标 WHERE 1=1 " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CEmphasesTarget::QueryEmphTargByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryEmphTargByCondit(bstrWhere);
	if(Rcst==NULL)
		return ;
	CBllHelp::Instance().QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}