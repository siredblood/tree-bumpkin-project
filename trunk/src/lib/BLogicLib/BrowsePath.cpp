#include "BrowsePath.h"

CBrowsePath CBrowsePath::instance;

CBrowsePath::CBrowsePath(void)
{
}

CBrowsePath::~CBrowsePath(void)
{
}
//�����ʼ��
CBrowsePath & CBrowsePath::Instance()
{
	return instance;
}
//�ж�����
BOOL CBrowsePath::IsConnectOk()
{
	if (!theBllApp.m_bConntSuccess)
	{
		MessageBox(NULL,_T("���ݿ�����ʧ�ܣ�"),_T("��ʾ"),0);
		return FALSE;
	}
	if (!theBllApp.m_pDB->CheckTableNameExist("·�����"))
	{
		MessageBox(NULL,_T("���ݿ��в����ڸ�������ҵ���"),_T("��ʾ"),0);
		return FALSE;
	}
	return TRUE;
}
//�ж������Ƿ����
BOOL CBrowsePath::IsNameExiste(_bstr_t strName)
{
	BOOL bIs=FALSE;
	if (!IsConnectOk())
		return FALSE;
	_bstr_t strSQL = "SELECT * FROM ·����� WHERE ���� = '" + strName+"'";
	_RecordsetPtr pRecordSet = theBllApp.m_pDB->ExcuteSqlRes(strSQL,adCmdText);
	if (pRecordSet==NULL)
		return FALSE;
	if (pRecordSet!=NULL && !pRecordSet->adoEOF)
		bIs=TRUE;
	pRecordSet->Close();
	pRecordSet.Release();
	return bIs;
}
//����
int CBrowsePath::Save(_bstr_t bstrId,_bstr_t bstrName,_bstr_t bstrSpeed,_bstr_t strTarget,_bstr_t strLoop)
{
	//�ж�����
	if (!IsConnectOk())
		return -1;
	//�ж�������Ч��
	if (bstrName.length()<1 || bstrSpeed.length()<1 || strTarget.length()<1)
	{
		MessageBox(NULL,_T("�뽫��д������Ϣ��"),0,0);
		return -1;
	}
	_bstr_t bstrSql;
	if (bstrId.length()>0) //�޸�
	{
		bstrSql="update ·����� set �Ƿ�ѭ��= "+strLoop+", ����= '"+bstrName+"', �ٶ�= " + bstrSpeed + ", ����Ŀ��= '"+strTarget+"'  where ���= "+bstrId;

		if (theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText))
			return atoi((char *)bstrId);
	}
	else     //�½�
	{
		bstrSql="insert into ·�����(����,�ٶ�,����Ŀ��,�Ƿ�ѭ��) values('"+bstrName+"',"+bstrSpeed+",'"+strTarget+"',"+strLoop+")";
		if (CDatabaseFactory::m_enumDatabaseType==OracleType)
			bstrSql="insert into ·�����(���,����,�ٶ�,����Ŀ��,�Ƿ�ѭ��) values(·���������.NextVal,'"+bstrName+"',"+bstrSpeed+",'"+strTarget+"',"+strLoop+")";
		if (theBllApp.m_pDB->ExcuteSql(bstrSql,adCmdText))
		{
			bstrSql="SELECT MAX(���) AS �����  FROM ·�����";
			if (CDatabaseFactory::m_enumDatabaseType==OracleType)
				bstrSql="select ·���������.currval as ����� from dual";
			_RecordsetPtr rcst=theBllApp.m_pDB->ExcuteSqlRes(bstrSql,adCmdText);
			if (rcst!=NULL && !rcst->adoEOF)
				return atoi((char *)(_bstr_t)rcst->GetCollect("�����"));
		}
	}
	return -1;
}
//��������
BOOL CBrowsePath::SaveNodes(_bstr_t bstrId,std::vector<_bstr_t> vpos)
{
	if (bstrId.length()<1)
	{
		MessageBox(NULL,_T("��ѡ��Ҫ���������·����"),0,0);
		return FALSE;
	}
	std::vector<_bstr_t> vstrSql;
	//ɾ��ԭ��
	_bstr_t bstPos,bstrSql="delete from ·������ڵ� where ·�����="+bstrId;
	vstrSql.push_back(bstrSql);
	//��������
	for(std::vector<_bstr_t>::iterator item=vpos.begin();item!=vpos.end();item++)
	{
		bstPos=*item;
		bstrSql="insert into ·������ڵ� (·�����,����) values ("+bstrId+",'"+bstPos+"')";
		vstrSql.push_back(bstrSql);
	}
	return theBllApp.m_pDB->ExcuteTrans(vstrSql,adCmdText);
}
//�ñ��ɾ��
BOOL CBrowsePath::DeleteById(_bstr_t bstrId)
{
	//�ж�����
	BOOL bIs=FALSE;
	if (!IsConnectOk())
		return FALSE;
	if (bstrId.length()<0)
	{
		MessageBox(NULL,_T("ɾ����¼��Ų���Ϊ�գ�"),0,0);
		return FALSE;
	}
	std::vector<_bstr_t> vbstrSql;
	vbstrSql.push_back( "DELETE FROM ·������ڵ� WHERE ·�����=" + bstrId );
	vbstrSql.push_back( "DELETE FROM ·����� WHERE ���="+bstrId);
	return theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
}
//������ɾ��
BOOL CBrowsePath::DeleteByName(_bstr_t bstrName)
{
	//�ж�����
	BOOL bIs=FALSE;
	if (!IsConnectOk())
		return FALSE;

	if (bstrName.length()<0)
	{
		MessageBox(NULL,_T("ɾ����¼���Ʋ���Ϊ�գ�"),0,0);
		return FALSE;
	}

	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from ·����� where ����='"+bstrName+"'",adCmdText);
	if (Rcst!=NULL)
	{
		if ( !Rcst->adoEOF )
		{
			_bstr_t bstrId=(_bstr_t)Rcst->GetCollect("���");
			std::vector<_bstr_t> vbstrSql;
			vbstrSql.push_back( "DELETE FROM ·������ڵ� WHERE ·�����=" + bstrId );
			vbstrSql.push_back( "DELETE FROM ·����� WHERE ���="+bstrId);
			bIs= theBllApp.m_pDB->ExcuteTrans( vbstrSql  ,adCmdText );
		}
		Rcst->Close();
		Rcst.Release();
	}
	return bIs;
}
//�ñ�ż���
PATHMODEL CBrowsePath::LoadById(_bstr_t bstrId)
{
	//�ж�����
	PATHMODEL model;
	if (!IsConnectOk())
		return model;
	if (bstrId.length()<0)
	{
		MessageBox(NULL,_T("ɾ����¼��Ų���Ϊ�գ�"),0,0);
		return model;
	}
	
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from ·����� where ���=" + bstrId,adCmdText);
	if (Rcst!=NULL)
	{
		if (!Rcst->adoEOF)
		{
			model.iId=(int)Rcst->GetCollect("���");
			model.strName=(char *)((_bstr_t)Rcst->GetCollect("����"));
			model.dSpeed=(double)Rcst->GetCollect("�ٶ�");
			model.strTarget=(char *)((_bstr_t)Rcst->GetCollect("����Ŀ��"));
			model.bLoop=(bool)Rcst->GetCollect("�Ƿ�ѭ��");
			model.vNodes=LoadNodes((_bstr_t)Rcst->GetCollect("���"));
		}
		Rcst->Close();
		Rcst.Release();
	}
	return model;
}
//�����Ƽ���
PATHMODEL CBrowsePath::LoadByName(_bstr_t bstrName)
{
	//�ж�����
	PATHMODEL model;
	if (!IsConnectOk())
		return model;
	if (bstrName.length()<0)
	{
		MessageBox(NULL,_T("ɾ����¼���Ʋ���Ϊ�գ�"),0,0);
		return model;
	}
	_RecordsetPtr Rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from ·����� where ����='" + bstrName+"'",adCmdText);
	if (Rcst!=NULL)
	{
		if (!Rcst->adoEOF)
		{
			model.iId=(int)Rcst->GetCollect("���");
			model.strName=(char *)((_bstr_t)Rcst->GetCollect("����"));
			model.dSpeed=(double)Rcst->GetCollect("�ٶ�");
			model.strTarget=(char *)((_bstr_t)Rcst->GetCollect("����Ŀ��"));
			model.bLoop=(bool)Rcst->GetCollect("�Ƿ�ѭ��");
			model.vNodes=LoadNodes((_bstr_t)Rcst->GetCollect("���"));
		}
		Rcst->Close();
		Rcst.Release();
	}
	return model;
}
//�ñ�ŵõ��ڵ�����
std::vector<string> CBrowsePath::LoadNodes(_bstr_t bstrId)
{
	std::vector<string> vNodes;
	if (!IsConnectOk())
		return vNodes;
	if (bstrId.length()<0)
	{
		MessageBox(NULL,_T("���ؼ�¼��Ų���Ϊ�գ�"),0,0);
		return vNodes;
	}
	
	_RecordsetPtr rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from ·������ڵ� where ·�����="+bstrId,adCmdText);
	if (rcst!=NULL)
	{
		string strTemp;
		while(!rcst->adoEOF)
		{
			strTemp=(char *)((_bstr_t)rcst->GetCollect("����"));
			vNodes.push_back(strTemp);
			rcst->MoveNext();
		}
		rcst->Close();
		rcst.Release();
	}
	return vNodes;
}
//��ѯ����·�����
std::vector<PATHMODEL> CBrowsePath::QueryAllPath()
{
	return QueryPathByCondition("");
}
//���ص�Ŀ���ѯ����·�����
std::vector<PATHMODEL> CBrowsePath::QueryPathByTarget(_bstr_t strTarget)
{
	vector<PATHMODEL> v;
	if (strTarget.length()<1)
	{
		MessageBox(NULL,_T("��ѡ���ص�Ŀ�꣡"),0,0);
		return v;
	}
	return QueryPathByCondition("  and ����Ŀ��='" + strTarget + "'");
}
//��ѯ����·�����
std::vector<PATHMODEL> CBrowsePath::QueryPathByCondition(_bstr_t bstrConditions)
{
	//�ж�����
	std::vector<PATHMODEL> vModel;
	if (!IsConnectOk())
		return vModel;
	_RecordsetPtr rcst=theBllApp.m_pDB->ExcuteSqlRes("select * from ·����� where 1=1 "+bstrConditions,adCmdText);
	if (rcst!=NULL)
	{
		PATHMODEL model;
		while(!rcst->adoEOF)
		{
			model.iId=(int)rcst->GetCollect("���");
			model.strName=(char *)((_bstr_t)rcst->GetCollect("����"));
			model.dSpeed=(double)rcst->GetCollect("�ٶ�");
			model.strTarget=(char *)((_bstr_t)rcst->GetCollect("����Ŀ��"));
			model.bLoop=(bool)rcst->GetCollect("�Ƿ�ѭ��");
			model.vNodes=LoadNodes((_bstr_t)rcst->GetCollect("���"));
			vModel.push_back(model);
			rcst->MoveNext();
		}
		rcst->Close();
		rcst.Release();
	}
	return vModel;
}