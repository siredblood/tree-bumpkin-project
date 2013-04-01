#pragma once
#include "BllHelp.h"
//·�����
struct PATHMODEL
{
	int iId;
	string strName;
	string strTarget;
	double dSpeed;
	bool bLoop;
	std::vector<string> vNodes;
};
class CBrowsePath
{
public:
	CBrowsePath(void);
	~CBrowsePath(void);
private:
	static CBrowsePath instance;
	//�ж�����
	BOOL IsConnectOk();
public:
	//�����ʼ��
	static CBrowsePath & Instance();
	//�ж������Ƿ����
	BOOL IsNameExiste(_bstr_t bstrName);
	//���������Ϣ���ر�����
	int Save(_bstr_t bstrId,_bstr_t bstrName,_bstr_t bstrSpeed,_bstr_t strTarget,_bstr_t strLoop);
	//��������
	BOOL SaveNodes(_bstr_t bstrId,std::vector<_bstr_t> vpos);
	//�ñ��ɾ��
	BOOL DeleteById(_bstr_t bstrId);
	//������ɾ��
	BOOL DeleteByName(_bstr_t bstrName);
	//�ñ�ż���
	PATHMODEL LoadById(_bstr_t bstrId);
	//�����Ƽ���
	PATHMODEL LoadByName(_bstr_t bstrName);
	//�ñ�ŵõ��ڵ�����
	std::vector<string> LoadNodes(_bstr_t bstrId);
	//��ѯ����·�����
	std::vector<PATHMODEL> QueryAllPath();
	//���ص�Ŀ���ѯ����·�����
	std::vector<PATHMODEL> QueryPathByTarget(_bstr_t strTarget);
	//��ѯ����·�����
	std::vector<PATHMODEL> QueryPathByCondition(_bstr_t bstrConditions);
};

