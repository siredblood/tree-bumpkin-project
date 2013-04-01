#include "TeamWork.h"

CTeamWork CTeamWork::instance;

CTeamWork::CTeamWork(void)
{
}

CTeamWork::~CTeamWork(void)
{
}

BOOL CTeamWork::IsConnectOk()
{
	if (!theBllApp.m_bConntSuccess || !theBllApp.m_pDB->CheckTableNameExist("רҵ����"))
		return FALSE;
	return TRUE;
}
std::vector<TEAMMENBER> CTeamWork::GetMenbers(_bstr_t bstrId)
{
	std::vector<TEAMMENBER> vmenbers;
	TEAMMENBER model;
	_RecordsetPtr RcstPrt;
	RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from ��Ա  where ������="+ bstrId,adCmdText);
	if ( RcstPrt!=NULL )	
	{
		while (!RcstPrt->adoEOF)
		{
			_variant_t var;
			model.iId=(int)RcstPrt->GetCollect("���");
			model.iAge=(int)RcstPrt->GetCollect("����");
			model.iTeamId=(int)RcstPrt->GetCollect("������");
			var=RcstPrt->GetCollect("��ַ");
			model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("������˾");
			model.strCompany=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("������ϵ");
			model.strContacts=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("��ϸ��Ϣ");
			model.strDetails=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("�س�");
			model.strGoodAt=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("GUID");
			model.strGuid=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("ְλ");
			model.strJobPosition=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("��ϵ�ֻ�");
			model.strMobilePhone=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("����");
			model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("ְҵ");
			model.strProfession=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("��ע");
			model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("�Ա�");
			model.strSex=(char*)((_bstr_t)(var.vt==1?"":var));
			var=RcstPrt->GetCollect("�Ա�");
			vmenbers.push_back(model);
			RcstPrt->MoveNext();
		}
		RcstPrt->Close();
		RcstPrt.Release();
	}
	return vmenbers;
}

