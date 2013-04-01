#include "TypeInfo.h"
CTypeInfo CTypeInfo::instance;
CTypeInfo::CTypeInfo(void)
{
}

CTypeInfo::~CTypeInfo(void)
{
}
CTypeInfo & CTypeInfo::Instance()
{
	return instance;
}


BOOL CTypeInfo::Add(_bstr_t STRtypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("类别信息"))
	{
		MessageBox(NULL,_T("数据库中不存在类别信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql="", strSql1 = "", strSql2 = "";
	vector<_bstr_t> vecStrSql;

	_RecordsetPtr pRecordSet;
	strSql = "SELECT * FROM 类别信息 WHERE 类别名称 = '" + STRtypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);

	//判断类别信息表是否存在表名
	if(pRecordSet == NULL)
		return FALSE;
	if(!pRecordSet->adoEOF)
	{	//释放资源
		pRecordSet.Release();
		return FALSE;
	}
	//释放资源
	pRecordSet.Release();

	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		{
			//添加记录
			strSql = "INSERT INTO 类别信息(类别名称) VALUES ('" 
				+ STRtypeName + "')";
			theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
			//创建表
			strSql = "CREATE TABLE [" + STRtypeName + "]  ([GUID] MEMO, [坐标] MEMO, [所属目标] MEMO, [名称]  MEMO, [备注]  MEMO)";
			return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
		}
	case SqlServerType:
		//添加记录和表
		strSql = "INSERT INTO 类别信息(类别名称) VALUES ('"
			+ STRtypeName + "'); CREATE TABLE [" + STRtypeName 
			+ "] (GUID VARCHAR(64), 坐标 VARCHAR(64), 所属目标 VARCHAR(128), \
			  名称 VARCHAR(64), 备注 VARCHAR(1024))";
		return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
	case OracleType:
		strSql1 = "INSERT INTO 类别信息(编号, 类别名称) VALUES (类别信息序列.nextVal, '" 
			+ STRtypeName + "')";
		strSql2 = " CREATE TABLE " + STRtypeName 
			+ "(GUID VARCHAR2(64), 坐标 VARCHAR2(64), 所属目标 VARCHAR2(128), \
			  名称 VARCHAR2(64), 备注 VARCHAR2(1024))";
		vecStrSql.push_back(strSql1);
		vecStrSql.push_back(strSql2);
		return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
	}
	return FALSE;
}

BOOL CTypeInfo::Update(_bstr_t strOldTypeName, _bstr_t strNewTypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("类别信息"))
	{
		MessageBox(NULL,_T("数据库中不存在类别信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql="", strSql1 = "", strSql2 = "";
	vector<_bstr_t> vecStrSql;
	_RecordsetPtr pRecordSet;
	strSql = "SELECT * FROM 类别信息 WHERE 类别名称 = '" + strOldTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);

	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
		return FALSE;
	else
		pRecordSet.Release();

	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		//没找到Access更新表名语句
		break;
	case SqlServerType:
		//更新记录
		strSql1 = "UPDATE 类别信息 SET 类别名称 = '" + strNewTypeName + "' WHERE 类别名称 = '"
			+ strOldTypeName + "'";
		theBllApp.m_pDB->ExcuteSql(strSql1,adCmdText);
		//更新表名
		strSql2 = "SP_RENAME '"+ strOldTypeName + "','" + strNewTypeName + "'";
		vecStrSql.push_back(strSql1);
		vecStrSql.push_back(strSql2);
		return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);

	case OracleType:
		//更新记录
		strSql1 = "UPDATE 类别信息 SET 类别名称 = '" + strNewTypeName + "' WHERE 类别名称 = '"
			+ strOldTypeName + "'";
		//更新表名
		strSql2 = "RENAME " + strOldTypeName + " TO " + strNewTypeName;
		vecStrSql.push_back(strSql1);
		vecStrSql.push_back(strSql2);
		return theBllApp.m_pDB->ExcuteTrans(vecStrSql, adCmdText);
	}
	return FALSE;
}

