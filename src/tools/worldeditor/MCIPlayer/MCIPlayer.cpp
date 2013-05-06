#include "pch.hpp"
#include "MCIPlayer.h"

CMCIPlayer::CMCIPlayer()
: m_uiElementID(0)
, m_uiDeviceID(0)
, m_hWnd(NULL)
, m_iCurrent(0)
{

}

CMCIPlayer::~CMCIPlayer()
{
	if(m_uiElementID != 0){  
		stop();  
	}  
	if(m_uiDeviceID != 0){  
		closeDevice();  
	} 
}

void CMCIPlayer::init(HWND hWnd)
{
	m_hWnd = hWnd;
	openDevice();
}

DWORD CMCIPlayer::openDevice()
{
	DWORD dwResult=0;  

	if (m_uiDeviceID == 0){  
		MCI_OPEN_PARMS mciOpenParms;  
		ZeroMemory(&mciOpenParms, sizeof(mciOpenParms));  

		//mciOpenParms.lpstrDeviceType = (LPCTSTR)MCI_DEVTYPE_WAVEFORM_AUDIO;  
		mciOpenParms.lpstrDeviceType = (LPCTSTR)MCI_DEVTYPE_SEQUENCER;  

		//open the wave device  
		dwResult = mciSendCommand(NULL,  
			MCI_OPEN,  
			MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_WAIT,  
			(DWORD)(LPVOID)&mciOpenParms);  

		//save device identifier,will use eith other MCI commands  
		m_uiDeviceID = mciOpenParms.wDeviceID;  

	}  
	
	return dwResult; 
}

DWORD CMCIPlayer::closeDevice()  
{  
	DWORD dwResult=0;  

	//close if currently open  
	if(m_uiDeviceID){  
		//close the MCI device  
		dwResult = mciSendCommand(m_uiDeviceID, MCI_CLOSE, NULL, NULL);  

		//display error message if failed  
		if(!dwResult){  
			m_uiDeviceID=0;  
		}  
	}  

	return dwResult;  
}

DWORD CMCIPlayer::play(const std::vector<std::string> &vFiles)
{
	updatePlayList(vFiles);
	if(m_vFiles.empty())
		return 0;

	return play(m_vFiles[m_iCurrent]);  
}

DWORD CMCIPlayer::play(const std::string &strMusicPath/* = */)
{
	DWORD dwResult = 0;
	if(!strMusicPath.empty()){
		stop();

		MCI_OPEN_PARMS mciOpenParms;  
		//initialize structure  
		memset(&mciOpenParms,0,sizeof(MCI_OPEN_PARMS));  

		//set the WAV file name to be played  
		mciOpenParms.lpstrElementName = strMusicPath.c_str();  

		//first open the device  
		dwResult = mciSendCommand(m_uiDeviceID,MCI_OPEN,  
			MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciOpenParms);  

		if(dwResult!=0){  
			return dwResult;  
		}else{  
			//save element indentifier  
			m_uiElementID = mciOpenParms.wDeviceID;  
		}  
	}  

	MCI_PLAY_PARMS mciPlayParms;  

	//set the window that will receive notification message  
	mciPlayParms.dwCallback = (DWORD)m_hWnd;  

	//instruct device to play file  
	dwResult=mciSendCommand(m_uiElementID,MCI_PLAY,  
		MCI_NOTIFY,(DWORD)(LPVOID)&mciPlayParms);  

	//display error and close element if failed  
	if(dwResult!=0){
		stop();  
	}  

	return dwResult;  
}

DWORD CMCIPlayer::replay()
{
	m_iCurrent = 0;
	return play(m_vFiles);
}

DWORD CMCIPlayer::pause()
{
	DWORD dwResult=0;
	if(m_uiElementID!=0){
		dwResult = mciSendCommand(m_uiElementID, MCI_PAUSE, 0, NULL);
	}

	return dwResult;
}

DWORD CMCIPlayer::resume()
{
	DWORD dwResult=0;
	if(m_uiElementID!=0){
		dwResult = mciSendCommand(m_uiElementID, MCI_RESUME, 0, NULL);
	}

	return dwResult;
}

DWORD CMCIPlayer::stop()
{
	DWORD dwResult=0;  

	//close if element is currently open  
	if(m_uiElementID != 0){  
		dwResult=mciSendCommand(m_uiElementID,MCI_CLOSE,NULL,NULL);  

		//display error message if failed  
		if(dwResult == 0) {  
			m_uiElementID=0;  
		}  
	}  
	return dwResult;  
}

DWORD CMCIPlayer::next()
{
	if(m_vFiles.empty()) return 0;

	// 对一个文件进行优化处理
	if(m_vFiles.size()==1){
		repeat();
		return 0;
	}

	if(++m_iCurrent>=m_vFiles.size()){
		m_iCurrent = 0;
	}
	return play(m_vFiles[m_iCurrent]);
}

DWORD CMCIPlayer::prev()
{
	if(m_vFiles.empty()) return 0;

	// 对一个文件进行优化处理
	if(m_vFiles.size()==1){
		repeat();
		return 0;
	}

	if(m_iCurrent!=0){
		--m_iCurrent ;
	}
	return play(m_vFiles[m_iCurrent]);
}

DWORD CMCIPlayer::repeat()  
{  
	DWORD dwResult=0;  

	//close if element is currently open  
	if(m_uiElementID != 0) {  
		MCI_SEEK_PARMS seekParam;  
		ZeroMemory(&seekParam, sizeof(seekParam));  
		dwResult=mciSendCommand(m_uiElementID,  
			MCI_SEEK,  
			MCI_SEEK_TO_START,  
			(DWORD)&seekParam);

		play();
	}  
	return dwResult;  
} 

void CMCIPlayer::getMusicInfo(DWORD dwParam, DWORD &info)
{
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback=NULL;

	mcistatusparms.dwItem = dwParam;//接受命令参数的地方
	mcistatusparms.dwReturn = 0;

	mciSendCommand(m_uiDeviceID, MCI_STATUS,MCI_STATUS_ITEM, (DWORD)&mcistatusparms);
	info = mcistatusparms.dwReturn;
}

bool CMCIPlayer::isFinish()
{
	DWORD dwMediaLength;
	DWORD dwMediaPlayPos;
	getMusicInfo(MCI_STATUS_LENGTH, dwMediaLength);
	getMusicInfo(MCI_STATUS_POSITION, dwMediaPlayPos);
	if(dwMediaPlayPos == dwMediaLength){
		return true;
	}else{
		return false;
	}
}

std::string CMCIPlayer::getCurrentName()
{
	if(m_vFiles.empty())
		return "";
	return m_vFiles[m_iCurrent];
}

void CMCIPlayer::updatePlayList(const std::vector<std::string> &vFiles)
{
	stop();
	m_vFiles = vFiles;
	m_iCurrent = 0;
}