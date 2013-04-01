#pragma once
#include "BllHelp.h"

struct LABLESTRUCT
{
	std::string strText;
	std::string strGUID;
	std::string strPos;
	std::string	strType; 
	std::string strTarget;
	std::string strCreator;
	std::string strCreatTime;
	std::string strRemark;
	float fEyeable;
};

class CLableMarker
{
public:
	CLableMarker(void);
	~CLableMarker(void);
private:
	//��ע�ֶ�
	_bstr_t m_strID;         //���
	_bstr_t m_strGUID;       //GUID
	_bstr_t m_strCoordinate; //����
	_bstr_t m_strTarget;     //����Ŀ�� 
	_bstr_t m_strName;       //����
	_bstr_t m_strType;       //����
	_bstr_t m_strCreator;     //������
	_bstr_t m_strCreateTime;  //����ʱ��
	_bstr_t m_strRemark;     //����
	_bstr_t m_strEyeable;   //���ӷ�Χ

	static CLableMarker instance;
public:
	//��ע���Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	////���ñ��
	//void SetID(_bstr_t val) { m_strID = val; }

	//���ر��
	_bstr_t GetGUID() const { return m_strGUID; }
	//���ñ��
	void SetGUID(_bstr_t val) { m_strGUID = val; }
	//��������
	_bstr_t GetCoordinate() const { return m_strCoordinate; }
	//��������
	void SetCoordinate(_bstr_t val) { m_strCoordinate = val; }
	//�����ص�Ŀ��
	_bstr_t GetTarget() const { return m_strTarget; }
	//�����ص�Ŀ��
	void SetTarget(_bstr_t val) { m_strTarget = val; }

	//��������
	_bstr_t GetName() const { return m_strName; }
	//��������
	void SetName(_bstr_t val) { m_strName = val; }

	//��������
	_bstr_t GetType() const { return m_strType; }
	//��������
	void SetType(_bstr_t val) { m_strType = val; }
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


	CLableMarker & Instance();
	//��ע�����ݿ����
	//�жϱ�ע�Ƿ����
	BOOL CheckLableExist(_bstr_t bstrGUID);
	//���ض���ģ��
	BOOL Load(_bstr_t bstrGUID);
	//��ʶ����
	BOOL Save(LABLESTRUCT modle);
	//��ʶ���������б�
	BOOL Save(vector<LABLESTRUCT> models);
	//ɾ����ע��¼��ͨ������GUID
	BOOL Delete(_bstr_t strGUID);
	//��ѯ���б�ע��¼
	_RecordsetPtr QueryAllLableMarker();
	void QueryAllLableMarker(std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	
	//��ѯ�����˺ʹ���ʱ���¼,��ѯ��ʼʱ��strBeginTime�ͽ���ʱ��strEndTime�ʹ�����ΪstrCreatorName�ı�ע,�������ʱ����ʱ��ֵΪ"",������Դ�������ֵΪ"";
	_RecordsetPtr  QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	//��ѯ�����˺ʹ���ʱ���¼,��ѯ��ʼʱ��strBeginTime�ͽ���ʱ��strEndTime�ʹ�����ΪstrCreatorName�ı�ע,�������ʱ����ʱ��ֵΪ"",������Դ�������ֵΪ"";
	void QueryCreateMarker(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	//��ѯ�����˺ʹ���ʱ���ע����,��ѯ��ʼʱ��strBeginTime�ͽ���ʱ��strEndTime�ʹ�����ΪstrCreatorName�ı�ע,�������ʱ����ʱ��ֵΪ"",������Դ�������ֵΪ"";
	vector<LABLESTRUCT> LoadCreateMark(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	
	//������ѯ��ע��¼
	_RecordsetPtr  QueryLableMarkerByCondit(_bstr_t STRWhere);
	void QueryLableMarkerByCondit(_bstr_t bstrWhere, std::vector<std::string> &vecField, std::vector<std::string> &vecRecordSet, long &lFieldCounts);
	vector<LABLESTRUCT> LoadLableMark();
	//�����ص�Ŀ��õ���ע
	vector<LABLESTRUCT> LoadLableMark(_bstr_t strTarget);
	
	void LoadMarks( const _bstr_t &strCondit, std::vector< LABLESTRUCT > &vMark );
};
