#pragma once

#include "BllHelp.h"
/************************************************************************/
/* ִ��                                                                     */
/************************************************************************/
class CDuty
{
public:
	CDuty(void);
	~CDuty(void);
private:
	//ִ���ֶ�
	_bstr_t m_strID;      //���
	_bstr_t m_strPliceID; //����ID
	_bstr_t m_strAdress;  //ִ�ڵص�
	_bstr_t m_strDate;    //ִ������
	_bstr_t m_strTime;    //ִ�ڰ��
	_bstr_t m_strAudit;   //������
	_bstr_t m_strRemark;  //��ע
public:
	//ִ�����Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	////���ñ��
	//void SetID(_bstr_t val) { m_strID = val; }

	//���ؾ������
	_bstr_t GetPliceID() const { return m_strPliceID; }
	//���þ������
	void SetPliceID(_bstr_t val) { m_strPliceID = val; }

	//����ִ�ڵص�
	_bstr_t GetAdress() const { return m_strAdress; }
	//����ִ�ڵص�
	void SetAdress(_bstr_t val) { m_strAdress = val; }

	//����ִ������
	_bstr_t GetDate() const { return m_strDate; }
	//����ִ������
	void SetDate(_bstr_t val) { m_strDate = val; }

	//����ִ�ڰ��
	_bstr_t GetTime() const { return m_strTime; }
	//����ִ�ڰ��
	void SetTime(_bstr_t val) { m_strTime = val; }

	//����ִ�ڰ��
	_bstr_t GetAudit() const {return m_strAudit;}
	//����ִ�ڰ��
	void SetAudit(_bstr_t val){m_strAudit=val;}

	//���ر�ע
	_bstr_t GetRemark() const { return m_strRemark; }
	//���ñ�ע
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//ִ�ڱ�����ݿ����

	//���ض���ģ��
	BOOL Load(_bstr_t bstrID);
	//����ִ�ڼ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	////��������
	//BOOL AddList(std::map<_bstr_t,std::vector<_bstr_t> mstrRst);
	//�༭ִ�ڼ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Update();
	//ɾ��ִ�ڼ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Delete();
	//ɾ��ִ�ڼ�¼������ʵ��������ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);

	//��ѯ����ִ�ڼ�¼
	_RecordsetPtr QueryAllDuty();
	void QueryAllDuty(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	//������ѯִ�ڼ�¼
	_RecordsetPtr  QueryDutyByCondit(_bstr_t STRWhere);
	void QueryDutyByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);


	//��ѯ��¼�б�
	_RecordsetPtr QueryDutyRcst(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	//����������ȿ���
	_RecordsetPtr QueryRCSTPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	vector<string> QueryVectorPolCtlGUID(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	//ͳ�ƾ���
	long SumDutyPol(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	//ͳ�Ƽ�¼��
	long SumDutyRecords(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
private:
	_bstr_t GetWhereSql(_bstr_t strBeginDate,_bstr_t strEndDate,_bstr_t strdutyTimes,_bstr_t strAddress);
	bool CheckCollision(_bstr_t strId, _bstr_t strPolId,_bstr_t strDate,_bstr_t strDutyTimes);
};



/************************************************************************/
/* ִ�ڰ��                                                                     */
/************************************************************************/
class CDutyTime
{
public:
	CDutyTime(void);
	~CDutyTime(void);
public:
	//ִ�ڰ�α�����ݿ����

	//����ִ�ڰ�μ�¼,����strtimeΪִ��ʱ�䣬strremarkΪ��ע
	BOOL Add(_bstr_t strTime,_bstr_t strRemark);
	//�༭ִ�ڰ�μ�¼,����stridΪ��ţ�strtimeΪִ��ʱ�䣬strremarkΪ��ע
	BOOL Update(_bstr_t strID,_bstr_t strTime,_bstr_t strRemark);
	//ɾ��ִ�ڰ�μ�¼��ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);
	//�õ����԰��
	std::vector<string> QueryTimes();
	//��ѯ����ִ�ڰ�μ�¼
	_RecordsetPtr QueryAllDutyTime();
	void QueryAllDutyTime(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯִ�ڰ�μ�¼
	_RecordsetPtr  QueryDutyTimeByCondit(_bstr_t STRWhere);
	void QueryDutyTimeByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};