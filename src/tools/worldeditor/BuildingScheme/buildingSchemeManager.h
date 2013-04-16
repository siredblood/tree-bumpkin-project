/*=======================================
文件：buildingSchemeManager.h
说明：建筑方案管理类
作者：波波
时间：2013-4-9
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
	说明：获取实例
	参数：
	返回：
	====================================*/
	static BuildingSchemeManager* getInstance();
	/*====================================
	说明：重载初始化
	参数：
	返回：
	====================================*/
	virtual void init();
	/*====================================
	说明：加载方案
	参数：
	返回：
	====================================*/
	void loadScheme();
	/*====================================
	说明：保存方案
	参数：
	返回：
	====================================*/
	void saveScheme();
	/*====================================
	说明：给方案添加替换列表
	参数：
	返回：
	====================================*/
	void addScheme(CString strSchemeName, std::map<CString, CString> vReplacelist);
	/*====================================
	说明：给方案添加一个列表
	参数：
	返回：
	====================================*/
	void addScheme(CString strSchemeName, CString strOldModel, CString strNewModel);
	/*====================================
	说明：删除整个方案
	参数：
	返回：
	====================================*/
	void deleteScheme(CString strSchemeName);
	/*====================================
	说明：删除方案中的一列
	参数：
	返回：
	====================================*/
	void deleteScheme(CString strSchemeName, CString strOldModel);
	/*====================================
	说明：删除指定模型的方案
	参数：
	返回：
	====================================*/
	void deleteSchemeByModel(CString strModel);
	/*====================================
	说明：获取所有方案
	参数：
	返回：
	====================================*/
	std::map<CString, std::map<CString, CString>> getAllScheme();
	/*====================================
	说明：获取所有方案名字
	参数：
	返回：
	====================================*/
	std::vector<CString> getAllSchemeName();
	/*====================================
	说明：获取某方案所有替换列表
	参数：
	返回：
	====================================*/
	std::map<CString, CString> getReplaceList(CString strSchemeName);
	/*====================================
	说明：执行方案
	参数：
	返回：
	====================================*/
	void executeScheme(CString strSchemeName);
	/*====================================
	说明：定位到方案模型
	参数：
	返回：
	====================================*/
	void locateToModel(CString strModel);

	//测试
	void handleKeyEvent( const KeyEvent & event );

private:
	ChunkItemPtr findItem(CString strGuid);

private:
	static BuildingSchemeManager* mInstance;
	typedef std::map<CString, CString> replaceList;
	std::map<CString, replaceList> mReplaceScheme;
};

#endif // buildingSchemeManager_h__