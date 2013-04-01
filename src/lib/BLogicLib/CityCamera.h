#pragma once
#include "BllHelp.h"


class CCityCamera
{
public:
	CCityCamera(void);
	~CCityCamera(void);
private:
	//城市摄像头字段
	_bstr_t m_strID;      //编号
	_bstr_t m_strCameraID; //摄像头编号
	_bstr_t m_strPosition;  //位置
	_bstr_t m_strType;    //类型
	_bstr_t m_strRemark;  //备注
public:
	//城市摄像头属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }

	//返回摄像头编号
	_bstr_t GetCameraID() const { return m_strCameraID; }
	//设置摄像头编号
	void SetCameraID(_bstr_t val) { m_strCameraID = val; }

	//返回位置
	_bstr_t GetPosition() const { return m_strPosition; }
	//设置位置
	void SetPosition(_bstr_t val) { m_strPosition = val; }

	//返回类型
	_bstr_t GetType() const { return m_strType; }
	//设置类型
	void SetType(_bstr_t val) { m_strType = val; }

	//返回备注
	_bstr_t GetRemark() const { return m_strRemark; }
	//设置备注
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//摄像头的数据库操作


	//加载对象模型
	BOOL Load(_bstr_t bstrID);
	//增加摄像头记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	//编辑摄像头记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Update();
	//删除摄像头记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Delete();
	//删除摄像头记录，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);
	//查询所有摄像头记录
	_RecordsetPtr QueryAllCamera();
	void QueryAllCamera(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//条件查询摄像头记录
	_RecordsetPtr  QueryCameraByCondit(_bstr_t STRWhere);
	void QueryCameraByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
