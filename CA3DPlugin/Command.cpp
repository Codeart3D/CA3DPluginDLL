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
typedef void(*CallbackFunctionBool)(bool);
typedef void(*CallbackFunctionInt)(int);
typedef void(*CallbackFunctionIntInt)(int, int);
typedef void(*CallbackFunctionIntIntFloat)(int, int, float *);
typedef void(*CallbackFunctionIntIntIntFloat)(int, int, int &, float **);
typedef void(*CallbackFunctionIntIntFloatFloat)(int, int, float *, float *);
typedef void(*CallbackFunctionIntIntFloatVFloatV)(int, int, float &, float &);
typedef void(*CallbackFunctionIntIntIntFloatFloat)(int, int, int&, float *, float **);
typedef void(*CallbackFunctionIntIntIntInt)(int, int, int&, int&);
typedef void(*CallbackFunctionVecVecVecFloatIntBool)(float*, float*, float*, float, int&, bool&);

CCommand::CCommand()
{
	CommandCount = 0;
	strcpy_s(success, "Successful");
}

CCommand::~CCommand()
{
}

void CCommand::AddCommand(COMMAND cmd)
{
	Command[CommandCount] = cmd;
	CommandCount++;
}

char* CCommand::RunCommand(char ** cmd)
{
	int code = atoi(cmd[0]);

	for (int i = 0; i < CommandCount; i++)
	{
		if (Command[i].Code == code)
			return CallFunction(Command[i], cmd);
	}

	return NULL;
}

char* CCommand::CallFunction(COMMAND & cmd, char ** params)
{
	switch (cmd.Code)
	{
	case 10101: // Game_Play
		((CallbackFunctionBool)cmd.Function)((bool)atoi(params[1]));
		return success;

	case 70001: // Level_Reload
		((CallbackFunctionInt)cmd.Function)(atoi(params[1]));
		return success;

	case 61804: // Vehicle_Forward
	case 61805: // Vehicle_Backward
	case 61806: // Vehicle_Left
	case 61807: // Vehicle_Right
	case 61808: // Vehicle_ReleaseForwadBackward
	case 61809: // Vehicle_ReleaseLeftRight
	case 61810: // Vehicle_Handbrake
	case 61811: // Vehicle_ReleaseHandbrake
	case 41001: // Timer2D_Reset
		((CallbackFunctionIntInt)cmd.Function)(atoi(params[1]), atoi(params[2]));
		return success;

	case 62601: // Spline_GetPoints
	{
		int count = 0;
		char posstr[64];
		float* result = NULL;

		((CallbackFunctionIntIntIntFloat)cmd.Function)(atoi(params[1]), atoi(params[2]), count, &result);
		sprintf_s(response, MAX_BUFFER, "%d", count);
		int ncount = count * 3;

		for (int i = 0; i < ncount; i += 3)
		{
			sprintf_s(posstr, 64, ",%.3f,%.3f,%.3f", result[i], result[i + 1], result[i + 2]);
			strcat_s(response, MAX_BUFFER, posstr);
		}

		return response;
	}

	case 62602: // Spline_GetNearestPoints
	{
		int max = atoi(params[3]);
		float pos[3];
		char posstr[64];
		float* result = NULL;
		pos[0] = (float)std::atof(params[4]);
		pos[1] = (float)std::atof(params[5]);
		pos[2] = (float)std::atof(params[6]);
		((CallbackFunctionIntIntIntFloatFloat)cmd.Function)(atoi(params[1]), atoi(params[2]), max, pos, &result);
		sprintf_s(response, MAX_BUFFER, "%d", max);
		int ncount = max * 3;

		for (int i = 0; i < ncount; i += 3)
		{
			sprintf_s(posstr, 64, ",%.3f,%.3f,%.3f", result[i], result[i + 1], result[i + 2]);
			strcat_s(response, MAX_BUFFER, posstr);
		}

		return response;
	}
	case 61812:
	{
		float max = 0.0f;
		float speed = 0.0f;
		((CallbackFunctionIntIntFloatVFloatV)cmd.Function)(atoi(params[1]), atoi(params[2]), max, speed);
		sprintf_s(response, MAX_BUFFER, "%.3f,%.3f", max, speed);
		return response;
	}

	case 62603: // Spline_GetWidth
	case 41002: // Timer2D_GetTimerTime
	{
		float result = 0.0f;
		((CallbackFunctionIntIntFloat)cmd.Function)(atoi(params[1]), atoi(params[2]), &result);
		sprintf_s(response, MAX_BUFFER, "%.3f", result);
		return response;
	}

	case 62604: // Spline_GetWayPercent
	{
		float result = 0.0f;
		float pos[3];
		pos[0] = (float)std::atof(params[3]);
		pos[1] = (float)std::atof(params[4]);
		pos[2] = (float)std::atof(params[5]);
		((CallbackFunctionIntIntFloatFloat)cmd.Function)(atoi(params[1]), atoi(params[2]), pos, &result);
		sprintf_s(response, MAX_BUFFER, "%.3f", result);
		return response;
	}

	case 61801: // Vehicle_GetPosition
	case 61802: // Vehicle_GetForwardVector
	{
		float result[3] = { 111.0f, 0.0f, 0.0f };
		((CallbackFunctionIntIntFloat)cmd.Function)(atoi(params[1]), atoi(params[2]), result);
		sprintf_s(response, MAX_BUFFER, "%.3f,%.3f,%.3f", result[0], result[1], result[2]);
		return response;
	}

	case 61803: // Vehicle_HasCollided
	{
		int result1 = atoi(params[3]);
		int result2 = atoi(params[4]);
		((CallbackFunctionIntIntIntInt)cmd.Function)(atoi(params[1]), atoi(params[2]), result1, result2);
		sprintf_s(response, MAX_BUFFER, "%d,%d", result1, result2);
		return response;
	}
	case 11101: // Ray_test
	{
		float org[3];
		org[0] = (float)std::atof(params[1]);
		org[1] = (float)std::atof(params[2]);
		org[2] = (float)std::atof(params[3]);

		float nor[3];
		nor[0] = (float)std::atof(params[4]);
		nor[1] = (float)std::atof(params[5]);
		nor[2] = (float)std::atof(params[6]);

		float hit[3]{ 0.0f, 0.0f, 0.0f };
		bool result = false;
		int groupid = 0;

		((CallbackFunctionVecVecVecFloatIntBool)cmd.Function)(org, nor, hit, (float)std::atof(params[7]), groupid, result);
		sprintf_s(response, MAX_BUFFER, "%d,%d,%.3f,%.3f,%.3f", (int)result, groupid, hit[0], hit[1], hit[2]);
		return response;
	}
	}

	return NULL;
}
