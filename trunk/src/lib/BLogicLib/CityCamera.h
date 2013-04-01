#pragma once
#include "BllHelp.h"


class CCityCamera
{
public:
	CCityCamera(void);
	~CCityCamera(void);
private:
	//��������ͷ�ֶ�
	_bstr_t m_strID;      //���
	_bstr_t m_strCameraID; //����ͷ���
	_bstr_t m_strPosition;  //λ��
	_bstr_t m_strType;    //����
	_bstr_t m_strRemark;  //��ע
public:
	//��������ͷ���Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }

	//��������ͷ���
	_bstr_t GetCameraID() const { return m_strCameraID; }
	//��������ͷ���
	void SetCameraID(_bstr_t val) { m_strCameraID = val; }

	//����λ��
	_bstr_t GetPosition() const { return m_strPosition; }
	//����λ��
	void SetPosition(_bstr_t val) { m_strPosition = val; }

	//��������
	_bstr_t GetType() const { return m_strType; }
	//��������
	void SetType(_bstr_t val) { m_strType = val; }

	//���ر�ע
	_bstr_t GetRemark() const { return m_strRemark; }
	//���ñ�ע
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//����ͷ�����ݿ����


	//���ض���ģ��
	BOOL Load(_bstr_t bstrID);
	//��������ͷ��¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	//�༭����ͷ��¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Update();
	//ɾ������ͷ��¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Delete();
	//ɾ������ͷ��¼��ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);
	//��ѯ��������ͷ��¼
	_RecordsetPtr QueryAllCamera();
	void QueryAllCamera(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ����ͷ��¼
	_RecordsetPtr  QueryCameraByCondit(_bstr_t STRWhere);
	void QueryCameraByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
