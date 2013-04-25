#include "pch.hpp"
#include "ApartmentDiagramMgr.h"
#include <algorithm>



CApartmentDiagramMgr CApartmentDiagramMgr::s_instance;


CApartmentDiagramMgr::CApartmentDiagramMgr()
{
	TaskManager::instance().add( this, "CApartmentDiagramMgr", NULL );
}

CApartmentDiagramMgr::~CApartmentDiagramMgr()
{

}

CApartmentDiagramMgr &CApartmentDiagramMgr::Instance()
{
	return s_instance;
}

void CApartmentDiagramMgr::init()
{
	//char szPath[MAX_PATH] = { 0 };
	//::GetModuleFileName( NULL, szPath, MAX_PATH );

	////保存exe所在的目录
	//std::string strPath = szPath;
	//m_strRoot = strPath.substr(0, strPath.find_last_of('\\')) + "\\apartment\\";
	m_strRoot = g_strExeFullPath + "\\data\\clientRes\\apartment\\";
	findDirectory(m_strRoot);
}

void CApartmentDiagramMgr::setCurrentApartment(const std::string &guid)
{
	m_strCurrentGuid = guid;
}

std::string CApartmentDiagramMgr::getCurrentDiagram()
{
	if(!isApartmentExist()) return "";
	return m_mapApartment[m_strCurrentGuid].getCurrentDiagram();
}

void CApartmentDiagramMgr::setCurrentDiagram(const std::string &diagram)
{
	if(isApartmentExist()){
		m_mapApartment[m_strCurrentGuid].setCurrentDiagram(diagram);
	}
}

std::list<std::string> CApartmentDiagramMgr::getCurrentDiagrams()
{
	std::list<std::string> diagrams;
	if(!isApartmentExist()) return diagrams;
	return m_mapApartment[m_strCurrentGuid].getDiagrams();
}

std::string CApartmentDiagramMgr::getCurrentDiagramPath()
{
	if(!isApartmentExist()) return "";
	std::string diagram = m_mapApartment[m_strCurrentGuid].getCurrentDiagram();
	if(diagram!="")
		diagram = m_strRoot + m_strCurrentGuid + "\\" + diagram;
	return diagram;
}

std::string CApartmentDiagramMgr::getCurrentApartmentPath()
{
	return m_strRoot + m_strCurrentGuid + "\\";
}

boolean CApartmentDiagramMgr::isApartmentExist()
{
	std::map<std::string , CApartmentDiagram>::iterator itr=m_mapApartment.find(m_strCurrentGuid);
	if(itr==m_mapApartment.end())
		return false;
	else 
		return true;
}


bool CApartmentDiagramMgr::first()
{
	if(!isApartmentExist()) return false;
	return m_mapApartment[m_strCurrentGuid].first();
}

bool CApartmentDiagramMgr::next()
{
	if(!isApartmentExist()) return false;
	return m_mapApartment[m_strCurrentGuid].next();
}

bool CApartmentDiagramMgr::prev()
{
	if(!isApartmentExist()) return false;
	return m_mapApartment[m_strCurrentGuid].prev();
}

bool CApartmentDiagramMgr::last()
{
	if(!isApartmentExist()) return false;
	return m_mapApartment[m_strCurrentGuid].last();
}

bool CApartmentDiagramMgr::add(const std::string &file)
{
	if(!isApartmentExist()){
		if(!makeDirectory(m_strCurrentGuid)){
			return false;
		}
	}
	std::string toPath = getCurrentApartmentPath();
	std::string filename = file.substr(file.find_last_of('\\')+1, file.length());
	if(copyFile(file, toPath+filename)){
		m_mapApartment[m_strCurrentGuid].push(filename);
		return true;
	}else{
		return false;
	}
}

bool CApartmentDiagramMgr::add(const std::vector<std::string> &vFiles)
{
	if(!isApartmentExist()){
		if(!makeDirectory(m_strCurrentGuid)){
			return false;
		}
	}
	std::string toPath = getCurrentApartmentPath();
	for(size_t i=0; i<vFiles.size(); i++){
		const std::string &fromFile = vFiles[i];
		std::string filename = fromFile.substr(fromFile.find_last_of('\\')+1, fromFile.length());
		if(copyFile(vFiles[i], toPath+filename))
			m_mapApartment[m_strCurrentGuid].push(filename);
		else
			return false;
	}
	return true;
}

