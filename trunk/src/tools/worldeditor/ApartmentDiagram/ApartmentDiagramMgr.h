#pragma once

#include <map>
#include <string>
#include <vector>
#include <map>
#include "worldeditor/BaseFramework/ITask.hpp"
#include "ApartmentDiagram.h"


class CApartmentDiagramMgr  : public ITask
{
private:
	CApartmentDiagramMgr();
	CApartmentDiagramMgr( const CApartmentDiagramMgr &rhs );
	CApartmentDiagramMgr &operator=( const CApartmentDiagramMgr &rhs );
	~CApartmentDiagramMgr();

	static CApartmentDiagramMgr s_instance;

public:
	static CApartmentDiagramMgr &Instance();

	void init();
	// 设置当前户型建筑
	void setCurrentApartment(const std::string &guid);

	// 获取/设置当前户型图名称
	std::string getCurrentDiagram();
	void setCurrentDiagram(const std::string &diagram);

	// 获取当前户型图路径
	std::string getCurrentDiagramPath();

	// 获取当前户型建筑路径
	std::string getCurrentApartmentPath();
	// 获取当前建筑所有户型图
	std::list<std::string> getCurrentDiagrams();

	bool next();
	bool prev();
	bool first();
	bool last();

	// 添加
	bool add(const std::vector<std::string> &vFiles);
	bool add(const std::string &file);
	// 删除
	bool del();
	// 户型文件夹是否存在
	boolean isApartmentExist();

private:
	// 文件操作
	bool makeDirectory(const std::string &strGuid);
	void findDirectory(const std::string &strFolder);
	void findFiles(const std::string &strFolder, std::vector<std::string> &vFiles);
	int copyFile(const std::string &fromFile, const std::string &toFile);
	int copyFiles(const std::string &fromPath, const std::string &toPath, 
		const std::vector<std::string> &vFileNames);
	int delFile(const std::string &file);

private:
	// 获取正确的路径，末尾含'\'
	std::string getRightPath(const std::string &path);

private:
	std::string m_strRoot;
	std::string m_strCurrentGuid;
	std::map<std::string, CApartmentDiagram> m_mapApartment;
};