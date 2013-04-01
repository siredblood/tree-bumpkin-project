#include "Concretion.h"

CConcretion CConcretion::instance;
CConcretion::CConcretion()
{

}

CConcretion::~CConcretion()
{

}

CConcretion & CConcretion::Instance()
{
	return instance;
}
//判断某个模型是否是建筑构件
BOOL CConcretion::IsBuildPart(_bstr_t strGuid)
{
	_bstr_t bstrSql="select * from 建筑构件 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 建筑构件 where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr!=NULL &&!RcstPtr->adoEOF)
		return TRUE;
	else
		return FALSE;
}
//判断某个模型是否在重点目标中
BOOL  CConcretion::IsHasTarget(_bstr_t strGuid)
{
	_variant_t var;
	//得到类型编号
	_bstr_t bstrTypeID,bstrTypeName="",bstrTargetName;
	_RecordsetPtr RcstPtr;
	_bstr_t bstrSql="select * from 基本信息 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 基本信息 where  GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("类别");
	if (var.vt==1)
		return FALSE;
	bstrTypeID=(_bstr_t)var;
	//得到类型名称
	bstrSql="select * from 类别信息 where 编号="+bstrTypeID;
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("类别名称");
	if (var.vt==1)
		return FALSE;
	bstrTypeName=(_bstr_t)var;
	//根据表去查找GUID去查找重点目标
	bstrSql="select * from "+bstrTypeName +"  where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from "+bstrTypeName +"  where GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("所属目标");
	if (var.vt==1)
		return FALSE;
	return TRUE;
}
//返回模型重点目标信息,key为字段名,value为字段值
map<string,string> CConcretion::GetTargetInfo(_bstr_t strGuid)
{
	map<string,string> m;
	_variant_t var;
	//得到类型编号
	_bstr_t bstrTypeID,bstrTypeName="",bstrTargetName;
	_RecordsetPtr RcstPtr;
	_bstr_t bstrSql="select * from 基本信息 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 基本信息 where  GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return m;
	var=RcstPtr->GetCollect("类别");
	if (var.vt==1)
		return m;
	bstrTypeID=(_bstr_t)var;
	//得到类型名称
	bstrSql="select * from 类别信息 where 编号="+bstrTypeID;
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return m;
	var=RcstPtr->GetCollect("类别名称");
	if (var.vt==1)
		return m;
	bstrTypeName=(_bstr_t)var;
	//根据表去查找GUID去查找重点目标
	bstrSql="select * from "+bstrTypeName +"  where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from "+bstrTypeName +"  where GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return m;
	var=RcstPtr->GetCollect("所属目标");
	if (var.vt==1)
		return m;
	bstrTargetName=(_bstr_t)var;
	//找重点目标信息
	bstrSql="select * from 重点目标  where 名称='"+bstrTargetName+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return m;
	long lFieldCounts = RcstPtr->GetFields()->GetCount();
	pair<string,string> p;
	for(long i = 0; i<lFieldCounts; i++)
	{
		bstrSql= RcstPtr->GetFields()->GetItem(i)->GetName();
		p.first=(char *)bstrSql;
		var=RcstPtr->GetCollect(i);
		bstrSql=(_bstr_t)(var.vt==1?"":var);
		p.second=(char *)bstrSql;
		m.insert(p);
	}
	return m;
}

