#include "pch.hpp"
#include "HideAndShowObject.h"
#include "GeneralClass/Common.h"

CHideAndShowObject CHideAndShowObject::instance;

CHideAndShowObject::CHideAndShowObject(void)
	{
	}

CHideAndShowObject::~CHideAndShowObject(void)
	{
	}

CHideAndShowObject &CHideAndShowObject::Instance()
{
	return instance;
}

void CHideAndShowObject::HideObject( std::vector<ChunkItemPtr> vSelItems )
{
	int iSize = vSelItems.size();

	for(int i=0; i<iSize; i++)
	{
		CancelSeleteItem( vSelItems[i] );
		vSelItems[i]->edSetShouldDraw( false );
		m_vAllHidedObject.push_back( vSelItems[i] );
	}
}

void CHideAndShowObject::ShowLastObject()
{
	int iSize = m_vAllHidedObject.size();
	if(iSize<=0)
		return;
	
	m_vAllHidedObject[iSize-1]->edSetShouldDraw( true );
	m_vAllHidedObject.pop_back();
}

void CHideAndShowObject::ShowAllHidedObject()
{
	int iSize = m_vAllHidedObject.size();
	for( int i=0; i<iSize; i++)
	{
		m_vAllHidedObject[i]->edSetShouldDraw( true );
	}
	m_vAllHidedObject.clear();
}

int CHideAndShowObject::GetHidedObjectSize()
{
	return m_vAllHidedObject.size();
}