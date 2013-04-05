#pragma once
#include "ObjectDB.h"
#include "AccessDB.h"
#include "SqlServerDB.h"
#include "OracleDB.h"
#include "Other.h"
#include <msxml.h>
#include <atlbase.h>
//#import "msxml4.dll"

 class CDatabaseFactory
{
private:
	static CObjectDB * CreateDatabase();

public:
	static BOOL LoadConfig();
	
	static BOOL ConnetDatabase(std::string strPath, int iType, std::string strServer, std::string strDatabase, 
								std::string strUser, std::string strPassword);
	
public:
	static DatabaseType m_enumDatabaseType;
	static _bstr_t m_strServer;
	static _bstr_t m_strDatabaseName;
	static _bstr_t m_strUID;
	static _bstr_t m_strPwd;
};