#pragma once

#include "BllHelp.h"
/************************************************************************/
/* 执勤                                                                     */
/************************************************************************/
class CDuty
{
public:
	CDuty(void);
	~CDuty(void);
private:
	//执勤字段
	_bstr_t m_strID;      //编号
	_bstr_t m_strPliceID; //警力ID
	_bstr_t m_strAdress;  //执勤地点
	_bstr_t m_strDate;    //执勤日期
	_bstr_t m_strTime;    //执勤班次
	_bstr_t m_strAudit;   //观众数
	_bstr_t m_strRemark;  //备注
public:
	//执勤属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	////设置编号
	//void SetID(_bstr_t val) { m_strID = val; }

	//返回警力编号
	_bstr_t GetPliceID() const { return m_strPliceID; }
	//设置警力编号
	void SetPliceID(_bstr_t val) { m_strPliceID = val; }

	//返回执勤地点
	_bstr_t GetAdress() const { return m_strAdress; }
	//设置执勤地点
	void SetAdress(_bstr_t val) { m_strAdress = val; }

	//返回执勤日期
	_bstr_t GetDate() const { return m_strDate; }
	//设置执勤日期
	void SetDate(_bstr_t val) { m_strDate = val; }

	//返回执勤班次
	_bstr_t GetTime() const { return m_strTime; }
	//设置执勤班次
	void SetTime(_bstr_t val) { m_strTime = val; }

	//返回执勤班次
	_bstr_t GetAudit() const {return m_strAudit;}
	//设置执勤班次
	void SetAudit(_bstr_t val){m_strAudit=val;}

	//返回备注
	_bstr_t GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//执勤表的数据库操作

	//加载对象模型
	BOOL Load(_bstr_t bstrID);
	//增加执勤记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	////批量增加
	//BOOL AddList(std::map<_bstr_t,std::vector<_bstr_t> mstrRst);
	//编辑执勤记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Update();
	//删除执勤记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Delete();
	//删除执勤记录，不用实例化对象，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);

	//查询所有执勤记录
	_RecordsetPtr QueryAllDuty();
	void QueryAllDuty(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	//条件查询执勤记录
	_RecordsetPtr  QueryDutyByCondit(_bstr_t STRWhere);
	void QueryDutyByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);


	//查询记录列表
	_RecordsetPtr QueryDutyRcst(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	//警力部署调度控制
	_RecordsetPtr QueryRCSTPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	vector<string> QueryVectorPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	//统计警力
	long SumDutyPol(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	//统计记录数
	long SumDutyRecords(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
private:
	_bstr_t GetWhereSql(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	bool CheckCollision(_bstr_t strId, _bstr_t strPolId,_bstr_t strDate,_bstr_t strDutyTimes);
};



/************************************************************************/
/* 执勤班次                                                                     */
/************************************************************************/
class CDutyTime
{
public:
	CDutyTime(void);
	~CDutyTime(void);
public:
	//执勤班次表的数据库操作

	//增加执勤班次记录,其中strtime为执勤时间，strremark为备注
	BOOL Add(_bstr_t strTime,_bstr_t strRemark);
	//编辑执勤班次记录,其中strid为编号，strtime为执勤时间，strremark为备注
	BOOL Update(_bstr_t strID,_bstr_t strTime,_bstr_t strRemark);
	//删除执勤班次记录，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);
	//得到所以班次
	std::vector<string> QueryTimes();
	//查询所有执勤班次记录
	_RecordsetPtr QueryAllDutyTime();
	void QueryAllDutyTime(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//条件查询执勤班次记录
	_RecordsetPtr  QueryDutyTimeByCondit(_bstr_t STRWhere);
	void QueryDutyTimeByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};