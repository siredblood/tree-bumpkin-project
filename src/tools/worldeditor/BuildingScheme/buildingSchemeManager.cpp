#include "pch.hpp"
#include "buildingSchemeManager.h"

BuildingSchemeManager* BuildingSchemeManager::mInstance = NULL;

BuildingSchemeManager::BuildingSchemeManager()
{

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
	loadScheme();
}

void BuildingSchemeManager::loadScheme()
{

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
}

void BuildingSchemeManager::deleteScheme( CString strSchemeName )
{
	std::map<CString, replaceList>::iterator iter;
	iter = mReplaceScheme.find( strSchemeName );
	if(iter!=mReplaceScheme.end())
	{
		mReplaceScheme.erase( iter );
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
	}
}

void BuildingSchemeManager::executeScheme( CString strSchemeName )
{

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