BOOL CConcretion::GetTargetInfo(_bstr_t strGuid,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_variant_t var;
	//得到类型编号
	_bstr_t bstrTypeID,bstrTypeName="",bstrTargetName;
	_RecordsetPtr RcstPtr;
	_bstr_t bstrSql="select * from 基本信息 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 基本信息 where  GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("类别");
	if (var.vt==1)
		return FALSE;
	bstrTypeID=(_bstr_t)var;
	//得到类型名称
	bstrSql="select * from 类别信息 where 编号="+bstrTypeID;
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("类别名称");
	if (var.vt==1)
		return FALSE;
	bstrTypeName=(_bstr_t)var;
	//根据表去查找GUID去查找重点目标
	bstrSql="select * from "+bstrTypeName +"  where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from "+bstrTypeName +"  where GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("所属目标");
	if (var.vt==1)
		return FALSE;
	bstrTargetName=(_bstr_t)var;
	//找重点目标信息
	bstrSql="select * from 重点目标  where 名称='"+bstrTargetName+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	CBllHelp::Instance().QueryByCondit(RcstPtr,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}

BOOL CConcretion::GetTarGetInfoByName(_bstr_t strTargetName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//找重点目标信息
	_bstr_t bstrSql="select * from 重点目标  where 名称='"+strTargetName+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	CBllHelp::Instance().QueryByCondit(RcstPtr,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}

//返回模型构件所属建筑信息
map<string,string> CConcretion::GetBuildInfo(_bstr_t strGuid)
{
	map<string,string> m;
	_bstr_t bstrSql="select * from 建筑构件 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 建筑构件 where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL  || RcstPtr->adoEOF)
		return m;
	_bstr_t bstrTarget,bstrName;
	_variant_t var;
	var=RcstPtr->GetCollect("所属目标");
	if (var.vt==1)
		return m;
	bstrTarget=(_bstr_t)var;
	var=RcstPtr->GetCollect("所属目标建筑");
	if (var.vt==1)
		return m;
	bstrName=(_bstr_t)var;
	bstrSql="select * from 重点目标建筑 where 名称='"+bstrName+"'  and 所属目标='"+bstrTarget+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL  || RcstPtr->adoEOF)
		return m;
	pair<string,string> p;
	long lFieldCounts = RcstPtr->GetFields()->GetCount();
	for(long i = 0; i<lFieldCounts; i++)
	{
		bstrSql= RcstPtr->GetFields()->GetItem(i)->GetName();
		p.first=(char *)bstrSql;
		var=RcstPtr->GetCollect(i);
		bstrSql=(_bstr_t)(var.vt==1?"":var);
		p.second=(char *)bstrSql;
		m.insert(p);
	}
	return m;
}
BOOL CConcretion::GetBuildInfo(_bstr_t strGuid,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_bstr_t bstrSql="select * from 建筑构件 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 建筑构件 where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL  || RcstPtr->adoEOF)
		return FALSE;

	_bstr_t bstrTarget,bstrName;
	_variant_t var;
	var=RcstPtr->GetCollect("所属目标");
	if (var.vt==1)
		return FALSE;
	bstrTarget=(_bstr_t)var;
	var=RcstPtr->GetCollect("所属目标建筑");
	if (var.vt==1)
		return FALSE;
	bstrName=(_bstr_t)var;
	bstrSql="select * from 重点目标建筑 where 名称='"+bstrName+"'  and 所属目标='"+bstrTarget+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	CBllHelp::Instance().QueryByCondit(RcstPtr,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}



BOOL CConcretion::Save(_bstr_t strGuid, _bstr_t strTypeName, map<_bstr_t,_bstr_t> &mapFlds)
{
	_bstr_t strSql = "",strOldID, strOldTypeName;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM 基本信息 WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM 基本信息 WHERE  [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	//判断类别信息表是否存在记录
	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
	{	//基本信息表查无记录
		return Add(strGuid,strTypeName, mapFlds);
	}
	else
	{
		//基本信息表存在记录
		strOldID = pRecordSet->GetCollect("类别");
		return Update(strGuid,strOldID,strTypeName,mapFlds);
	}
}
BOOL CConcretion::Save(_bstr_t strGuid, _bstr_t strTypeName, vector<_bstr_t>&vfileds,vector<_bstr_t> &vValues)
{
	_bstr_t strSql = "", strOldID, strOldTypeName;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM 基本信息 WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM 基本信息 WHERE [GUID] = '" + strGuid + "'";
	
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	//判断类别信息表是否存在记录
	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
	{	//基本信息表查无记录
		return Add(strGuid,strTypeName,vfileds,vValues);
	}
	else
	{
		//基本信息表存在记录
		strOldID = pRecordSet->GetCollect("类别");
		return Update(strGuid,strOldID,strTypeName,vfileds,vValues);
	}
}

BOOL CConcretion::Delete(_bstr_t strGuid)
{
	vector<_bstr_t> vecStrSql;
	_bstr_t strDelSql1="", strDelSql2="", strSql = "", strID, strOldTypeName;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM 基本信息 WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM 基本信息 WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	//判断类别信息表是否存在记录
	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
	{	//基本信息表查无记录
		return TRUE;
	}
	else
	{
		//基本信息表存在记录
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strDelSql1 = "DELETE FROM 基本信息 WHERE GUID='" + strGuid + "'";
		else
			strDelSql1 = "DELETE FROM 基本信息 WHERE [GUID]='" + strGuid + "'";
		strID = pRecordSet->GetCollect("类别");
		strSql = "SELECT * FROM 类别信息 WHERE 编号= " + strID;
		pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
		if(pRecordSet == NULL)
			return FALSE;
		if(!pRecordSet->adoEOF)
		{
			strOldTypeName = pRecordSet->GetCollect("类别名称");
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSql = "SELECT * FROM " + strOldTypeName + " WHERE GUID='" + strGuid +"'";
			else
				strSql = "SELECT * FROM " + strOldTypeName + " WHERE [GUID]='" + strGuid +"'";
			pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
			//具体类别表存在记录
			if(!pRecordSet->adoEOF)
			{
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					strDelSql2 = "DELETE FROM " + strOldTypeName + " WHERE GUID='" + strGuid + "'";
				else
					strDelSql2 = "DELETE FROM " + strOldTypeName + " WHERE [GUID]='" + strGuid + "'";
			}
		}
	}
	vecStrSql.push_back(strDelSql1);
	if(strDelSql2.length() != 0)
		vecStrSql.push_back(strDelSql2);

	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strDelSql2 = "DELETE FROM 模型基本信息 WHERE GUID='" + strGuid + "'";
	else
		strDelSql2 = "DELETE FROM 模型基本信息 WHERE [GUID]='" + strGuid + "'";
	vecStrSql.push_back(strDelSql2);

	return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
}

int CConcretion::Load(_bstr_t strGUID,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts,string &strType,vector<string> &vecRecordSetH)
{
	_bstr_t strSQL;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL = "SELECT GUID,类别 FROM	基本信息 WHERE GUID = '" + strGUID + "'";
	else
		strSQL = "SELECT [GUID],[类别] FROM	基本信息 WHERE [GUID] = '" + strGUID + "'";
	
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//数据库层抓到异常返回
		return -4;//发生异常
	if(pRecordSet->adoEOF)
		return -3;//基本信息表中没有记录
	_bstr_t str;
	str = (_bstr_t)pRecordSet->GetCollect("类别");

	//得到所有的类别名称
	strSQL = "SELECT 编号,类别名称 FROM 类别信息";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//数据库层抓到异常返回
		return -4;//发生异常
	if(pRecordSet->adoEOF)
		return -2;//类别信息表中没有记录
	CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSetH,lFieldCounts);

	strSQL = "SELECT 编号,类别名称 FROM 类别信息 WHERE 编号 = " + str;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//数据库层抓到异常返回
		return -4;//发生异常
	if(pRecordSet->adoEOF)
		return -1;//类别信息表中符合条件的记录
	str = (_bstr_t)pRecordSet->GetCollect("类别名称");
	strType =((char *) (_bstr_t)pRecordSet->GetCollect("类别名称"));

	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		strSQL = "SELECT * FROM " + str + " WHERE GUID = '" + strGUID + "'";
	}
	else
		strSQL = "SELECT * FROM " + str + " WHERE [GUID] = '" + strGUID + "'";
	
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//数据库层抓到异常返回
		return -4;//发生异常
	if(pRecordSet->adoEOF)
	{
		CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSet,lFieldCounts);
		return 0;//对象表中没有记录
	}

	CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSet,lFieldCounts);
	return 1;//对象表中有记录
}