bool CApartmentDiagramMgr::del()
{
	if(!isApartmentExist()) return false;
	std::string file = m_mapApartment[m_strCurrentGuid].getCurrentDiagram();
	std::string path = getCurrentApartmentPath();
	if(delFile(path+file)){
		m_mapApartment[m_strCurrentGuid].remove(file);
		return true;
	}else{
		return false;
	}
}

bool CApartmentDiagramMgr::makeDirectory(const std::string &strGuid)
{
	std::string floder = m_strRoot;
	floder += strGuid;
	if(!CreateDirectory(floder.c_str(), NULL)){
		return false;
	}
	m_mapApartment.insert(std::make_pair<std::string, CApartmentDiagram>(strGuid, CApartmentDiagram()));
	m_mapApartment[strGuid].setGuid(strGuid);
	return true;
}

void CApartmentDiagramMgr::findDirectory( const std::string &strFolder )
{
	WIN32_FIND_DATA findFileData;
	std::string strPath, strFileName;

	// 所有类型文件
	if( ( strFolder.find_last_of('\\') + 1 ) != strFolder.length() )
		strPath = strFolder + "\\*.*";
	else
		strPath = strFolder + "*.*";

	HANDLE hFind = FindFirstFile( strPath.c_str(), &findFileData );
	if( INVALID_HANDLE_VALUE == hFind )
		return;

	//
	while( TRUE )
	{
		// 当前是文件夹
		if( findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
		{
			// 我们需要的文件夹
			if( findFileData.cFileName[0] != '.')
			{
				std::string dir = findFileData.cFileName;
				std::vector<std::string> vFiles;
				findFiles(strFolder+findFileData.cFileName, vFiles);

				m_mapApartment.insert(std::make_pair<std::string, CApartmentDiagram>(dir, CApartmentDiagram()));
				m_mapApartment[dir].setGuid(dir);
				m_mapApartment[dir].push(vFiles);
			}
		}

		// 查找下一个文件
		if( !FindNextFile( hFind, &findFileData ) )
			break;
	}

	FindClose( hFind );
}

void CApartmentDiagramMgr::findFiles( const std::string &strFolder, std::vector<std::string> &vFiles )
{
	WIN32_FIND_DATA findFileData;
	std::string strPath, strFileName;

	// 所有类型文件
	if( ( strFolder.find_last_of('\\') + 1 ) != strFolder.length() )
		strPath = strFolder + "\\*.*";
	else
		strPath = strFolder + "*.*";

	HANDLE hFind = FindFirstFile( strPath.c_str(), &findFileData );
	if( INVALID_HANDLE_VALUE == hFind )
		return;

	//
	while( TRUE )
	{
		// 当前是文件
		if(!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			strFileName = findFileData.cFileName;
			size_t iDotIndex = strFileName.find_last_of( '.' );
			// 只处理文件后缀是bmp,jpg的文件
			std::string strPostfix = strFileName.substr(iDotIndex+1, strFileName.length());
			std::transform(strPostfix.begin(), strPostfix.end(), strPostfix.begin(), tolower);
			if( iDotIndex != -1 && (strPostfix == "bmp"||strPostfix == "jpg") )
			{
				vFiles.push_back(strFileName);
			}
		}

		// 查找下一个文件
		if( !FindNextFile( hFind, &findFileData ) )
			break;
	}

	FindClose( hFind );
}

int CApartmentDiagramMgr::copyFile(const std::string &fromFile, const std::string &toFile)
{
	return CopyFile(fromFile.c_str(), toFile.c_str(), FALSE);// 复制文件，如果文件存在则覆盖
}

int CApartmentDiagramMgr::copyFiles(const std::string &fromPath, const std::string &toPath, 
		const std::vector<std::string> &vFileNames)
{
	std::string newFromPath = getRightPath(fromPath);
	std::string newToPath = getRightPath(toPath);
	for(size_t i=0; i<vFileNames.size(); i++){
		// 复制文件，如果文件存在则覆盖
		if(!copyFile((newFromPath+vFileNames[i]).c_str(), (newToPath+vFileNames[i]).c_str()))
			return 0;
	}
	return 1;
}

std::string CApartmentDiagramMgr::getRightPath(const std::string &path)
{
	return *path.rbegin()=='\\' ?  path : (path + '\\');
}

int CApartmentDiagramMgr::delFile(const std::string &file)
{
	return DeleteFile(file.c_str());
}