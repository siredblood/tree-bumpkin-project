#pragma once

#include <afxwin.h>

/**
 *	Used by all tools to make ParseCommandLine work with the --res/-r options.
 */
struct MFCommandLineInfo : public CCommandLineInfo
{
	MFCommandLineInfo() :
		resPath(""),
		wasRes(false)
	{}
	
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
	{
		bool processed = false;
		if (wasRes)
		{
			resPath   = pszParam;
			wasRes    = false;
			processed = true;
		}
		if (bFlag)
		{
			CString param(pszParam);
			if (param == "-res" || param == "r")
			{
				wasRes = true;
				processed = true;
			}
			else if (param == "o" )
				processed = true;
		}
		if (!processed)
		{
			CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
		}
	}
	
	CString resPath;
	bool wasRes;
};
