#pragma once

#include <string>

class ToolsCommon
{
public:
	static bool canRun();
	static bool isEval();
	static void outOfDateMessage( const std::string& toolName );
};