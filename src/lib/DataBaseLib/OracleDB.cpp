#include "OracleDB.h"

COracleDB::COracleDB()
{
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_strDatabaseName = "";
	m_strServer = "";
	m_strUID = "";
	m_strPwd = "";
}

COracleDB::~COracleDB()
{
	//如果有连接，关闭连接，释放资源
	Close();
}

BOOL COracleDB::ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, _bstr_t strPwd, int iOptions /*= 0*/)
{
	//如果有连接，关闭连接，释放资源
	Close();

	try //建立数据库连接
	{
		::CoInitialize(NULL);//初始化OLE/COM库环境
		m_pConnection.CreateInstance(__uuidof(Connection));
		m_pCommand.CreateInstance(__uuidof(Command));

		_bstr_t strConn;
		strConn = "Provider=MSDAORA.1;Data Source=" + strServer + ";User ID=" + strUID
			+";Password="+strPwd+";Persist Security Info=True";

		m_pConnection->Open(strConn,strUID,strPwd,adModeUnknown);
		m_pCommand->ActiveConnection = m_pConnection;

		m_strDatabaseName = strDatabaseName;
		m_strUID = strUID;
		m_strPwd = strPwd;
	}
	catch(_com_error e)
	{
		Close();
		return FALSE;
	}  
	return TRUE;
}
bool COracleDB::CheckTableNameExist(_bstr_t bstrTableName)
{
	bool exist=true;
	_bstr_t strSql = "select * from user_catalog where table_name='"+bstrTableName+"'";
	_RecordsetPtr prst=ExcuteSqlRes(strSql,adCmdText);
	if (prst==NULL||prst->adoEOF)
	{
		exist= false;
	}
	return exist;
}
BOOL COracleDB::CreateTable(_bstr_t strTableName, _bstr_t strFieldsFormat, _bstr_t strExtended )
{
	_bstr_t strSql;
	strSql = "CREATE TABLE " + strTableName +"(" + strFieldsFormat + ")TABLESPACE " + strExtended;
	
	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL COracleDB::RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName)
{
	_bstr_t strSql;
	strSql = "RENAME " + strOldTableName + " TO " + strNewTableName;

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL COracleDB::ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat)
{
	_bstr_t strSql;
	strSql = "ALTER TABLE " + strTableName + " MODIFY " + strFieldsFormat + "";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL COracleDB::Backup(_bstr_t strFullPath)
{
	//_bstr_t strSql;
	//strSql = "exp " + m_strUID + "/" + m_strPwd + "@" + m_strDatabaseName + " FULL=y, file=" + strFullPath;

	//system(strSql);
	return TRUE;
}

BOOL COracleDB::Restore(_bstr_t strFullPath)
{
	//_bstr_t strSql;
	//strSql = "imp " + m_strUID + "/" + m_strPwd + "@" + m_strDatabaseName + " FULL=y, file=" + strFullPath;

	//system(strSql);
	return TRUE;
}