#pragma once
#include "BllHelp.h"

class CDrawLine
{
public:
	CDrawLine(void);
	~CDrawLine(void);
private:
	//�Ի����ֶ�
	_bstr_t m_strID;         //���
	_bstr_t m_strName;       //����
	_bstr_t m_strColor;      //��ɫ
	_bstr_t m_strCreator;    //������
	_bstr_t m_strCreateTime; //����ʱ��
	_bstr_t m_strRemark;     //��ע
public:
	//�Ի������Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	////���ñ��
	//void SetID(_bstr_t val) { m_strID = val; }

	//��������
	_bstr_t GetName() const { return m_strName; }
	//��������
	void SetName(_bstr_t val) { m_strName = val; }

	//������ɫ
	_bstr_t GetColor() const { return m_strColor; }
	//������ɫ
	void SetColor(_bstr_t val) { m_strColor = val; }

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


	//�Ի��ߵ����ݿ����,�����Ի������нڵ�

	//�����Ի�����Ϣ��
	//�������Ի��߱��
	BOOL LoadInfo( _bstr_t bstrID);
	//�����Ի��߽ڵ��¼����
	//�������Ի��߱��
	_RecordsetPtr LoadNodesRCS( _bstr_t bstrID );
	//�����Ի��߽ڵ��б�
	//�������Ի��߱��
	std::vector<_bstr_t> LoadNodesVetors( _bstr_t bstrID );

	//�����Ի��߼�¼,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	//�༭�Ի��߼�¼��Ϣ,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL UpdateLineInfo();

	//����Ի��߽ڵ�
	BOOL ClearLineNodes( _bstr_t bstrIDs );
	//�༭�Ի��߼�¼��Ϣ,
	//�����������б�
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates );

	//ɾ���Ի��߼�¼��
	//ͨ�����ݱ�ţ��á���"�������������Ի��߱��
	BOOL Delete(_bstr_t bstrIDS);

	//��ѯ�����Ի����б�
	_RecordsetPtr QueryAllLines();
	void QueryAllLines(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ�Ի��߼�¼����������ѯ����
	_RecordsetPtr  QueryLinesByCondit(_bstr_t bstrWhere);
	void QueryLinesByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);	
	//������ѯ
	_RecordsetPtr  QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);	
};