BOOL CConcretion::LoadType(_bstr_t strTable,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_bstr_t strSQL;
	strSQL = "SELECT * FROM " + strTable;
	_RecordsetPtr pRecordSet;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet==NULL)
		return FALSE;

	CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}

BOOL CConcretion::LoadType(_bstr_t strTable,_bstr_t strConditiong,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_bstr_t strSQL;
	strSQL = "SELECT * FROM " + strTable+"  where 1=1 "+strConditiong;
	_RecordsetPtr pRecordSet;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet==NULL)
		return FALSE;

	CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}

BOOL CConcretion::Add(_bstr_t strGuid,_bstr_t strTypeName,std::map<_bstr_t,_bstr_t,less<_bstr_t> > &mapFlds)
{
	_bstr_t strSql,strID,strSql1,strSql2;
	_RecordsetPtr pRecordSet;
	vector<_bstr_t> vecStrSql;
	_variant_t var;
	adoDataTypeEnum adoFldType;
	//从类别名称获取类别编号
	strSql = "SELECT * FROM 类别信息 WHERE 类别名称 = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL||pRecordSet->adoEOF)
		return FALSE;
	strID = pRecordSet->GetCollect("编号");
	//插入基本信息表语句
	if(CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql1 = "INSERT INTO 基本信息(GUID,类别) VALUES ('"+ strGuid + "'," + strID + ")";
	else
		strSql1 = "INSERT INTO [基本信息]([GUID],[类别]) VALUES ('"+ strGuid + "'," + strID + ")";
	//具体类别表存不存记录
	if(CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM " + strTypeName + " WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM " + strTypeName + " WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);

	string strTemp="";
	//测试
	if(pRecordSet == NULL)
		return FALSE;
	else
	{
		if(pRecordSet->adoEOF)
		{//具体类别表不存在记录
			map<_bstr_t,_bstr_t>::iterator itr1, itr2;
			_bstr_t strColumns,strValues;
			itr1 = mapFlds.begin();
			itr2 = --mapFlds.end();
			
			while(itr1 != itr2)
			{
				strTemp=(char *)(*itr1).first;
				if (strTemp=="ID")
				{
					itr1++;
					continue;
				}
				//字段
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					strColumns += (*itr1).first + ",";
				else
					strColumns +="[" +(*itr1).first + "],";
				//值
				var.bstrVal = (*itr1).first;
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
						strValues += "#" + (*itr1).second + "#,";
						break;
					case SqlServerType:
						strValues += "'" + (*itr1).second + "',";
						break;
					case OracleType:
						strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
						break;
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
					strValues+=(*itr1).second+",";
				else
					strValues+="'"+(*itr1).second+"',";
				//循环
				itr1++;
			}
			//最后一个字段
			//字段
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strColumns += (*itr1).first;
			else
				strColumns +="[" +(*itr1).first + "]";
			//值
			var.bstrVal = (*itr1).first;
			adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
			if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
					strValues += "#" + (*itr1).second + "#";
					break;
				case SqlServerType:
					strValues += "'" + (*itr1).second + "'";
					break;
				case OracleType:
					strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd')";
					break;
				}
			}
			else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
				strValues+=(*itr1).second;
			else
				strValues+="'"+(*itr1).second+"'";
			strSql2 = "INSERT INTO " + strTypeName + " ( " +  strColumns + " ) VALUES (" + strValues + ")";
		}
		else
		{//具体类别表存在记录
			map<_bstr_t,_bstr_t>::iterator itr1, itr2;
			_bstr_t strUpdateFormat="";
			itr1 = mapFlds.begin();
			itr2 = --mapFlds.end();
			while(itr1 != itr2)
			{
				strTemp=(char *)(*itr1).first;
				if (strTemp=="ID")
				{
					itr1++;
					continue;
				}
				var.bstrVal = (*itr1).first;
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
						strUpdateFormat +="["+ (*itr1).first + "]=#" + (*itr1).second + "#,";
						break;
					case SqlServerType:
						strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "',";
						break;
					case OracleType:
						strUpdateFormat += (*itr1).first +"=to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
						break;
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
					case SqlServerType:
						strUpdateFormat += "["+(*itr1).first + "]=" + (*itr1).second+ ",";
						break;
					case OracleType:
						strUpdateFormat += (*itr1).first +"="+(*itr1).second+ ",";
						break;
					}
				}
					
				else
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
					case SqlServerType:
						strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "',";
						break;
					case OracleType:
						strUpdateFormat += (*itr1).first + "='" + (*itr1).second + "',";
						break;
					}
				}
				//循环
				itr1++;
			}
			//最后一个字段
			var.bstrVal = (*itr1).first;
			adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
			if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
					strUpdateFormat +="["+ (*itr1).first + "]=#" + (*itr1).second + "#";
					break;
				case SqlServerType:
					strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "'";
					break;
				case OracleType:
					strUpdateFormat += (*itr1).first +"=to_date('" + (*itr1).second + "','yyyy-mm-dd')";
					break;
				}
			}
			else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
				case SqlServerType:
					strUpdateFormat += "["+(*itr1).first + "]=" + (*itr1).second;
					break;
				case OracleType:
					strUpdateFormat += (*itr1).first +"="+(*itr1).second;
					break;
				}
			}

			else
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
				case SqlServerType:
					strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "'";
					break;
				case OracleType:
					strUpdateFormat += (*itr1).first + "='" + (*itr1).second + "'";
					break;
				}
			}
			strSql2 = "UPDATE " + strTypeName + " SET " + strUpdateFormat + " WHERE [GUID] ='" + strGuid + "'";
		}
	}
	vecStrSql.push_back(strSql1);
	vecStrSql.push_back(strSql2);

	return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
}