BOOL CTypeInfo::Delete(_bstr_t STRtypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("类别信息"))
	{
		MessageBox(NULL,_T("数据库中不存在类别信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql="";
	vector<_bstr_t> vecStrSql;
	strSql = "DELETE FROM 类别信息 WHERE 类别名称 = '" + STRtypeName + "'";
	vecStrSql.push_back(strSql);
	strSql = "DROP TABLE [" + STRtypeName+"]";
	vecStrSql.push_back(strSql);
	return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
}

_RecordsetPtr CTypeInfo::QueryAllType()
{
	return QueryTypeInfoByCondit("类别信息");
}

void CTypeInfo::QueryAllType(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllType();
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CTypeInfo::QueryTypeInfoByCondit(_bstr_t STRTypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("类别信息"))
	{
		MessageBox(NULL,_T("数据库中不存在类别信息业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql = "";
	strSql = "SELECT * FROM  [" + STRTypeName+"]" ;
	return theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
}

void CTypeInfo::QueryTypeInfoByCondit(_bstr_t STRTypeName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryTypeInfoByCondit(STRTypeName);
	if(Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

vector<string> CTypeInfo::GetTypeNames()
{
	vector<string> VtypeNames;
	_RecordsetPtr Rst=QueryAllType();
	if (Rst!=NULL)
	{
		while(!Rst->adoEOF)
		{
			VtypeNames.push_back((char*)((_bstr_t)Rst->GetCollect("类别名称")));
			Rst->MoveNext();
		}
		Rst->Close();
		Rst.Release();
	}
	return VtypeNames;
}

//图层控件显示
_RecordsetPtr CTypeInfo::QueryGUIDByLayerRcst(_bstr_t strTableName,_bstr_t strWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql = "";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT  GUID  FROM [" + strTableName + "]  WHERE 1=1 "+strWhere;
	else
		strSql = "SELECT [GUID] FROM [" + strTableName + "]  WHERE 1=1 "+strWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
}
vector<string> CTypeInfo::QueryGUIDBylayerVector(_bstr_t strTableName,_bstr_t strWhere)
{
	vector<string> strGUIDs;
	_RecordsetPtr rst=QueryGUIDByLayerRcst(strTableName,strWhere);
	if (rst!=NULL)
	{
		string strvalue;
		while(!rst->adoEOF)
		{
			strvalue=(char*)((_bstr_t)rst->GetCollect("GUID"));
			strGUIDs.push_back(strvalue);
			rst->MoveNext();
		}
	}
	return strGUIDs;
}

//void CTypeInfo::GetTypeInfoDetail(_RecordsetPtr pRecordSet, Vector &vecField, Vector &vecRecordSet, long &lFieldCounts)
//{
//	//判断存在记录
//	if(pRecordSet == NULL)
//		return ;
//
//	try
//	{
//		//字段个数
//		lFieldCounts = pRecordSet->GetFields()->GetCount();
//		DataTypeEnum enumDataType;
//		_bstr_t str;
//		//字段名称、类型、大小
//		for(long i = 0; i<lFieldCounts; i++)
//		{
//				
//			vecField.push_back((LPSTR)str);
//			enumDataType = pRecordSet->GetFields()->GetItem(i)->GetType();
//			str = GetDataTypeString(enumDataType);
//			vecField.push_back((LPSTR)str);
//			str = pRecordSet->GetFields()->GetItem(i)->GetDefinedSize();
//			vecField.push_back((LPSTR)str);
//		}
//		pRecordSet->MoveFirst();
//		long lCounts = 0;
//		//获取记录
//		while(!pRecordSet->adoEOF)
//		{
//			for(long j=0; j<lFieldCounts; j++)
//			{
//				str = pRecordSet->GetCollect(j);
//				vecRecordSet.push_back((LPSTR)str);
//			}
//			pRecordSet->MoveNext();
//			lCounts++;
//		}
//	}
//	catch(_com_error e)
//	{
//		AfxMessageBox("获取类别信息出错");
//	}
//}
//
//_bstr_t CTypeInfo::GetDataTypeString(DataTypeEnum enumType)
//{
//	_bstr_t strType = "";
//	switch(enumType)
//	{
//	case adInteger:
//	case adNumeric:
//		strType = "整型";
//		break;
//	case adDouble:
//		strType = "浮点型";
//		break;
//	case adDate:
//	case adDBTimeStamp:
//		strType = "日期";
//		break;
//	case adVarChar:
//	case adLongVarWChar:
//		strType = "字符";
//		break;
//	default:
//		strType = " ";
//		break;
//	}
//	return strType;
//}