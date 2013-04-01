#include "ObjectDB.h"

CObjectDB::CObjectDB()
{
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_strDatabaseName = "";
	m_strServer = "";
	m_strUID = "";
	m_strPwd = "";
}

CObjectDB::~CObjectDB()
{
	Close();
}

void CObjectDB::Close()
{
	if(m_pConnection != NULL)
	{
		if (m_pConnection->State)
		{
			m_pConnection->Close();
		}
		m_pConnection = NULL;
	}
	if(m_pCommand != NULL)
	{
		m_pCommand = NULL;
	}

	::CoUninitialize();
}
//获取连接
_ConnectionPtr CObjectDB::GetConnection()
{
	return m_pConnection;
}

//获取命令
_CommandPtr CObjectDB::GetCommand()
{
	return m_pCommand;
}

BOOL CObjectDB::ExcuteSql(_bstr_t strSql, CommandTypeEnum enumCommandType)
{
	try
	{
		m_pCommand->CommandText = strSql;
		m_pCommand->Execute(NULL,NULL,enumCommandType);
	}
	catch(_com_error e)
	{
		return FALSE;
	}
	return TRUE;
}

_RecordsetPtr CObjectDB::ExcuteSqlRes(_bstr_t strSql, CommandTypeEnum enumCommandType)
{
	_RecordsetPtr pRecordSet;
	try
	{
		pRecordSet.CreateInstance(__uuidof(Recordset));
		m_pCommand->CommandText = strSql;
		pRecordSet = m_pCommand->Execute(NULL,NULL,enumCommandType);
	}
	catch(_com_error e)
	{
		return NULL;
	}
	return pRecordSet;
}

//事务处理
BOOL CObjectDB::ExcuteTrans(std::vector<_bstr_t> &strSqls, CommandTypeEnum enumType)
{
	try
	{
		m_pCommand->ActiveConnection = m_pConnection;
		m_pConnection->BeginTrans();
		
		for ( std::vector <_bstr_t>::iterator strSql = strSqls.begin(); strSql != strSqls.end(); strSql++ )
		{
			m_pCommand->CommandText =((_bstr_t) *strSql);
			m_pCommand->Execute(NULL,NULL,enumType);
		}
		m_pConnection->CommitTrans();
	}
	catch(_com_error e)
	{
		m_pConnection->RollbackTrans();
		return FALSE;
	}
	return TRUE;
}

//判断表名是否存在
bool CObjectDB::CheckTableNameExist(_bstr_t bstrTableName)
{
	return true;
}

BOOL CObjectDB::CreateTable(_bstr_t strTableName, _bstr_t strFieldsFormat, _bstr_t strExtended /* = */ )
{
	_bstr_t strSql;
	strSql = "CREATE TABLE [" + strTableName +"] (" + strFieldsFormat + ")";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::DropTable(_bstr_t strTableName)
{
	_bstr_t strSql;
	strSql = "DROP TABLE [" + strTableName+"]";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName)
{
	return TRUE;
}

BOOL CObjectDB::CreateField(_bstr_t strTableName, _bstr_t strFieldsFormat)
{
	_bstr_t strSql;
	strSql = "ALTER TABLE [" + strTableName + "] ADD " + strFieldsFormat;

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat)
{
	return TRUE;
}

BOOL CObjectDB::DropField(_bstr_t strTableName, _bstr_t strFieldName)
{
	_bstr_t strSql;
	strSql = "ALTER TABLE [" + strTableName + "] DROP COLUMN [" + strFieldName+"]";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::AddRecord(_bstr_t strTableName, _bstr_t strColumnsFormat, _bstr_t strValuesFormat)
{
	_bstr_t strSql;
	strSql = "INSERT INTO [" + strTableName + "] ( " +  strColumnsFormat + " ) VALUES (" + strValuesFormat + ")";
	
	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::ModifyRecord(_bstr_t strTableName, _bstr_t strSelectItemName, _bstr_t strSelectItemValue, _bstr_t strModifyItemsFormat)
{
	_bstr_t strSql;
	strSql = "UPDATE [" + strTableName + "] SET " + strModifyItemsFormat + " WHERE " + strSelectItemName + "='" + strSelectItemValue + "'";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::ModifyRecords(_bstr_t strTableName, _bstr_t strModifyColumnName, _bstr_t strModifyColumnValue)
{
	_bstr_t strSql;
	strSql = "UPDATE [" + strTableName + "] SET " + strModifyColumnName + " = " + strModifyColumnValue;

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CObjectDB::DropRecord(_bstr_t strTableName, _bstr_t strColumnName, _bstr_t strColumnValue)
{
	_bstr_t strSql;
	strSql = "DELETE FROM [" + strTableName + "] WHERE " + strColumnName + " = " + strColumnValue;

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

_RecordsetPtr CObjectDB::Query(_bstr_t strTableName,_bstr_t strSelectItems /* =  */,_bstr_t strOrderByItem /* = */ )
{
	_bstr_t strSql;
	if(strOrderByItem.length() == 0)
		strSql = "SELECT " + strSelectItems + " FROM [" + strTableName+"]";
	else
		strSql = "SELECT " + strSelectItems + " FROM [" + strTableName + "] ORDER BY '" + strOrderByItem + "'";

	return ExcuteSqlRes(strSql, adCmdText);
}

_RecordsetPtr CObjectDB::Query(_bstr_t strTableName, _bstr_t strKeyItem, _bstr_t strKeyValue, QueryModeEnum enumMode, _bstr_t strSelectItems /* = */,_bstr_t strOrderByItem /* = */ )
{
	_bstr_t strSql, strQuery;
	switch(enumMode)
	{
	case LikeMode:
		strSql = "SELECT " + strSelectItems + " FROM [" + strTableName + "] WHERE " + strKeyItem + " LIKE '%" + strKeyValue + "%'";
		break;
	default:
		strQuery = GetQueryModeString(enumMode);
		strSql = "SELECT " + strSelectItems + " FROM [" + strTableName + "] WHERE " + strKeyItem + strQuery + "'" + strKeyValue + "'";
		break;
	}

	if(strOrderByItem.length() != 0)
		strSql += " ORDER BY '" + strOrderByItem + "'";

	return ExcuteSqlRes(strSql, adCmdText);
}

_bstr_t CObjectDB::GetQueryModeString(QueryModeEnum enumMode)
{
	switch(enumMode)
	{
	case EqualMode:
		return "=";
	case LikeMode:
		return "LIKE";
	case BiggerMode:
		return ">";
	case BiggerEqualMode:
		return ">=";
	case SmallerMode:
		return "<";
	case SmallerEqualMode:
		return "<=";
	default:
		return " ";
	}
}


_RecordsetPtr CObjectDB::GetRecordSet(_bstr_t strTableName)
{
	_bstr_t strSql = "SELECT * FROM [" + strTableName+"]";
	return ExcuteSqlRes(strSql, adCmdText);
}