BOOL CConcretion::Update(_bstr_t strGuid, _bstr_t  strOldID,_bstr_t strTypeName, std::map<_bstr_t,_bstr_t> &mapFlds)
{
	_bstr_t strSql, strNewID,strOldTypeName ;
	_bstr_t strSql1 = "",strSql2 = "", strSql3;
	_RecordsetPtr pRecordSet;
	vector<_bstr_t> vecStrSql;
	_variant_t var;
	adoDataTypeEnum adoFldType;
	string strTemp="";

	strSql = "SELECT * FROM 类别信息 WHERE 类别名称 = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL||pRecordSet->adoEOF)
		return FALSE;
	strNewID = pRecordSet->GetCollect("编号");
	if(strNewID != strOldID)
	{//类别修改
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql1 = "UPDATE 基本信息 SET 类别 = " + strNewID + " WHERE  GUID= '"+ strGuid + "'";
		else
			strSql1 = "UPDATE 基本信息 SET 类别 = " + strNewID + " WHERE  [GUID]= '"+ strGuid + "'";

		strSql = "SELECT * FROM 类别信息 WHERE 编号= " + strOldID;
		pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
		if(pRecordSet == NULL||pRecordSet->adoEOF)
			return FALSE;
		strOldTypeName = (_bstr_t)pRecordSet->GetCollect("类别名称");
		//从旧具体类别表删除记录
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE GUID  = '" + strGuid + "'";
		else
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE [GUID]  = '" + strGuid + "'";
	}

	//具体类别表存不存记录
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM " + strTypeName + " WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM " + strTypeName + " WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL)
		return FALSE;
	else
	{
		if(pRecordSet->adoEOF)
		{//具体类别表不存在记录
			map<_bstr_t,_bstr_t>::iterator itr1, itr2;
			_bstr_t strColumns,strValues;

			itr1 = mapFlds.begin();
			itr2 = --mapFlds.end();
			while(itr1 != itr2)
			{
				strTemp=(char *)(*itr1).first;
				if (strTemp=="ID")
				{
					itr1++;
					continue;
				}
				//字段
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					strColumns += (*itr1).first + ",";
				else
					strColumns +="[" +(*itr1).first + "],";
				//值
				var.bstrVal = (*itr1).first;
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
						strValues += "#" + (*itr1).second + "#,";
						break;
					case SqlServerType:
						strValues += "'" + (*itr1).second + "',";
						break;
					case OracleType:
						strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
						break;
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
					strValues+=(*itr1).second+",";
				else
					strValues+="'"+(*itr1).second+"',";
				//循环
				itr1++;
			}
			//最后一个字段
			//字段
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strColumns += (*itr1).first;
			else
				strColumns +="[" +(*itr1).first + "]";
			//值
			var.bstrVal = (*itr1).first;
			adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
			if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
					strValues += "#" + (*itr1).second + "#";
					break;
				case SqlServerType:
					strValues += "'" + (*itr1).second + "'";
					break;
				case OracleType:
					strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd')";
					break;
				}
			}
			else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
				strValues+=(*itr1).second;
			else
				strValues+="'"+(*itr1).second+"'";

			strSql3 = "INSERT INTO " + strTypeName + " ( " +  strColumns + " ) VALUES (" + strValues + ")";
		}
		else
		{//具体类别表存在记录
			map<_bstr_t,_bstr_t>::iterator itr1, itr2;
			_bstr_t strUpdateFormat="";
			mapFlds.erase("GUID");
			itr1 = mapFlds.begin();
			itr2 = --mapFlds.end();
			while(itr1 != itr2)
			{
				strTemp=(char *)(*itr1).first;
				if (strTemp=="ID")
				{
					itr1++;
					continue;
				}
				var.bstrVal = (*itr1).first;
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
						strUpdateFormat +="["+ (*itr1).first + "]=#" + (*itr1).second + "#,";
						break;
					case SqlServerType:
						strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "',";
						break;
					case OracleType:
						strUpdateFormat += (*itr1).first +"=to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
						break;
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
					case SqlServerType:
						strUpdateFormat += "["+(*itr1).first + "]=" + (*itr1).second+ ",";
						break;
					case OracleType:
						strUpdateFormat += (*itr1).first +"="+(*itr1).second+ ",";
						break;
					}
				}

				else
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
					case SqlServerType:
						strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "',";
						break;
					case OracleType:
						strUpdateFormat += (*itr1).first + "='" + (*itr1).second + "',";
						break;
					}
				}
				//循环
				itr1++;
			}
			//最后一个字段
			var.bstrVal = (*itr1).first;
			adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
			if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
					strUpdateFormat +="["+ (*itr1).first + "]=#" + (*itr1).second + "#";
					break;
				case SqlServerType:
					strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "'";
					break;
				case OracleType:
					strUpdateFormat += (*itr1).first +"=to_date('" + (*itr1).second + "','yyyy-mm-dd')";
					break;
				}
			}
			else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
				case SqlServerType:
					strUpdateFormat += "["+(*itr1).first + "]=" + (*itr1).second;
					break;
				case OracleType:
					strUpdateFormat += (*itr1).first +"="+(*itr1).second;
					break;
				}
			}

			else
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
				case AccessType:
				case SqlServerType:
					strUpdateFormat += "["+(*itr1).first + "]='" + (*itr1).second + "'";
					break;
				case OracleType:
					strUpdateFormat += (*itr1).first + "='" + (*itr1).second + "'";
					break;
				}
			}
			strSql3 = "UPDATE " + strTypeName + " SET " + strUpdateFormat + " WHERE GUID ='" + strGuid + "'";
		}
	}
	if(strSql1.length() != 0)
		vecStrSql.push_back(strSql1);
	if(strSql2.length() != 0)
		vecStrSql.push_back(strSql2);
	vecStrSql.push_back(strSql3);

	return theBllApp.m_pDB->ExcuteTrans(vecStrSql, adCmdText);
}

