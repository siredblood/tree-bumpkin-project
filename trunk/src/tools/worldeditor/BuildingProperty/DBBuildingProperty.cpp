#include "pch.hpp"
#include "DataBaseLib/DBHelper.h"
#include "DBBuildingProperty.h"

CDBBuildingProperty::CDBBuildingProperty()
{

}

CDBBuildingProperty::~CDBBuildingProperty()
{

}

bool CDBBuildingProperty::Save(const LinkedStringMap &mapProperty)
{
	std::string strId;
	int id = -1;
	for(LinkedStringMap::const_iterator citr=mapProperty.begin(); 
		citr!=mapProperty.end(); ++citr)
	{
		if((*citr).first=="±‡∫≈"){
			strId = (*citr).second.c_str();
			id = ::atoi(strId.c_str());
			break;
		}
	}

	if(id<0){
		return Add(mapProperty);
	}else{
		return Update(mapProperty);
	}
	return true;
}

bool CDBBuildingProperty::Save(const std::vector< LinkedStringMap > &vProperties)
{
	std::vector<_bstr_t> vStrSql;
	for(std::vector< LinkedStringMap >::const_iterator citr=vProperties.begin();
		citr!=vProperties.end(); ++citr)
	{
		std::string strSql = GetUpdateSql(*citr);
		vStrSql.push_back(strSql.c_str());
	}
	BOOL bRes = theBllApp.m_pDB->ExcuteTrans(vStrSql, adCmdText);
	return bRes==TRUE ? true : false;
}

bool CDBBuildingProperty::Delete(const std::vector<std::string> &vIds)
{
	std::vector<_bstr_t> vStrSql;
	std::string strSql;
	for(std::vector<std::string>::const_iterator citr=vIds.begin(); citr!=vIds.end(); ++citr)
	{
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql = "DELETE FROM Ω®÷˛ Ù–‘ WHERE ±‡∫≈=" + (*citr);
		else
			strSql = "DELETE FROM Ω®÷˛ Ù–‘ WHERE [±‡∫≈]=" + (*citr);
		vStrSql.push_back(strSql.c_str());
	}
	BOOL bRes = theBllApp.m_pDB->ExcuteTrans(vStrSql, adCmdText);
	return bRes==TRUE ? true : false;
}

bool CDBBuildingProperty::Query(std::vector< LinkedStringMap > &vProperties)
{
	_bstr_t bstrSql = "select * from Ω®÷˛ Ù–‘";

	_RecordsetPtr rs = theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (rs==NULL || rs->adoEOF)
		return false;

	long lFieldCounts = rs->GetFields()->GetCount();
	while(!rs->adoEOF){
		_bstr_t bstrField, bstrValue;
		_variant_t vart;
		LinkedStringMap mapProperty;

		for(long i = 0; i<lFieldCounts; i++){
			bstrField = rs->GetFields()->GetItem(i)->GetName();
			vart = rs->GetCollect(i);
			bstrValue=(_bstr_t)(vart.vt==1?"":vart);
			mapProperty.insert(std::make_pair<std::string, std::string>((char *)bstrField, (char *)bstrValue));
		}
		vProperties.push_back(mapProperty);
		rs->MoveNext();
	}
	return true;
}

bool CDBBuildingProperty::Query(const std::string &strGuid, LinkedStringMap &mapProperty)
{
	_bstr_t bstrSql;
	_bstr_t bstrGuid(strGuid.c_str());
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from Ω®÷˛ Ù–‘ where GUID='"+bstrGuid+"'";
	else
		bstrSql="select * from Ω®÷˛ Ù–‘ where [GUID]='"+bstrGuid+"'";

	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL)
		return false;

	long lFieldCounts = RcstPtr->GetFields()->GetCount();
	_bstr_t bstrField, bstrValue;
	_variant_t vart;
	if(RcstPtr->adoEOF){
		for(long i = 0; i<lFieldCounts; i++)
		{
			bstrField = RcstPtr->GetFields()->GetItem(i)->GetName();
			mapProperty.insert(std::make_pair<std::string, std::string>((char *)bstrField, ""));
		}
		return false;
	}else{
		for(long i = 0; i<lFieldCounts; i++)
		{
			bstrField = RcstPtr->GetFields()->GetItem(i)->GetName();
			vart = RcstPtr->GetCollect(i);
			bstrValue=(_bstr_t)(vart.vt==1?"":vart);
			mapProperty.insert(std::make_pair<std::string, std::string>((char *)bstrField, (char *)bstrValue));
		}
		return true;
	}
}

bool CDBBuildingProperty::IsExist(const std::string &strGuid)
{
	_bstr_t bstrSql;
	_bstr_t bstrGuid(strGuid.c_str());
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from Ω®÷˛ Ù–‘ where GUID='"+bstrGuid+"'";
	else
		bstrSql="select * from Ω®÷˛ Ù–‘ where [GUID]='"+bstrGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return false;
	else
		return true;
}

bool CDBBuildingProperty::Add(const LinkedStringMap &mapProperty)
{
	std::string strSql, strVal, strKey;
	bool bFirst = true;
	//≤Â»Î”Ôæ‰
	for(LinkedStringMap::const_iterator citr=mapProperty.begin(); 
		citr!=mapProperty.end(); ++citr)
	{
		if((*citr).first=="±‡∫≈") 
			continue;
		if(bFirst){
			bFirst = false;
			if(CDatabaseFactory::m_enumDatabaseType==OracleType)
				strKey = (*citr).first;
			else
				strKey = "[" + (*citr).first + "]";
			strVal = "'" + (*citr).second + "'";
		}else{
			if(CDatabaseFactory::m_enumDatabaseType==OracleType)
				strKey += "," + (*citr).first;
			else
				strKey += ",[" + (*citr).first + "]";
			strVal += ",'" + (*citr).second + "'";
		}
	}

	strSql = "INSERT INTO Ω®÷˛ Ù–‘(" + strKey + ") VALUES (" + strVal + ")";
	BOOL bRes = theBllApp.m_pDB->ExcuteSql(strSql.c_str(), adCmdText);

	return bRes==TRUE ? true : false;
}

bool CDBBuildingProperty::Update(const LinkedStringMap &mapProperty)
{
	std::string strSql = GetUpdateSql(mapProperty);
	BOOL bRes = theBllApp.m_pDB->ExcuteSql(strSql.c_str(), adCmdText);

	return bRes==TRUE ? true : false;
}

std::string CDBBuildingProperty::GetUpdateSql(const LinkedStringMap &mapProperty)
{
	std::string strSql, strSet, strCondition;
	bool bFirst = true;
	//≤Â»Î”Ôæ‰
	for(LinkedStringMap::const_iterator citr=mapProperty.begin(); 
		citr!=mapProperty.end(); ++citr)
	{
		if((*citr).first=="±‡∫≈"){
			if(CDatabaseFactory::m_enumDatabaseType==OracleType)
				strCondition = "±‡∫≈=" + (*citr).second;
			else
				strCondition = "[±‡∫≈]=" + (*citr).second;
			continue;
		}
		if(bFirst){
			bFirst = false;
			if(CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSet = (*citr).first + "='" + (*citr).second + "'";
			else
				strSet = "[" + (*citr).first + "]='" + (*citr).second + "'";
		}else{
			if(CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSet += "," + (*citr).first + "='" + (*citr).second + "'";
			else
				strSet += ",[" + (*citr).first + "]='" + (*citr).second + "'";
		}
	}

	strSql = "UPDATE Ω®÷˛ Ù–‘ SET " + strSet + " WHERE " + strCondition;
	return strSql;
}