// MessageRecord.cpp: implementation of the CMessageRecord class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.hpp"
#include "MessageRecord.h"
#include "cstdarg"//动态参数头文件

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// CMessageRecord class

IMPLEMENT_SERIAL(CMessageRecord, CXTPReportRecord, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)
IMPLEMENT_SERIAL(CMessageRecordItemCheck, CXTPReportRecordItem, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMessageRecord::CMessageRecord()
{
}

CMessageRecord::CMessageRecord(BOOL mbool,int i)
{
	CreateItems(i);
}

CMessageRecord::CMessageRecord(int i...)
{
	va_list ap;//动态参数列表
	va_start(ap,i);

	//动态字符串数组
	//CString *s;
	//s = new CString[i];

	for(int j = 0;j < i;j++)
	{
		AddItem(new CXTPReportRecordItemText(va_arg(ap,CString)));
	}
	va_end(ap);
}

CMessageRecord::CMessageRecord(CMessageRecord* pRecord)
{
	for(int i = 0; i < 3; i++)
	{
		AddItem(new CXTPReportRecordItemText(((CXTPReportRecordItemText*)pRecord->GetItem(i))->GetValue()));
	}
}

CMessageRecord& CMessageRecord::operator= (const CMessageRecord& x)
{
	for(int i = 0; i < GetItemCount(); i++)
	{
		((CXTPReportRecordItemText*)GetItem(i))->SetValue(((CXTPReportRecordItemText*)x.GetItem(i))->GetValue());
	}

	return *this;
}

void CMessageRecord::CreateItems(int i)
{
	// Initialize record items with empty values
	for (int j = 0;j < i;j++)
	{
		AddItem(new CXTPReportRecordItemText(_T("")));
	}
}

void CMessageRecord::CreateSingeleItems(CString sinItem)
{
	// Initialize record items with empty values
	
	AddItem(new CXTPReportRecordItemText(sinItem));

}
void CMessageRecord::CreateCheckBoxItems(BOOL bCheck)
{
	AddItem(new CMessageRecordItemCheck(bCheck));
}

void CMessageRecord::CreateSingeleItems(COleDateTime sinItem)
{
	// 插入日期格式
	AddItem(new CTaskItemDueDateGV(sinItem));

}
CMessageRecord::~CMessageRecord()
{
}

void CMessageRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPReportRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}
CMessageRecordItemCheck::CMessageRecordItemCheck(BOOL bCheck)
{
	HasCheckbox(TRUE);
	SetChecked(bCheck);
}

