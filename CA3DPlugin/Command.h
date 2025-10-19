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

#define MAX_BUFFER 2048
#define MAX_COMMAND 100

enum AssetType
{
	Timer2D = 41000,
	Screen = 50000,
	SoundBox = 60100,
	WheeledVehicle = 61800,
	Spline = 62600,
	Level = 70000,
	Math = 11100,
};

struct COMMAND
{
	char Name[64];
	int Code;
	void* Function;

	COMMAND() {}

	COMMAND(int code, const char* name, void* func)
	{
		Code = code;
		strcpy_s(Name, 64, name);
		Function = func;
	}
};

class CCommand
{
public:
	CCommand();
	~CCommand();

	void AddCommand(COMMAND cmd);
	char* RunCommand(char** cmd);
	char* CallFunction(COMMAND& cmd, char** params);

private:
	int CommandCount;

	char success[11];
	char response[MAX_BUFFER];

	COMMAND Command[MAX_COMMAND];
};

