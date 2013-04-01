#include "BaseInfo.h"

CBaseInfo::CBaseInfo(void)
{
}

CBaseInfo::~CBaseInfo(void)
{
}

BOOL CBaseInfo::AddField(_bstr_t strTableName,_bstr_t strFieldName, string enumFieldType, int iFieldSize)
{
	CFields *fileds=new CFields();
	fileds->AddField(strFieldName,GetDataTypeByString(enumFieldType),iFieldSize);
	_bstr_t strFormatstring = fileds->GetFieldFormat();
	return theBllApp.m_pDB->CreateField(strTableName,strFormatstring);
}
BOOL CBaseInfo::UpdateFiled(_bstr_t strTableName,_bstr_t strFieldName, string enumFieldType, int iFieldSize)
{
	CFields *fileds=new CFields();
	fileds->AddField(strFieldName,GetDataTypeByString(enumFieldType),iFieldSize);
	_bstr_t strFormatstring = fileds->GetFieldFormat();
	return theBllApp.m_pDB->ModifyField(strTableName,strFormatstring);
}
BOOL CBaseInfo::DeleteFiled(_bstr_t strTableName,_bstr_t strFieldName )
{
	return theBllApp.m_pDB->DropField(strTableName,strFieldName);
}

void CBaseInfo::QueryFileds(_bstr_t strTableName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"表！"),_T("提示"),0);
		return ;
	}
	std::vector<std::string> myFiled;
	std::vector<std::string> myRcst;
	long mycount;

	_RecordsetPtr pRS=theBllApp.m_pDB->GetRecordSet(strTableName);
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(pRS,myFiled,myRcst,mycount);
	//字段
	vecField.clear();
	vecField.push_back("字段名称");
	vecField.push_back("字符");
	vecField.push_back("64");
	vecField.push_back("字段类型");
	vecField.push_back("字符");
	vecField.push_back("64");
	vecField.push_back("字段大小");
	vecField.push_back("整型");
	vecField.push_back("64");
	//记录
	vecRecordSet.clear();
	vecRecordSet=myFiled;
	lFieldCounts=3;
}
FieldType CBaseInfo::GetDataTypeByString(string strType)
{
	FieldType type;
	if (strType=="整型")
	{
		type=IntType;
	}
	else if (strType=="浮点型")
	{
		type=FloatType;
	}
	else if (strType=="日期")
	{
		type=DateType;
	}
	else
	{
		type=CharType;
	}
	return type;
}