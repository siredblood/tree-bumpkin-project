#pragma once
#include "BllHelp.h"

class CTypeInfo
{
public:
	CTypeInfo(void);
	~CTypeInfo(void);
private:
	static CTypeInfo instance;
public:
	static CTypeInfo & Instance();
	BOOL Add(_bstr_t STRtypeName);
	BOOL Update(_bstr_t strOldTypeName,_bstr_t strNewTypeName);
	BOOL Delete(_bstr_t STRtypeName/*STRID*/);
	_RecordsetPtr QueryAllType();
	void QueryAllType(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	_RecordsetPtr QueryTypeInfoByCondit(_bstr_t STRTypeName/*STRID*/);
	void QueryTypeInfoByCondit(_bstr_t STRTypeName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	//≤π≥‰
	vector<string> GetTypeNames();
	//Õº≤„øÿ÷∆œ‘ æ
	_RecordsetPtr QueryGUIDByLayerRcst(_bstr_t strTableName,_bstr_t strWhere);
	vector<string> QueryGUIDBylayerVector(_bstr_t strTableName,_bstr_t strWhere);
};
