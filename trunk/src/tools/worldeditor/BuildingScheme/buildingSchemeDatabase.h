/*=======================================
�ļ���buildingSchemeDatabase.h
˵����ģ���滻�������ݿ⴦��
���ߣ�bobo
ʱ�䣺13-4-9
========================================*/
#ifndef buildingSchemeDatabase_h__
#define buildingSchemeDatabase_h__

class BuildingSchemeDatabase
{
public:
	BuildingSchemeDatabase();
	~BuildingSchemeDatabase();
	/*====================================
	˵�������ط�����Ϣ
	������
	���أ�
	====================================*/
	void loadScheme(std::map<CString, std::map<CString, CString>> &vScheme);
	/*====================================
	˵������ӷ�����Ϣ
	������
	���أ�
	====================================*/
	BOOL addScheme(CString strScheme, CString strBeReplacedModel, CString strNewModel );
	/*====================================
	˵����ɾ��ĳ������
	������
	���أ�
	====================================*/
	BOOL deleteScheme(CString strScheme);
	/*====================================
	˵����ɾ��������ĳ����¼
	������
	���أ�
	====================================*/
	BOOL deleteScheme(CString strScheme, CString strBeReplacedModel);
};

#endif // buildingSchemeDatabase_h__