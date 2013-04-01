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
//�ж�ĳ��ģ���Ƿ��ǽ�������
BOOL CConcretion::IsBuildPart(_bstr_t strGuid)
{
	_bstr_t bstrSql="select * from �������� where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from �������� where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr!=NULL &&!RcstPtr->adoEOF)
		return TRUE;
	else
		return FALSE;
}
//�ж�ĳ��ģ���Ƿ����ص�Ŀ����
BOOL  CConcretion::IsHasTarget(_bstr_t strGuid)
{
	_variant_t var;
	//�õ����ͱ��
	_bstr_t bstrTypeID,bstrTypeName="",bstrTargetName;
	_RecordsetPtr RcstPtr;
	_bstr_t bstrSql="select * from ������Ϣ where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from ������Ϣ where  GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("���");
	if (var.vt==1)
		return FALSE;
	bstrTypeID=(_bstr_t)var;
	//�õ���������
	bstrSql="select * from �����Ϣ where ���="+bstrTypeID;
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("�������");
	if (var.vt==1)
		return FALSE;
	bstrTypeName=(_bstr_t)var;
	//���ݱ�ȥ����GUIDȥ�����ص�Ŀ��
	bstrSql="select * from "+bstrTypeName +"  where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from "+bstrTypeName +"  where GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("����Ŀ��");
	if (var.vt==1)
		return FALSE;
	return TRUE;
}
//����ģ���ص�Ŀ����Ϣ,keyΪ�ֶ���,valueΪ�ֶ�ֵ
map<string,string> CConcretion::GetTargetInfo(_bstr_t strGuid)
{
	map<string,string> m;
	_variant_t var;
	//�õ����ͱ��
	_bstr_t bstrTypeID,bstrTypeName="",bstrTargetName;
	_RecordsetPtr RcstPtr;
	_bstr_t bstrSql="select * from ������Ϣ where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from ������Ϣ where  GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return m;
	var=RcstPtr->GetCollect("���");
	if (var.vt==1)
		return m;
	bstrTypeID=(_bstr_t)var;
	//�õ���������
	bstrSql="select * from �����Ϣ where ���="+bstrTypeID;
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return m;
	var=RcstPtr->GetCollect("�������");
	if (var.vt==1)
		return m;
	bstrTypeName=(_bstr_t)var;
	//���ݱ�ȥ����GUIDȥ�����ص�Ŀ��
	bstrSql="select * from "+bstrTypeName +"  where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from "+bstrTypeName +"  where GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return m;
	var=RcstPtr->GetCollect("����Ŀ��");
	if (var.vt==1)
		return m;
	bstrTargetName=(_bstr_t)var;
	//���ص�Ŀ����Ϣ
	bstrSql="select * from �ص�Ŀ��  where ����='"+bstrTargetName+"'";
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
	//�õ����ͱ��
	_bstr_t bstrTypeID,bstrTypeName="",bstrTargetName;
	_RecordsetPtr RcstPtr;
	_bstr_t bstrSql="select * from ������Ϣ where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from ������Ϣ where  GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("���");
	if (var.vt==1)
		return FALSE;
	bstrTypeID=(_bstr_t)var;
	//�õ���������
	bstrSql="select * from �����Ϣ where ���="+bstrTypeID;
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("�������");
	if (var.vt==1)
		return FALSE;
	bstrTypeName=(_bstr_t)var;
	//���ݱ�ȥ����GUIDȥ�����ص�Ŀ��
	bstrSql="select * from "+bstrTypeName +"  where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from "+bstrTypeName +"  where GUID='"+strGuid+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	var=RcstPtr->GetCollect("����Ŀ��");
	if (var.vt==1)
		return FALSE;
	bstrTargetName=(_bstr_t)var;
	//���ص�Ŀ����Ϣ
	bstrSql="select * from �ص�Ŀ��  where ����='"+bstrTargetName+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	CBllHelp::Instance().QueryByCondit(RcstPtr,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}

BOOL CConcretion::GetTarGetInfoByName(_bstr_t strTargetName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//���ص�Ŀ����Ϣ
	_bstr_t bstrSql="select * from �ص�Ŀ��  where ����='"+strTargetName+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr == NULL || RcstPtr->adoEOF)
		return FALSE;
	CBllHelp::Instance().QueryByCondit(RcstPtr,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}

//����ģ�͹�������������Ϣ
map<string,string> CConcretion::GetBuildInfo(_bstr_t strGuid)
{
	map<string,string> m;
	_bstr_t bstrSql="select * from �������� where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from �������� where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL  || RcstPtr->adoEOF)
		return m;
	_bstr_t bstrTarget,bstrName;
	_variant_t var;
	var=RcstPtr->GetCollect("����Ŀ��");
	if (var.vt==1)
		return m;
	bstrTarget=(_bstr_t)var;
	var=RcstPtr->GetCollect("����Ŀ�꽨��");
	if (var.vt==1)
		return m;
	bstrName=(_bstr_t)var;
	bstrSql="select * from �ص�Ŀ�꽨�� where ����='"+bstrName+"'  and ����Ŀ��='"+bstrTarget+"'";
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
	_bstr_t bstrSql="select * from �������� where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from �������� where GUID='"+strGuid+"'";
	_RecordsetPtr RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (RcstPtr==NULL  || RcstPtr->adoEOF)
		return FALSE;

	_bstr_t bstrTarget,bstrName;
	_variant_t var;
	var=RcstPtr->GetCollect("����Ŀ��");
	if (var.vt==1)
		return FALSE;
	bstrTarget=(_bstr_t)var;
	var=RcstPtr->GetCollect("����Ŀ�꽨��");
	if (var.vt==1)
		return FALSE;
	bstrName=(_bstr_t)var;
	bstrSql="select * from �ص�Ŀ�꽨�� where ����='"+bstrName+"'  and ����Ŀ��='"+bstrTarget+"'";
	RcstPtr=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	CBllHelp::Instance().QueryByCondit(RcstPtr,vecField,vecRecordSet,lFieldCounts);
	return TRUE;
}



BOOL CConcretion::Save(_bstr_t strGuid, _bstr_t strTypeName, map<_bstr_t,_bstr_t> &mapFlds)
{
	_bstr_t strSql = "",strOldID, strOldTypeName;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM ������Ϣ WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM ������Ϣ WHERE  [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	//�ж������Ϣ���Ƿ���ڼ�¼
	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
	{	//������Ϣ����޼�¼
		return Add(strGuid,strTypeName, mapFlds);
	}
	else
	{
		//������Ϣ����ڼ�¼
		strOldID = pRecordSet->GetCollect("���");
		return Update(strGuid,strOldID,strTypeName,mapFlds);
	}
}
BOOL CConcretion::Save(_bstr_t strGuid, _bstr_t strTypeName, vector<_bstr_t>&vfileds,vector<_bstr_t> &vValues)
{
	_bstr_t strSql = "", strOldID, strOldTypeName;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM ������Ϣ WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM ������Ϣ WHERE [GUID] = '" + strGuid + "'";
	
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	//�ж������Ϣ���Ƿ���ڼ�¼
	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
	{	//������Ϣ����޼�¼
		return Add(strGuid,strTypeName,vfileds,vValues);
	}
	else
	{
		//������Ϣ����ڼ�¼
		strOldID = pRecordSet->GetCollect("���");
		return Update(strGuid,strOldID,strTypeName,vfileds,vValues);
	}
}

BOOL CConcretion::Delete(_bstr_t strGuid)
{
	vector<_bstr_t> vecStrSql;
	_bstr_t strDelSql1="", strDelSql2="", strSql = "", strID, strOldTypeName;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM ������Ϣ WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM ������Ϣ WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	//�ж������Ϣ���Ƿ���ڼ�¼
	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
	{	//������Ϣ����޼�¼
		return TRUE;
	}
	else
	{
		//������Ϣ����ڼ�¼
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strDelSql1 = "DELETE FROM ������Ϣ WHERE GUID='" + strGuid + "'";
		else
			strDelSql1 = "DELETE FROM ������Ϣ WHERE [GUID]='" + strGuid + "'";
		strID = pRecordSet->GetCollect("���");
		strSql = "SELECT * FROM �����Ϣ WHERE ���= " + strID;
		pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
		if(pRecordSet == NULL)
			return FALSE;
		if(!pRecordSet->adoEOF)
		{
			strOldTypeName = pRecordSet->GetCollect("�������");
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSql = "SELECT * FROM " + strOldTypeName + " WHERE GUID='" + strGuid +"'";
			else
				strSql = "SELECT * FROM " + strOldTypeName + " WHERE [GUID]='" + strGuid +"'";
			pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
			//����������ڼ�¼
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
		strDelSql2 = "DELETE FROM ģ�ͻ�����Ϣ WHERE GUID='" + strGuid + "'";
	else
		strDelSql2 = "DELETE FROM ģ�ͻ�����Ϣ WHERE [GUID]='" + strGuid + "'";
	vecStrSql.push_back(strDelSql2);

	return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
}

int CConcretion::Load(_bstr_t strGUID,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts,string &strType,vector<string> &vecRecordSetH)
{
	_bstr_t strSQL;
	_RecordsetPtr pRecordSet;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL = "SELECT GUID,��� FROM	������Ϣ WHERE GUID = '" + strGUID + "'";
	else
		strSQL = "SELECT [GUID],[���] FROM	������Ϣ WHERE [GUID] = '" + strGUID + "'";
	
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//���ݿ��ץ���쳣����
		return -4;//�����쳣
	if(pRecordSet->adoEOF)
		return -3;//������Ϣ����û�м�¼
	_bstr_t str;
	str = (_bstr_t)pRecordSet->GetCollect("���");

	//�õ����е��������
	strSQL = "SELECT ���,������� FROM �����Ϣ";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//���ݿ��ץ���쳣����
		return -4;//�����쳣
	if(pRecordSet->adoEOF)
		return -2;//�����Ϣ����û�м�¼
	CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSetH,lFieldCounts);

	strSQL = "SELECT ���,������� FROM �����Ϣ WHERE ��� = " + str;
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//���ݿ��ץ���쳣����
		return -4;//�����쳣
	if(pRecordSet->adoEOF)
		return -1;//�����Ϣ���з��������ļ�¼
	str = (_bstr_t)pRecordSet->GetCollect("�������");
	strType =((char *) (_bstr_t)pRecordSet->GetCollect("�������"));

	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		strSQL = "SELECT * FROM " + str + " WHERE GUID = '" + strGUID + "'";
	}
	else
		strSQL = "SELECT * FROM " + str + " WHERE [GUID] = '" + strGUID + "'";
	
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if(pRecordSet == NULL)//���ݿ��ץ���쳣����
		return -4;//�����쳣
	if(pRecordSet->adoEOF)
	{
		CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSet,lFieldCounts);
		return 0;//�������û�м�¼
	}

	CBllHelp::Instance().QueryByCondit(pRecordSet,vecField,vecRecordSet,lFieldCounts);
	return 1;//��������м�¼
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
	//��������ƻ�ȡ�����
	strSql = "SELECT * FROM �����Ϣ WHERE ������� = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL||pRecordSet->adoEOF)
		return FALSE;
	strID = pRecordSet->GetCollect("���");
	//���������Ϣ�����
	if(CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql1 = "INSERT INTO ������Ϣ(GUID,���) VALUES ('"+ strGuid + "'," + strID + ")";
	else
		strSql1 = "INSERT INTO [������Ϣ]([GUID],[���]) VALUES ('"+ strGuid + "'," + strID + ")";
	//��������治���¼
	if(CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT * FROM " + strTypeName + " WHERE GUID = '" + strGuid + "'";
	else
		strSql = "SELECT * FROM " + strTypeName + " WHERE [GUID] = '" + strGuid + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);

	string strTemp="";
	//����
	if(pRecordSet == NULL)
		return FALSE;
	else
	{
		if(pRecordSet->adoEOF)
		{//�����������ڼ�¼
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
				//�ֶ�
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					strColumns += (*itr1).first + ",";
				else
					strColumns +="[" +(*itr1).first + "],";
				//ֵ
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
				//ѭ��
				itr1++;
			}
			//���һ���ֶ�
			//�ֶ�
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strColumns += (*itr1).first;
			else
				strColumns +="[" +(*itr1).first + "]";
			//ֵ
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
		{//����������ڼ�¼
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
				//ѭ��
				itr1++;
			}
			//���һ���ֶ�
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

	strSql = "SELECT * FROM �����Ϣ WHERE ������� = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL||pRecordSet->adoEOF)
		return FALSE;
	strNewID = pRecordSet->GetCollect("���");
	if(strNewID != strOldID)
	{//����޸�
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql1 = "UPDATE ������Ϣ SET ��� = " + strNewID + " WHERE  GUID= '"+ strGuid + "'";
		else
			strSql1 = "UPDATE ������Ϣ SET ��� = " + strNewID + " WHERE  [GUID]= '"+ strGuid + "'";

		strSql = "SELECT * FROM �����Ϣ WHERE ���= " + strOldID;
		pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
		if(pRecordSet == NULL||pRecordSet->adoEOF)
			return FALSE;
		strOldTypeName = (_bstr_t)pRecordSet->GetCollect("�������");
		//�Ӿɾ�������ɾ����¼
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE GUID  = '" + strGuid + "'";
		else
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE [GUID]  = '" + strGuid + "'";
	}

	//��������治���¼
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
		{//�����������ڼ�¼
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
				//�ֶ�
				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
					strColumns += (*itr1).first + ",";
				else
					strColumns +="[" +(*itr1).first + "],";
				//ֵ
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
				//ѭ��
				itr1++;
			}
			//���һ���ֶ�
			//�ֶ�
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strColumns += (*itr1).first;
			else
				strColumns +="[" +(*itr1).first + "]";
			//ֵ
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
		{//����������ڼ�¼
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
				//ѭ��
				itr1++;
			}
			//���һ���ֶ�
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

	//��������ƻ�ȡ�����
	strSql = "SELECT * FROM �����Ϣ WHERE ������� = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL||pRecordSet->adoEOF)
		return FALSE;
	strID = pRecordSet->GetCollect("���");
	//���������Ϣ�����
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql1 = "INSERT INTO ������Ϣ(GUID,���) VALUES ('"+ strGuid + "'," + strID + ")";
	else
		strSql1 = "INSERT INTO ������Ϣ([GUID],[���]) VALUES ('"+ strGuid + "'," + strID + ")";
	//��������治���¼
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
		{//�����������ڼ�¼
			_bstr_t strColumns,strValues;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				if (isFirst)
				{
					isFirst=false;
					//�ֶ�
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns+=(*itr);
					else
						strColumns+="["+(*itr)+"]";
					//ֵ
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
		{//����������ڼ�¼
			_bstr_t strUpdateFormat;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				//�ֶ�
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
				//ֵ
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
				//ѭ��
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

	strSql = "SELECT * FROM �����Ϣ WHERE ������� = '" + strTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
	if(pRecordSet == NULL || pRecordSet->adoEOF)
		return FALSE;
	strNewID = pRecordSet->GetCollect("���");
	if(strNewID != strOldID)
	{//����޸�
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql1 = "UPDATE ������Ϣ SET ��� = " + strNewID + " WHERE  GUID= '"+ strGuid + "'";
		else
			strSql1 = "UPDATE ������Ϣ SET [���] = " + strNewID + " WHERE  [GUID]= '"+ strGuid + "'";
		strSql = "SELECT * FROM �����Ϣ WHERE ���= " + strOldID;
		pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
		if(pRecordSet == NULL || pRecordSet->adoEOF)
			return FALSE;
		strOldTypeName = (_bstr_t)pRecordSet->GetCollect("�������");
		//�Ӿɾ�������ɾ����¼
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE GUID  = '" + strGuid + "'";
		else
			strSql2 = "DELETE FROM " + strOldTypeName + " WHERE [GUID]  = '" + strGuid + "'";
	}

	//��������治���¼
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
		{//�����������ڼ�¼
			_bstr_t strColumns,strValues;
			bool isFirst=true;
			vector<_bstr_t>::iterator itr = vfileds.begin();
			vector<_bstr_t>::iterator itr2=vValues.begin();
			while(itr!=vfileds.end()&&itr2!=vValues.end())
			{
				if (isFirst)
				{
					isFirst=false;
					//�ֶ�
					if (CDatabaseFactory::m_enumDatabaseType==OracleType)
						strColumns+=(*itr);
					else
						strColumns+="["+(*itr)+"]";
					//ֵ
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
		{//����������ڼ�¼
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
//����
//�õ�ģ�ͱ������GUID
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

//�ж��Ƿ�������ͷ
BOOL CConcretion::IsCamara(_bstr_t strGuid)
{
	BOOL bIs=FALSE;
	_bstr_t bstrSql="select * from ����ͷ where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from ����ͷ where GUID='"+strGuid+"'";
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
	
//�ж��Ƿ��Ǹ�����ʩ
BOOL CConcretion::IsFacilitie(_bstr_t strGuid)
{
	BOOL bIs=FALSE;
	_bstr_t bstrSql="select * from ������ʩ where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from ������ʩ where GUID='"+strGuid+"'";
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
	
//�ж��Ƿ��Ǿ���
BOOL CConcretion::IsPolice(_bstr_t strGuid)
{
	BOOL bIs=FALSE;
	_bstr_t bstrSql="select * from ���� where [GUID]='"+strGuid+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="select * from ���� where GUID='"+strGuid+"'";
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