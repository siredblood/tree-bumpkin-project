#pragma once
#include "BllHelp.h"

class CControlUser
{
public:
	CControlUser(void);
	~CControlUser(void);
private:
	//����û��ֶ�
	_bstr_t m_strID;         //���
	_bstr_t m_strServer;       //������
	_bstr_t m_strUserName;       //�û���
	_bstr_t m_strPassWord;       //����
public:
	//����û����Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	////���ñ��
	//void SetID(_bstr_t val) { m_strID = val; }

	//���ط�����
	_bstr_t GetServer() const { return m_strServer; }
	//���÷�����
	void SetServer(_bstr_t val) { m_strServer = val; }

	//�����û���
	_bstr_t GetUserName() const { return m_strUserName; }
	//�����û���
	void SetUserName(_bstr_t val) { m_strUserName = val; }

	//��������
	_bstr_t GetPassWord() const { return m_strPassWord; }
	//��������
	void SetPassWord(_bstr_t val) { m_strPassWord = val; }

	//����û������ݿ����


	//���ض���ģ��
	BOOL Load(_bstr_t bstrID);
	//���Ӽ���û���¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	//�༭����û���¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Update();
	//ɾ������û���¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Delete();
	//ɾ������û���¼��ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);
	//��ѯ�����ص�Ŀ��
	vector<string> GetAllUserName();
	_RecordsetPtr QueryAllUser();
	void QueryAllUser(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ�ص�Ŀ���¼
	_RecordsetPtr  QueryUserByCondit(_bstr_t STRWhere);
	void QueryUserByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
