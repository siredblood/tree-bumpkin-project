#include "pch.hpp"
#include "buildingSchemeManager.h"
#include "buildingSchemeDatabase.h"
#include "world/editor_chunk.hpp"
#include "editor/chunk_item_placer.hpp"
#include <atlimage.h>
#include "AddBuildingSchemeDlg.h"
#include "common/utilities.hpp"
#include "CameraTravel/CustomWorldCamera.h"

BuildingSchemeManager* BuildingSchemeManager::mInstance = NULL;

BuildingSchemeManager::BuildingSchemeManager()
{

	//TaskManager::instance().add( this, "BuildingSchemeManager", NULL );
	init();
}

BuildingSchemeManager::~BuildingSchemeManager()
{

}

BuildingSchemeManager* BuildingSchemeManager::getInstance()
{
	if(mInstance==NULL)
	{
		mInstance = new BuildingSchemeManager;
	}
	return mInstance;
}

void BuildingSchemeManager::init()
{
	INFO_MSG("BuildingSchemeManager::init\n");
	loadScheme();
}

void BuildingSchemeManager::loadScheme()
{
	BuildingSchemeDatabase database;
	database.loadScheme(mReplaceScheme);
}

void BuildingSchemeManager::saveScheme()
{

}

void BuildingSchemeManager::addScheme( CString strSchemeName, std::map<CString, CString> vReplacelist )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter==mReplaceScheme.end())
	{
		mReplaceScheme.insert(std::pair<CString, replaceList>(strSchemeName, vReplacelist));
	}
	else
	{
		std::map<CString, CString>::iterator childIter;
		for(childIter=vReplacelist.begin(); childIter!=vReplacelist.end(); childIter++)
		{
			iter->second.insert( std::pair<CString, CString>(childIter->first,childIter->second) );
		}
	}
	BuildingSchemeDatabase database;
	std::map<CString, CString>::iterator childIter;
	for(childIter=vReplacelist.begin(); childIter!=vReplacelist.end(); childIter++)
	{
		database.addScheme(strSchemeName, childIter->first, childIter->second);
	}
}

void BuildingSchemeManager::addScheme( CString strSchemeName, CString strOldModel, CString strNewModel )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter==mReplaceScheme.end())
	{
		replaceList list;
		list.insert( std::pair<CString, CString>(strOldModel, strNewModel) );
		mReplaceScheme.insert( std::pair<CString, replaceList>(strSchemeName, list) );
	}
	else
	{
		iter->second.insert( std::pair<CString, CString>(strOldModel, strNewModel) );
	}
	BuildingSchemeDatabase database;
	database.addScheme(strSchemeName, strOldModel, strNewModel);
}

void BuildingSchemeManager::deleteScheme( CString strSchemeName )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter!=mReplaceScheme.end())
	{
		mReplaceScheme.erase( iter );
		BuildingSchemeDatabase database;
		database.deleteScheme(strSchemeName);
	}
}

void BuildingSchemeManager::deleteScheme( CString strSchemeName, CString strOldModel )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter!=mReplaceScheme.end())
	{
		replaceList::iterator childIter = iter->second.find(strOldModel);
		if(childIter!=iter->second.end())
		{
			iter->second.erase(childIter);
		}
		BuildingSchemeDatabase database;
		database.deleteScheme(strSchemeName, strOldModel);

	}

}

void BuildingSchemeManager::deleteSchemeByModel( CString strModel )
{
	std::map<CString, replaceList>::iterator iter;
	for(iter=mReplaceScheme.begin(); iter!=mReplaceScheme.end(); iter++)
	{
		replaceList::iterator childIter = iter->second.find( strModel );
		if(childIter!=iter->second.end())
		{
			iter->second.erase(childIter);
		}
		BuildingSchemeDatabase database;
		database.deleteScheme(iter->first, strModel);
	}
}


void BuildingSchemeManager::executeScheme( CString strSchemeName )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter!=mReplaceScheme.end())
	{
		replaceList list = iter->second;
		for(replaceList::iterator childIter=list.begin(); childIter!=list.end(); childIter++)
		{
			ChunkItemPtr oldItem = findItem( childIter->first );
			if(oldItem!=NULL)
			{
				//怎么获取对象的坐标、面向、缩放
				Matrix mat = oldItem->chunk()->transform();
				mat.preMultiply(oldItem->edTransform());

				Vector3 pos, dir, scale;
				Utilities::decompose(mat, scale, pos, dir);

				pos = mat.applyToOrigin();
				//dir = mat.applyToUnitAxisVector(2);

				float yaw = mat.yaw();
				float pitch = mat.pitch();
				float roll = mat.roll();

				if(yaw<0)
					yaw += MATH_2PI;
				if(roll >= -0.001 && roll <= 0.001)
					roll = 0.f;

				//INFO_MSG("%f,%f,%f\n", yaw, pitch, roll);

				dir = Vector3(RAD_TO_DEG(pitch), RAD_TO_DEG(yaw), RAD_TO_DEG(roll) );
				
				//pos = mat.applyToOrigin();
				CString strPath = childIter->second;
				ChunkItemPtr newItem = ChunkItemPlacer::createDBChunkItem(
					strPath.GetBuffer(), oldItem->edGUID(), pos,
					dir, scale );

				//oldItem->edPreDelete();	//删除原来的模型
				oldItem->chunk()->delStaticItem( oldItem );
			}
		}
		
	}
}

std::map<CString, std::map<CString, CString>> BuildingSchemeManager::getAllScheme()
{
	return mReplaceScheme;
}

std::vector<CString> BuildingSchemeManager::getAllSchemeName()
{
	std::vector<CString> vAllName;
	std::map<CString, replaceList>::iterator iter;
	for(iter=mReplaceScheme.begin(); iter!=mReplaceScheme.end(); iter++)
	{
		vAllName.push_back( iter->first );
	}
	return vAllName;
}

std::map<CString, CString> BuildingSchemeManager::getReplaceList( CString strSchemeName )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter!=mReplaceScheme.end())
	{
		return iter->second;
	}

	replaceList nulllist;
	return nulllist;
}

ChunkItemPtr BuildingSchemeManager::findItem( CString strGuid )
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

void BuildingSchemeManager::handleKeyEvent( const KeyEvent & event )
{
	//INFO_MSG("BuildingSchemeManager::handleKeyEvent\n");
	//switch (event.key())
	//{
	//case KeyEvent::KEY_T:
	//	//给对象添加方案
	//	std::vector<ChunkItemPtr> vSelItems = WorldManager::instance().selectedItems();
	//	if(vSelItems.size()==1)
	//	{
	//		std::string strGuid = vSelItems[0]->edGUID();
	//		AddBuildingSchemeDlg::getInstance()->ShowWindow(SW_SHOW);
	//		AddBuildingSchemeDlg::getInstance()->setSelectedModel(strGuid);
	//	}
	//	break;
	//}
}

void BuildingSchemeManager::locateToModel( CString strModel )
{
	ChunkItemPtr pModelItem = findItem(strModel);
	if(pModelItem)
	{
		INFO_MSG("定位到模型\n");
		CCustomWorldCamera::Instance().TeleportToTar(pModelItem);
	}
}


