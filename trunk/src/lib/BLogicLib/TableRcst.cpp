#include "TableRcst.h"

CTableRcst CTableRcst::instance;
CTableRcst::CTableRcst(void)
{
}

CTableRcst::~CTableRcst(void)
{
}
CTableRcst & CTableRcst::Instance()
{
	return instance;
}
BOOL CTableRcst::Save(_bstr_t strTableName,_bstr_t strExceptField, map<_bstr_t,_bstr_t> mPropertys)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}

	if (mPropertys.empty() || mPropertys.size()<1)
		return FALSE;
	mPropertys.erase(strExceptField);
	if (mPropertys.empty()||mPropertys.size()<1)
		return FALSE;

	//变量声明
	map<_bstr_t,_bstr_t>::iterator itr1, itr2;
	_bstr_t strColumns,strValues,strSql;
	adoDataTypeEnum adoFldType;
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	_variant_t var;
	itr1 = mPropertys.begin();
	itr2 = --mPropertys.end();
	//构造sql语句
	while(itr1 != itr2)
	{
		var.bstrVal =((*itr1).first);
		adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strColumns += (*itr1).first + ",";
		else
			strColumns +="["+ (*itr1).first + "],";
		if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case OracleType:
				strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
				break;
			case AccessType:
				strValues += "#"+(*itr1).second+"#,";
				break;
			default:
				strValues+="'"+(*itr1).second+"',";
			}
			
		}
		else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
			strValues+=(*itr1).second+",";
		else
			strValues+="'"+(*itr1).second+"',";
		itr1++;
	}
	//构造最后一个字段
	var.bstrVal =((*itr1).first);
	adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strColumns += (*itr1).first;
	else
		strColumns +="["+ (*itr1).first + "]";
	if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
			strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd')";
			break;
		case AccessType:
			strValues += "#"+(*itr1).second+"#";
			break;
		default:
			strValues+="'"+(*itr1).second+"'";
		}

	}
	else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
		strValues+=(*itr1).second;
	else
		strValues+="'"+(*itr1).second+"'";

	strSql = "INSERT INTO  "+strTableName+" ( " +  strColumns + " ) VALUES (" + strValues + ")";
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
BOOL CTableRcst::Save(_bstr_t strTableName, _bstr_t strExceptField,vector<map<_bstr_t,_bstr_t>> vModels)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (vModels.empty() || vModels.size()<1)
		return FALSE;
	//变量声明
	vector<_bstr_t> vSql;
	_bstr_t strColumns,strValues,strSql;
	map<_bstr_t,_bstr_t> mModel;
	map<_bstr_t,_bstr_t>::iterator itr1, itr2;
	adoDataTypeEnum adoFldType;
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	_variant_t var;

	for (vector<map<_bstr_t,_bstr_t>>::iterator vi=vModels.begin();vi!=vModels.end();vi++)
	{
		strColumns="";
		strValues="";
		mModel=*vi;
		if (!mModel.empty()&&mModel.size()>0)
		{
			mModel.erase(strExceptField);
			if (!mModel.empty()&&mModel.size()>0)
			{
				itr1 = mModel.begin();
				itr2 = --mModel.end();
				while(itr1 != itr2)
				{
					var.bstrVal =((*itr1).first);
					adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();

					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns += (*itr1).first + ",";
					else
						strColumns +="["+ (*itr1).first + "],";
					if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
					{
						switch(CDatabaseFactory::m_enumDatabaseType)
						{
						case OracleType:
							strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
							break;
						case AccessType:
							strValues += "#"+(*itr1).second+"#,";
							break;
						default:
							strValues += "'"+(*itr1).second+"',";
						}
					}
					else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
						strValues+=(*itr1).second+",";
					else
						strValues+="'"+(*itr1).second+"',";
					itr1++;
				}
				//构造sql语句
				var.bstrVal =((*itr1).first);
				adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					strColumns += (*itr1).first;
				else
					strColumns +="["+ (*itr1).first + "]";
				if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
				{
					switch(CDatabaseFactory::m_enumDatabaseType)
					{
					case OracleType:
						strValues += "to_date('" + (*itr1).second + "','yyyy-mm-dd')";
						break;
					case AccessType:
						strValues += "#"+(*itr1).second+"#";
						break;
					default:
						strValues += "'"+(*itr1).second+"'";
					}
				}
				else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
					strValues+=(*itr1).second;
				else
					strValues+="'"+(*itr1).second+"'";

				strSql = "INSERT INTO  "+strTableName+" ( " +  strColumns + " ) VALUES (" + strValues + ")";
				vSql.push_back(strSql);
			}
		}
	}
	if (vSql.size()>0)
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	else 
		return FALSE;
}
BOOL CTableRcst::Update(_bstr_t strTableName,_bstr_t strKeyName,map<_bstr_t,_bstr_t> mPropertys)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (mPropertys.empty() || mPropertys.size()<1)
		return FALSE;
	map<_bstr_t,_bstr_t>::iterator iid=mPropertys.find(strKeyName);
	if (iid==mPropertys.end())
		return FALSE;
	_bstr_t strId=(*iid).second;
	if (strId.operator ==(""))
		return FALSE;
	mPropertys.erase(strKeyName);
	if (mPropertys.size()<1)
		return FALSE;

	//变量声明
	adoDataTypeEnum adoFldType;
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	_variant_t var;
	map<_bstr_t,_bstr_t>::iterator itr1, itr2;
	_bstr_t strUpdateFormat="",strSql="";
	itr1 = mPropertys.begin();
	itr2 = --mPropertys.end();
	while(itr1 != itr2)
	{
		var.bstrVal =((*itr1).first);
		adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strUpdateFormat += (*itr1).first + "=";
		else
			strUpdateFormat +="["+ (*itr1).first + "]=";
		if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case OracleType:
				strUpdateFormat +="to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
				break;
			case AccessType:
				strUpdateFormat += "#"+(*itr1).second+"#,";
				break;
			default:
				strUpdateFormat += "'"+(*itr1).second+"',";
			}
		}	
		else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
			strUpdateFormat+=(*itr1).second+",";
		else
			strUpdateFormat+="'"+(*itr1).second+"',";
		itr1++;
	}
	//构造最后一个字段
	var.bstrVal =((*itr1).first);
	adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strUpdateFormat += (*itr1).first + "=";
	else
		strUpdateFormat +="["+ (*itr1).first + "]=";
	if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
			strUpdateFormat +="to_date('" + (*itr1).second + "','yyyy-mm-dd')";
			break;
		case AccessType:
			strUpdateFormat += "#"+(*itr1).second+"#";
			break;
		default:
			strUpdateFormat += "'"+(*itr1).second+"'";
		}
	}	
	else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
		strUpdateFormat+=(*itr1).second;
	else
		strUpdateFormat+="'"+(*itr1).second+"'";

	//构造where条件
	adoFldType = pRecordSet->GetFields()->GetItem(strKeyName)->GetType();
	if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
				strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" =" + "to_date('" + strId + "','yyyy-mm-dd')";
				break;
			case AccessType:
				strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" =#"+strId+"#";
				break;
			default:
				strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" ='"+strId+"'";
		}
	}
	else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
		strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" ="+strId;
	else
		strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + "  WHERE  "+strKeyName+" ='"+strId+"'";
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
BOOL CTableRcst::Update(_bstr_t strTableName,_bstr_t strKeyName,vector<map<_bstr_t,_bstr_t>> vModels)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}
	if (vModels.empty() || vModels.size()<1)
		return FALSE;
	vector<_bstr_t> vsqls;
	map<_bstr_t,_bstr_t> mPropertys;
	map<_bstr_t,_bstr_t>::iterator iid,itr1, itr2;
	adoDataTypeEnum adoFldType;
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	_variant_t var;
	_bstr_t strUpdateFormat="",strSql="",strId="";
	for (vector<map<_bstr_t,_bstr_t>>::iterator vi=vModels.begin();vi!=vModels.end();vi++)
	{
		strUpdateFormat="";
		mPropertys=*vi;
		if (!mPropertys.empty()&&mPropertys.size()>0)
		{
			iid=mPropertys.find(strKeyName);
			if (iid!=mPropertys.end())
			{
				strId=(*iid).second;
				if (strId.operator !=(""))
				{
					mPropertys.erase(strKeyName);
					if (mPropertys.size()>0)
					{
						itr1 = mPropertys.begin();
						itr2 = --mPropertys.end();
						while(itr1 != itr2)
						{
							var.bstrVal =((*itr1).first);
							adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
							if (CDatabaseFactory::m_enumDatabaseType==OracleType)
								strUpdateFormat += (*itr1).first + "=";
							else
								strUpdateFormat +="["+ (*itr1).first + "]=";

							if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
							{
								switch(CDatabaseFactory::m_enumDatabaseType)
								{
								case OracleType:
									strUpdateFormat +="to_date('" + (*itr1).second + "','yyyy-mm-dd'),";
									break;
								case AccessType:
									strUpdateFormat += "#"+(*itr1).second+"#,";
									break;
								default:
									strUpdateFormat += "'"+(*itr1).second+"',";
								}
							}
							else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
								strUpdateFormat+=(*itr1).second+",";
							else
								strUpdateFormat+="'"+(*itr1).second+"',";
							itr1++;
						}
						//构造最后一个字段
						var.bstrVal =((*itr1).first);
						adoFldType = pRecordSet->GetFields()->GetItem(var.bstrVal)->GetType();
						if (CDatabaseFactory::m_enumDatabaseType==OracleType)
							strUpdateFormat += (*itr1).first + "=";
						else
							strUpdateFormat +="["+ (*itr1).first + "]=";

						if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
						{
							switch(CDatabaseFactory::m_enumDatabaseType)
							{
							case OracleType:
								strUpdateFormat +="to_date('" + (*itr1).second + "','yyyy-mm-dd')";
								break;
							case AccessType:
								strUpdateFormat += "#"+(*itr1).second+"#";
								break;
							default:
								strUpdateFormat += "'"+(*itr1).second+"'";
							}
						}
						else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
							strUpdateFormat+=(*itr1).second;
						else
							strUpdateFormat+="'"+(*itr1).second+"'";

						//构造where条件
						adoFldType = pRecordSet->GetFields()->GetItem(strKeyName)->GetType();
						if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
						{
							switch(CDatabaseFactory::m_enumDatabaseType)
							{
							case OracleType:
									strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" =" + "to_date('" + strId + "','yyyy-mm-dd')";
									break;
							case AccessType:
								strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" =#"+strId+"#";
								break;
							default:
								strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" ='"+strId+"'";
							}
						}
						else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
							strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + " WHERE  "+strKeyName+" ="+strId;
						else
							strSql = "UPDATE  "+strTableName+"  SET " + strUpdateFormat + "  WHERE  "+strKeyName+" ='"+strId+"'";
						vsqls.push_back(strSql);
					}
				}
			}
		}
	}
	if (vsqls.size()>0)
		return theBllApp.m_pDB->ExcuteTrans(vsqls,adCmdText);
	else
		return FALSE;
}
BOOL CTableRcst::Delete(_bstr_t strTableName,_bstr_t strKeyName,_bstr_t strId)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	_bstr_t strSql;
	adoDataTypeEnum adoFldType;
	adoFldType = pRecordSet->GetFields()->GetItem(strKeyName)->GetType();
	if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
			case OracleType:
				strSql = "delete from  "+strTableName +"  WHERE  "+strKeyName+" =to_date('" + strId + "','yyyy-mm-dd')";
				break;
			case AccessType:
				strSql = "delete from  "+strTableName +"  WHERE  "+strKeyName+" =#"+strId+"#";
				break;
			default:
				strSql = "delete from  "+strTableName +"  WHERE  "+strKeyName+" ='"+strId+"'";
		}
	}
	else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
		strSql = "delete from  "+strTableName +"  WHERE  "+strKeyName+" ="+strId;
	else
		strSql = "delete from  "+strTableName+ "  WHERE  "+strKeyName+" ='"+strId+"'";
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
BOOL CTableRcst::Delete(_bstr_t strTableName,_bstr_t strKeyName,vector<_bstr_t> vIds)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("数据库中不存在"+strTableName+"业务表！"),_T("提示"),0);
		return FALSE;
	}
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	adoDataTypeEnum adoFldType;
	adoFldType = pRecordSet->GetFields()->GetItem(strKeyName)->GetType();
	_bstr_t strSql, strIds;
	bool isFirst=true;

	for (vector<_bstr_t>::iterator i=vIds.begin();i!=vIds.end();i++)
	{
		if (isFirst)
		{
			isFirst=false;
			if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
					case OracleType:
						strIds = "to_date('" + (*i) + "','yyyy-mm-dd')";
						break;
					case AccessType:
						strIds = "#"+(*i)+"#";
						break;
					default:
						strIds = "'"+(*i)+"'";
				}
			}
			else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
				strIds+=(*i);
			else
				strIds = "'"+(*i)+"'";
		}
		else
		{
			if(adoFldType == ADODB::adDate || adoFldType == ADODB::adDBTimeStamp)
			{
				switch(CDatabaseFactory::m_enumDatabaseType)
				{
					case OracleType:
						strIds = ",to_date('" + (*i) + "','yyyy-mm-dd')";
						break;
				case AccessType:
					strIds = ",#"+(*i)+"#";
					break;
				default:
					strIds = ",'"+(*i)+"'";
				}
			}
			else if( (adoFldType == ADODB::adInteger ) || (adoFldType == ADODB::adNumeric) || (adoFldType == ADODB::adDouble ) )
				strIds+=","+(*i);
			else
				strIds = ",'"+(*i)+"'";
		}
	}
	strSql=" delete from "+strTableName+" where "+strKeyName+" in("+strIds+")";
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}


