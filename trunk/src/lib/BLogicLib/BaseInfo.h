#pragma once
#include "BllHelp.h"
//���ֱ��ֶεĲ���
class CBaseInfo
{
public:
	CBaseInfo(void);
	~CBaseInfo(void);
public:
	//����
	//����
	BOOL AddField(_bstr_t strTableName, _bstr_t strFieldName, string enumFieldType, int iFieldSize);
	BOOL UpdateFiled(_bstr_t strTableName,_bstr_t strFieldName, string enumFieldType, int iFieldSize);
	BOOL DeleteFiled(_bstr_t strTableName,_bstr_t strFieldName);
	void QueryFileds(_bstr_t strTableName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	FieldType GetDataTypeByString(string strType);
};
