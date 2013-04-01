//Concretion.h
//实现具体类别对象的添加、修改和删除
#pragma once
#include "BllHelp.h"

using namespace std;

class CConcretion
{
public:
	CConcretion();
	~CConcretion();


public:
	static CConcretion & Instance();
	//保存
	//传入参数分别为：GUID，类别名称，字段名和字段值的map
	BOOL Save(_bstr_t strGuid, _bstr_t strTableName, map<_bstr_t,_bstr_t> &mapFlds);
	BOOL Save(_bstr_t strGuid, _bstr_t strTableName, vector<_bstr_t>&vfileds,vector<_bstr_t> &vValues);
	//删除
	//传入参数：GUID
	BOOL Delete(_bstr_t strGuid);

	//加载对象模型
	int Load(_bstr_t strGUID,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts,string &strType,vector<string> &vecRecordSetH);

	BOOL LoadType(_bstr_t strTable,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	BOOL LoadType(_bstr_t strTable,_bstr_t strConditiong,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//补充
	//得到模型表的所有GUID
	vector<string> GetAllGuid(_bstr_t strTableName);

	//判断某个模型是否是建筑构件
	BOOL IsBuildPart(_bstr_t strGuid);
	//判断某个模型是否在重点目标中
	BOOL IsHasTarget(_bstr_t strGuid);
	//判断是否是摄像头
	BOOL IsCamara(_bstr_t strGuid);
	//判断是否是附属设施
	BOOL IsFacilitie(_bstr_t strGuid);
	//判断是否是警力
	BOOL IsPolice(_bstr_t strGuid);
	
	//返回模型重点目标信息,key为字段名,value为字段值
	map<string,string> GetTargetInfo(_bstr_t strGuid);
	BOOL GetTargetInfo(_bstr_t strGuid,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	BOOL GetTarGetInfoByName( _bstr_t strTargetName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//返回模型构件所属建筑信息
	map<string,string> GetBuildInfo(_bstr_t strGuid);
	BOOL GetBuildInfo(_bstr_t strGuid,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

private:
	static CConcretion instance;
private:
	//增加
	//传入参数：GUID，类别名称，字段名和字段值的map
	BOOL Add(_bstr_t strGuid, _bstr_t strTypeName, map<_bstr_t,_bstr_t> &mapFlds);
	//更新
	//传入参数：GUID，修改前类别编号，类别名称，字段名和字段值的map
	BOOL Update(_bstr_t strGuid, _bstr_t strOldID,_bstr_t strTypeName, map<_bstr_t,_bstr_t> &mapFlds);
	//增加
	//传入参数：GUID，类别名称，字段名和字段值的map
	BOOL Add(_bstr_t strGuid, _bstr_t strTypeName, vector<_bstr_t> &vfileds,vector<_bstr_t> &vValues);
	//更新
	//传入参数：GUID，修改前类别编号，类别名称，字段名和字段值的map
	BOOL Update(_bstr_t strGuid, _bstr_t strOldID,_bstr_t strTypeName, vector<_bstr_t> &vfileds,vector<_bstr_t> &vValues);


};