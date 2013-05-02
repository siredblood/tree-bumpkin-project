/************************************************************************/
/* �����������ݿ������                                                */
/************************************************************************/
#ifndef _DB_BUILDING_PROPERTY_H_
#define _DB_BUILDING_PROPERTY_H_

// �Ƚϵĺ�������������Map�Զ�����
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
	//����
	static bool Save(const LinkedStringMap &mapProperty);
	static bool Save(const std::vector< LinkedStringMap > &vProperties);
	//ɾ�� - ���������id
	static bool Delete(const std::vector<std::string> &vIds);
	// ����
	static bool Query(const std::string &strGuid, LinkedStringMap &mapProperty);
	static bool Query(std::vector< LinkedStringMap > &vProperties);
	// �����Ƿ����
	static bool IsExist(const std::string &strGuid);

private:
	static bool Add(const LinkedStringMap &mapProperty);
	static bool Update(const LinkedStringMap &mapProperty);

	static std::string GetUpdateSql(const LinkedStringMap &mapProperty);
};

#endif