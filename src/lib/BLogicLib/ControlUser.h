#pragma once
#include "BllHelp.h"

class CControlUser
{
public:
	CControlUser(void);
	~CControlUser(void);
private:
	//监控用户字段
	_bstr_t m_strID;         //编号
	_bstr_t m_strServer;       //服务器
	_bstr_t m_strUserName;       //用户名
	_bstr_t m_strPassWord;       //密码
public:
	//监控用户属性获取和设置

	//返回编号
	_bstr_t GetID() const { return m_strID; }
	////设置编号
	//void SetID(_bstr_t val) { m_strID = val; }

	//返回服务器
	_bstr_t GetServer() const { return m_strServer; }
	//设置服务器
	void SetServer(_bstr_t val) { m_strServer = val; }

	//返回用户名
	_bstr_t GetUserName() const { return m_strUserName; }
	//设置用户名
	void SetUserName(_bstr_t val) { m_strUserName = val; }

	//返回类型
	_bstr_t GetPassWord() const { return m_strPassWord; }
	//设置类型
	void SetPassWord(_bstr_t val) { m_strPassWord = val; }

	//监控用户的数据库操作


	//加载对象模型
	BOOL Load(_bstr_t bstrID);
	//增加监控用户记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Add();
	//编辑监控用户记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Update();
	//删除监控用户记录,首先实例化一个对象再给对象各个字段赋值，最后调用这个函数
	BOOL Delete();
	//删除监控用户记录，通过传递编号（用“，"隔开）
	BOOL Delete(_bstr_t strIDS);
	//查询所有重点目标
	vector<string> GetAllUserName();
	_RecordsetPtr QueryAllUser();
	void QueryAllUser(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//条件查询重点目标记录
	_RecordsetPtr  QueryUserByCondit(_bstr_t STRWhere);
	void QueryUserByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