BOOL CConcretion::Add(_bstr_t strGuid,_bstr_t strTypeName,vector<_bstr_t>&vfileds,vector<_bstr_t> &vValues)
{
	if ( strGuid.length()<1 ||strTypeName.length()<1 || vfileds.size()<1||vValues.size()<1)
		return FALSE;
	_bstr_t strSql,strID, strSql1,strSql2;
	_RecordsetPtr pRecordSet;
	vector<_bstr_t> vecStrSql;
	adoDataTypeEnum adoFldType;
	_variant_t var;
	string strTemp="";

	//从类别名称获取类别编号
	strSql = "SELECT * FROM 类别信息 WHERE 类别名称 = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL||pRecordSet->adoEOF)
		return FALSE;
	strID = pRecordSet->GetCollect("编号");
	//插入基本信息表语句
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql1 = "INSERT INTO 基本信息(GUID,类别) VALUES ('"+ strGuid + "'," + strID + ")";
	else
		strSql1 = "INSERT INTO 基本信息([GUID],[类别]) VALUES ('"+ strGuid + "'," + strID + ")";
	//具体类别表存不存记录
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM " + strTypeName + " WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM " + strTypeName + " WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL)
		return FALSE;
	else
	{
		bool isAdd=false;
		if (pRecordSet->adoEOF)
			isAdd=true;
		if(isAdd)
		{//具体类别表不存在记录
			_bstr_t strColumns,strValues;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				if (isFirst)
				{
					isFirst=false;
					//字段
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns+=(*itr);
					else
						strColumns+="["+(*itr)+"]";
					//值
					var.bstrVal = (*itr);
					adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
					if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
					{
						switch(CDatabaseFactory::m_enumDatabaseType)
						{
						case AccessType:
							strValues += "#" + (*itr2) + "#";
							break;
						case SqlServerType:
							strValues += "'" + (*itr2) + "'";
							break;
						case OracleType:
							strValues += "to_date('" + (*itr2) + "','yyyy-mm-dd')";
							break;
						}
					}
					else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
						strValues+=(*itr2);
					else
						strValues+="'"+(*itr2)+"'";
				}
				else
				{
					strTemp=(char *)(*itr);
					if (strTemp=="ID")
					{
						itr++;
						itr2++;
						continue;
					}

					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns+=","+(*itr);
					else
						strColumns+=",["+(*itr)+"]";

					var.bstrVal = (*itr);
					adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
					if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
					{
						switch(CDatabaseFactory::m_enumDatabaseType)
						{
						case AccessType:
							strValues += ",#" + (*itr2) + "#";
							break;
						case SqlServerType:
							strValues += ",'" + (*itr2) + "'";
							break;
						case OracleType:
							strValues += ",to_date('" + (*itr2) + "','yyyy-mm-dd')";
							break;
						}
					}
					else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
						strValues+=","+(*itr2);
					else
						strValues+=",'"+(*itr2)+"'";
				}
				itr++;
				itr2++;
			}
			strSql2 = "INSERT INTO " + strTypeName + " ( " +  strColumns + " ) VALUES (" + strValues + ")";
		}
		else
		{//具体类别表存在记录
			_bstr_t strUpdateFormat;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				//字段
				if (isFirst)
				{
					isFirst=false;
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strUpdateFormat+=(*itr);
					else
						strUpdateFormat+="["+(*itr)+"]";
				}
				else
				{
					strTemp=(char *)(*itr);
					if (strTemp=="ID")
					{
						itr++;
						itr2++;
						continue;
					}

					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strUpdateFormat+=","+(*itr);
					else
						strUpdateFormat+=",["+(*itr)+"]";
				}
				//值
				var.bstrVal = (*itr);
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
						strUpdateFormat += "= #"+(*itr2)+"#";
						break;
					case SqlServerType:
						strUpdateFormat+="='"+(*itr2)+"'";
						break;
					case OracleType:
						strUpdateFormat += " = to_date('" + (*itr2) + "','yyyy-mm-dd')";
						break;
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
					strUpdateFormat += "=" + (*itr2);
				else
					strUpdateFormat+="='"+(*itr2)+"'";
				//循环
				itr++;
				itr2++;
			}
			strSql2 = "UPDATE " + strTypeName + " SET " + strUpdateFormat + " WHERE [GUID] ='" + strGuid + "'";
		}

	}
	vecStrSql.push_back(strSql1);
	vecStrSql.push_back(strSql2);
	return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
}

