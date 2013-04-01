#include "AccessDB.h"

CAccessDB::CAccessDB()
{
	m_pConnection = NULL;
	m_pCommand = NULL;
	m_strDatabaseName = "";
	m_strServer = "";
	m_strUID = "";
	m_strPwd = "";
}

CAccessDB::~CAccessDB()
{
	//如果有连接，关闭连接，释放资源
	Close();
}

BOOL CAccessDB::ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, _bstr_t strPwd, int iOptions /*= 0*/)
{
	//如果有连接，关闭连接，释放资源
	Close();

	try //建立数据库连接
	{
		::CoInitialize(NULL);//初始化OLE/COM库环境
		m_pConnection.CreateInstance(__uuidof(Connection));
		m_pCommand.CreateInstance(__uuidof(Command));

		_bstr_t bstrConn;
		bstrConn = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source="+strDatabaseName;
		m_pConnection->Open(bstrConn ,strUID,strPwd,iOptions);
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

bool CAccessDB::CheckTableNameExist(_bstr_t bstrTableName)
{
	/*bool exist=true;
	_bstr_t strSql = "SELECT NAME FROM MSysObjects WHERE TYPE=1 AND FLAGS=0 AND NAME='"+bstrTableName+"'";
	_RecordsetPtr prst=ExcuteSqlRes(strSql,adCmdText);
	if (prst==NULL||prst->adoEOF)
	{
		exist= false;
	}
	return exist;*/
	return true;
}

BOOL CAccessDB::RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName)
{
	_bstr_t strSql;
	//_CatalogPtr pCatalog;
	//pCatalog.CreateInstance(__uuidof(Catalog));
	//pCatalog->PutActiveConnection(m_pConnection);
	//pCatalog->GetTables()->GetItem(strOldTableName);
	//strSql = "RENAME " + strOldTableName + " TO " + strNewTableName;

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CAccessDB::ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat)
{
	_bstr_t strSql;
	strSql = "ALTER TABLE " + strTableName + " ALTER " + strFieldsFormat + "";

	BOOL bRes;
	bRes = ExcuteSql(strSql, adCmdText);
	return bRes;
}

BOOL CAccessDB::Backup(_bstr_t strFullPath)
{
	return TRUE;
}

BOOL CAccessDB::Restore(_bstr_t strFullPath)
{
	return TRUE;
}