//�����ʼ��
CTeamWork & CTeamWork::Instance()
{
	return instance;
}
///////////////////////////////�ж�///////////////////////////////////////////
//�ж϶��������Ƿ����
BOOL CTeamWork::CheckTeamName(_bstr_t bstrName)
{
	_RecordsetPtr RcstPrt;
	BOOL BExist=FALSE;
	if (IsConnectOk())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ��ʶ='רҵ����' and  ����='"+ bstrName+"'",adCmdText);
		if (RcstPrt!=NULL )
		{
			if (!RcstPrt->adoEOF)
				BExist=TRUE;
			RcstPrt->Close();
			RcstPrt.Release();
		}	
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return BExist;
}
//�ж�ר���������Ƿ����
BOOL CTeamWork::CheckExpertName(_bstr_t bstrName)
{
	_RecordsetPtr RcstPrt;
	BOOL BExist=FALSE;
	if (IsConnectOk())
	{
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ��ʶ='ר����' and  ����='"+ bstrName+"'",adCmdText);
		if (RcstPrt!=NULL )
		{
			if (!RcstPrt->adoEOF)
				BExist=TRUE;
			RcstPrt->Close();
			RcstPrt.Release();
		}	
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return BExist;
}
////////////////////////////����//////////////////////////////////////////////
//���������Ϣ���ر��
int CTeamWork::SaveTeam(TEAMWORKMODEL tmodel)
{
	CString strId;
	strId.Format("%d",tmodel.iID);
	CString strAddress=tmodel.strAddress.c_str();
	CString strArea= tmodel.strArea.c_str();
	CString strDetail = tmodel.strDetail.c_str();
	CString strMark = tmodel.strMark.c_str();
	CString strName = tmodel.strName.c_str();
	CString strRemark = tmodel.strRemark.c_str();
	CString strTeamId= tmodel.strTeamId.c_str();
	CString strType = tmodel.strType.c_str();
	CString strSql;

	if (tmodel.iID>0) //����
			strSql="UPDATE רҵ���� SET ���� = '"+strTeamId+"',���� ='"+strName+"',���� = '"+ strType+"',���� = '"+strArea+"',��ַ = '"+strAddress+"',��ϸ��Ϣ = '"+strDetail+"',��ע = '"+strRemark+"'  WHERE ���="+strId;
	else //����
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql="INSERT INTO רҵ����(���,����,����,����,����,��ַ,��ϸ��Ϣ,��ע,��ʶ)VALUES(רҵ��������.NextVal,'"+strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail+"','"+strRemark+"','רҵ����')";
		else
			strSql="INSERT INTO רҵ����([����],[����],[����],[����],[��ַ],[��ϸ��Ϣ],[��ע],[��ʶ])VALUES('"+strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail+"','"+strRemark+"','רҵ����')";
		
	theBllApp.m_pDB->ExcuteSql(strSql.GetBuffer(0),adCmdText);
	strSql="select MAX(���) as ����� from רҵ����";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql="select ������������.currval as ����� from dual";
	_RecordsetPtr Ptr=theBllApp.m_pDB->ExcuteSqlRes(strSql.GetBuffer(),adCmdText);
	int thisId=-1;
	if (Ptr!=NULL)
	{
		if (!Ptr->adoEOF)
		{
			_variant_t var;
			var=Ptr->GetCollect("�����");
			thisId= (int)((var.vt==1?"-1":var));
		}
		Ptr->Close();
		Ptr.Release();
	}	
	return thisId;
}
//����ר����Ϣ���ر��
int CTeamWork::SaveExpert(TEAMWORKMODEL tmodel)
{
	CString strId;
	strId.Format("%d",tmodel.iID);
	CString strAddress=tmodel.strAddress.c_str();
	CString strArea= tmodel.strArea.c_str();
	CString strDetail = tmodel.strDetail.c_str();
	CString strMark = tmodel.strMark.c_str();
	CString strName = tmodel.strName.c_str();
	CString strRemark = tmodel.strRemark.c_str();
	CString strTeamId= tmodel.strTeamId.c_str();
	CString strType = tmodel.strType.c_str();
	CString strSql;

	if (tmodel.iID>0) //����
		strSql="UPDATE רҵ���� SET ���� = '"+strTeamId+"',���� ='"+strName
		+"',���� = '"+ strType+"',���� = '"+strArea+"',��ַ = '"+strAddress
		+"',��ϸ��Ϣ = '"+strDetail+"',��ע = '"+strRemark+"'  WHERE ���="+strId;
	else //����
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			strSql="INSERT INTO רҵ����(���,����,����,����,����,��ַ,��ϸ��Ϣ,��ע,��ʶ)VALUES(רҵ��������.NextVal,'"+
			strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail
			+"','"+strRemark+"','ר����')";
		else
			strSql="INSERT INTO רҵ����([����],[����],[����],[����],[��ַ],[��ϸ��Ϣ],[��ע],[��ʶ])VALUES('"+
			strTeamId+"','"+strName+"','"+strType+"','"+strArea+"','"+strAddress+"','"+strDetail
			+"','"+strRemark+"','ר����')";

	theBllApp.m_pDB->ExcuteSql(strSql.GetBuffer(0),adCmdText);
	strSql="select MAX(���) as ����� from רҵ����";
	if (CDatabaseFactory::m_enumDatabaseType==OracleType)
		strSql="select ������������.currval as ����� from dual";
	_RecordsetPtr Ptr=theBllApp.m_pDB->ExcuteSqlRes(strSql.GetBuffer(),adCmdText);
	int IthisId = -1;
	if (Ptr!=NULL)
	{
		if (!Ptr->adoEOF)
		{
			_variant_t var;
			var=Ptr->GetCollect("�����");
			IthisId = (int)((var.vt==1?"-1":var));
		}
		Ptr->Close();
		Ptr.Release();
	}
	return IthisId;
}
//�����Ա
BOOL CTeamWork::SaveMenbers(int iId, std::vector<TEAMMENBER> vmenber)
{
	if (iId>0 && vmenber.size()>0 )
	{
		CString strSql,strId,strGuid,strName,strSex,strAge,strJob,strPosition,strCompany,strAddress,strPhone,strContact,strGoodAt,strDetails,strRemark;
		strId.Format("%d",iId);

		std::vector<_bstr_t> vSql;

		strSql="delete from ��Ա where ������="+strId;
		vSql.push_back(strSql.GetBuffer(0));

		TEAMMENBER model;

		for (std::vector<TEAMMENBER>::iterator it=vmenber.begin();it!=vmenber.end();it++)
		{
			model=*it;
			strGuid=model.strGuid.c_str();
			strName=model.strName.c_str();
			strSex=model.strSex.c_str();
			strAge.Format("%d",model.iAge);
			strJob=model.strProfession.c_str();
			strPosition=model.strJobPosition.c_str();
			strCompany=model.strCompany.c_str();
			strAddress=model.strAddress.c_str();
			strPhone=model.strMobilePhone.c_str();
			strContact=model.strContacts.c_str();
			strGoodAt=model.strGoodAt.c_str();
			strDetails=model.strDetails.c_str();
			strRemark=model.strRemark.c_str();

			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				strSql="INSERT INTO ��Ա(���,GUID,����,�Ա�,����,ְҵ,ְλ,������˾,��ַ,��ϵ�ֻ�,������ϵ,�س�,��ϸ��Ϣ,��ע,������)VALUES(��Ա����.NextVal,'"+ 
				strGuid +"','"+ strName +"','"+strSex+"',"+strAge+",'"+strJob+"','"+strPosition+"','"+strCompany+"','"+
				strAddress+"','"+strPhone+"','"+strContact+"','"+strGoodAt+"','"+strDetails+"','"+strRemark+"',"+strId+")";
			else
				strSql="INSERT INTO ��Ա([GUID],[����],[�Ա�],[����],[ְҵ],[ְλ],[������˾],[��ַ],[��ϵ�ֻ�],[������ϵ],[�س�],[��ϸ��Ϣ],[��ע],[������])VALUES('"+ 
				strGuid +"','"+ strName +"','"+strSex+"',"+strAge+",'"+strJob+"','"+strPosition+"','"+strCompany+"','"+
				strAddress+"','"+strPhone+"','"+strContact+"','"+strGoodAt+"','"+strDetails+"','"+strRemark+"',"+strId+")";
			vSql.push_back(strSql.GetBuffer());
		}
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	}
	return FALSE;
}
//////////////////////////////ɾ��////////////////////////////////////////////
//�ñ��ɾ��
BOOL CTeamWork::Delete(_bstr_t bstrId)
{
	if (IsConnectOk())
	{
		std::vector<_bstr_t> vSql;
		_bstr_t bstrSql="delete  רҵ����  where ���=" + bstrId ;
		vSql.push_back(bstrSql);
		bstrSql = "delete  ��Ա  where ������=" + bstrId ;
		vSql.push_back(bstrSql);
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//�ñ������ɾ��
BOOL CTeamWork::Delete(std::vector<_bstr_t> vstrId)
{
	if (vstrId.size()<1)
		return FALSE;
	if (IsConnectOk())
	{
		_bstr_t  bstrIds;
		std::vector<_bstr_t>::iterator it=vstrId.begin();
		bstrIds=*it;
		it++;
		for (;it!=vstrId.end();it++)
		{
			bstrIds+=",";
			bstrIds+=*it;
		}

		std::vector<_bstr_t> vSql;
		_bstr_t bstrSql="delete  רҵ����  where ��� in(" + bstrIds +")";
		vSql.push_back(bstrSql);
		bstrSql = "delete  ��Ա  where ������ in(" + bstrIds +")";
		vSql.push_back(bstrSql);
		return theBllApp.m_pDB->ExcuteTrans(vSql,adCmdText);
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return FALSE;
}
//////////////////////////////��ѯ////////////////////////////////////////////	
//�ñ�ż��ض������ר������Ϣ
TEAMWORKMODEL CTeamWork::LoadInfoById(_bstr_t bstrId)
{
	TEAMWORKMODEL model;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ���="+ bstrId,adCmdText);
		if ( RcstPrt!=NULL )	
		{
			if (!RcstPrt->adoEOF)
			{
				_variant_t var;
				model.iID=(int)RcstPrt->GetCollect("���");
				var=RcstPrt->GetCollect("��ַ");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ϸ��Ϣ");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ע");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ʶ");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("���"));
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return model;
}
//�����Ƽ��ض�����Ϣ
TEAMWORKMODEL CTeamWork::LoadTeamByName(_bstr_t bstrName)
{
	TEAMWORKMODEL model;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ��ʶ='רҵ����' and ����='"+ bstrName+"'",adCmdText);
		if ( RcstPrt!=NULL )	
		{
			if (!RcstPrt->adoEOF)
			{
				_variant_t var;
				model.iID=(int)RcstPrt->GetCollect("���");
				var=RcstPrt->GetCollect("��ַ");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ϸ��Ϣ");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ע");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ʶ");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("���"));
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return model;
}
//�����Ƽ���ר������Ϣ
TEAMWORKMODEL CTeamWork::LoadExpertByName(_bstr_t bstrName)
{
	TEAMWORKMODEL model;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ��ʶ='ר����' and ����='"+ bstrName+"'",adCmdText);
		if ( RcstPrt!=NULL )	
		{
			if (!RcstPrt->adoEOF)
			{
				_variant_t var;
				model.iID=(int)RcstPrt->GetCollect("���");
				var=RcstPrt->GetCollect("��ַ");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ϸ��Ϣ");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ע");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ʶ");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("���"));
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return model;
}
//������ѯ�����鼯��
std::vector<TEAMWORKMODEL> CTeamWork::QueryTeamWork(_bstr_t bstrConditions)
{
	std::vector<TEAMWORKMODEL> vteams;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ��ʶ='רҵ����'  "+ bstrConditions,adCmdText);
		if ( RcstPrt!=NULL )	
		{
			_variant_t var;
			TEAMWORKMODEL model;
			while (!RcstPrt->adoEOF)
			{
				model.iID=(int)RcstPrt->GetCollect("���");
				var=RcstPrt->GetCollect("��ַ");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ϸ��Ϣ");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ע");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ʶ");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("���"));
				vteams.push_back(model);
				RcstPrt->MoveNext();
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return vteams;
}
//������ѯר���鼯��
std::vector<TEAMWORKMODEL> CTeamWork::QueryExperts(_bstr_t bstrConditions)
{
	std::vector<TEAMWORKMODEL> vExperts;
	if (IsConnectOk())
	{
		_RecordsetPtr RcstPrt;
		RcstPrt=theBllApp.m_pDB->ExcuteSqlRes("select * from רҵ����  where ��ʶ='ר����' "+ bstrConditions,adCmdText);
		if ( RcstPrt!=NULL )	
		{
			TEAMWORKMODEL model;
			_variant_t var;
			while (!RcstPrt->adoEOF)
			{
				model.iID=(int)RcstPrt->GetCollect("���");
				var=RcstPrt->GetCollect("��ַ");
				model.strAddress=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strArea=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ϸ��Ϣ");
				model.strDetail=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strName=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ע");
				model.strRemark=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strTeamId=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("����");
				model.strType=(char*)((_bstr_t)(var.vt==1?"":var));
				var=RcstPrt->GetCollect("��ʶ");
				model.strMark=(char*)((_bstr_t)(var.vt==1?"":var));
				model.vMenbers=GetMenbers((_bstr_t)RcstPrt->GetCollect("���"));
				vExperts.push_back(model);
				RcstPrt->MoveNext();
			}
			RcstPrt->Close();
			RcstPrt.Release();
		}
	}
	else
		MessageBox(NULL,"���ݿ����ʧ�ܣ�",0,0);
	return vExperts;
}