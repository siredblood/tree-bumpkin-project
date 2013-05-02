/************************************************************************/
/* 建筑属性数据库操作类                                                */
/************************************************************************/
#ifndef _DB_BUILDING_PROPERTY_H_
#define _DB_BUILDING_PROPERTY_H_

// 比较的函数，用于屏蔽Map自动排序
template<class T>
struct DisableCompare :public std::binary_function<T,T,bool>
{
	bool operator()(T lhs,T rhs)  const
	{
		return true;
	}
};

typedef std::map<std::string, std::string, DisableCompare<std::string> > LinkedStringMap;

class CDBBuildingProperty
{
public:
	CDBBuildingProperty();
	~CDBBuildingProperty();

public:
	//保存
	static bool Save(const LinkedStringMap &mapProperty);
	static bool Save(const std::vector< LinkedStringMap > &vProperties);
	//删除 - 传入参数：id
	static bool Delete(const std::vector<std::string> &vIds);
	// 载入
	static bool Query(const std::string &strGuid, LinkedStringMap &mapProperty);
	static bool Query(std::vector< LinkedStringMap > &vProperties);
	// 属性是否存在
	static bool IsExist(const std::string &strGuid);

private:
	static bool Add(const LinkedStringMap &mapProperty);
	static bool Update(const LinkedStringMap &mapProperty);

	static std::string GetUpdateSql(const LinkedStringMap &mapProperty);
};

#endif