/************************************************************************/
/* 查询所有重点目标建筑记录                                              */
/************************************************************************/
BOOL  CTableRcst::DelateTGBuild(_bstr_t bstrids)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标建筑"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标建筑业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql=" delete from 重点目标建筑 where 编号 in("+bstrids+")";
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
_RecordsetPtr CTableRcst::QueryAllTgBuilding()
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标建筑"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标建筑业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql=" select * from 重点目标建筑 ";
	return theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
}
void CTableRcst::QueryAllTgBuilding( vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标建筑"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标建筑业务表！"),_T("提示"),0);
		return;
	}
	CBllHelp::Instance().QueryByCondit(QueryAllTgBuilding(),vecField,vecRecordSet,lFieldCounts);
}
_RecordsetPtr CTableRcst::QueryTgBuilding(_bstr_t strTargetName)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标建筑"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标建筑业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql=" select * from 重点目标建筑 where 所属目标='"+ strTargetName +"'";
	return theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
}
void CTableRcst::QueryTgBuilding( _bstr_t strTargetName ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标建筑"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标建筑业务表！"),_T("提示"),0);
		return;
	}
	CBllHelp::Instance().QueryByCondit(QueryTgBuilding(strTargetName),vecField,vecRecordSet,lFieldCounts);
}
vector<string> CTableRcst::QueryTgBuildingNames(_bstr_t strTargetName)
{
	vector<string> v;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return v;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标建筑"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标建筑业务表！"),_T("提示"),0);
		return v;
	}
	_RecordsetPtr Rcst=QueryTgBuilding(strTargetName);
	string temp;
	if (Rcst!=NULL &&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			temp=(char*)((_bstr_t)Rcst->GetCollect("名称"));
			v.push_back(temp);
			Rcst->MoveNext();
		}
	}
	return v;
}

