// MessageRecord.h: interface for the CMessageRecord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
#define AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////////
// This class is your main custom Record class which you'll manipulate with.
// It contains any kind of specific methods like different types of constructors,
// any additional custom data as class members, any data manipulation methods.
class CMessageRecord : public CXTPReportRecord
{
	DECLARE_SERIAL(CMessageRecord)
public:
	CMessageRecord();

	// Construct record object using empty values on each field
	//创建空行构造函数，i是列数
	CMessageRecord(BOOL mbool,int i);

	// Construct record object from detailed values on each field
	CMessageRecord(int i...);

	// Construct record object from CMessageRecord object
	CMessageRecord(CMessageRecord* pRecord);

	CMessageRecord& operator= (const CMessageRecord& x);

	// Clean up internal objects
	virtual ~CMessageRecord();

	// Create record fields using empty values
	virtual void CreateItems(int i);

	//创建单项
	virtual void CreateSingeleItems(CString sinItem);
	virtual void CreateSingeleItems(COleDateTime sinItem);
	//创建checkbox项
	virtual void CreateCheckBoxItems(BOOL bCheck);

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);
};

#endif // !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
class CTaskItemDueDateGV : public CXTPReportRecordItemDateTime
{
public:
	CTaskItemDueDateGV(COleDateTime dtDateTime)
		: CXTPReportRecordItemDateTime(dtDateTime)
	{
		m_strFormatString = _T("%Y-%m-%d");
	}
	CString GetCaption(CXTPReportColumn* /*pColumn*/)
	{
		if ((DATE)m_odtValue == 0)
			return _T("None");

		return m_odtValue.Format(m_strFormatString);
	}
};
typedef enum MESSAGE_IMPORTANCE
{
	msgImportanceNormal,
	msgImportanceHigh,
	msgImportanceLow
};

class CMessageRecordItemCheck : public CXTPReportRecordItem
{
	DECLARE_SERIAL(CMessageRecordItemCheck)
public:
	// Constructs record item with the initial checkbox value.
	CMessageRecordItemCheck(BOOL bCheck = FALSE);
};