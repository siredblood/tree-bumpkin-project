#pragma once
#include "DBHead.h"
#include "ObjectDB.h"
class CBllApp
{
public:
	CBllApp();
	~CBllApp();
public:
	CObjectDB * m_pDB;
	bool m_bConntSuccess;
};
extern CBllApp theBllApp;