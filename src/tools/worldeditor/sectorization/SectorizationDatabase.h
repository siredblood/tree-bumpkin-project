/*=======================================
文件：SectorizationDatabase.h
说明：功能分区数据库
作者：bobo
时间：13-5-2
========================================*/
#ifndef SectorizationDatabase_h__
#define SectorizationDatabase_h__

#include "SectorizationManager.h"

class SectorizationDatabase
{
public:
	SectorizationDatabase();
	~SectorizationDatabase();

	void loadSectorization(std::vector<SECTORIZATIONDATA>& vData);

	BOOL addSectorization(CString strName, Vector3 viewpos, Vector3 viewdir);

	BOOL editSectorization(CString strName, Vector3 viewpos, Vector3 viewdir);

	BOOL addSectorizationObject(CString strName, CString strGuid);

	BOOL deleteSectorization(CString strName);

	BOOL deleteSectorizationObject(CString strName, CString strGuid);
};

#endif // SectorizationDatabase_h__