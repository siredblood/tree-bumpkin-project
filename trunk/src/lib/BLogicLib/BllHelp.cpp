//#include "stdafx.h"
#include "BllHelp.h"
CBllHelp CBllHelp::instance;

CBllHelp::CBllHelp()
{

}

CBllHelp::~CBllHelp()
{

}

CBllHelp &CBllHelp::Instance()
{
	return instance;
}
void CBllHelp::QueryByCondit(_RecordsetPtr pRecordSet,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts)
{
	//�жϴ��ڼ�¼
	if(pRecordSet == NULL)
		return ;

	if (!vecRecordSet.empty())
	{
		vecRecordSet.clear();
	}
	if (!vecField.empty())
	{
		vecField.clear();
	}
	try
	{
		//�ֶθ���
		lFieldCounts = pRecordSet->GetFields()->GetCount();
		adoDataTypeEnum enumDataType;
		_bstr_t str;
		//�ֶ����ơ����͡���С
		for(long i = 0; i<lFieldCounts; i++)
		{
			str= pRecordSet->GetFields()->GetItem(i)->GetName();
			vecField.push_back((LPSTR)str);
			enumDataType = pRecordSet->GetFields()->GetItem(i)->GetType();
			str = GetDataTypeString(enumDataType);
			vecField.push_back((LPSTR)str);
			str = pRecordSet->GetFields()->GetItem(i)->GetDefinedSize();
			vecField.push_back((LPSTR)str);
		}
		pRecordSet->MoveFirst();

		long lCounts = 0;
		_variant_t var;
		//��ȡ��¼
		while(!pRecordSet->adoEOF)
		{
			for(long j=0; j<lFieldCounts; j++)
			{
				var=pRecordSet->GetCollect(j);
				str=(_bstr_t)(var.vt==1?"":var);
				vecRecordSet.push_back((LPSTR)str);	
			}
			pRecordSet->MoveNext();
			lCounts++;
		}
	}
	catch(_com_error e)
	{
		//AfxMessageBox("��¼Ϊ��");
	}
}

_bstr_t CBllHelp::GetDataTypeString(adoDataTypeEnum enumType)
{
	_bstr_t strType = "";
	switch(enumType)
	{
	case ADODB::adInteger:
	case ADODB::adNumeric:
		strType = "����";
		break;
	case ADODB::adDouble:
		strType = "������";
		break;
	case ADODB::adDate:
	case ADODB::adDBTimeStamp:
		strType = "����";
		break;
	case ADODB::adVarChar:
	case ADODB::adLongVarWChar:
		strType = "�ַ�";
		break;
	default:
		strType = " ";
		break;
	}
	return strType;
}