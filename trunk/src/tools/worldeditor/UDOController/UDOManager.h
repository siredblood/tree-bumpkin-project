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
	// ��ȡUdoCamera������
	void GetUdoCamera( int id, UDOCamera &udoCamera );

	// ����UdoCamera������
	void UpdateUdoCamera( const UDOCamera &udoCamera );

	// ���UdoCamera������
	void AddUdoCamera( const UDOCamera &udoCamera );

	// ɾ��UdoCamera������
	void DelUdoCamera( int id );

	// ��ȡ����UdoCamera������
	void GetAllUdoCamera( std::vector<UDOCamera> &vUdoCamera );

public:
	// ���ݿ��������
	BOOL Load( std::vector<UDOCamera> &vUdoCamera );
	BOOL Save( const UDOCamera &udoCamera );
	BOOL Delete( int id );

private:
	std::vector<UDOCamera>		m_vUdoCamera;
};

#endif