//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : Command.cpp
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 21:28:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "stdafx.h"
#include "Command.h"
#include <cstdlib>

typedef void(*CallbackFunctionVoid)();
typedef void(*CallbackFunctionInt)(int);
typedef void(*CallbackFunctionIntInt)(int, int);

CCommand::CCommand()
{
	CommandCount = 0;
}

CCommand::~CCommand()
{
}

void CCommand::AddCommand(COMMAND cmd)
{
	Command[CommandCount] = cmd;
	CommandCount++;
}

bool CCommand::RunCommand(char ** cmd)
{
	for (int i = 0; i < CommandCount; i++)
	{
		if (strcmp(Command[i].Name, cmd[0]) == 0)
		{
			switch (Command[i].ParameterCount)
			{
			case 0:
				((CallbackFunctionVoid)Command[i].Function)();
				return true;
			case 1:
				((CallbackFunctionInt)Command[i].Function)(atoi(cmd[1]));
				return true;
			case 2:
				((CallbackFunctionIntInt)Command[i].Function)(atoi(cmd[1]), atoi(cmd[2]));
				return true;
			}
		}
	}

	return false;
}
