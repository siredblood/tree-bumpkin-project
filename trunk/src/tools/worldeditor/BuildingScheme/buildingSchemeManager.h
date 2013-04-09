/*=======================================
�ļ���buildingSchemeManager.h
˵������������������
���ߣ�����
ʱ�䣺2013-4-9
========================================*/
#ifndef buildingSchemeManager_h__
#define buildingSchemeManager_h__

#include "worldeditor/BaseFramework/ITask.hpp"

class BuildingSchemeManager : public ITask
{
public:
	BuildingSchemeManager();
	~BuildingSchemeManager();
	/*====================================
	˵������ȡʵ��
	������
	���أ�
	====================================*/
	static BuildingSchemeManager* getInstance();
	/*====================================
	˵�������س�ʼ��
	������
	���أ�
	====================================*/
	virtual void init();
	/*====================================
	˵�������ط���
	������
	���أ�
	====================================*/
	void loadScheme();
	/*====================================
	˵�������淽��
	������
	���أ�
	====================================*/
	void saveScheme();
	/*====================================
	˵��������������滻�б�
	������
	���أ�
	====================================*/
	void addScheme(CString strSchemeName, std::map<CString, CString> vReplacelist);
	/*====================================
	˵�������������һ���б�
	������
	���أ�
	====================================*/
	void addScheme(CString strSchemeName, CString strOldModel, CString strNewModel);
	/*====================================
	˵����ɾ����������
	������
	���أ�
	====================================*/
	void deleteScheme(CString strSchemeName);
	/*====================================
	˵����ɾ�������е�һ��
	������
	���أ�
	====================================*/
	void deleteScheme(CString strSchemeName, CString strOldModel);
	/*====================================
	˵������ȡ���з���
	������
	���أ�
	====================================*/
	std::map<CString, std::map<CString, CString>> getAllScheme();
	/*====================================
	˵������ȡ���з�������
	������
	���أ�
	====================================*/
	std::vector<CString> getAllSchemeName();
	/*====================================
	˵������ȡĳ���������滻�б�
	������
	���أ�
	====================================*/
	std::map<CString, CString> getReplaceList(CString strSchemeName);
	/*====================================
	˵����ִ�з���
	������
	���أ�
	====================================*/
	void executeScheme(CString strSchemeName);

private:
	static BuildingSchemeManager* mInstance;
	typedef std::map<CString, CString> replaceList;
	std::map<CString, replaceList> mReplaceScheme;
};

#endif // buildingSchemeManager_h__