#include "MaterialSource.h"

CMaterialSource CMaterialSource::instance;

CMaterialSource::CMaterialSource(void)
{
}

CMaterialSource::~CMaterialSource(void)
{
}
BOOL CMaterialSource::IsConnectOk()
{
	if (!theBllApp.m_bConntSuccess || !theBllApp.m_pDB->CheckTableNameExist("����"))
		return FALSE;
	return TRUE;
}

//�����ʼ��
CMaterialSource & CMaterialSource::Instance()
{
	return instance;
}
//��������
BOOL CMaterialSource::Save(std::vector<MATERIALSOURCE> vSource)
{
	if (vSource.size()<1)
		return FALSE;

	std::vector<_bstr_t> vSql;
	MATERIALSOURCE model;
	CString strSQL,strId,strGuid,strType,strName,strCompany,strAddress,strReserves,strProduceArea,strPurpose,strInstruct,strDescipt,strRemark; 
	for (std::vector<MATERIALSOURCE>::iterator it=vSource.begin();it!=vSource.end();it++)
	{
		model=*it;
		strId.Format("%d",model.iId);
		strGuid=model.strGuid.c_str();
		strType=model.strType.c_str();
		strName=model.strName.c_str();
		strCompany=model.strCompany.c_str();
		strAddress=model.strAddress.c_str();
		strReserves.Format("%f",model.strReserves);
		strProduceArea=model.strProduceArea.c_str();
		strPurpose=model.strPurpose.c_str();
		strInstruct=model.strInstruct.c_str();
		strDescipt=model.strDescipt.c_str();
		strRemark=model.strRemark.c_str();

		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSQL="INSERT INTO ����(���,GUID,��������,��������,���湫˾,�����ַ,������,���ʲ���,������;,ʹ��˵��,������Ϣ,��ע)VALUES(��������.NextVal,'"+
			strGuid+"','"+strType+"','"+strName+"','"+strCompany+"','"+strAddress+"',"+strReserves+",'"+strProduceArea
			+"','"+strPurpose+"','"+strInstruct+"','"+strDescipt+"','"+strRemark+"')";
		else
			strSQL="INSERT INTO ����([GUID],[��������],[��������],[���湫˾],[�����ַ],[������],[���ʲ���],[������;],[ʹ��˵��],[������Ϣ],[��ע])VALUES('"+
			strGuid+"','"+strType+"','"+strName+"','"+strCompany+"','"+strAddress+"',"+strReserves+",'"+strProduceArea
			+"','"+strPurpose+"','"+strInstruct+"','"+strDescipt+"','"+strRemark+"')";
		vSql.push_back(strSQL.GetBuffer(0));
	}
	return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
}
//�ñ��ɾ������
BOOL CMaterialSource::Delete(_bstr_t bstrId)
{
	if (IsConnectOk())
		return theBllApp.m_pDB->ExcuteSql("delete  ����  where ���=" + bstrId,adCmdText);
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//�ñ������ɾ������
BOOL CMaterialSource::Detele(std::vector<_bstr_t> vBstrIds)
{
	if (vBstrIds.size()<1)
		return FALSE;
	if (IsConnectOk())
	{
		_bstr_t  bstrIds;
		std::vector<_bstr_t>::iterator it=vBstrIds.begin();
		bstrIds=*it;
		it++;
		for (;it!=vBstrIds.end();it++)
		{
			bstrIds+=",";
			bstrIds+=*it;
		}
		return theBllApp.m_pDB->ExcuteSql("delete  רҵ����  where ��� in(" + bstrIds +")",adCmdText);
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//��ѯ��������
std::vector<MATERIALSOURCE> CMaterialSource::GetAllMaterial()
{
	return GetMaterialByCondt("");
}
//�����ѯ����
std::vector<MATERIALSOURCE> CMaterialSource::GetMaterialByType(_bstr_t bstrTypeName)
{
	return GetMaterialByCondt("  and ��������='"+ bstrTypeName +"'");
}
//������ѯ����
std::vector<MATERIALSOURCE> CMaterialSource::GetMaterialByCondt(_bstr_t bstrCondt)
{
	std::vector<MATERIALSOURCE> vSource;
	MATERIALSOURCE model;
	_RecordsetPtr Ptr=theBllApp.m_pDB->ExcuteSqlRes("SELECT  * FROM ����  WHERE 1=1 " + bstrCondt ,adCmdText);
	if (Ptr!=NULL)
	{
		_variant_t var;
		while(!Ptr->adoEOF)
		{
			model.iId=(int)Ptr->GetCollect("���");
			var=Ptr->GetCollect("GUID");
			model.strGuid=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("�����ַ");
			model.strAddress=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("���湫˾");
			model.strCompany=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("������Ϣ");
			model.strDescipt=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("ʹ��˵��");
			model.strInstruct=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("��������");
			model.strName=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("���ʲ���");
			model.strProduceArea=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("������;");
			model.strPurpose=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("��ע");
			model.strRemark=(char *)(_bstr_t)(var.vt==1?"":var);
			var=Ptr->GetCollect("������");
			model.strReserves=(double)(var.vt==1?"0":var);
			var=Ptr->GetCollect("��������");
			model.strType==(char *)(_bstr_t)(var.vt==1?"":var);

			vSource.push_back(model);
			Ptr->MoveNext();
		}
		Ptr->Close();
		Ptr.Release();
	}
	return vSource;
}
