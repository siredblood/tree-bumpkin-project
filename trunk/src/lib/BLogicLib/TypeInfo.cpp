#include "TypeInfo.h"
CTypeInfo CTypeInfo::instance;
CTypeInfo::CTypeInfo(void)
{
}

CTypeInfo::~CTypeInfo(void)
{
}
CTypeInfo & CTypeInfo::Instance()
{
	return instance;
}


BOOL CTypeInfo::Add(_bstr_t STRtypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����Ϣ"))
	{
		MessageBox(NULL,_T("���ݿ��в����������Ϣҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql="", strSql1 = "", strSql2 = "";
	vector<_bstr_t> vecStrSql;

	_RecordsetPtr pRecordSet;
	strSql = "SELECT * FROM �����Ϣ WHERE ������� = '" + STRtypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);

	//�ж������Ϣ���Ƿ���ڱ���
	if(pRecordSet == NULL)
		return FALSE;
	if(!pRecordSet->adoEOF)
	{	//�ͷ���Դ
		pRecordSet.Release();
		return FALSE;
	}
	//�ͷ���Դ
	pRecordSet.Release();

	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		{
			//��Ӽ�¼
			strSql = "INSERT INTO �����Ϣ(�������) VALUES ('" 
				+ STRtypeName + "')";
			theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
			//������
			strSql = "CREATE TABLE [" + STRtypeName + "]  ([GUID] MEMO, [����] MEMO, [����Ŀ��] MEMO, [����]  MEMO, [��ע]  MEMO)";
			return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
		}
	case SqlServerType:
		//��Ӽ�¼�ͱ�
		strSql = "INSERT INTO �����Ϣ(�������) VALUES ('"
			+ STRtypeName + "'); CREATE TABLE [" + STRtypeName 
			+ "] (GUID VARCHAR(64), ���� VARCHAR(64), ����Ŀ�� VARCHAR(128), \
			  ���� VARCHAR(64), ��ע VARCHAR(1024))";
		return theBllApp.m_pDB->ExcuteSql(strSql,adCmdText);
	case OracleType:
		strSql1 = "INSERT INTO �����Ϣ(���, �������) VALUES (�����Ϣ����.nextVal, '" 
			+ STRtypeName + "')";
		strSql2 = " CREATE TABLE " + STRtypeName 
			+ "(GUID VARCHAR2(64), ���� VARCHAR2(64), ����Ŀ�� VARCHAR2(128), \
			  ���� VARCHAR2(64), ��ע VARCHAR2(1024))";
		vecStrSql.push_back(strSql1);
		vecStrSql.push_back(strSql2);
		return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
	}
	return FALSE;
}

BOOL CTypeInfo::Update(_bstr_t strOldTypeName, _bstr_t strNewTypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����Ϣ"))
	{
		MessageBox(NULL,_T("���ݿ��в����������Ϣҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql="", strSql1 = "", strSql2 = "";
	vector<_bstr_t> vecStrSql;
	_RecordsetPtr pRecordSet;
	strSql = "SELECT * FROM �����Ϣ WHERE ������� = '" + strOldTypeName + "'";
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSql,adCmdText);

	if(pRecordSet == NULL)
		return FALSE;
	if(pRecordSet->adoEOF)
		return FALSE;
	else
		pRecordSet.Release();

	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case AccessType:
		//û�ҵ�Access���±������
		break;
	case SqlServerType:
		//���¼�¼
		strSql1 = "UPDATE �����Ϣ SET ������� = '" + strNewTypeName + "' WHERE ������� = '"
			+ strOldTypeName + "'";
		theBllApp.m_pDB->ExcuteSql(strSql1,adCmdText);
		//���±���
		strSql2 = "SP_RENAME '"+ strOldTypeName + "','" + strNewTypeName + "'";
		vecStrSql.push_back(strSql1);
		vecStrSql.push_back(strSql2);
		return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);

	case OracleType:
		//���¼�¼
		strSql1 = "UPDATE �����Ϣ SET ������� = '" + strNewTypeName + "' WHERE ������� = '"
			+ strOldTypeName + "'";
		//���±���
		strSql2 = "RENAME " + strOldTypeName + " TO " + strNewTypeName;
		vecStrSql.push_back(strSql1);
		vecStrSql.push_back(strSql2);
		return theBllApp.m_pDB->ExcuteTrans(vecStrSql, adCmdText);
	}
	return FALSE;
}

BOOL CTypeInfo::Delete(_bstr_t STRtypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����Ϣ"))
	{
		MessageBox(NULL,_T("���ݿ��в����������Ϣҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql="";
	vector<_bstr_t> vecStrSql;
	strSql = "DELETE FROM �����Ϣ WHERE ������� = '" + STRtypeName + "'";
	vecStrSql.push_back(strSql);
	strSql = "DROP TABLE [" + STRtypeName+"]";
	vecStrSql.push_back(strSql);
	return theBllApp.m_pDB->ExcuteTrans(vecStrSql,adCmdText);
}

_RecordsetPtr CTypeInfo::QueryAllType()
{
	return QueryTypeInfoByCondit("�����Ϣ");
}

void CTypeInfo::QueryAllType(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryAllType();
	if (Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CTypeInfo::QueryTypeInfoByCondit(_bstr_t STRTypeName)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("�����Ϣ"))
	{
		MessageBox(NULL,_T("���ݿ��в����������Ϣҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql = "";
	strSql = "SELECT * FROM  [" + STRTypeName+"]" ;
	return theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
}

void CTypeInfo::QueryTypeInfoByCondit(_bstr_t STRTypeName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr Rcst=QueryTypeInfoByCondit(STRTypeName);
	if(Rcst==NULL)
		return;
	CBllHelp * help = new CBllHelp();
	help->QueryByCondit(Rcst,vecField,vecRecordSet,lFieldCounts);
}

vector<string> CTypeInfo::GetTypeNames()
{
	vector<string> VtypeNames;
	_RecordsetPtr Rst=QueryAllType();
	if (Rst!=NULL)
	{
		while(!Rst->adoEOF)
		{
			VtypeNames.push_back((char*)((_bstr_t)Rst->GetCollect("�������")));
			Rst->MoveNext();
		}
		Rst->Close();
		Rst.Release();
	}
	return VtypeNames;
}

//ͼ��ؼ���ʾ
_RecordsetPtr CTypeInfo::QueryGUIDByLayerRcst(_bstr_t strTableName,_bstr_t strWhere)
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist(strTableName))
	{
		MessageBox(NULL,_T("���ݿ��в�����"+strTableName+"ҵ��"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSql = "";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql = "SELECT  GUID  FROM [" + strTableName + "]  WHERE 1=1 "+strWhere;
	else
		strSql = "SELECT [GUID] FROM [" + strTableName + "]  WHERE 1=1 "+strWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSql, adCmdText);
}
vector<string> CTypeInfo::QueryGUIDBylayerVector(_bstr_t strTableName,_bstr_t strWhere)
{
	vector<string> strGUIDs;
	_RecordsetPtr rst=QueryGUIDByLayerRcst(strTableName,strWhere);
	if (rst!=NULL)
	{
		string strvalue;
		while(!rst->adoEOF)
		{
			strvalue=(char*)((_bstr_t)rst->GetCollect("GUID"));
			strGUIDs.push_back(strvalue);
			rst->MoveNext();
		}
	}
	return strGUIDs;
}

//void CTypeInfo::GetTypeInfoDetail(_RecordsetPtr pRecordSet, Vector &vecField, Vector &vecRecordSet, long &lFieldCounts)
//{
//	//�жϴ��ڼ�¼
//	if(pRecordSet == NULL)
//		return ;
//
//	try
//	{
//		//�ֶθ���
//		lFieldCounts = pRecordSet->GetFields()->GetCount();
//		DataTypeEnum enumDataType;
//		_bstr_t str;
//		//�ֶ����ơ����͡���С
//		for(long i = 0; i<lFieldCounts; i++)
//		{
//				
//			vecField.push_back((LPSTR)str);
//			enumDataType = pRecordSet->GetFields()->GetItem(i)->GetType();
//			str = GetDataTypeString(enumDataType);
//			vecField.push_back((LPSTR)str);
//			str = pRecordSet->GetFields()->GetItem(i)->GetDefinedSize();
//			vecField.push_back((LPSTR)str);
//		}
//		pRecordSet->MoveFirst();
//		long lCounts = 0;
//		//��ȡ��¼
//		while(!pRecordSet->adoEOF)
//		{
//			for(long j=0; j<lFieldCounts; j++)
//			{
//				str = pRecordSet->GetCollect(j);
//				vecRecordSet.push_back((LPSTR)str);
//			}
//			pRecordSet->MoveNext();
//			lCounts++;
//		}
//	}
//	catch(_com_error e)
//	{
//		AfxMessageBox("��ȡ�����Ϣ����");
//	}
//}
//
//_bstr_t CTypeInfo::GetDataTypeString(DataTypeEnum enumType)
//{
//	_bstr_t strType = "";
//	switch(enumType)
//	{
//	case adInteger:
//	case adNumeric:
//		strType = "����";
//		break;
//	case adDouble:
//		strType = "������";
//		break;
//	case adDate:
//	case adDBTimeStamp:
//		strType = "����";
//		break;
//	case adVarChar:
//	case adLongVarWChar:
//		strType = "�ַ�";
//		break;
//	default:
//		strType = " ";
//		break;
//	}
//	return strType;
//}