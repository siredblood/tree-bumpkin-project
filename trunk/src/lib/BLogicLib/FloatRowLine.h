#pragma once
#include "BllHelp.h"


/************************************************************************/
/* ��������                                                             */
/************************************************************************/
class CFloatRowLine
{
public:
	CFloatRowLine(void);
	~CFloatRowLine(void);
private:
	//�������ֶ�
	_bstr_t m_strID;         //���
	_bstr_t m_strName;       //����
	_bstr_t m_strToTarger;   //����Ŀ��
	_bstr_t m_strColor;		 //��ɫ
	_bstr_t m_strLineType;   //ʵ��������
	_bstr_t m_strDerection;  //�Ƿ��м�ͷ
	_bstr_t m_strWidth;      //�߿��
	_bstr_t m_strCreator;     //������
	_bstr_t m_strCreateTime;  //����ʱ��
	_bstr_t m_strRemark;     //��ע

	static CFloatRowLine instance;
public:
	//���������Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	////���ñ��
	//void SetID(_bstr_t val) { m_strID = val; }

	//��������
	_bstr_t GetName() const { return m_strName; }
	//��������
	void SetName(_bstr_t val) { m_strName = val; }

	//��������Ŀ��
	_bstr_t GetToTarger() const { return m_strToTarger; }
	//��������Ŀ��
	void SetToTarger(_bstr_t val) { m_strToTarger = val; }

	//������ɫ
	_bstr_t GetColor() const { return m_strColor; }
	//������ɫ
	void SetColor(_bstr_t val) { m_strColor = val; }

	//������ʵ��
	_bstr_t GetLineType() const { return m_strLineType; }
	//������ʵ��
	void SetLineType(_bstr_t val) { m_strLineType = val; }

	//�����Ƿ����ͷ
	_bstr_t GetDerection() const { return m_strDerection; }
	//�����Ƿ����ͷ
	void SetDerection(_bstr_t val) { m_strDerection = val; }

	//�����߿��
	_bstr_t GetWidth() const { return m_strWidth; }
	//�����߿��
	void SetWidth(_bstr_t val) { m_strWidth = val; }

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


	static CFloatRowLine & Instance();
	//�����ߵ����ݿ����

	//������������Ϣ
	BOOL LoadInfo( _bstr_t bstrID);
	//���������߽ڵ����ݼ�
	_RecordsetPtr LoadNodesRCS( _bstr_t bstrID);
	//���������߽ڵ��б�
	std::vector<string> LoadNodesVetor( _bstr_t bstrID);
	////ʹ�����Ƽ���������
	//BOOL LoadInfoByName(_bstr_t bstrName);
	//_RecordsetPtr LoadByNameRCS(_bstr_t bstrName);
	//std::vector<string> LoadNodesByName(_bstr_t bstrName);
	//���������������б�
	_RecordsetPtr Loadproperties( _bstr_t bstrID );
	void Loadproperties(_bstr_t bstrID, std::vector<string> &vecField, std::vector<string> &vecRecordSet, long &lFieldCounts);

	//�ж������Ƿ��Ѿ�����
	bool CheckNameExiest(_bstr_t strName);

	//���������߼�¼,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	int AddGetID();
	//�༭�����߼�¼,
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Update();

	//��������߽ڵ�
	BOOL ClearLineNodes( _bstr_t bstrIDs );
	//�༭�����߼�¼��Ϣ,
	//�����������б�
	//����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL SaveLineNodes( std::vector<_bstr_t> vbstrCoordinates );

	//ɾ�������߼�¼��
	//ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t bstrIDS);
	
	
	//��ѯ����������Ŀ���б�
	_RecordsetPtr QueryAllLines();
	std::vector<_bstr_t> QueryAllLinesID();
	void QueryAllLines(vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//��ѯ����Ŀ��������
	_RecordsetPtr QueryTargetLines(_bstr_t strTarget);
	std::vector<_bstr_t> QueryTargetinesID(_bstr_t strTarget);
	void QueryTargetLines(_bstr_t strTarget,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ�����߼�¼
	_RecordsetPtr  QueryLinesByCondit(_bstr_t bstrWhere);
	std::vector<_bstr_t> QueryLinesIDByCondit(_bstr_t bstrWhere);
	void QueryLinesByCondit(_bstr_t bstrWhere,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	
	//��ѯʱ�������Ч��������
	_RecordsetPtr QueryValidateLines(_bstr_t bstrBeginDate,_bstr_t bstrEndDate);
	//��ѯʱ�������Ч��������
	void QueryValidateLines( _bstr_t bstrBeginDate,_bstr_t bstrEndDate,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
	//������ѯ
	_RecordsetPtr QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName);
	void QueryCreateLines(_bstr_t strBeginTime,_bstr_t strEndTime,_bstr_t strCreatorName,vector<string> &vecField, vector<string> &vecRecordSet, long &lFieldCounts);
};
/************************************************************************/
/* ������������                                                                     */
/************************************************************************/
class CFRowLineProperty
{
public:
	CFRowLineProperty(void);
	~CFRowLineProperty(void);

private:
	//�����������ֶ�
	_bstr_t m_strID;         //���
	_bstr_t m_strLineID;     //���������߱��
	_bstr_t m_strBeginDate;  //����ʱ��
	_bstr_t m_strEndDate;    //����ʱ��
	_bstr_t m_strRemark;     //��ע
public:
	//���������Ի�ȡ������

	//���ر��
	_bstr_t GetID() const { return m_strID; }
	//���ñ��
	void SetID(_bstr_t val) { m_strID = val; }

	//�������������߱��
	_bstr_t GetLineID() const { return m_strLineID; }
	//�������������߱��
	void SetLineID(_bstr_t val) { m_strLineID = val; }

	//��������ʱ��
	_bstr_t GetBeginDate() const { return m_strBeginDate; }
	//��������ʱ��
	void SetBeginDate(_bstr_t val) { m_strBeginDate = val; }

	//���ؽ���ʱ��
	_bstr_t GetEndDate() const { return m_strEndDate; }
	//���ý���ʱ��
	void SetToEndDate(_bstr_t val) { m_strEndDate = val; }

	//���ر�ע
	_bstr_t GetRemark() const { return m_strRemark; }
	//���ñ�ע
	void SetRemark(_bstr_t val) { m_strRemark = val; }


	//���������Ե����ݿ����

	//��������:���������Ա��еı��
	BOOL LoadInfo( _bstr_t bstrID );
	//�������������¼��ĳ�ͻ
	BOOL CheckLnPrptyColn(_bstr_t bstrID, _bstr_t bstrLineid,_bstr_t bstrBeginDate,_bstr_t bstrEndDate);
	//�������������Լ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Add();
	//�༭���������Լ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Update();
	//ɾ�����������Լ�¼,����ʵ����һ�������ٸ���������ֶθ�ֵ���������������
	BOOL Delete();
	//ɾ�����������Լ�¼��ͨ�����ݱ�ţ��á���"������
	BOOL Delete(_bstr_t strIDS);
};
