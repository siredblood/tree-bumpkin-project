#include "CityCamera.h"


CCityCamera::CCityCamera(void)
{
}

CCityCamera::~CCityCamera(void)
{
}

BOOL CCityCamera::Add()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("城市摄像头"))
	{
		MessageBox(NULL,_T("数据库中不存在该城市摄像头业务表！"),_T("提示"),0);
		return FALSE;
	}

	_bstr_t strColumnsFormat;
	_bstr_t strValuesFormat;
	_bstr_t strSQL;
	strColumnsFormat = "";
	strValuesFormat = "";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strColumnsFormat = " (编号,摄像头编号,位置,类型,描述)";
		strValuesFormat = "(城市摄像头序列.NextVal,'" + m_strCameraID + "','"
			+ m_strPosition +  "','" + m_strType + "','" + m_strRemark +"')";
		break;
	case AccessType:
	case SqlServerType:
		strColumnsFormat = "(摄像头编号,位置,类型,描述)";
		strValuesFormat = "('" + m_strCameraID + "','" + m_strPosition +  
			"','" + m_strType + "','" + m_strRemark + "')";
		break;
	default:
		return FALSE;
	}
	strSQL = "INSERT INTO  城市摄像头 " + strColumnsFormat + " Values " + strValuesFormat;

	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CCityCamera::Load(_bstr_t bstrID)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("城市摄像头"))
	{
		MessageBox(NULL,_T("数据库中不存在该城市摄像头业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (bstrID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要加载的城市摄像头编号！"),_T("提示"),0);
		return FALSE;
	}

	BOOL bFlag;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT 编号,摄像头编号,位置,类型,描述 FROM 城市摄像头 WHERE 编号 = " + bstrID;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet!=NULL && !pRecordSet->adoEOF)//如果记录集中有记录
	{
		bFlag = TRUE;
		m_strID = (_bstr_t)pRecordSet->GetCollect("编号");
		m_strCameraID = (_bstr_t)pRecordSet->GetCollect("摄像头编号");
		m_strPosition = (_bstr_t)pRecordSet->GetCollect("位置");
		m_strType = (_bstr_t)pRecordSet->GetCollect("类型");
		m_strRemark = (_bstr_t)pRecordSet->GetCollect("描述");

		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CCityCamera::Update()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("城市摄像头"))
	{
		MessageBox(NULL,_T("数据库中不存在该城市摄像头业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要更新的记录编号！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "UPDATE 城市摄像头 SET 摄像头编号 = '" + m_strCameraID 
		+ "',位置 = '" + m_strPosition + "',类型 = '" + m_strType 
		+ "',描述 = '" + m_strRemark + "' WHERE 编号 = " 
		+ m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CCityCamera::Delete()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("城市摄像头"))
	{
		MessageBox(NULL,_T("数据库中不存在该城市摄像头业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (m_strID.length()<=0)
	{
		MessageBox(NULL,_T("请选择要更新的记录编号！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 城市摄像头 WHERE 编号 = " + m_strID;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CCityCamera::Delete(_bstr_t strIDS)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("城市摄像头"))
	{
		MessageBox(NULL,_T("数据库中不存在该城市摄像头业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (strIDS.length()<=0)
	{
		MessageBox(NULL,_T("请选择要更新的记录编号！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "DELETE FROM 城市摄像头 WHERE 编号 IN (" + strIDS + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CCityCamera::QueryAllCamera()
{
	return QueryCameraByCondit("");
}

void CCityCamera::QueryAllCamera(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllCamera();
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CCityCamera::QueryCameraByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("城市摄像头"))
	{
		MessageBox(NULL,_T("数据库中不存在该城市摄像头业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL;
	strSQL = "SELECT  编号,摄像头编号,位置,类型,描述  FROM 城市摄像头 WHERE 1=1 " + STRWhere;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

void CCityCamera::QueryCameraByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryCameraByCondit(bstrWhere);
	if (Rcst==NULL)
		return;
	CBllHelp *help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}