/************************************************************************/
/* 查询所有重点目标属性                                                 */
/************************************************************************/
_RecordsetPtr CTableRcst::QueryTargetProperty()
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标属性"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标属性业务表！"),_T("提示"),0);
		return FALSE;
	}
	_bstr_t strSql=" select * from 重点目标属性 ";
	return theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
}
void CTableRcst::QueryTargetProperty( vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//数据库操作前判断
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("重点目标属性"))
	{
		MessageBox(NULL,_T("数据库中不存在重点目标属性业务表！"),_T("提示"),0);
		return;
	}
	CBllHelp::Instance().QueryByCondit(QueryTargetProperty(),vecField,vecRecordSet,lFieldCounts);
}
/************************************************************************/
/* 建筑构件                                                             */
/************************************************************************/
//通过重点目标和重点目标建筑去找建筑构件
//string CTableRcst::GetGUIDbyName(_bstr_t strTargetName,_bstr_t strTgBuildName,_bstr_t strCompanentName)
//{
//	if (!theBllApp.m_bConntSuccess)
//	{
//		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
//		return FALSE;
//	}
//	if (!theBllApp.m_pDB->CheckTableNameExist("建筑构件"))
//	{
//		MessageBox(NULL,_T("数据库中不存在建筑构件业务表！"),_T("提示"),0);
//		return FALSE;
//	}
//	_bstr_t strSql=" select * from 建筑构件 where 所属目标='"+strTargetName+"' and  所属目标建筑='"+strTgBuildName+"' and 名称='"+strCompanentName+"'";
//	_RecordsetPtr pRcst=theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
//	if (pRcst!=NULL&&!pRcst->adoEOF)
//	{
//		return ((char *)((_bstr_t)pRcst->GetCollect("GUID")));
//	}
//	else
//		return "";
//}
//
//
//BOOL CTableRcst::GetTgNamesByGuid(_bstr_t strGuid,_bstr_t &strTarget,_bstr_t &strTgBuild,_bstr_t&strName)
//{
//	//数据库操作前判断
//	if (!theBllApp.m_bConntSuccess)
//	{
//		MessageBox(NULL,_T("数据库连接失败！"),_T("提示"),0);
//		return FALSE;
//	}
//	if (!theBllApp.m_pDB->CheckTableNameExist("建筑构件"))
//	{
//		MessageBox(NULL,_T("数据库中不存在建筑构件业务表！"),_T("提示"),0);
//		return FALSE;
//	}
//	_bstr_t strSql;
//	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
//		strSql="select * from 建筑构件 where GUID='"+strGuid+"'";
//	else
//		strSql="select * from 建筑构件 where [GUID]='"+strGuid+"'";
//	_RecordsetPtr  Rcst=theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
//	if (Rcst!=NULL&&!Rcst->adoEOF)
//	{
//		strTarget=(_bstr_t)Rcst->GetCollect("所属目标");
//		strTgBuild=(_bstr_t)Rcst->GetCollect("所属目标建筑");
//		strName=(_bstr_t)Rcst->GetCollect("名称");
//		return TRUE;
//	}
//	else
//		return FALSE;
//}