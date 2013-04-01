#pragma once
#include "BllHelp.h"
struct TARGETMODEL
{
	string m_strID;         //编号
	string m_strName;       //名称
	string m_strType;       //类型
	string m_strArea;       //所属区域
	string m_strAddress;    //地址
	string m_strCoordinate; //坐标
	string m_strRemark;     //描述
};
class CEmphasesTarget
{
public:
	CEmphasesTarget(void);
	~CEmphasesTarget(void);
private:
	//重点目标字段
	_bstr_t m_strID;         //编号
	_bstr_t m_strName;       //名称
	_bstr_t m_strType;       //类型
	_bstr_t m_strArea;       //所属区域
	_bstr_t m_strAddress;    //地址
	_bstr_t m_strCoordinate; //坐标
	_bstr_t m_strRemark;     //描述

	static CEmphasesTarget instance;
public:
	//重点目标属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	////设置编号
	//void SetID(_bstr_t val) { m_strID = val; }

	//返回坐标
	_bstr_t GetCoordinate() const { return m_strCoordinate; }
	//设置坐标
	void SetCoordinate(_bstr_t val) { m_strCoordinate = val; }

	//返回名称
	_bstr_t GetName() const { return m_strName; }
	//设置名称
	void SetName(_bstr_t val) { m_strName = val; }

	//返回类型
	_bstr_t GetType() const { return m_strType; }
	//设置类型
	void SetType(_bstr_t val) { m_strType = val; }

	//返回所属区域
	_bstr_t GetArea() const { return m_strArea; }
	//设置所属区域
	void SetArea(_bstr_t val) { m_strArea = val; }

	_bstr_t GetAddress() const { return m_strAddress; }
	void SetAddress(_bstr_t val) { m_strAddress = val; }

	//返回备注
	_bstr_t GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//重点目标的数据库操作

	 static CEmphasesTarget & Instance();
	//加载对象模型
	BOOL Load(_bstr_t bstrID);
	//用名称加载对象模型
	BOOL LoadByName(_bstr_t bstrName);
	//检查重点目标名称是否存在
	BOOL CheckNameExist(_bstr_t bstrName);
	//检查重点目标名称更新
	BOOL NameValidate(_bstr_t bstrName,_bstr_t bstrID);
	//增加重点目标记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	//编辑重点目标记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Update();
	//删除重点目标记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Delete();
	//用名称实现删除
	BOOL DeleteByName(_bstr_t strName);
	//删除重点目标记录，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);
	//查询所有重点目标
	vector<string> GetAllTargetName();
	//区域
	std::vector<string> GetAreas();
	//区域重点目标
	std::vector<string> GetTargetByArea(string strArea);

	_RecordsetPtr QueryAllEmphTarg();
	std::vector<TARGETMODEL> QueryAllTarget();
	void QueryAllEmphTarg(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//条件查询重点目标记录
	_RecordsetPtr  QueryEmphTargByCondit(_bstr_t STRWhere);
	void QueryEmphTargByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
