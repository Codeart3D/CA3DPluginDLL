//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : Command.h
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 21:25:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#pragma once

#include <iostream>

#define MAX_COMMAND 100

struct COMMAND
{
	char Name[64];
	int ParameterCount;
	void* Function;

	COMMAND() {}

	COMMAND(const char* name, int pc, void* func)
	{
		strcpy_s(Name, 64, name);
		ParameterCount = pc;
		Function = func;
	}
};

class CCommand
{
public:
	CCommand();
	~CCommand();

	void AddCommand(COMMAND cmd);
	bool RunCommand(char** cmd);

private:
	int CommandCount;

	COMMAND Command[MAX_COMMAND];
};

