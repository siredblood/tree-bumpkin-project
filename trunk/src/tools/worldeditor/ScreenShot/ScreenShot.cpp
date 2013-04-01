#include "pch.hpp"
#include "ScreenShot.hpp"
#include "GeneralClass/Common.h"
#include "framework/mainframe.hpp"

ScreenShot ScreenShot::instance_;

ScreenShot::ScreenShot(void)
: bSreen_(false)
, strPicType_( "jpg" )
, strSaveFolder_( "" )
, index_( 1 )
{
	TaskManager::instance().add( this, "ScreenShot", NULL );
}

ScreenShot::~ScreenShot(void)
{
}
	
ScreenShot &ScreenShot::Instance()
{
	return instance_;
}

void ScreenShot::tick( float dTime )
{
	if(!bSreen_)
		return;

	std::ostringstream fileName;
	fileName << strSaveFolder_ << "\\" << index_;
	
	Moo::rc().screenShot( strPicType_, fileName.str(), false );
	
	index_++;
}

void ScreenShot::BeginScreen()
{
	if( bSreen_ )
		return;
		
	bSreen_ = true;
	index_ = 1;
}

void ScreenShot::EndScreen()
{
	bSreen_ = false;
}

void ScreenShot::handleKeyEvent( const KeyEvent & event )
{	
	switch (event.key())
	{
		case KeyEvent::KEY_F12:
		{
			if (event.isCtrlDown() && event.isKeyDown())
			{
				if ( !bSreen_ )
				{
					CheckAndCreateFolder();
					ScreenShot::Instance().BeginScreen();
				}
				else
				{
					ScreenShot::Instance().EndScreen();	
				}
			}
			break;
		}
		case KeyEvent::KEY_ESCAPE:
			{
				MainFrame *pFrame=(MainFrame*)AfxGetApp()->m_pMainWnd;
				pFrame->OnClose();
			}
	}
}

void ScreenShot::CheckAndCreateFolder()
{
	std::ostringstream mainFolderName;
	mainFolderName << g_strExeFullPath.GetBuffer( 0 ) << "\\ScreenShot";
	CreateDirectory( mainFolderName.str().c_str(), NULL );

	static uint32 sequence = 1;
	bool foundFolder = false;
	
	while ( !foundFolder )
	{
		std::ostringstream folderName;
		folderName << mainFolderName.str() << "\\" << sequence;
		
		strSaveFolder_ = folderName.str();

		if ( !BWResource::fileAbsolutelyExists( strSaveFolder_ ))
		{
			foundFolder = true;
			CreateDirectory( strSaveFolder_.c_str(), NULL );
		}		
		else
		{
			sequence++;
		}
	}
}