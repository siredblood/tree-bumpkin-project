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
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}

	if (mPropertys.empty() || mPropertys.size()<1)
		return FALSE;
	mPropertys.erase(strExceptField);
	if (mPropertys.empty()||mPropertys.size()<1)
		return FALSE;

	//��������
	map<_bstr_t,_bstr_t>::iterator itr1, itr2;
	_bstr_t strColumns,strValues,strSql;
	adoDataTypeEnum adoFldType;
	_RecordsetPtr pRecordSet=theBllApp.m_pDB->ExcuteSqlRes("select * from "+strTableName,adCmdText);
	_variant_t var;
	itr1 = mPropertys.begin();
	itr2 = --mPropertys.end();
	//����sql���
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
	//�������һ���ֶ�
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
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	if (vModels.empty() || vModels.size()<1)
		return FALSE;
	//��������
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
				//����sql���
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
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ���"),_T("��ʾ"),0);
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

	//��������
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
	//�������һ���ֶ�
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

	//����where����
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
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ���"),_T("��ʾ"),0);
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
						//�������һ���ֶ�
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

						//����where����
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
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ���"),_T("��ʾ"),0);
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
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ���"),_T("��ʾ"),0);
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
/* ��ѯ�����ص�Ŀ�꽨����¼                                              */
/************************************************************************/
BOOL  CTableRcst::DelateTGBuild(_bstr_t bstrids)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ�꽨��"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ�꽨��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql=" delete from �ص�Ŀ�꽨�� where ��� in("+bstrids+")";
	return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
}
_RecordsetPtr CTableRcst::QueryAllTgBuilding()
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ�꽨��"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ�꽨��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql=" select * from �ص�Ŀ�꽨�� ";
	return theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
}
void CTableRcst::QueryAllTgBuilding( vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ�꽨��"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ�꽨��ҵ���"),_T("��ʾ"),0);
		return;
	}
	CBllHelp::Instance().QueryByCondit(QueryAllTgBuilding(),vecField,vecRecordSet,lFieldCounts);
}
_RecordsetPtr CTableRcst::QueryTgBuilding(_bstr_t strTargetName)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ�꽨��"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ�꽨��ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql=" select * from �ص�Ŀ�꽨�� where ����Ŀ��='"+ strTargetName +"'";
	return theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
}
void CTableRcst::QueryTgBuilding( _bstr_t strTargetName ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ�꽨��"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ�꽨��ҵ���"),_T("��ʾ"),0);
		return;
	}
	CBllHelp::Instance().QueryByCondit(QueryTgBuilding(strTargetName),vecField,vecRecordSet,lFieldCounts);
}
vector<string> CTableRcst::QueryTgBuildingNames(_bstr_t strTargetName)
{
	vector<string> v;
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return v;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ�꽨��"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ�꽨��ҵ���"),_T("��ʾ"),0);
		return v;
	}
	_RecordsetPtr Rcst=QueryTgBuilding(strTargetName);
	string temp;
	if (Rcst!=NULL &&!Rcst->adoEOF)
	{
		while(!Rcst->adoEOF)
		{
			temp=(char*)((_bstr_t)Rcst->GetCollect("����"));
			v.push_back(temp);
			Rcst->MoveNext();
		}
	}
	return v;
}

/************************************************************************/
/* ��ѯ�����ص�Ŀ������                                                 */
/************************************************************************/
_RecordsetPtr CTableRcst::QueryTargetProperty()
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ������"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql=" select * from �ص�Ŀ������ ";
	return theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
}
void CTableRcst::QueryTargetProperty( vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�ص�Ŀ������"))
	{
		MessageBox(NULL,_T("���ݿ��в������ص�Ŀ������ҵ���"),_T("��ʾ"),0);
		return;
	}
	CBllHelp::Instance().QueryByCondit(QueryTargetProperty(),vecField,vecRecordSet,lFieldCounts);
}
/************************************************************************/
/* ��������                                                             */
/************************************************************************/
//ͨ���ص�Ŀ����ص�Ŀ�꽨��ȥ�ҽ�������
//string CTableRcst::GetGUIDbyName(_bstr_t strTargetName,_bstr_t strTgBuildName,_bstr_t strCompanentName)
//{
//	if (!theBllApp.m_bConntSuccess)
//	{
//		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
//		return FALSE;
//	}
//	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
//	{
//		MessageBox(NULL,_T("���ݿ��в����ڽ�������ҵ���"),_T("��ʾ"),0);
//		return FALSE;
//	}
//	_bstr_t strSql=" select * from �������� where ����Ŀ��='"+strTargetName+"' and  ����Ŀ�꽨��='"+strTgBuildName+"' and ����='"+strCompanentName+"'";
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
//	//���ݿ����ǰ�ж�
//	if (!theBllApp.m_bConntSuccess)
//	{
//		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
//		return FALSE;
//	}
//	if (!theBllApp.m_pDB->CheckTableNameExist("��������"))
//	{
//		MessageBox(NULL,_T("���ݿ��в����ڽ�������ҵ���"),_T("��ʾ"),0);
//		return FALSE;
//	}
//	_bstr_t strSql;
//	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
//		strSql="select * from �������� where GUID='"+strGuid+"'";
//	else
//		strSql="select * from �������� where [GUID]='"+strGuid+"'";
//	_RecordsetPtr  Rcst=theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);
//	if (Rcst!=NULL&&!Rcst->adoEOF)
//	{
//		strTarget=(_bstr_t)Rcst->GetCollect("����Ŀ��");
//		strTgBuild=(_bstr_t)Rcst->GetCollect("����Ŀ�꽨��");
//		strName=(_bstr_t)Rcst->GetCollect("����");
//		return TRUE;
//	}
//	else
//		return FALSE;
//}