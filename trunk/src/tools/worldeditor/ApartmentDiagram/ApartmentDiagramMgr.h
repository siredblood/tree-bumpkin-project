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
	// ���õ�ǰ���ͽ���
	void setCurrentApartment(const std::string &guid);

	// ��ȡ/���õ�ǰ����ͼ����
	std::string getCurrentDiagram();
	void setCurrentDiagram(const std::string &diagram);

	// ��ȡ��ǰ����ͼ·��
	std::string getCurrentDiagramPath();

	// ��ȡ��ǰ���ͽ���·��
	std::string getCurrentApartmentPath();
	// ��ȡ��ǰ�������л���ͼ
	std::list<std::string> getCurrentDiagrams();

	bool next();
	bool prev();
	bool first();
	bool last();

	// ���
	bool add(const std::vector<std::string> &vFiles);
	bool add(const std::string &file);
	// ɾ��
	bool del();
	// �����ļ����Ƿ����
	boolean isApartmentExist();

private:
	// �ļ�����
	bool makeDirectory(const std::string &strGuid);
	void findDirectory(const std::string &strFolder);
	void findFiles(const std::string &strFolder, std::vector<std::string> &vFiles);
	int copyFile(const std::string &fromFile, const std::string &toFile);
	int copyFiles(const std::string &fromPath, const std::string &toPath, 
		const std::vector<std::string> &vFileNames);
	int delFile(const std::string &file);

private:
	// ��ȡ��ȷ��·����ĩβ��'\'
	std::string getRightPath(const std::string &path);

private:
	std::string m_strRoot;
	std::string m_strCurrentGuid;
	std::map<std::string, CApartmentDiagram> m_mapApartment;
};