#pragma once
#include "BllHelp.h"

struct MATERIALSOURCE
{
	int iId;//���
	string strGuid;//GUID
	string strType;//��������
	string strName; //��������
	string strCompany;//���湫˾
	string strAddress; //�����ַ
	double strReserves;//������
	string strProduceArea; //���ʲ���
	string strPurpose;//������;
	string strInstruct;//ʹ��˵��
	string strDescipt;//������Ϣ
	string strRemark;//��ע 
};
class CMaterialSource
{
public:
	CMaterialSource(void);
	~CMaterialSource(void);
private:
	static CMaterialSource instance;
	BOOL IsConnectOk();
public:
	//�����ʼ��
	static CMaterialSource & Instance();
	//��������
	BOOL Save(std::vector<MATERIALSOURCE> vSource);
	//�ñ��ɾ������
	BOOL Delete(_bstr_t bstrId);
	//�ñ������ɾ������
	BOOL Detele(std::vector<_bstr_t> vBstrIds);
	//��ѯ��������
	std::vector<MATERIALSOURCE> GetAllMaterial();
	//�����ѯ����
	std::vector<MATERIALSOURCE> GetMaterialByType(_bstr_t bstrTypeName);
	//������ѯ����
	std::vector<MATERIALSOURCE> GetMaterialByCondt(_bstr_t bstrCondt);
};
