#include "pch.hpp"

#include "tools_common.hpp"
#include "compile_time.hpp"

#include "controls/message_box.hpp"
#include "resmgr/string_provider.hpp"


//Uncomment the following line to build the evaluation version...
//#define BW_EVALUATION 1
static const int DEADDATE = 20091201;
/**
 *	This function returns whether or not the tool can run.
 */
/*static*/ bool ToolsCommon::canRun()
{
	return true;
}

/*static*/ bool ToolsCommon::isEval()
{
	return false;
}

#include <windows.h>

/*static*/ void ToolsCommon::outOfDateMessage( const std::string& toolName )
{
	MessageBox( NULL, 
		L("COMMON/TOOLS_COMMON/EXPIRED", toolName, aboutCompileTimeString ), 
		L("COMMON/TOOLS_COMMON/TOOL_EXPIRED"),
		MB_OK | MB_ICONERROR );
}