BOOL CConcretion::Update(_bstr_t strGuid, _bstr_t  strOldID,_bstr_t strTypeName, vector<_bstr_t>&vfileds,vector<_bstr_t> &vValues)
{
	_bstr_t strSql, strNewID,strOldTypeName , strSql1 = "",strSql2 = "", strSql3;
	_RecordsetPtr pRecordSet;
	vector<_bstr_t> vecStrSql;
	adoDataTypeEnum adoFldType;
	_variant_t var;
	string strTemp="";

	strSql = "SELECT * FROM 类别信息 WHERE 类别名称 = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL || pRecordSet->adoEOF)
		return FALSE;
	strNewID = pRecordSet->GetCollect("编号");
	if(strNewID != strOldID)
	{//类别修改
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql1 = "UPDATE 基本信息 SET 类别 = " + strNewID + " WHERE  GUID= '"+ strGuid + "'";
		else
			strSql1 = "UPDATE 基本信息 SET [类别] = " + strNewID + " WHERE  [GUID]= '"+ strGuid + "'";
		strSql = "SELECT * FROM 类别信息 WHERE 编号= " + strOldID;
		pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
		if(pRecordSet == NULL || pRecordSet->adoEOF)
			return FALSE;
		strOldTypeName = (_bstr_t)pRecordSet->GetCollect("类别名称");
		//从旧具体类别表删除记录
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE GUID  = '" + strGuid + "'";
		else
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE [GUID]  = '" + strGuid + "'";
	}

	//具体类别表存不存记录
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM " + strTypeName + " WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM " + strTypeName + " WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL)
		return FALSE;
	else
	{
		if(pRecordSet->adoEOF)
		{//具体类别表不存在记录
			_bstr_t strColumns,strValues;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				if (isFirst)
				{
					isFirst=false;
					//字段
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns+=(*itr);
					else
						strColumns+="["+(*itr)+"]";
					//值
					var.bstrVal = (*itr);
					adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
					if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
					{
						switch(CDatabaseFactory::m_enumDatabaseType)
						{
						case AccessType:
							strValues += "#" + (*itr2) + "#";
							break;
						case SqlServerType:
							strValues += "'" + (*itr2) + "'";
							break;
						case OracleType:
							strValues += "to_date('" + (*itr2) + "','yyyy-mm-dd')";
							break;
						}
					}
					else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
						strValues+=(*itr2);
					else
						strValues+="'"+(*itr2)+"'";
				}
				else
				{
					strTemp=(char *)(*itr);
					if (strTemp=="ID")
					{
						itr++;
						itr2++;
						continue;
					}

					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns+=","+(*itr);
					else
						strColumns+=",["+(*itr)+"]";

					var.bstrVal = (*itr);
					adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
					if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
					{
						switch(CDatabaseFactory::m_enumDatabaseType)
						{
						case AccessType:
							strValues += ",#" + (*itr2) + "#";
							break;
						case SqlServerType:
							strValues += ",'" + (*itr2) + "'";
							break;
						case OracleType:
							strValues += ",to_date('" + (*itr2) + "','yyyy-mm-dd')";
							break;
						}
					}
					else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
						strValues+=","+(*itr2);
					else
						strValues+=",'"+(*itr2)+"'";
				}
				itr++;
				itr2++;
			}
			strSql3 = "INSERT INTO " + strTypeName + " ( " +  strColumns + " ) VALUES (" + strValues + ")";
		}
		else
		{//具体类别表存在记录
			_bstr_t strUpdateFormat;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				if (isFirst)
				{
					isFirst=false;
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strUpdateFormat+=(*itr);
					else
						strUpdateFormat+="["+(*itr)+"]";
				}
				else
				{
					strTemp=(char *)(*itr);
					if (strTemp=="ID")
					{
						itr++;
						itr2++;
						continue;
					}
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strUpdateFormat+=","+(*itr);
					else
						strUpdateFormat+=",["+(*itr)+"]";
				}
				var.bstrVal = (*itr);
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case AccessType:
						strUpdateFormat += "= #"+(*itr2)+"#";
						break;
					case SqlServerType:
						strUpdateFormat+="='"+(*itr2)+"'";
						break;
					case OracleType:
						strUpdateFormat += " = to_date('" + (*itr2) + "','yyyy-mm-dd')";
						break;
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
					strUpdateFormat += "=" + (*itr2);
				else
					strUpdateFormat+="='"+(*itr2)+"'";
				itr++;
				itr2++;
			}
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSql3 = "UPDATE " + strTypeName + " SET " + strUpdateFormat + " WHERE GUID ='" + strGuid + "'";
			else
				strSql3 = "UPDATE " + strTypeName + " SET " + strUpdateFormat + " WHERE [GUID] ='" + strGuid + "'";
		}
	}
	if(strSql1.length() != 0)
		vecStrSql.push_back(strSql1);
	if(strSql2.length() != 0)
		vecStrSql.push_back(strSql2);
	vecStrSql.push_back(strSql3);

	return theBllApp.m_pDB->ExcuteTrans(vecStrSql, adCmdText);
}
//补充
//得到模型表的所有GUID
vector<string> CConcretion::GetAllGuid(_bstr_t strTableName)
{
	vector<string> v;
	string strGuid;
	_variant_t var;
	_bstr_t strSql="SELECT [GUID] FROM  "+strTableName;
	if(CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		strSql="SELECT  GUID  FROM   "+strTableName;
	}
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
	if (Rcst!=NULL&&!Rcst->adoEOF)
	{
		var=(Rcst->GetCollect("GUID"));
		if (var.vt==1)
			return v;
		while(!Rcst->adoEOF)
		{
			strGuid=(char *)((_bstr_t)Rcst->GetCollect("GUID"));
			v.push_back(strGuid);
			Rcst->MoveNext();
		}
	}
	return v;
}

//判断是否是摄像头
BOOL CConcretion::IsCamara(_bstr_t strGuid)
{
	BOOL bIs=FALSE;
	_bstr_t bstrSql="select * from 摄像头 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 摄像头 where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr!=NULL)
	{
		if ( !RcstPtr->adoEOF)
			bIs = TRUE;
		RcstPtr->Close();
		RcstPtr.Release();
	}
	return bIs;
}
	
//判断是否是附属设施
BOOL CConcretion::IsFacilitie(_bstr_t strGuid)
{
	BOOL bIs=FALSE;
	_bstr_t bstrSql="select * from 附属设施 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 附属设施 where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr!=NULL)
	{
		if ( !RcstPtr->adoEOF)
			bIs = TRUE;
		RcstPtr->Close();
		RcstPtr.Release();
	}
	return bIs;
}
	
//判断是否是警力
BOOL CConcretion::IsPolice(_bstr_t strGuid)
{
	BOOL bIs=FALSE;
	_bstr_t bstrSql="select * from 警力 where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from 警力 where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr!=NULL)
	{
		if ( !RcstPtr->adoEOF)
			bIs = TRUE;
		RcstPtr->Close();
		RcstPtr.Release();
	}
	return bIs;
}