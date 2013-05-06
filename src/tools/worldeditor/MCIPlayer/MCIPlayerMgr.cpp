#include "pch.hpp"
#include "MCIPlayerMgr.h"

CMCIPlayerMgr CMCIPlayerMgr::s_instance;

CMCIPlayerMgr::CMCIPlayerMgr()
{
	m_bPause = false;
}

CMCIPlayerMgr::~CMCIPlayerMgr()
{

}

CMCIPlayerMgr &CMCIPlayerMgr::Instance()
{
	return s_instance;
}

void CMCIPlayerMgr::init(HWND hWnd)
{
	m_mciPlayer.init(hWnd);

	m_strRoot = g_strExeFullPath + "\\music\\";
	findFiles(m_strRoot, m_vAllFiles);
}

DWORD CMCIPlayerMgr::playDefault()
{
	return play(m_vAllFiles);
}

DWORD CMCIPlayerMgr::play(const std::vector<std::string> &vFiles)
{
	m_bPause = false;
	return m_mciPlayer.play(getFilesPath(vFiles));
}

DWORD CMCIPlayerMgr::pause()
{
	m_bPause = true;
	return m_mciPlayer.pause();
}

DWORD CMCIPlayerMgr::resume()
{
	m_bPause = false;
	return m_mciPlayer.resume();
}

DWORD CMCIPlayerMgr::stop()
{
	m_bPause = true;
	return m_mciPlayer.stop();
}

DWORD CMCIPlayerMgr::next()
{
	return m_mciPlayer.next();
}

DWORD CMCIPlayerMgr::prev()
{
	return m_mciPlayer.prev();
}

bool CMCIPlayerMgr::add(const std::vector<std::string> &vFiles)
{
	m_mciPlayer.stop();
	std::string toPath = m_strRoot;
	for(size_t i=0; i<vFiles.size(); i++){
		const std::string &fromFile = vFiles[i];
		std::string filename = fromFile.substr(fromFile.find_last_of('\\')+1, fromFile.length());
		if(copyFile(vFiles[i], toPath+filename))
			m_vAllFiles.push_back(filename);
		else
			return false;
	}
	m_mciPlayer.updatePlayList(m_vAllFiles);
	return true;
}

bool CMCIPlayerMgr::del(const std::vector<std::string> &vFiles)
{
	m_mciPlayer.stop();
	std::vector<std::string> vDelFiles;
	for(std::vector<std::string>::const_iterator citr=vFiles.begin();
		citr!=vFiles.end(); ++citr)
	{
		vDelFiles.push_back(m_strRoot + (*citr));
	}
	if(delFiles(vDelFiles)){
		// 更新当前文件
		findFiles(m_strRoot, m_vAllFiles);
		m_mciPlayer.updatePlayList(m_vAllFiles);
		return true;
	}else{
		return false;
	}
}

std::vector<std::string> CMCIPlayerMgr::getFilesPath(const std::vector<std::string> &vFiles)
{
	std::vector<std::string> vPaths;
	for(std::vector<std::string>::const_iterator citr=vFiles.begin();
		citr!=vFiles.end(); ++citr)
	{
		vPaths.push_back(m_strRoot + (*citr));
	}
	return vPaths;
}

void CMCIPlayerMgr::findFiles( const std::string &strFolder, std::vector<std::string> &vFiles )
{
	vFiles.clear();
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
			// 只处理文件后缀是wav的文件
			std::string strPostfix = strFileName.substr(iDotIndex+1, strFileName.length());
			std::transform(strPostfix.begin(), strPostfix.end(), strPostfix.begin(), tolower);
			if( iDotIndex != -1 && (strPostfix == "wav") )
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

int CMCIPlayerMgr::copyFile(const std::string &fromFile, const std::string &toFile)
{
	return CopyFile(fromFile.c_str(), toFile.c_str(), FALSE);// 复制文件，如果文件存在则覆盖
}

int CMCIPlayerMgr::copyFiles(const std::string &fromPath, const std::string &toPath, 
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

std::string CMCIPlayerMgr::getRightPath(const std::string &path)
{
	return *path.rbegin()=='\\' ?  path : (path + '\\');
}

int CMCIPlayerMgr::delFile(const std::string &file)
{
	return DeleteFile(file.c_str());
}

int CMCIPlayerMgr::delFiles(const std::vector<std::string> &vFiles)
{
	bool flag = true;
	for(size_t i=0; i<vFiles.size(); i++){
		// 删除文件
		if(!DeleteFile(vFiles[i].c_str()))
			flag = false;
	}
	return flag ? 1 : 0;
}

std::string CMCIPlayerMgr::getCurrentName()
{
	std::string file = m_mciPlayer.getCurrentName();
	return file.substr(file.find_last_of('\\')+1, file.length());
}