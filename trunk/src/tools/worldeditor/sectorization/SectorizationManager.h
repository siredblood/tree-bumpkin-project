/*=======================================
文件：SectorizationManager.h
说明：功能分区管理类
作者：bobo
时间：13-5-1
========================================*/
#ifndef SectorizationManager_h__
#define SectorizationManager_h__
#include <vector>

struct SECTORIZATIONDATA
{
	CString strName;		//分块名称
	Vector3 viewpos;		//视角位置
	Vector3 viewdir;		//视角方向
	std::vector<CString> vGuids;	//所属分块对象
};

class SectorizationManager
{
public:
	SectorizationManager();
	~SectorizationManager();

	static SectorizationManager* getInstance();

	void init();
	/*====================================
	说明：加载功能分区信息
	参数：
	返回：
	====================================*/
	void loadSectorization();
	/*====================================
	说明：添加功能分区
	参数：
	返回：
	====================================*/
	void addSectorization(CString strName, Vector3 viewpos, Vector3 viewdir);
	/*====================================
	说明：修改分区视角
	参数：
	返回：
	====================================*/
	void editSectorizationViewport(CString strName, Vector3 viewpos, Vector3 viewdir);
	/*====================================
	说明：添加分区所属对象
	参数：
	返回：
	====================================*/
	void addSectorizationObject(CString strName, CString strGuid);
	/*====================================
	说明：删除分区
	参数：
	返回：
	====================================*/
	void deleteSectorization(CString strName);
	/*====================================
	说明：删除分区所属的对象
	参数：
	返回：
	====================================*/
	void deleteSectorizationObject(CString strName, CString strGuid);

	/*====================================
	说明：显示分块
	参数：
	返回：
	====================================*/
	void showSectorization(CString strName);
	/*====================================
	说明：返回功能分块数据
	参数：
	返回：
	====================================*/
	std::vector<SECTORIZATIONDATA> getSectorizationData(){ return m_vSectorizationData;}

	/*====================================
	说明：定位到方案模型
	参数：
	返回：
	====================================*/
	void locateToModel(CString strModel);

private:
	ChunkItemPtr findItem(CString strGuid);

private:
	static SectorizationManager *instance;

	std::vector<SECTORIZATIONDATA> m_vSectorizationData;
};

#endif // SectorizationManager_h__