#include "Factory.h"
#include "BllApp.h"


DatabaseType CDatabaseFactory::m_enumDatabaseType = NullType;
_bstr_t CDatabaseFactory::m_strServer="";
_bstr_t CDatabaseFactory::m_strDatabaseName = "";
_bstr_t CDatabaseFactory::m_strUID = "";
_bstr_t CDatabaseFactory::m_strPwd = "";

BOOL CDatabaseFactory::LoadConfig()
{
	try
	{
		::CoInitialize(NULL);

		CComPtr<MSXML2::IXMLDOMDocument> spDoc;
		HRESULT hr;
		hr = spDoc.CoCreateInstance(__uuidof(MSXML2::DOMDocument));
		if(FAILED(hr))
			MessageBox(NULL, "XML����ʧ�ܣ�", "��ʾ", MB_OK);
		//��ȡ��ǰ����·��
		CString strExe;
		TCHAR exeFullPath[128];
		int iTmp;
		CString strTmp;
			const TCHAR chr[2]=_T("\\");
		GetModuleFileName(NULL,exeFullPath,128);
		strExe.Format(_T("%s"),exeFullPath);
		iTmp=strExe.ReverseFind(chr[0]);
		strTmp=strExe.Left(iTmp+1);
		CString strDataPath;
		strDataPath=strTmp;
		//�����ļ�·��
		strTmp +="Config.xml";

		hr = spDoc->load(CComVariant(strTmp.GetBuffer()));
		CComPtr<MSXML2::IXMLDOMElement> spElement;
		CComPtr<MSXML2::IXMLDOMNodeList> spNodeList;
		CComPtr<MSXML2::IXMLDOMNode> spNode;
		MSXML2::DOMNodeType nodeType;

		///��ȡXMLԪ��
		spElement = spDoc->GetdocumentElement();
		if(spElement == NULL)
			return FALSE;
		///��ȡXML��һ����Ϣ
		spNodeList = spElement->GetchildNodes();
		if(spNodeList == NULL)
			return FALSE;
		///��ȡ��һ���б�
		spNode = spNodeList->Getitem(0L);
		if(spNode == NULL)
			return FALSE;
		///��ȡ����
		nodeType = spNode->GetnodeType();
		if(NODE_ELEMENT != nodeType)
			return FALSE;

		CComPtr<MSXML2::IXMLDOMNodeList> spChildList;
		///��ʼ��ȡ�����ļ���Ϣ
		spChildList = spNode->GetchildNodes();
		if(spChildList == NULL)
			return FALSE;

		///��ȡ���ݿ�����
		CComPtr<MSXML2::IXMLDOMNamedNodeMap> soAtribute;
		CComPtr<MSXML2::IXMLDOMNode> spTypeNode, spServerNode, spNameNode, spUidNode, spPwdNode;
		BSTR bstrType;
		spTypeNode = spChildList->Getitem(0L);
		if(spTypeNode == NULL)
			return FALSE;
		bstrType = spTypeNode->Gettext();
		m_enumDatabaseType = (DatabaseType)atoi((LPSTR)bstrType);

		///��ȡ������
		spServerNode = spChildList->Getitem(1L);
		if(spServerNode == NULL)
			return FALSE;
		m_strServer = spServerNode->Gettext();

		///��ȡ���ݿ���
		spNameNode = spChildList->Getitem(2L);
		if(spNameNode == NULL)
			return FALSE;
		m_strDatabaseName = spNameNode->Gettext();

		///��ȡ�û�ID
		spUidNode = spChildList->Getitem(3L);
		if(spUidNode == NULL)
			return FALSE;
		m_strUID = spUidNode->Gettext();

		///��ȡӵ��Password
		spPwdNode = spChildList->Getitem(4L);
		if(spPwdNode == NULL)
			return FALSE;
		m_strPwd = spPwdNode->Gettext();

		///�ͷ���Դ
		spTypeNode.Release();
		spServerNode.Release();
		spNameNode.Release();
		spUidNode.Release();
		spPwdNode.Release();
		soAtribute.Release();
		spChildList.Release();

		spNode.Release();
		spNodeList.Release();
		spElement.Release();
		spDoc.Release();

		::CoUninitialize();

		theBllApp.m_pDB=CDatabaseFactory::CreateDatabase();
		if(theBllApp.m_pDB == NULL)
		{
			MessageBox(NULL,_T("�������ݿ���ʧ��"),_T("��ʾ"),MB_OK | MB_ICONEXCLAMATION);
			return FALSE;
		}
		if (m_enumDatabaseType==AccessType)
		{
			m_strDatabaseName=strDataPath.GetBuffer(0)+m_strDatabaseName;
		}
		BOOL bRes = theBllApp.m_pDB->ConnectDB(CDatabaseFactory::m_strServer,CDatabaseFactory::m_strDatabaseName,
			CDatabaseFactory::m_strUID,CDatabaseFactory::m_strPwd);
		if(bRes)
		{
			CFields::SetDatabaseType(m_enumDatabaseType);
			theBllApp.m_bConntSuccess=true;
		}
		else
		{
			MessageBox( NULL, _T("�����ݿ�ʧ�ܣ�"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION );
			return FALSE;
		}
	}
	catch(_com_error e)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDatabaseFactory::ConnetDatabase(std::string strPath, int iType, std::string strServer, std::string strDatabase, std::string strUser, std::string strPassword)
{
	m_enumDatabaseType = (DatabaseType)iType;
	m_strServer = strServer.c_str();
	m_strDatabaseName = strDatabase.c_str();
	m_strUID = strUser.c_str();
	m_strPwd = strPassword.c_str();
	
	theBllApp.m_pDB=CDatabaseFactory::CreateDatabase();
	if(theBllApp.m_pDB == NULL)
	{
		MessageBox(NULL,_T("�������ݿ���ʧ��"),_T("��ʾ"),MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	if (m_enumDatabaseType==AccessType)
	{
		std::string strDataPath = strPath;
		strDataPath += "\\";
		strDataPath += strDatabase;
		
		m_strDatabaseName = strDataPath.c_str();
	}
	BOOL bRes = theBllApp.m_pDB->ConnectDB(CDatabaseFactory::m_strServer,CDatabaseFactory::m_strDatabaseName,
		CDatabaseFactory::m_strUID,CDatabaseFactory::m_strPwd);
	if(bRes)
	{
		CFields::SetDatabaseType(m_enumDatabaseType);
		theBllApp.m_bConntSuccess=true;
	}
	else
	{
		MessageBox( NULL, _T("�����ݿ�ʧ�ܣ�"), _T("��ʾ"), MB_OK | MB_ICONEXCLAMATION );
		return FALSE;
	}
	
	return TRUE;
}

CObjectDB * CDatabaseFactory::CreateDatabase()
{
	CObjectDB *pDB = NULL;
	switch(m_enumDatabaseType)
	{
	case AccessType:
		pDB = new CAccessDB();
		break;
	case SqlServerType:
		pDB = new CSqlServerDB();
		break;
	case OracleType:
		pDB = new COracleDB();
		break;
	default:
		break;

	}
	return pDB;
}
