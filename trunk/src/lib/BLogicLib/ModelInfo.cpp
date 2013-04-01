#include "ModelInfo.h"

CModelInfo::CModelInfo()
{
	m_strModPath="c:\\";//模型路径
	m_strPosX="0";//位置X
	m_strPosY="0";//位置Y
	m_strPosZ="0";//位置Z
	m_strCirX="0";//旋转X
	m_strCirY="0";//旋转Y
	m_strCirZ="0";//旋转Z
	m_strZoomX="0";//缩放X
	m_strZoomY="0";//缩放Y
	m_strZoomZ="0";//缩放Z
	m_strCreator=""; //创建人
	m_strCreateTime="2010-1-1";//创建时间
}

CModelInfo::~CModelInfo()
{

}

void CModelInfo::AddField(_bstr_t strFieldName, FieldType enumFieldType,
						  int iFieldSize)
{
	CFields fld;
	fld.AddField(strFieldName,enumFieldType,iFieldSize);
	fld.ClearListFields();
}

BOOL CModelInfo::DelFiled(_bstr_t strTableName, _bstr_t strFieldName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}
	return theBllApp.m_pDB->DropField(strTableName,strTableName);
}

_RecordsetPtr CModelInfo::LoadInfo(std::vector<_bstr_t> vbstrFieldName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL, strFieldName = "",strTmp;
	vector<_bstr_t>::iterator item;
	bool isFirst=true;
	item = vbstrFieldName.begin();
	while(item != vbstrFieldName.end())
	{
		strTmp = ((_bstr_t)*item);
		if (isFirst)
		{
			isFirst=false;
			if(CDatabaseFactory::m_enumDatabaseType==OracleType)
				strFieldName=strTmp;
			else
				strFieldName="["+strTmp+"]";
		}
		else
			strFieldName+=",["+strTmp+"]";
	}
	strSQL = "SELECT " + strFieldName + " FROM 模型基本信息";
	theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

_RecordsetPtr CModelInfo::LoadStr(_bstr_t strField)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT " + strField + " FROM 模型基本信息";
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

BOOL CModelInfo::Add(std::map<_bstr_t,_bstr_t> &mapFlds)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL,strFieldVal,strFieldName;
	_RecordsetPtr pRecordSet;
	_variant_t var;
	adoDataTypeEnum enumDataType;

	strSQL = "SELECT * FROM 模型基本信息";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	MapFld::iterator itr1 = mapFlds.begin();
	MapFld::iterator itr2 = --mapFlds.end();
	while(itr1 != itr2)
	{
		//字段
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strFieldName += (*itr1).first + ",";
		else
			strFieldName +="[" +(*itr1).first + "],";
		//值
		var.bstrVal = (*itr1).first;
		enumDataType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
		if(enumDataType == ADODB::adDate || enumDataType == ADODB::adDBTimeStamp)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case AccessType:
				strFieldVal += "#" + (*itr1).second + "#,";
				break;
			case SqlServerType:
				strFieldVal += "'" + (*itr1).second + "',";
				break;
			case OracleType:
				strFieldVal += "to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
				break;
			}
		}
		else if( (enumDataType == ADODB::adInteger ) || (enumDataType == ADODB::adNumeric) || (enumDataType == ADODB::adDouble ) )
			strFieldVal+=(*itr1).second+",";
		else
			strFieldVal+="'"+(*itr1).second+"',";
		//循环
		itr1++;
	}
	//最后字段
	//字段
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strFieldName += (*itr1).first;
	else
		strFieldName +="[" +(*itr1).first + "]";
	//值
	var.bstrVal = (*itr1).first;
	enumDataType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
	if(enumDataType == ADODB::adDate || enumDataType == ADODB::adDBTimeStamp)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case AccessType:
			strFieldVal += "#" + (*itr1).second + "#";
			break;
		case SqlServerType:
			strFieldVal += "'" + (*itr1).second + "'";
			break;
		case OracleType:
			strFieldVal += "to_date('" + (*itr1).second + "','yyyy-mm-dd')";
			break;
		}
	}
	else if( (enumDataType == ADODB::adInteger ) || (enumDataType == ADODB::adNumeric) || (enumDataType == ADODB::adDouble ) )
		strFieldVal+=(*itr1).second;
	else
		strFieldVal+="'"+(*itr1).second+"'";
	strSQL = "INSERT INTO 模型基本信息 (" + strFieldName + ") VALUES (" + strFieldVal + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CModelInfo::Add(_bstr_t GUID)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	m_strModID = GUID;
	_bstr_t strSQL, strFieldName, strFieldVal;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strFieldName = "(GUID,模型路径,位置X,位置Y,位置Z,旋转X,旋转Y,旋转Z,缩放X,缩放Y,缩放Z,创建人,创建时间)";
	else
		strFieldName = "([GUID],模型路径,位置X,位置Y,位置Z,旋转X,旋转Y,旋转Z,缩放X,缩放Y,缩放Z,创建人,创建时间)";

	strFieldVal = "('" + m_strModID + "','" + m_strModPath + "'," + m_strPosX + "," + m_strPosY + ","
		+ m_strPosZ + "," + m_strCirX + "," + m_strCirY + "," + m_strCirZ + "," + m_strZoomX + ","
		+ m_strZoomY + "," + m_strZoomZ;
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		strFieldVal+=",'"+m_strCreator+"',to_date('" + m_strCreateTime + "','dd/mm/yyyy'))";
		break;
	case SqlServerType:
		strFieldVal+=",'"+m_strCreator+"','"+m_strCreateTime+"')";
		break;
	case AccessType:
		strFieldVal+=",'"+m_strCreator+"',#"+m_strCreateTime+"#)";
		break;
	default :
		return FALSE;
	}
	strSQL = "INSERT INTO 模型基本信息" + strFieldName + " values " + strFieldVal;
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CModelInfo::Load(_bstr_t strGUID)
{
	if (strGUID.length()<1)
	{
		MessageBox(NULL,_T("请选择要加载的模型！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	BOOL bFlag=FALSE;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT * FROM 模型基本信息 WHERE [GUID] = '"+ strGUID + "'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL = "SELECT * FROM 模型基本信息 WHERE GUID = '"+ strGUID + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL&&!pRecordSet->adoEOF)
	{
		bFlag = TRUE;
		m_strModID = strGUID;
		m_strModPath = (_bstr_t)pRecordSet->GetCollect("模型路径");
		m_strPosX = (_bstr_t)pRecordSet->GetCollect("位置X");
		m_strPosY = (_bstr_t)pRecordSet->GetCollect("位置Y");
		m_strPosZ = (_bstr_t)pRecordSet->GetCollect("位置Z");
		m_strCirX = (_bstr_t)pRecordSet->GetCollect("旋转X");
		m_strCirY = (_bstr_t)pRecordSet->GetCollect("旋转Y");
		m_strCirZ = (_bstr_t)pRecordSet->GetCollect("旋转Z");
		m_strZoomX = (_bstr_t)pRecordSet->GetCollect("缩放X");
		m_strZoomY = (_bstr_t)pRecordSet->GetCollect("缩放Y");
		m_strZoomZ = (_bstr_t)pRecordSet->GetCollect("缩放Z");
		m_strCreator=(_bstr_t)pRecordSet->GetCollect("创建人");
		m_strCreateTime=(_bstr_t)pRecordSet->GetCollect("创建时间");

		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

BOOL CModelInfo::Update()
{
	if (m_strModID.length()<1)
	{
		MessageBox(NULL,_T("请选择要更新模型"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	strSQL = "UPDATE 模型基本信息 SET 模型路径 = '" + m_strModPath
		+ "',位置X = " + m_strPosX + ",位置Y = " + m_strPosY + ",位置Z = " + m_strPosZ 
		+ ",旋转X = " + m_strCirX + ",旋转Y = " + m_strCirY + ",旋转Z = " + m_strCirZ 
		+ ",缩放X = " + m_strZoomX + ",缩放Y = " + m_strZoomY + ",缩放Z = " + m_strZoomZ;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL+= "  WHERE GUID = '" + m_strModID + "'";
	else
		strSQL+= "  WHERE [GUID] = '" + m_strModID + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CModelInfo::Delete()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL = "DELETE FROM 模型基本信息 WHERE [GUID] = '" + m_strModID + "'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL = "DELETE FROM 模型基本信息 WHERE GUID = '" + m_strModID + "'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CModelInfo::Delete(CString strGUIDS)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSQL, strBuf;
	CString str;
	int nPos = 0;
	str = strGUIDS.Tokenize(_T(","),nPos);
	while(!str.IsEmpty())
	{
		strBuf += "'";
		strBuf += (_bstr_t)str;
		strBuf += "'";
		str = strGUIDS.Tokenize(_T(","),nPos);
		if(!str.IsEmpty())
		{
			strBuf += ",";
		}
	}
	strSQL = "DELETE FROM 模型基本信息 WHERE [GUID] IN(" + strBuf + ")";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL = "DELETE FROM 模型基本信息 WHERE GUID IN(" + strBuf + ")";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CModelInfo::QueryAllModel()
{
	return QueryModelByCondit("");
}

void CModelInfo::QueryAllModel(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryAllModel();
	if (prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CModelInfo::QueryModelByCondit(_bstr_t STRWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("模型基本信息"))
	{
		MessageBox(NULL,_T("数据库中不存在模型基本信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL = "SELECT [GUID],模型路径,位置X,位置Y,位置Z,旋转X,旋转Y,旋转Z,缩放X,缩放Y,缩放Z,创建人,创建时间  FROM 模型基本信息 WHERE 1=1 " + STRWhere;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL="SELECT GUID,模型路径,位置X,位置Y,位置Z,旋转X,旋转Y,旋转Z,缩放X,缩放Y,缩放Z,创建人,创建时间   FROM 模型基本信息 WHERE 1=1 " + STRWhere;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	return pRecordSet;
}

void CModelInfo::QueryModelByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryModelByCondit(bstrWhere);
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
//创建查询
//创建查询
_RecordsetPtr CModelInfo::QueryCreateModel(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere="";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and 创建人='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and 创建时间 = to_date('" + strBeginTime + "','dd/mm/yyyy') and  to_date('" + strEndTime + "','dd/mm/yyyy')";
		else if(strBeginTime.length()>0)
			strSqlwhere+="    and 创建时间 = to_date('" + strBeginTime + "','dd/mm/yyyy')";
		else if(strEndTime.length()>0)
			strSqlwhere+="    and 创建时间 = to_date('" + strEndTime + "','dd/mm/yyyy')";
		break;
	case SqlServerType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and 创建人='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and 创建时间 between '"+strBeginTime+"' and '"+strEndTime+"'";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and 创建时间='"+strBeginTime+"'";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and 创建时间='"+strEndTime+"'";
		break;
	case AccessType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and 创建人='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and 创建时间 between #"+strBeginTime+"# and #"+strEndTime+"#";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and 创建时间=#"+strBeginTime+"#";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and 创建时间=#"+strEndTime+"#";
		break;
	default:
		return NULL;
	}
	return QueryModelByCondit(strSqlwhere);
}
void CModelInfo::QueryCreateModel(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateModel( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}