//Concretion.h
//ʵ�־������������ӡ��޸ĺ�ɾ��
#pragma once
#include "BllHelp.h"

using namespace std;

class CConcretion
{
public:
	CConcretion();
	~CConcretion();


public:
	static CConcretion & Instance();
	//����
	//��������ֱ�Ϊ��GUID��������ƣ��ֶ������ֶ�ֵ��map
	BOOL Save(_bstr_t strGuid, _bstr_t strTableName, map<_bstr_t,_bstr_t> &mapFlds);
	BOOL Save(_bstr_t strGuid, _bstr_t strTableName, vector<_bstr_t>&vfileds,vector<_bstr_t> &vValues);
	//ɾ��
	//���������GUID
	BOOL Delete(_bstr_t strGuid);

	//���ض���ģ��
	int Load(_bstr_t strGUID,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts,string &strType,vector<string> &vecRecordSetH);

	BOOL LoadType(_bstr_t strTable,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	BOOL LoadType(_bstr_t strTable,_bstr_t strConditiong,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//����
	//�õ�ģ�ͱ������GUID
	vector<string> GetAllGuid(_bstr_t strTableName);

	//�ж�ĳ��ģ���Ƿ��ǽ�������
	BOOL IsBuildPart(_bstr_t strGuid);
	//�ж�ĳ��ģ���Ƿ����ص�Ŀ����
	BOOL IsHasTarget(_bstr_t strGuid);
	//�ж��Ƿ�������ͷ
	BOOL IsCamara(_bstr_t strGuid);
	//�ж��Ƿ��Ǹ�����ʩ
	BOOL IsFacilitie(_bstr_t strGuid);
	//�ж��Ƿ��Ǿ���
	BOOL IsPolice(_bstr_t strGuid);
	
	//����ģ���ص�Ŀ����Ϣ,keyΪ�ֶ���,valueΪ�ֶ�ֵ
	map<string,string> GetTargetInfo(_bstr_t strGuid);
	BOOL GetTargetInfo(_bstr_t strGuid,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	BOOL GetTarGetInfoByName( _bstr_t strTargetName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//����ģ�͹�������������Ϣ
	map<string,string> GetBuildInfo(_bstr_t strGuid);
	BOOL GetBuildInfo(_bstr_t strGuid,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

private:
	static CConcretion instance;
private:
	//����
	//���������GUID��������ƣ��ֶ������ֶ�ֵ��map
	BOOL Add(_bstr_t strGuid, _bstr_t strTypeName, map<_bstr_t,_bstr_t> &mapFlds);
	//����
	//���������GUID���޸�ǰ����ţ�������ƣ��ֶ������ֶ�ֵ��map
	BOOL Update(_bstr_t strGuid, _bstr_t strOldID,_bstr_t strTypeName, map<_bstr_t,_bstr_t> &mapFlds);
	//����
	//���������GUID��������ƣ��ֶ������ֶ�ֵ��map
	BOOL Add(_bstr_t strGuid, _bstr_t strTypeName, vector<_bstr_t> &vfileds,vector<_bstr_t> &vValues);
	//����
	//���������GUID���޸�ǰ����ţ�������ƣ��ֶ������ֶ�ֵ��map
	BOOL Update(_bstr_t strGuid, _bstr_t strOldID,_bstr_t strTypeName, vector<_bstr_t> &vfileds,vector<_bstr_t> &vValues);


};