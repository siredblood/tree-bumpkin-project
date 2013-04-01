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
	if (!theBllApp.m_bConntSuccess || !theBllApp.m_pDB->CheckTableNameExist("用户管理"))
		return FALSE;
	return TRUE;
}

_RecordsetPtr CUserManage::QueryUserByCondition(string bstrWhere)
{
	_RecordsetPtr RcstPrt;
	_bstr_t bstrSql= bstrWhere.c_str();
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 用户管理  where 1=1 " +bstrSql,adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return RcstPrt;
}
CUserManage & CUserManage::Instance()
{
	return instance;
}
//检查用户名是否存在
BOOL CUserManage::CheckUserName(string strName)
{
	_RecordsetPtr RcstPrt;
	CString strTemp=strName.c_str();
	_bstr_t bstrSql=strTemp.Trim().GetBuffer() ;
	if (CheckValidateConnection())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 用户管理  where 用户名='"+ bstrSql+"'",adCmdText);
		if (RcstPrt!=NULL && !RcstPrt->adoEOF)
			return TRUE;
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//检查用户状态是否有效
BOOL CUserManage::CheckUserValidate(string strName)
{
	if (CheckUserName(strName))
	{
		_RecordsetPtr RcstPrt;
		CString strTemp=strName.c_str();
		_bstr_t bstrSql=strTemp.Trim().GetBuffer() ;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 用户管理  where 状态='有效' and  用户名='"+ bstrSql+"'",adCmdText);
		if (RcstPrt!=NULL && !RcstPrt->adoEOF)
			return TRUE;
	}
	return FALSE;
}
//添加用户
BOOL CUserManage::AddUser(string strName,string strPswd)
{
	CString strTemp=strName.c_str();
	_bstr_t bstrName=strTemp.Trim().GetBuffer();
	strTemp=strPswd.c_str();
	_bstr_t bstrPswd=strTemp.Trim().GetBuffer();
	_bstr_t bstrSql="insert into  用户管理 (用户名,密码) values('" + bstrName + "','" + bstrPswd + "')";
	if (CheckValidateConnection())
		if (CheckUserName(strName))
			MessageBox(NULL,"用户名已存在！",0,0);
		else
			return theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//修改密码
BOOL CUserManage::EditPassWord(string strID,string strNewPswd)
{
	CString strTemp=strID.c_str();
	_bstr_t bstrName=strTemp.Trim().GetBuffer();
	strTemp=strNewPswd.c_str();
	_bstr_t bstrPswd=strTemp.Trim().GetBuffer();

	_bstr_t bstrSql="update  用户管理  set 密码='" + bstrPswd + "' where 编号=" + bstrName ;
	if (CheckValidateConnection())
		return theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//审核用户
BOOL CUserManage::AuditingUser(string strID)
{
	_bstr_t bstrSql= strID.c_str();
	if (CheckValidateConnection())
		return theBllApp.m_pDB->ExcuteSql("update  用户管理  set 状态='有效' where 编号=" +bstrSql ,adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//注销用户使用
BOOL CUserManage::DeleteUser(string strID)
{
	_bstr_t bstrSql= strID.c_str();
	if (CheckValidateConnection())
		return theBllApp.m_pDB->ExcuteSql("delete  用户管理  where 编号=" + bstrSql ,adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//用户登录
BOOL CUserManage::Login(string strName,string strPswd)
{
	_RecordsetPtr RcstPrt;
	CString strTemp=strName.c_str();
	_bstr_t bstrName=strTemp.Trim().GetBuffer();
	strTemp=strPswd.c_str();
	_bstr_t bstrPswd=strTemp.Trim().GetBuffer();

	_bstr_t bstrSql="select * from 用户管理  where 用户名='"+ bstrName +"'  and 密码='" + bstrPswd + "'";
	if (CheckValidateConnection())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
		if (RcstPrt!=NULL && !RcstPrt->adoEOF)
			return TRUE;
	}
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
	return FALSE;
}
//所有用户
_RecordsetPtr CUserManage::QueryAllUser()
{
	_RecordsetPtr RcstPrt;
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 用户管理 ",adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
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
//所有待审用户
_RecordsetPtr CUserManage::QueryAuditingUser()
{
	_RecordsetPtr RcstPrt;
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 用户管理  where 状态='待审'",adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
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
//所有有效用户
_RecordsetPtr CUserManage::QueryValidateUser()
{
	_RecordsetPtr RcstPrt;
	if (CheckValidateConnection())
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from 用户管理  where 状态='有效'",adCmdText);
	else
		MessageBox(NULL,"数据库访问失败！",0,0);
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
