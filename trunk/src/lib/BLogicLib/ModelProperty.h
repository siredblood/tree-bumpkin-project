#pragma once
#include "DBHelper.h"
#include "BllHelp.h"

#define MapFields map<_bstr_t,_bstr_t,less<_bstr_t>>
#define BStrVector vector<_bstr_t>
typedef pair <CString, CString> CString_Pair;

class CModelProperty
{
public:
	CModelProperty(void);
	~CModelProperty(void);

private:
	//����ֶ����Ƿ����
	bool CheckFieldNameExist(CString strFieldName);
	//�������͵��ֶ�����ת��Ϊ���ݿ��ֶ�����
	CString GetFieldTypeByString(CString strTypeString);
	//����������ת��Ϊ��������
	CString GetChianeseTypeByDataType(adoDataTypeEnum datatype);
	//�õ���������ֶ��ã�����
	_bstr_t GetFieldNames();
public:
	//������άģ����Ϣ
	//���������GUID
	std::map<CString,CString> LoadInfo(CString strGUID);
	//�������Ը���άģ��
	//������ģ��GUID���ֶεļ�ֵ
	BOOL SaveInfo(CString strGuid, MapFields &mapFlds);
	//ɾ����άģ������
	//���������GUID
	BOOL Delete(CString strGuid);

	//��ѯ������άģ�������б�
	_RecordsetPtr QueryModelProperty(CString strWhere);
	//��ѯ������άģ�������б�,���ذ��б�ʹ��
	void QueryModelProperty(CString strWhere,std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);

	//////////////////////////////////////////////////////////////////////////

	//�����άģ�������ֶ�
	BOOL AddField(CString strFieldName, CString enumFieldType, int iFieldSize);
	//�޸���άģ�������ֶ�
	BOOL UpdateField(CString strOldFieldName,CString strNewFieldName,  CString enumFieldType, 
		int iFieldSize);
	//ɾ����άģ�������ֶ�
	BOOL DeleteField(CString strFieldName);

	//��ѯ��άģ�����Ա������ֶ��б�
	FieldsPtr  QueryPropertyFields();
	//��ѯ������άģ�������б�,���ذ��б�ʹ��
	void QueryPropertyFields(std::vector<CString> &vecField, std::vector<CString> &vecRecordSet, long &lFieldCounts);
};
