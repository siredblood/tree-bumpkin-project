#pragma once

#include "ObjectDB.h"

class COracleDB : public CObjectDB
{
public:
	COracleDB();
	~COracleDB();

public:
	//建立连接
	BOOL ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, _bstr_t strPwd, int iOptions  = 0 );

	//表操作
	BOOL CreateTable(_bstr_t strTableName, _bstr_t strFieldsFormat, _bstr_t strExtended /* = */ );
	BOOL RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName);

	//字段操作
	BOOL ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat);

	//查看用户表
	bool CheckTableNameExist(_bstr_t bstrTableName);

	//备份和还原
	BOOL Backup(_bstr_t strFullPath);
	BOOL Restore(_bstr_t strFullPath);
};