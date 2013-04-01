#pragma once
#include "BllHelp.h"
/************************************************************************/
/* ����������                                                           */
/************************************************************************/
class CAnalyseDemo
{
public:
	CAnalyseDemo(void);
	~CAnalyseDemo(void);
private:
	//���������ֶ�
	_bstr_t m_strID;                //���
	_bstr_t m_strName;              //����
	_bstr_t m_targetPoint;          //Ŀ���
	_bstr_t m_strToTarger;          //����Ŀ��
	_bstr_t m_strRange;             //��Χ
	_bstr_t m_strType;              //����
	_bstr_t m_strTypeID;            //���ͱ��
	_bstr_t m_strOuterColor;        //�����ɫ
	_bstr_t m_strResultColor;       //�����ɫ
	_bstr_t m_strPartResultColor;   //���ݽ����ɫ
	_bstr_t m_strCreator;     //������
	_bstr_t m_strCreateTime;  //����ʱ��
	_bstr_t m_strRemark;            //��ע
private:
	_bstr_t GetWhereString(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
public:
	//�����������Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	//��������
	_bstr_t GetName() const { return m_strName; }
	//��������
	void SetName(_bstr_t val) { m_strName = val; }
	//����Ŀ���
	_bstr_t GetTargetPoint() const { return m_targetPoint; }
	//����Ŀ���
	void SetTargetPoint(_bstr_t val) { m_targetPoint = val; }
	//������������
	_bstr_t GetToTarger() const { return m_strToTarger; }
	//������������
	void SetToTarger(_bstr_t val) { m_strToTarger = val; }
	//���ط�Χ
	_bstr_t GetRange() const { return m_strRange; }
	//���÷�Χ
	void SetRange(_bstr_t val) { m_strRange = val; }
	//��������
	_bstr_t GetType() const { return m_strType; }
	//��������
	void SetType(_bstr_t val) { m_strType = val; }
	//�������ͱ��
	_bstr_t GetTypeID() const { return m_strTypeID; }
	//�������ͱ��
	void SetTypeID(_bstr_t val) { m_strTypeID = val; }
	//���������ɫ
	_bstr_t GetOuterColor() const { return m_strOuterColor; }
	//���������ɫ
	void SetOuterColor(_bstr_t val) { m_strOuterColor = val; }

	//���ؽ����ɫ
	_bstr_t GetResultColor() const { return m_strResultColor; }
	//���ý����ɫ
	void SetResultColor(_bstr_t val) { m_strResultColor = val; }

	//��ȡ������ʾ��ɫ
	_bstr_t GetPartResultColor() const { return m_strPartResultColor; }
	//���ò�����ʾ��ɫ
	void SetPartResultColor(_bstr_t val) { m_strPartResultColor = val; }

	//���ش�����
	_bstr_t GetCreator() const { return m_strCreator; }
	//���ô�����
	void SetCreator(_bstr_t val) { m_strCreator = val; }
	//���ش���ʱ��
	_bstr_t GetCreateTime() const { return m_strCreateTime; }
	//���ô���ʱ��
	void SetCreateTime(_bstr_t val) { m_strCreateTime = val; }
	//���ر�ע
	_bstr_t GetRemark() const { return m_strRemark; }
	//���ñ�ע
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//�������������ݿ����

	//����


	//���ط���:
	//����������������
	BOOL LoadDemoInfo(_bstr_t bstrId);
	//���ط���:������������������
	BOOL LoadDemoInfoByName(_bstr_t bstrName);
	//�жϷ��������Ƿ����
	BOOL ExistDemoName(_bstr_t bstrName);

	//���ط����������Χ��ǰ�����ȼ��ط���
	_RecordsetPtr LoadDemoRange();
	//���ط����������Χ���������������
	_RecordsetPtr LoadDemoRange( _bstr_t strDemoID );
	//���ط����������Χ����������������
	vector<string> LoadDemoRangeByName(_bstr_t strDemoName);
	//���ط������ͷ������ꡣǰ�����ȼ��ط���
	_RecordsetPtr LoadDemoCoordinates();
	//���ط������ͷ������꣺�������������
	_RecordsetPtr LoadDemoCoordinates( _bstr_t strDemoID);
	//���ط������ͷ������꣺��������������
	std::vector<std::vector<string>> LoadDemoCoodis(_bstr_t strDemoName);
	//���ط������ͷ������ͣ���������������
	vector<string> LoadDemoResult( _bstr_t strDemoName);

	//���������Ի��߼�ط���������¼
	_RecordsetPtr LoadAllDrawLineDemo( _bstr_t bstrWhere );
	void LoadAllDrawLineDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//�������������߼�ط���������¼
	_RecordsetPtr LoadAllFRowLineDemo( _bstr_t bstrWhere );
	void LoadAllFRowLineDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//�������е㷽��������¼
	_RecordsetPtr LoadAllPointDemo( _bstr_t bstrWhere );
	void LoadAllPointDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//���������淽��������¼
	_RecordsetPtr LoadAllRangDemo( _bstr_t bstrWhere );
	void LoadAllRangDemo( _bstr_t bstrWhere ,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);


	//���淽��

	//�����Ի��߼�ط���������¼,
	//������������ţ�����ͷ����б���������б�
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveDrawLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds);

	//���������߼�ط���������¼,
	//������������ţ�����ͷ����б���������б�
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveFRowLineDemo(std::vector<_bstr_t> strCameraIds , std::vector<_bstr_t> strPoliceIds);

	//���ӵ㷽��������¼,
	//������key����ID,value�����б�
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SavePointDemo(std::map<_bstr_t,std::vector<std::vector<_bstr_t>>> mBuilding);
	//�²���
	BOOL SavePointDemo(_bstr_t strNewName,std::vector<_bstr_t> vGuid,std::vector<std::vector<_bstr_t>> vvCoodints);

	//�����淽��������¼,
	//������key����ID,value�����б�,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveRangDemo(std::map<_bstr_t,std::vector<std::vector<_bstr_t>>> mBuilding ,std::vector<_bstr_t> strRanges );
	//�����淽��������¼,
	//�������������ƣ��������GUID�б�����,��Χ
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveRangDemo(_bstr_t strNewName,std::vector<_bstr_t> vGuid,std::vector<std::vector<_bstr_t>> vvCoodints,std::vector<_bstr_t> strRanges );


	//ɾ������

	//ɾ������������¼,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Delete();

	//ɾ������������¼��
	//����ʵ��������ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);

	//������ѯ
	_RecordsetPtr QueryCreateDrawLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateDrawLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryCreateFRowLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateFRowLineDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryCreatePointDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreatePointDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);

	_RecordsetPtr QueryCreateRangeDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateRangeDemo(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};