#include "pch.hpp"
//#include "app.hpp"
#include "MarkManage.h"
#include "BLogicLib/BllHelper.h"
#include "GeneralClass/Common.h"
#include "worldeditor/world/world_manager.hpp"
#include "worldeditor/Editor/chunk_item_placer.hpp"
//#include "../place/place_manage.hpp"

CMarkManage CMarkManage::instance;

CMarkManage::CMarkManage(void)
{
	/*m_szFile = "scripts/MarkManage.xml";*/
}

CMarkManage::~CMarkManage(void)
{
}

CMarkManage &CMarkManage::Instance()
{
	return instance;
}

//�����ע������ע���ƣ����꣬������Ϊ0��1��1��ʾ�Ѿ����ڵĶ���ı�ע��0��ʾ����λ�õı�ע����
void CMarkManage::AddMarkMessage( const Vector3& pos, const std::string& name, const std::string& guid )
{
	MARKDATA markdata;
	markdata.pos = pos;
	markdata.bHaveObject = true;
	markdata.strText = name;
	markdata.strGUID = guid;
	markdata.strType = "1";
	markdata.strCreator = g_strSysUserName.GetBuffer(0);
	markdata.fViewDist = 10.0f;
	
	AddMarkMessage( markdata );
}


void CMarkManage::AddMarkMessage(MARKDATA markdata)
{
	if( markdata.strType.length()==0)
		return;

	//����λ�ñ�ע���������ǰ�洴��һ������
	if( markdata.strType=="0" )
	{

		ChunkItemPtr pMarkitem = ChunkItemPlacer::createDBChunkItem( "sets/items/information.model", markdata.strGUID, 
			markdata.pos.x,markdata.pos.y-1,markdata.pos.z,0.0,0.0,0.0,1.0,1.0,1.0 );
		if(pMarkitem==NULL)
		{
			markdata.bHaveObject = false;
			CMarkObject::Instance().AddDrawMessage(markdata);
		}
		else
		{
			BoundingBox box;
			Matrix mat = pMarkitem->chunk()->transform();
			mat.preMultiply(pMarkitem->edTransform());
			pMarkitem->edSelectedBox( box );
			box.transformBy( mat );
			Vector3 centre = box.centre();
			float fBottom = (centre - mat.applyToOrigin()).length() - box.height()/2;

			Vector3 pos = markdata.pos - Vector3(0, box.height() + fBottom + 1.0f, 0);
			MoveItemToPos(pMarkitem, pos, Vector3(0,0,0) );

			markdata.bHaveObject = true;
			if(markdata.strGUID.length()==0)
				markdata.strGUID = pMarkitem->edGUID();
			CMarkObject::Instance().AddDrawMessage( markdata );
			CMarkObject::Instance().m_vAllMarkIcon.push_back(pMarkitem);
		}
	}
	else
	{
		if(markdata.strGUID.length()==0)
		{
			return;
		}	
		
		markdata.bHaveObject = true;
		CMarkObject::Instance().AddDrawMessage( markdata );
	}
}

void CMarkManage::DeleteMarkByGUID(const std::string &strGUID)
{
	if (strGUID.length()==0)
	{
		return;
	}
	CString myGuid;
	myGuid=strGUID.c_str();
	CLableMarker lableMaker;
	if (lableMaker.Delete(myGuid.GetBuffer()))
	{
		CMarkObject::Instance().DeleteMark(strGUID);
	}
}

//�������ݿ������еı�ע
void CMarkManage::LoadMarks()
{
	int iMarkSize = CMarkObject::Instance().m_vAllMarkIcon.size();
	for(int i=0; i<iMarkSize; i++)
	{
		CancelSeleteItem( CMarkObject::Instance().m_vAllMarkIcon[i] );
		CMarkObject::Instance().m_vAllMarkIcon[i]->chunk()->delStaticItem( CMarkObject::Instance().m_vAllMarkIcon[i] );
	}
	CMarkObject::Instance().m_vAllMarkIcon.clear();
	CMarkObject::Instance().ClearAllMark();

	CLableMarker lableMaker;
	std::vector<LABLESTRUCT> dataLables=lableMaker.LoadLableMark( g_strImportantTarget.GetBuffer(0) );
	CString strPos;
	Vector3 pos;
	MARKDATA markdata;
	
	for ( std::vector <LABLESTRUCT>::iterator lable = dataLables.begin(); lable != dataLables.end(); lable++ )//������Ϣ��ע
	{
		strPos = lable->strPos.c_str();
		pos = ConvertStrToVec3( strPos.GetBuffer(0) );
		markdata.strText = lable->strText;
		markdata.pos = pos;
		markdata.strGUID = lable->strGUID;
		markdata.strType = lable->strType;
		markdata.bHaveObject = false;
		markdata.strCreator = lable->strCreator;
		markdata.strCreateTime = lable->strCreatTime;
		markdata.fViewDist = lable->fEyeable;
		
		AddMarkMessage( markdata );
	}
}

void CMarkManage::CStringToVector3(CString strOrg,Vector3 &v3Aim)
{
	int nPos = 0;
	CString str1,str2,str3;
	str1 = strOrg.Tokenize(",",nPos);//�Զ��ŷָ��������ַ���
	str2 = strOrg.Tokenize(",",nPos);
	str3 = strOrg.Tokenize(",",nPos);
	double dX;
	double dY;
	double dZ;
	dX = ::atof(str1.GetBuffer());
	dY = ::atof(str2.GetBuffer());
	dZ = ::atof(str3.GetBuffer());

	dY += 1.1f;
	v3Aim = Vector3((float)dX,(float)dY,(float)dZ);
}

//�������б�ע��Ϣ
void CMarkManage::SaveMarks()
{
	std::vector<MARKDATA> vMarkData = CMarkObject::Instance().GetDrawMessage();
	std::vector<LABLESTRUCT> vDataLables;
	LABLESTRUCT Lable;
	CString strPos;
	
	int iMarkDataSize = vMarkData.size();
	for(int i=0; i<iMarkDataSize; i++)
	{
		Lable.strGUID = vMarkData[i].strGUID;
		Lable.strText = vMarkData[i].strText;
		Lable.strType = vMarkData[i].strType;
		Lable.strPos = ConvertVec3ToStr( vMarkData[i].pos);
		Lable.strCreator = vMarkData[i].strCreator;
		Lable.strCreatTime = vMarkData[i].strCreateTime;
		Lable.strTarget = g_strImportantTarget;
		Lable.fEyeable = vMarkData[i].fViewDist;
		vDataLables.push_back( Lable );
	}
	CLableMarker lableMaker;
	if( !lableMaker.Save( vDataLables ) )
		AfxMessageBox("��ע����ʧ��");
}

void CMarkManage::ReleaseMark()
{
	CMarkObject::Instance().ClearAllMark();
}
