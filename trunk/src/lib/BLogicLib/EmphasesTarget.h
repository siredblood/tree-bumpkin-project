#pragma once
#include "BllHelp.h"
struct TARGETMODEL
{
	string m_strID;         //���
	string m_strName;       //����
	string m_strType;       //����
	string m_strArea;       //��������
	string m_strAddress;    //��ַ
	string m_strCoordinate; //����
	string m_strRemark;     //����
};
class CEmphasesTarget
{
public:
	CEmphasesTarget(void);
	~CEmphasesTarget(void);
private:
	//�ص�Ŀ���ֶ�
	_bstr_t m_strID;         //���
	_bstr_t m_strName;       //����
	_bstr_t m_strType;       //����
	_bstr_t m_strArea;       //��������
	_bstr_t m_strAddress;    //��ַ
	_bstr_t m_strCoordinate; //����
	_bstr_t m_strRemark;     //����

	static CEmphasesTarget instance;
public:
	//�ص�Ŀ�����Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	////���ñ��
	//void SetID(_bstr_t val) { m_strID = val; }

	//��������
	_bstr_t GetCoordinate() const { return m_strCoordinate; }
	//��������
	void SetCoordinate(_bstr_t val) { m_strCoordinate = val; }

	//��������
	_bstr_t GetName() const { return m_strName; }
	//��������
	void SetName(_bstr_t val) { m_strName = val; }

	//��������
	_bstr_t GetType() const { return m_strType; }
	//��������
	void SetType(_bstr_t val) { m_strType = val; }

	//������������
	_bstr_t GetArea() const { return m_strArea; }
	//������������
	void SetArea(_bstr_t val) { m_strArea = val; }

	_bstr_t GetAddress() const { return m_strAddress; }
	void SetAddress(_bstr_t val) { m_strAddress = val; }

	//���ر�ע
	_bstr_t GetRemark() const { return m_strRemark; }
	//���ñ�ע
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//�ص�Ŀ������ݿ����

	 static CEmphasesTarget & Instance();
	//���ض���ģ��
	BOOL Load(_bstr_t bstrID);
	//�����Ƽ��ض���ģ��
	BOOL LoadByName(_bstr_t bstrName);
	//����ص�Ŀ�������Ƿ����
	BOOL CheckNameExist(_bstr_t bstrName);
	//����ص�Ŀ�����Ƹ���
	BOOL NameValidate(_bstr_t bstrName,_bstr_t bstrID);
	//�����ص�Ŀ���¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	//�༭�ص�Ŀ���¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Update();
	//ɾ���ص�Ŀ���¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Delete();
	//������ʵ��ɾ��
	BOOL DeleteByName(_bstr_t strName);
	//ɾ���ص�Ŀ���¼��ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);
	//��ѯ�����ص�Ŀ��
	vector<string> GetAllTargetName();
	//����
	std::vector<string> GetAreas();
	//�����ص�Ŀ��
	std::vector<string> GetTargetByArea(string strArea);

	_RecordsetPtr QueryAllEmphTarg();
	std::vector<TARGETMODEL> QueryAllTarget();
	void QueryAllEmphTarg(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ�ص�Ŀ���¼
	_RecordsetPtr  QueryEmphTargByCondit(_bstr_t STRWhere);
	void QueryEmphTargByCondit(_bstr_t bstrWhere, vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
