#pragma once
#include "BllHelp.h"
/************************************************************************/
/* 分析方案类                                                           */
/************************************************************************/
class CAnalyseDemo
{
public:
	CAnalyseDemo(void);
	~CAnalyseDemo(void);
private:
	//方案分析字段
	_bstr_t m_strID;                //编号
	_bstr_t m_strName;              //名称
	_bstr_t m_targetPoint;          //目标点
	_bstr_t m_strToTarger;          //所属目标
	_bstr_t m_strRange;             //范围
	_bstr_t m_strType;              //类型
	_bstr_t m_strTypeID;            //类型编号
	_bstr_t m_strOuterColor;        //外框颜色
	_bstr_t m_strResultColor;       //结果颜色
	_bstr_t m_strPartResultColor;   //部份结果颜色
	_bstr_t m_strCreator;     //创建人
	_bstr_t m_strCreateTime;  //创建时间
	_bstr_t m_strRemark;            //备注
private:
	_bstr_t GetWhereString(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
public:
	//方案分析属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	//返回名称
	_bstr_t GetName() const { return m_strName; }
	//设置名称
	void SetName(_bstr_t val) { m_strName = val; }
	//返回目标点
	_bstr_t GetTargetPoint() const { return m_targetPoint; }
	//设置目标点
	void SetTargetPoint(_bstr_t val) { m_targetPoint = val; }
	//返回所属区域
	_bstr_t GetToTarger() const { return m_strToTarger; }
	//设置所属区域
	void SetToTarger(_bstr_t val) { m_strToTarger = val; }
	//返回范围
	_bstr_t GetRange() const { return m_strRange; }
	//设置范围
	void SetRange(_bstr_t val) { m_strRange = val; }
	//返回类型
	_bstr_t GetType() const { return m_strType; }
	//设置类型
	void SetType(_bstr_t val) { m_strType = val; }
	//返回类型编号
	_bstr_t GetTypeID() const { return m_strTypeID; }
	//设置类型编号
	void SetTypeID(_bstr_t val) { m_strTypeID = val; }
	//返回外框颜色
	_bstr_t GetOuterColor() const { return m_strOuterColor; }
	//设置外框颜色
	void SetOuterColor(_bstr_t val) { m_strOuterColor = val; }

	//返回结果颜色
	_bstr_t GetResultColor() const { return m_strResultColor; }
	//设置结果颜色
	void SetResultColor(_bstr_t val) { m_strResultColor = val; }

	//获取部份显示颜色
	_bstr_t GetPartResultColor() const { return m_strPartResultColor; }
	//设置部份显示颜色
	void SetPartResultColor(_bstr_t val) { m_strPartResultColor = val; }

	//返回创建人
	_bstr_t GetCreator() const { return m_strCreator; }
	//设置创建人
	void SetCreator(_bstr_t val) { m_strCreator = val; }
	//返回创建时间
	_bstr_t GetCreateTime() const { return m_strCreateTime; }
	//设置创建时间
	void SetCreateTime(_bstr_t val) { m_strCreateTime = val; }
	//返回备注
	_bstr_t GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//方案分析的数据库操作

	//加载


	//加载方案:
	//参数：方案对象编号
	BOOL LoadDemoInfo(_bstr_t bstrId);
	//加载方案:参数：方案对象名称
	BOOL LoadDemoInfoByName(_bstr_t bstrName);
	//判断方案名称是否存在
	BOOL ExistDemoName(_bstr_t bstrName);

	//加载方案面分析范围。前提是先加载方案
	_RecordsetPtr LoadDemoRange();
	//加载方案面分析范围：参数：方案编号
	_RecordsetPtr LoadDemoRange( _bstr_t strDemoID );
	//加载方案面分析范围：参数：方案名称
	vector<string> LoadDemoRangeByName(_bstr_t strDemoName);
	//加载方案类型分析坐标。前提是先加载方案
	_RecordsetPtr LoadDemoCoordinates();
	//加载方案类型分析坐标：参数：方案编号
	_RecordsetPtr LoadDemoCoordinates( _bstr_t strDemoID);
	//加载方案类型分析坐标：参数：方案名称
	std::vector<std::vector<string>> LoadDemoCoodis(_bstr_t strDemoName);
	//加载方案类型分析类型：参数：方案名称
	vector<string> LoadDemoResult( _bstr_t strDemoName);

	//加载所有自画线监控方案分析记录
	_RecordsetPtr LoadAllDrawLineDemo( _bstr_t bstrWhere );
	void LoadAllDrawLineDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//加载所有流行线监控方案分析记录
	_RecordsetPtr LoadAllFRowLineDemo( _bstr_t bstrWhere );
	void LoadAllFRowLineDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//加载所有点方案分析记录
	_RecordsetPtr LoadAllPointDemo( _bstr_t bstrWhere );
	void LoadAllPointDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//加载所有面方案分析记录
	_RecordsetPtr LoadAllRangDemo( _bstr_t bstrWhere );
	void LoadAllRangDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);


	//保存方案

	//增加自画线监控方案分析记录,
	//参数：方案编号，摄像头编号列表，警力编号列表
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveDrawLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds);

	//增加流行线监控方案分析记录,
	//参数：方案编号，摄像头编号列表，警力编号列表
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveFRowLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds);

	//增加点方案分析记录,
	//参数：key建筑ID,value坐标列表
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SavePointDemo(std::map<_bstr_t,std::vector<std::vector<_bstr_t>>> mBuilding);
	//新补充
	BOOL SavePointDemo(_bstr_t strNewName,std::vector<_bstr_t> vGuid,std::vector<std::vector<_bstr_t>> vvCoodints);

	//增加面方案分析记录,
	//参数：key建筑ID,value坐标列表,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveRangDemo(std::map<_bstr_t,std::vector<std::vector<_bstr_t>>> mBuilding ,std::vector<_bstr_t> strRanges );
	//增加面方案分析记录,
	//参数：方案名称，分析结果GUID列表，坐标,范围
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL SaveRangDemo(_bstr_t strNewName,std::vector<_bstr_t> vGuid,std::vector<std::vector<_bstr_t>> vvCoodints,std::vector<_bstr_t> strRanges );


	//删除方案

	//删除方案分析记录,
	//首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Delete();

	//删除方案分析记录，
	//不用实例化对象，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);

	//创建查询
	_RecordsetPtr QueryCreateDrawLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateDrawLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryCreateFRowLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateFRowLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryCreatePointDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreatePointDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryCreateRangeDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateRangeDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};