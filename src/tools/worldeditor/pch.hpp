#ifndef WE_PCH_HPP
#define WE_PCH_HPP

// pch.hpp : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#pragma warning(disable:4786)	// remove "truncated identifier" warnings from STL

#define EDCALL __stdcall
#define WORLDEDITORDLL_API 

//#include <afxsock.h>
#include "GeneralClass/PublicVariable.h"

#include "cstdmf/pch.hpp"
#include "resmgr/pch.hpp"
#include "pyscript/pch.hpp"
#include "worldeditor/config.hpp"
#include "worldeditor/forward.hpp"
#include "worldeditor/world/world_manager.hpp"
#include <afxdlgs.h>
#include <XTToolkitPro.h>



#endif // WE_PCH_HPP
