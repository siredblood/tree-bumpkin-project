#include "UserManage.h"

CUserManage CUserManage::instance;

CUserManage::CUserManage(void)
{
}

CUserManage::~CUserManage(void)
{
}

BOOL CUserManage::CheckValidateConnection()
{
	if (!theBllApp.m_bConntSuccess || !theBllApp.m_pDB->CheckTableNameExist("�û�����"))
		return FALSE;
	return TRUE;
}

_RecordsetPtr CUserManage::QueryUserByCondition(string bstrWhere)
{
	_RecordsetPtr RcstPrt;
	_bstr_t bstrSql= bstrWhere.c_str();
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from �û�����  where 1=1 " +bstrSql,adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return RcstPrt;
}
CUserManage & CUserManage::Instance()
{
	return instance;
}
//����û����Ƿ����
BOOL CUserManage::CheckUserName(string strName)
{
	_RecordsetPtr RcstPrt;
	CString strTemp=strName.c_str();
	_bstr_t bstrSql=strTemp.Trim().GetBuffer() ;
	if (CheckValidateConnection())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from �û�����  where �û���='"+ bstrSql+"'",adCmdText);
		if (RcstPrt!=NULL && !RcstPrt->adoEOF)
			return TRUE;
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//����û�״̬�Ƿ���Ч
BOOL CUserManage::CheckUserValidate(string strName)
{
	if (CheckUserName(strName))
	{
		_RecordsetPtr RcstPrt;
		CString strTemp=strName.c_str();
		_bstr_t bstrSql=strTemp.Trim().GetBuffer() ;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from �û�����  where ״̬='��Ч' and  �û���='"+ bstrSql+"'",adCmdText);
		if (RcstPrt!=NULL && !RcstPrt->adoEOF)
			return TRUE;
	}
	return FALSE;
}
//����û�
BOOL CUserManage::AddUser(string strName,string strPswd)
{
	CString strTemp=strName.c_str();
	_bstr_t bstrName=strTemp.Trim().GetBuffer();
	strTemp=strPswd.c_str();
	_bstr_t bstrPswd=strTemp.Trim().GetBuffer();
	_bstr_t bstrSql="insert into  �û����� (�û���,����) values('" + bstrName + "','" + bstrPswd + "')";
	if (CheckValidateConnection())
		if (CheckUserName(strName))
			MessageBox(NULL,"�û����Ѵ��ڣ�",0,0);
		else
			return theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//�޸�����
BOOL CUserManage::EditPassWord(string strID,string strNewPswd)
{
	CString strTemp=strID.c_str();
	_bstr_t bstrName=strTemp.Trim().GetBuffer();
	strTemp=strNewPswd.c_str();
	_bstr_t bstrPswd=strTemp.Trim().GetBuffer();

	_bstr_t bstrSql="update  �û�����  set ����='" + bstrPswd + "' where ���=" + bstrName ;
	if (CheckValidateConnection())
		return theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//����û�
BOOL CUserManage::AuditingUser(string strID)
{
	_bstr_t bstrSql= strID.c_str();
	if (CheckValidateConnection())
		return theBllApp.m_pDB->ExcuteSql("update  �û�����  set ״̬='��Ч' where ���=" +bstrSql ,adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//ע���û�ʹ��
BOOL CUserManage::DeleteUser(string strID)
{
	_bstr_t bstrSql= strID.c_str();
	if (CheckValidateConnection())
		return theBllApp.m_pDB->ExcuteSql("delete  �û�����  where ���=" + bstrSql ,adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//�û���¼
BOOL CUserManage::Login(string strName,string strPswd)
{
	_RecordsetPtr RcstPrt;
	CString strTemp=strName.c_str();
	_bstr_t bstrName=strTemp.Trim().GetBuffer();
	strTemp=strPswd.c_str();
	_bstr_t bstrPswd=strTemp.Trim().GetBuffer();

	_bstr_t bstrSql="select * from �û�����  where �û���='"+ bstrName +"'  and ����='" + bstrPswd + "'";
	if (CheckValidateConnection())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
		if (RcstPrt!=NULL && !RcstPrt->adoEOF)
			return TRUE;
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//�����û�
_RecordsetPtr CUserManage::QueryAllUser()
{
	_RecordsetPtr RcstPrt;
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from �û����� ",adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return RcstPrt;
}
void CUserManage::QueryAllUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllUser();
	if (Rcst!=NULL)
	{
		CBllHelp * help = new CBllHelp();
		help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
		delete help;
	}
}
//���д����û�
_RecordsetPtr CUserManage::QueryAuditingUser()
{
	_RecordsetPtr RcstPrt;
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from �û�����  where ״̬='����'",adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return RcstPrt;
}
void CUserManage::QueryAuditingUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAuditingUser();
	if (Rcst!=NULL)
	{
		CBllHelp * help = new CBllHelp();
		help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
		delete help;
	}
}
//������Ч�û�
_RecordsetPtr CUserManage::QueryValidateUser()
{
	_RecordsetPtr RcstPrt;
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from �û�����  where ״̬='��Ч'",adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return RcstPrt;
}
void CUserManage::QueryValidateUser(std::vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryValidateUser();
	if (Rcst!=NULL)
	{
		CBllHelp * help = new CBllHelp();
		help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
		delete help;
	}
}
