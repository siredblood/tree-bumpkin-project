#pragma once

#include "ObjectDB.h"

class CSqlServerDB : public CObjectDB
{
public:
	CSqlServerDB();
	~CSqlServerDB();

public:
	///��������
	BOOL ConnectDB(_bstr_t strServer, _bstr_t strDatabaseName, _bstr_t strUID, _bstr_t strPwd, int iOptions /* = 0 */);

	///�����
	BOOL RenameTable(_bstr_t strOldTableName, _bstr_t strNewTableName);

	///�ֶβ���
	BOOL ModifyField(_bstr_t strTableName, _bstr_t strFieldsFormat);
	//�������Ƿ����
	bool CheckTableNameExist(_bstr_t bstrTableName);

	//���ݺͻ�ԭ
	BOOL Backup(_bstr_t strFullPath);
	BOOL Restore(_bstr_t strFullPath);
};