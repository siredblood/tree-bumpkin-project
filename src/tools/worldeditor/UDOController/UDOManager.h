#ifndef _UDO_MANAGER_H_
#define _UDO_MANAGER_H_

#include "UDOHeader.hpp"


class CUDOManager 
{
private:
	CUDOManager();
	CUDOManager( const CUDOManager &rhs );
	CUDOManager &operator=( const CUDOManager &rhs );

	static CUDOManager s_instance;

public:
	~CUDOManager();
	static CUDOManager &Instance();

public:
	// 获取UdoCamera的数据
	void GetUdoCamera( int id, UDOCamera &udoCamera );

	// 更新UdoCamera的数据
	void UpdateUdoCamera( const UDOCamera &udoCamera );

	// 添加UdoCamera的数据
	void AddUdoCamera( const UDOCamera &udoCamera );

	// 删除UdoCamera的数据
	void DelUdoCamera( int id );

	// 获取所有UdoCamera的数据
	void GetAllUdoCamera( std::vector<UDOCamera> &vUdoCamera );

public:
	// 数据库操作部分
	BOOL Load( std::vector<UDOCamera> &vUdoCamera );
	BOOL Save( const UDOCamera &udoCamera );
	BOOL Delete( int id );

private:
	std::vector<UDOCamera>		m_vUdoCamera;
};

#endif