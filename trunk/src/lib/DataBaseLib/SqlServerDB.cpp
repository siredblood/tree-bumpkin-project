#include "SqlServerDB.h"

CSqlServerDB::CSqlServerDB()
{
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_strDatabaseName = "";
	m_strServer = "";
	m_strUID = "";
	m_strPwd = "";
}

CSqlServerDB::~CSqlServerDB()
{
	//如果有连接，关闭连接，释放资源
	Close();
}

BOOL CSqlServerDB::ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, _bstr_t strPwd, int iOptions)
{
	//如果有连接，关闭连接，释放资源
	Close();

	try //建立数据库连接
	{
		::CoInitialize(NULL);//初始化OLE/COM库环境
		m_pConnection.CreateInstance(__uuidof(Connection));
		m_pCommand.CreateInstance(__uuidof(Command));

		_bstr_t strConn;
		strConn = "Provider=SQLOLEDB;Server=" + strServer + ";User ID=" + strUID
			+ ";Password="+strPwd+";Database="+strDatabaseName+";Persist Security Info=True";

		m_pConnection->Open(strConn,strUID,strPwd,iOptions);
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
bool CSqlServerDB::CheckTableNameExist(_bstr_t bstrTableName)
{
	bool exist=true;
	_bstr_t strSql = "select [name] from sysobjects where xtype='u' and [name]='"+bstrTableName+"'";
	_RecordsetPtr prst=ExcuteSqlRes(strSql,adCmdText);
	if (prst==NULL||prst->adoEOF)
	{
		exist= false;
	}
	return exist;
}
BOOL CSqlServerDB::RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName)
{
	_bstr_t strSql;
	strSql = "SP_RENAME '" + strOldTableName + "','" + strNewTableName + "'";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CSqlServerDB::ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat)
{
	_bstr_t strSql;
	strSql = "ALTER TABLE " + strTableName + " ALTER COLUMN " + strFieldsFormat + "";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CSqlServerDB::Backup(_bstr_t strFullPath)
{
	//_bstr_t strSql;
	//strSql = "BACKUP DATABASE " + m_strDatabaseName + " TO DISK='" + strFullPath + "'";

	//BOOL bRes;
	//bRes = ExcuteSql(strSql, adCmdText);
	//return bRes;
	return TRUE;
}

BOOL CSqlServerDB::Restore(_bstr_t strFullPath)
{
	//_bstr_t strSql;
	//strSql = "RESTORE DATABASE " + m_strDatabaseName + " FROM DISK='" + strFullPath + "'";

	//BOOL bRes;
	//bRes = ExcuteSql(strSql, adCmdText);
	//return bRes;
	return TRUE;
}