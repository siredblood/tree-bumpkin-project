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
	//����û����Ƿ����
	BOOL CheckUserName(string strName);
	//����û�״̬�Ƿ���Ч
	BOOL CheckUserValidate(string strName);
	//����û�
	BOOL AddUser(string strName,string strPswd);
	//�޸�����
	BOOL EditPassWord(string strID,string strNewPswd);
	//����û�
	BOOL AuditingUser(string strID);
	//ע���û�ʹ��
	BOOL DeleteUser(string strID);
	//�û���¼
	BOOL Login(string strName,string strPswd);
	//�����û�
	_RecordsetPtr QueryAllUser();
	void QueryAllUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//���д����û�
	_RecordsetPtr QueryAuditingUser();
	void QueryAuditingUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������Ч�û�
	_RecordsetPtr QueryValidateUser();
	void QueryValidateUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
