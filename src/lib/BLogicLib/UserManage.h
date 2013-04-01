#pragma once
#include "BllHelp.h"

class CUserManage
{
public:
	CUserManage(void);
	~CUserManage(void);
private:
	static CUserManage instance;
	BOOL CheckValidateConnection();
	_RecordsetPtr QueryUserByCondition(string bstrWhere);
public:
	static CUserManage & Instance();
	//检查用户名是否存在
	BOOL CheckUserName(string strName);
	//检查用户状态是否有效
	BOOL CheckUserValidate(string strName);
	//添加用户
	BOOL AddUser(string strName,string strPswd);
	//修改密码
	BOOL EditPassWord(string strID,string strNewPswd);
	//审核用户
	BOOL AuditingUser(string strID);
	//注销用户使用
	BOOL DeleteUser(string strID);
	//用户登录
	BOOL Login(string strName,string strPswd);
	//所有用户
	_RecordsetPtr QueryAllUser();
	void QueryAllUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//所有待审用户
	_RecordsetPtr QueryAuditingUser();
	void QueryAuditingUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//所有有效用户
	_RecordsetPtr QueryValidateUser();
	void QueryValidateUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
