#pragma once
#include "BllHelp.h"

class CTableRcst
{
public:
	CTableRcst(void);
	~CTableRcst(void);
private:
	static CTableRcst instance;
public:
	static CTableRcst &Instance();
	BOOL Save(_bstr_t strTableName,_bstr_t strExceptField, map<_bstr_t,_bstr_t> mPropertys);
	BOOL Save(_bstr_t strTableName,_bstr_t strExceptField,vector<map<_bstr_t,_bstr_t>> vModels);
	BOOL Update(_bstr_t strTableName,_bstr_t strKeyName, map<_bstr_t,_bstr_t> mPropertys);
	BOOL Update(_bstr_t strTableName,_bstr_t strKeyName,vector<map<_bstr_t,_bstr_t>> vModels);
	BOOL Delete(_bstr_t strTableName,_bstr_t strKeyName,_bstr_t strId);
	BOOL Delete(_bstr_t strTableName,_bstr_t strKeyName,vector<_bstr_t> vIds);
	//重点目标建筑查询
	BOOL DelateTGBuild(_bstr_t bstrids);
	_RecordsetPtr QueryAllTgBuilding();
	void QueryAllTgBuilding( vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	_RecordsetPtr QueryTgBuilding(_bstr_t strTargetName);
	void QueryTgBuilding( _bstr_t strTargetName ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	vector<string> QueryTgBuildingNames(_bstr_t strTargetName);
	//重点目标属性
	_RecordsetPtr QueryTargetProperty();
	void QueryTargetProperty( vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//建筑构件
	/*string GetGUIDbyName(_bstr_t strTargetName,_bstr_t strTgBuildName,_bstr_t strCompanentName);
	BOOL GetTgNamesByGuid(_bstr_t strGuid,_bstr_t &strTarget,_bstr_t &strTgBuild,_bstr_t&strName);*/
};
