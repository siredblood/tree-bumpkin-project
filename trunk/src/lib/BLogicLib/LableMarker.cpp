//#include "stdafx.h"
#include "LableMarker.h"

CLableMarker CLableMarker::instance;
CLableMarker::CLableMarker(void)
{
	m_strID="";         //���
	m_strGUID="";       //GUID
	m_strCoordinate=""; //����
	m_strTarget="";     //����Ŀ��
	m_strName="";       //����
	m_strType="1";       //����
	m_strCreator="";     //������
	m_strCreateTime="2010-1-1";  //����ʱ��
	m_strRemark="";     //����
}

CLableMarker::~CLableMarker(void)
{
}

CLableMarker & CLableMarker::Instance()
{
	return instance;
}
//�жϱ�ע�Ƿ����
BOOL CLableMarker::CheckLableExist(_bstr_t bstrGUID)
{
	if (bstrGUID.length()<=0)
	{
		MessageBox(NULL,_T("�������עģ��GUID��"),_T("��ʾ"),0);
		return FALSE;
	}
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t bstrSql="SELECT * FROM ��ע WHERE [GUID] = '" + bstrGUID+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		bstrSql="SELECT * FROM ��ע WHERE GUID = '" + bstrGUID+"'";
	_RecordsetPtr rst=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
	if (rst!=NULL && !rst->adoEOF)
		return TRUE;
	else 
		return FALSE;
}
//��ʶ����
BOOL CLableMarker::Save(LABLESTRUCT modle)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	//����
	m_strGUID=modle.strGUID.c_str();
	m_strName=modle.strText.c_str();
	m_strType=modle.strType.c_str();
	m_strTarget=modle.strTarget.c_str();
	m_strCoordinate=modle.strPos.c_str();
	m_strCreator=modle.strCreator.c_str();
	m_strCreateTime=modle.strCreatTime.c_str();
	if (m_strGUID.length()<=0)
	{
		MessageBox(NULL,_T("�������עģ�͵�GUID��"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	if (CheckLableExist(m_strGUID))
	{
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		{
			strSQL = "UPDATE ��ע SET  ������='"+m_strCreator+"',����ʱ��=to_date('" + m_strCreateTime + "','dd/mm/yyyy'), ����Ŀ��='"+m_strTarget+"', ���� = '" + m_strCoordinate + "',���� = '"
				+ m_strName + "',���� = '" + m_strType + "',���� = '" 
				+ m_strRemark + "'  WHERE GUID = '" + m_strGUID+"'";
		} 
		else
		{
			strSQL = "UPDATE ��ע SET  ������='"+m_strCreator+"',����ʱ��='"+m_strCreateTime+"',����Ŀ��='"+m_strTarget+"',���� = '" + m_strCoordinate + "',���� = '"
				+ m_strName + "',���� = '" + m_strType + "',���� = '" 
				+ m_strRemark + "'  WHERE  [GUID] = '" + m_strGUID+"'";
		}
	}
	else
	{
		switch(CDatabaseFactory::m_enumDatabaseType)
		{
		case OracleType:
				strSQL="INSERT INTO ��ע  (���,GUID,����,����,����Ŀ��,����,������,����ʱ��,����) values (��ע����.NextVal,'"+m_strGUID+"','" + m_strCoordinate + "','"
				+ m_strName+"','" +m_strTarget+ "','" +  m_strType + "','"+m_strCreator+"',"+"to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark + "')";
			break;
		case AccessType:
			strSQL="INSERT INTO ��ע  ([GUID],����,����,����Ŀ��,����,������,����ʱ��,����) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
				+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"',#"+m_strCreateTime+"#,'"+ m_strRemark + "')";
			break;
		case SqlServerType:
			strSQL="INSERT INTO ��ע  ([GUID],����,����,����Ŀ��,����,������,����ʱ��,����) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
				+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark + "')";
			break;
		default:
			return FALSE;
		}
	}
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

BOOL CLableMarker::Save(vector<LABLESTRUCT> models)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL;
	vector<_bstr_t> vbstrSqls;
	LABLESTRUCT modle;

	strSQL = "DELETE FROM ��ע";//��ɾ���������
	vbstrSqls.push_back(strSQL);
	for (vector<LABLESTRUCT>::iterator item=models.begin();item!=models.end();item++)
	{
		modle=*item;
		m_strGUID=modle.strGUID.c_str();
		m_strName=modle.strText.c_str();
		m_strType=modle.strType.c_str();
		m_strTarget=modle.strTarget.c_str();
		m_strCoordinate=modle.strPos.c_str();
		m_strCreator=modle.strCreator.c_str();
		m_strCreateTime=modle.strCreatTime.c_str();
		CString strEyeable;
		strEyeable.Format("%f",modle.fEyeable);
		m_strEyeable = strEyeable.GetBuffer(0);

		if (m_strGUID.length()>=0)
		{
			switch(CDatabaseFactory::m_enumDatabaseType)
			{
			case OracleType:
				strSQL="INSERT INTO ��ע  (���,GUID,����,����,����Ŀ��,����,������,����ʱ��,����,���ӷ�Χ) values (��ע����.NextVal,'"+m_strGUID+"','" + m_strCoordinate + "','"
					+ m_strName+"','" +m_strTarget+ "','" +  m_strType + "','"+m_strCreator+"',"+"to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark 
					+ "'," + m_strEyeable +")";
				break;
			case AccessType:
				strSQL="INSERT INTO ��ע  ([GUID],����,����,����Ŀ��,����,������,����ʱ��,����,���ӷ�Χ) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
					+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"',#"+m_strCreateTime+"#,'"+ m_strRemark 
					+ "'," + m_strEyeable +")";
				break;
			case SqlServerType:
				strSQL="INSERT INTO ��ע  ([GUID],����,����,����Ŀ��,����,������,����ʱ��,����,���ӷ�Χ) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
					+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark
					+ "'," + m_strEyeable +")";
				break;
			default:
				return FALSE;
			}
			vbstrSqls.push_back(strSQL);
		}
	}
	if (vbstrSqls.size()>0)
		return theBllApp.m_pDB->ExcuteTrans(vbstrSqls,adCmdText);
	else 
		return FALSE;
}


//BOOL CLableMarker::Save(vector<LABLESTRUCT> models)
//{
//	//���ݿ����ǰ�ж�
//	if (!theBllApp.m_bConntSuccess)
//	{
//		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
//		return FALSE;
//	}
//	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
//	{
//		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
//		return FALSE;
//	}
//	_bstr_t strSQL;
//	vector<_bstr_t> vbstrSqls;
//	LABLESTRUCT modle;
//	for (vector<LABLESTRUCT>::iterator item=models.begin();item!=models.end();item++)
//	{
//		modle=*item;
//		m_strGUID=modle.strGUID.c_str();
//		m_strName=modle.strText.c_str();
//		m_strType=modle.strType.c_str();
//		m_strTarget=modle.strTarget.c_str();
//		m_strCoordinate=modle.strPos.c_str();
//		m_strCreator=modle.strCreator.c_str();
//		m_strCreateTime=modle.strCreatTime.c_str();
//		CString strEyeable;
//		strEyeable.Format("%f",modle.fEyeable);
//		m_strEyeable = strEyeable.GetBuffer(0);
//
//		if (m_strGUID.length()>=0)
//		{
//			if (CheckLableExist(m_strGUID))
//			{
//				if (CDatabaseFactory::m_enumDatabaseType==OracleType)
//				{
//					strSQL = "UPDATE ��ע SET  ������='"+m_strCreator+"',����ʱ��=to_date('" + m_strCreateTime + "','dd/mm/yyyy'), ����Ŀ��='"+m_strTarget+"', ���� = '" + m_strCoordinate + "',���� = '"
//						+ m_strName + "',���� = '" + m_strType + "',���� = '" 
//						+ m_strRemark + "',���ӷ�Χ="+ m_strEyeable + " WHERE GUID = '" + m_strGUID+"'";
//				} 
//				else
//				{
//					strSQL = "UPDATE ��ע SET  ������='"+m_strCreator+"',����ʱ��='"+m_strCreateTime+"',����Ŀ��='"+m_strTarget+"',���� = '" + m_strCoordinate + "',���� = '"
//						+ m_strName + "',���� = '" + m_strType + "',���� = '" 
//						+ m_strRemark + "',���ӷ�Χ="+ m_strEyeable + " WHERE  [GUID] = '" + m_strGUID+"'";
//				}
//			}
//			else
//			{
//				switch(CDatabaseFactory::m_enumDatabaseType)
//				{
//				case OracleType:
//					strSQL="INSERT INTO ��ע  (���,GUID,����,����,����Ŀ��,����,������,����ʱ��,����,���ӷ�Χ) values (��ע����.NextVal,'"+m_strGUID+"','" + m_strCoordinate + "','"
//						+ m_strName+"','" +m_strTarget+ "','" +  m_strType + "','"+m_strCreator+"',"+"to_date('" + m_strCreateTime + "','dd/mm/yyyy'),'" + m_strRemark 
//						+ "'," + m_strEyeable +")";
//					break;
//				case AccessType:
//					strSQL="INSERT INTO ��ע  ([GUID],����,����,����Ŀ��,����,������,����ʱ��,����,���ӷ�Χ) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
//						+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"',#"+m_strCreateTime+"#,'"+ m_strRemark 
//						+ "'," + m_strEyeable +")";
//					break;
//				case SqlServerType:
//					strSQL="INSERT INTO ��ע  ([GUID],����,����,����Ŀ��,����,������,����ʱ��,����,���ӷ�Χ) values ('"+m_strGUID+"','" + m_strCoordinate + "','"
//						+ m_strName +"','" +m_strTarget+ "','" +  m_strType + "','" +m_strCreator+"','"+m_strCreateTime+"','"+ m_strRemark
//						+ "'," + m_strEyeable +")";
//					break;
//				default:
//					return FALSE;
//				}
//			}
//			vbstrSqls.push_back(strSQL);
//		}
//	}
//	if (vbstrSqls.size()>0)
//		return theBllApp.m_pDB->ExcuteTrans(vbstrSqls,adCmdText);
//	else 
//		return FALSE;
//}


//���ض���ģ��
BOOL CLableMarker::Load(_bstr_t bstrGUID)
{
	if (bstrGUID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���ر�ע��"),_T("��ʾ"),0);
		return FALSE;
	}
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	BOOL bFlag;
	_RecordsetPtr pRecordSet;
	_bstr_t strSQL="SELECT [���],[GUID],[����],[����],[����Ŀ��],[����],[������],[����ʱ��],[����]  FROM ��ע WHERE [GUID] = '" +bstrGUID+"'" ;
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
	{
		strSQL="SELECT ���,GUID,����,����,����Ŀ��,����,������,����ʱ��,���� FROM ��ע WHERE GUID = '" +bstrGUID+"'" ;
	}
	pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet!=NULL)
	{
		if(!pRecordSet->adoEOF)
		{
			bFlag = TRUE;
			_variant_t var;
			var=pRecordSet->GetCollect("���");
			m_strID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("GUID");
			m_strGUID = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strCoordinate = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strName = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����");
			m_strType = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����Ŀ��");
			m_strTarget = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("������");
			m_strCreator = (_bstr_t)(var.vt==1?"":var);
			var=pRecordSet->GetCollect("����ʱ��");
			m_strCreateTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			var=pRecordSet->GetCollect("����");
			m_strRemark = (_bstr_t)(var.vt==1?"":var);
		}
		pRecordSet->Close();
		pRecordSet.Release();
	}
	return bFlag;
}

//ɾ����ע��¼��ͨ������GUID
BOOL CLableMarker::Delete(_bstr_t strGUID)
{
	if (strGUID.length()<=0)
	{
		MessageBox(NULL,_T("��ѡ��Ҫɾ���ı�ע��"),_T("��ʾ"),0);
		return FALSE;
	}
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL = "DELETE  FROM  ��ע  WHERE [GUID] = '" + strGUID+"'";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSQL  = "DELETE  FROM  ��ע  WHERE GUID = '" + strGUID+"'";
	return theBllApp.m_pDB->ExcuteSql(strSQL,adCmdText);
}

_RecordsetPtr CLableMarker::QueryAllLableMarker()
{
	return QueryLableMarkerByCondit("");
}

void CLableMarker::QueryAllLableMarker(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryAllLableMarker();
	if (prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}

_RecordsetPtr CLableMarker::QueryLableMarkerByCondit(_bstr_t STRWhere)
{
	//���ݿ����ǰ�ж�
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("��ע"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڱ�עҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	_bstr_t strSQL = "SELECT *  FROM ��ע WHERE 1=1  " + STRWhere;
	return theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
}

void CLableMarker::QueryLableMarkerByCondit(_bstr_t bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryLableMarkerByCondit(bstrWhere);
	if(prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
vector<LABLESTRUCT> CLableMarker::LoadLableMark()
{
	std::vector<LABLESTRUCT> te;
	_RecordsetPtr	rst=QueryAllLableMarker();
	if (rst!=NULL)
	{
		_variant_t var;
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			var=rst->GetCollect("GUID");
			data.strGUID = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strPos = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strText = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strType = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����Ŀ��");
			data.strTarget = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("������");
			data.strCreator = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����ʱ��");
			data.strCreatTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			te.push_back(data);
			rst->MoveNext();
		}
	}
	return te;
}
//�����ص�Ŀ��õ���ע
vector<LABLESTRUCT> CLableMarker::LoadLableMark(_bstr_t strTarget)
{
	std::vector<LABLESTRUCT> te;
	_RecordsetPtr	rst=QueryLableMarkerByCondit("  and ����Ŀ��='"+strTarget+"'");
	if (rst!=NULL)
	{
		_variant_t var;
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			var=rst->GetCollect("GUID");
			data.strGUID = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strPos = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strText = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strType = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����Ŀ��");
			data.strTarget = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("������");
			data.strCreator = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����ʱ��");
			data.strCreatTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			var=rst->GetCollect("���ӷ�Χ");
			data.fEyeable = (float)(var.vt==1?300.f:var);
			te.push_back(data);
			rst->MoveNext();
		}
	}
	return te;
}
/************************************************************************/
/* �����˺ʹ���ʱ���ѯ                                                 */
/************************************************************************/
//��ѯ�����˺ʹ���ʱ���¼,��ѯ��ʼʱ��strBeginTime�ͽ���ʱ��strEndTime�ʹ�����ΪstrCreatorName�ı�ע,�������ʱ����ʱ��ֵΪ"",������Դ�������ֵΪ"";
_RecordsetPtr  CLableMarker::QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	_bstr_t strSqlwhere="";
	switch(CDatabaseFactory::m_enumDatabaseType)
	{
	case OracleType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and ������='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and ����ʱ�� = to_date('" + strBeginTime + "','dd/mm/yyyy') and  to_date('" + strEndTime + "','dd/mm/yyyy')";
		else if(strBeginTime.length()>0)
			strSqlwhere+="    and ����ʱ�� = to_date('" + strBeginTime + "','dd/mm/yyyy')";
		else if(strEndTime.length()>0)
			strSqlwhere+="    and ����ʱ�� = to_date('" + strEndTime + "','dd/mm/yyyy')";
		break;
	case SqlServerType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and ������='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and ����ʱ�� between '"+strBeginTime+"' and '"+strEndTime+"'";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and ����ʱ��='"+strBeginTime+"'";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and ����ʱ��='"+strEndTime+"'";
		break;
	case AccessType:
		if (strCreatorName.length()>0)
		{
			strSqlwhere+="and ������='"+strCreatorName+"'";
		}
		if (strBeginTime.length()>0&&strEndTime.length()>0)
			strSqlwhere+="  and ����ʱ�� between #"+strBeginTime+"# and #"+strEndTime+"#";
		else if(strBeginTime.length()>0)
			strSqlwhere+="   and ����ʱ��=#"+strBeginTime+"#";
		else if(strEndTime.length()>0)
			strSqlwhere+="   and ����ʱ��=#"+strEndTime+"#";
		break;
	default:
		return NULL;
	}
	return QueryLableMarkerByCondit(strSqlwhere);
}
//��ѯ�����˺ʹ���ʱ���¼,��ѯ��ʼʱ��strBeginTime�ͽ���ʱ��strEndTime�ʹ�����ΪstrCreatorName�ı�ע,�������ʱ����ʱ��ֵΪ"",������Դ�������ֵΪ"";
void CLableMarker::QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts)
{
	_RecordsetPtr prst=QueryCreateMarker( strBeginTime, strEndTime, strCreatorName );
	if(prst==NULL)
		return;
	CBllHelp::Instance().QueryByCondit(prst,vecField,vecRecordSet,lFieldCounts);
}
//��ѯ�����˺ʹ���ʱ���ע����,��ѯ��ʼʱ��strBeginTime�ͽ���ʱ��strEndTime�ʹ�����ΪstrCreatorName�ı�ע,�������ʱ����ʱ��ֵΪ"",������Դ�������ֵΪ"";
vector<LABLESTRUCT> CLableMarker::LoadCreateMark(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName)
{
	std::vector<LABLESTRUCT> te;
	_RecordsetPtr	rst=QueryCreateMarker( strBeginTime, strEndTime, strCreatorName );
	if (rst!=NULL)
	{
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			data.strText = ((char *)(_bstr_t)rst->GetCollect("����"));
			data.strGUID = ((char *)(_bstr_t)rst->GetCollect("GUID"));
			data.strPos = ((char *)(_bstr_t)rst->GetCollect("����"));
			data.strType = ((char *)(_bstr_t)rst->GetCollect("����"));
			data.strCreator=((char *)(_bstr_t)rst->GetCollect("������"));
			data.strCreatTime=((char *)(_bstr_t)rst->GetCollect("����ʱ��"));
			te.push_back(data);
			rst->MoveNext();
		}
	}
	return te;
}

void CLableMarker::LoadMarks( const _bstr_t &strCondit, std::vector< LABLESTRUCT > &vMark )
{
	_RecordsetPtr	rst=QueryLableMarkerByCondit( strCondit );
	if (rst!=NULL)
	{
		_variant_t var;
		while(!rst->adoEOF)
		{
			LABLESTRUCT data;
			var=rst->GetCollect("GUID");
			data.strGUID = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strPos = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strText = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����");
			data.strType = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����Ŀ��");
			data.strTarget = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("������");
			data.strCreator = (_bstr_t)(var.vt==1?"":var);
			var=rst->GetCollect("����ʱ��");
			data.strCreatTime = (_bstr_t)(var.vt==1?"2010-1-1":var);
			var=rst->GetCollect("���ӷ�Χ");
			data.fEyeable = (float)(var.vt==1?300.f:var);
			vMark.push_back(data);
			rst->MoveNext();
		}
	}
}