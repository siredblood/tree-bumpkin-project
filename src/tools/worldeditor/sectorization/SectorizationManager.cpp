#include "pch.hpp"
#include "SectorizationManager.h"
#include "CameraTravel/CustomWorldCamera.h"
#include "SectorizationDatabase.h"
#include "world/editor_chunk.hpp"
//#include "GeneralClass/Common.h"

SectorizationManager * SectorizationManager::instance = NULL;

SectorizationManager::SectorizationManager()
{
	init();
}

SectorizationManager::~SectorizationManager()
{

}

SectorizationManager* SectorizationManager::getInstance()
{
	if(instance==NULL)
	{
		instance = new SectorizationManager;
	}
	return instance;
}

void SectorizationManager::init()
{
	loadSectorization();
}

void SectorizationManager::loadSectorization()
{
	SectorizationDatabase database;
	database.loadSectorization(m_vSectorizationData);
}

void SectorizationManager::addSectorization( CString strName, Vector3 viewpos, Vector3 viewdir )
{
	std::vector<SECTORIZATIONDATA>::iterator itr;
	for(itr=m_vSectorizationData.begin(); itr!=m_vSectorizationData.end(); itr++)
	{
		if(itr->strName==strName)
			break;
	}
	if(itr!=m_vSectorizationData.end())
		return;

	SECTORIZATIONDATA item;
	item.strName = strName;
	item.viewpos = viewpos;
	item.viewdir = viewdir;

	m_vSectorizationData.push_back(item);

	SectorizationDatabase database;
	database.addSectorization(strName, viewpos, viewdir);
}

void SectorizationManager::editSectorizationViewport(CString strName, Vector3 viewpos, Vector3 viewdir)
{
	std::vector<SECTORIZATIONDATA>::iterator itr;
	for(itr=m_vSectorizationData.begin(); itr!=m_vSectorizationData.end(); itr++)
	{
		if(itr->strName==strName)
			break;
	}
	if(itr==m_vSectorizationData.end())
		return;

	itr->viewdir = viewdir;
	itr->viewpos = viewpos;

	SectorizationDatabase database;
	database.editSectorization(strName, viewpos, viewdir);
}

void SectorizationManager::addSectorizationObject( CString strName, CString strGuid )
{
	std::vector<SECTORIZATIONDATA>::iterator itr;
	for(itr=m_vSectorizationData.begin(); itr!=m_vSectorizationData.end(); itr++)
	{
		if(itr->strName==strName)
			break;
	}
	if(itr==m_vSectorizationData.end())
		return;

	itr->vGuids.push_back(strGuid);

	SectorizationDatabase database;
	database.addSectorizationObject(strName, strGuid);
}

void SectorizationManager::deleteSectorization( CString strName )
{
	std::vector<SECTORIZATIONDATA>::iterator itr;
	for(itr=m_vSectorizationData.begin(); itr!=m_vSectorizationData.end(); itr++)
	{
		if(itr->strName==strName)
			break;
	}
	if(itr!=m_vSectorizationData.end())
	{
		m_vSectorizationData.erase(itr);

		SectorizationDatabase database;
		database.deleteSectorization(strName);
	}
}

void SectorizationManager::deleteSectorizationObject( CString strName, CString strGuid )
{
	std::vector<SECTORIZATIONDATA>::iterator itr;
	for(itr=m_vSectorizationData.begin(); itr!=m_vSectorizationData.end(); itr++)
	{
		if(itr->strName==strName)
			break;
	}
	if(itr==m_vSectorizationData.end())
		return;
	
	std::vector<CString>::iterator subitr =  itr->vGuids.begin();
	for(;subitr!=itr->vGuids.end(); subitr++)
	{
		if( *subitr==strGuid )
			break;
	}
	if(subitr!=itr->vGuids.end())
	{
		itr->vGuids.erase(subitr);

		SectorizationDatabase database;
		database.deleteSectorizationObject(strName, strGuid);
	}
	
}

void SectorizationManager::showSectorization( CString strName )
{
	std::vector<SECTORIZATIONDATA>::iterator itr;
	for(itr=m_vSectorizationData.begin(); itr!=m_vSectorizationData.end(); itr++)
	{
		std::vector<CString> vGuids = itr->vGuids;
		if(itr->strName==strName)
		{
			//是当前分区则显示
			CCustomWorldCamera::Instance().TeleportCamera(itr->viewpos, itr->viewdir);
			int isize = vGuids.size();
			for(int i=0; i<isize; i++)
			{
				ChunkItemPtr item = findItem(vGuids[i]);
				if(item)
				{
					item->edSetShouldDraw(true);
				}
			}
		}
		else
		{
			//否则隐藏
			int isize = vGuids.size();
			for(int i=0; i<isize; i++)
			{
				ChunkItemPtr item = findItem(vGuids[i]);
				if(item)
				{
					item->edSetShouldDraw(false);
				}
			}
		}
	}
}

ChunkItemPtr SectorizationManager::findItem( CString strGuid )
{
	ChunkItemPtr pResultItem=NULL;
	std::vector<ChunkItemPtr> items;
	for( std::set<Chunk*>::iterator iter = EditorChunkCache::chunks_.begin();
		iter != EditorChunkCache::chunks_.end(); ++iter )
	{

		items = EditorChunkCache::instance( **iter ).staticItems();
		for(std::vector<ChunkItemPtr>::iterator itrItems = items.begin(); itrItems != items.end(); ++itrItems)
		{
			std::string strTMP = (*itrItems)->edGUID();
			if( !strTMP.compare( strGuid.GetBuffer() ) )
			{
				pResultItem = *itrItems;
				break;
			}
		}
		if(pResultItem!=NULL)
			break;
	}
	return pResultItem;
}

void SectorizationManager::locateToModel( CString strModel )
{
	ChunkItemPtr pModelItem = findItem(strModel);
	if(pModelItem)
	{
		INFO_MSG("定位到模型\n");
		CCustomWorldCamera::Instance().TeleportToTar(pModelItem);
	}
}
