/*=======================================
�ļ���SectorizationManager.h
˵�������ܷ���������
���ߣ�bobo
ʱ�䣺13-5-1
========================================*/
#ifndef SectorizationManager_h__
#define SectorizationManager_h__
#include <vector>

struct SECTORIZATIONDATA
{
	CString strName;		//�ֿ�����
	Vector3 viewpos;		//�ӽ�λ��
	Vector3 viewdir;		//�ӽǷ���
	std::vector<CString> vGuids;	//�����ֿ����
};

class SectorizationManager
{
public:
	SectorizationManager();
	~SectorizationManager();

	static SectorizationManager* getInstance();

	void init();
	/*====================================
	˵�������ع��ܷ�����Ϣ
	������
	���أ�
	====================================*/
	void loadSectorization();
	/*====================================
	˵������ӹ��ܷ���
	������
	���أ�
	====================================*/
	void addSectorization(CString strName, Vector3 viewpos, Vector3 viewdir);
	/*====================================
	˵�����޸ķ����ӽ�
	������
	���أ�
	====================================*/
	void editSectorizationViewport(CString strName, Vector3 viewpos, Vector3 viewdir);
	/*====================================
	˵������ӷ�����������
	������
	���أ�
	====================================*/
	void addSectorizationObject(CString strName, CString strGuid);
	/*====================================
	˵����ɾ������
	������
	���أ�
	====================================*/
	void deleteSectorization(CString strName);
	/*====================================
	˵����ɾ�����������Ķ���
	������
	���أ�
	====================================*/
	void deleteSectorizationObject(CString strName, CString strGuid);

	/*====================================
	˵������ʾ�ֿ�
	������
	���أ�
	====================================*/
	void showSectorization(CString strName);
	/*====================================
	˵�������ع��ֿܷ�����
	������
	���أ�
	====================================*/
	std::vector<SECTORIZATIONDATA> getSectorizationData(){ return m_vSectorizationData;}

	/*====================================
	˵������λ������ģ��
	������
	���أ�
	====================================*/
	void locateToModel(CString strModel);

private:
	ChunkItemPtr findItem(CString strGuid);

private:
	static SectorizationManager *instance;

	std::vector<SECTORIZATIONDATA> m_vSectorizationData;
};

#endif // SectorizationManager_h__