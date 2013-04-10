/*=======================================
文件：buildingSchemeDatabase.h
说明：模型替换方案数据库处理
作者：bobo
时间：13-4-9
========================================*/
#ifndef buildingSchemeDatabase_h__
#define buildingSchemeDatabase_h__

class BuildingSchemeDatabase
{
public:
	BuildingSchemeDatabase();
	~BuildingSchemeDatabase();
	/*====================================
	说明：加载方案信息
	参数：
	返回：
	====================================*/
	void loadScheme(std::map<CString, std::map<CString, CString>> &vScheme);
	/*====================================
	说明：添加方案信息
	参数：
	返回：
	====================================*/
	BOOL addScheme(CString strScheme, CString strBeReplacedModel, CString strNewModel );
	/*====================================
	说明：删除某个方案
	参数：
	返回：
	====================================*/
	BOOL deleteScheme(CString strScheme);
	/*====================================
	说明：删除方案中某条记录
	参数：
	返回：
	====================================*/
	BOOL deleteScheme(CString strScheme, CString strBeReplacedModel);
};

#endif // buildingSchemeDatabase_h__