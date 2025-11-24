//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : dllmain.cpp
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 20:22:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "targetver.h"
#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN
#define EXP __declspec(dllexport)

// Windows Header Files
#include <typeinfo>
#include <windows.h>

#include "CA3DPlugin.h"

CA3DPlugin Plugin;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

typedef void(*CallbackFunctionVoid)(void(*)());
typedef void(*CallbackFunctionBool)(void(*)(bool));
typedef void(*CallbackFunctionInt)(void(*)(int));
typedef void(*CallbackFunctionIntInt)(void(*)(int, int));
typedef void(*CallbackFunctionIntIntFloat)(void(*)(int, int, float *));
typedef void(*CallbackFunctionIntIntIntFloat)(void(*)(int, int, int &, float **));
typedef void(*CallbackFunctionIntIntFloatFloat)(void(*)(int, int, float *, float *));
typedef void(*CallbackFunctionIntIntFloatVFloatV)(void(*)(int, int, float &, float &));
typedef void(*CallbackFunctionIntIntIntFloatFloat)(void(*)(int, int, int&, float *, float **));
typedef void(*CallbackFunctionIntIntIntInt)(void(*)(int, int, int&, int&));
typedef void(*CallbackFunctionVecVecVecFloatIntBool)(void(*)(float*, float*, float*, float, int&, bool&));

extern "C"
{
#pragma region Game

	CallbackFunctionBool Game_Play = NULL;
	EXP void SetGame_Play_Callback(CallbackFunctionBool f) { Game_Play = f; }

#pragma endregion

#pragma region Level

	CallbackFunctionInt Level_Reload = NULL;
	EXP void SetLevel_Reload_Callback(CallbackFunctionInt f) { Level_Reload = f; }

#pragma endregion

#pragma region Spline

	CallbackFunctionIntIntIntFloat Spline_GetPoints = NULL;
	EXP void SetSpline_GetPoints_Callback(CallbackFunctionIntIntIntFloat f) { Spline_GetPoints = f; }
	CallbackFunctionIntIntIntFloatFloat Spline_GetNearestPoints = NULL;
	EXP void SetSpline_GetNearestPoints_Callback(CallbackFunctionIntIntIntFloatFloat f) { Spline_GetNearestPoints = f; }
	CallbackFunctionIntIntFloat Spline_GetWidth = NULL;
	EXP void SetSpline_GetWidth_Callback(CallbackFunctionIntIntFloat f) { Spline_GetWidth = f; }
	CallbackFunctionIntIntFloatFloat Spline_GetWayPercent = NULL;
	EXP void SetSpline_GetWayPercent_Callback(CallbackFunctionIntIntFloatFloat f) { Spline_GetWayPercent = f; }

#pragma endregion

#pragma region Vehicle

	CallbackFunctionIntIntFloat Vehicle_GetPosition = NULL;
	EXP void SetVehicle_GetPosition_Callback(CallbackFunctionIntIntFloat f) { Vehicle_GetPosition = f; }
	CallbackFunctionIntIntFloat Vehicle_GetForwardVector = NULL;
	EXP void SetVehicle_GetForwardVector_Callback(CallbackFunctionIntIntFloat f) { Vehicle_GetForwardVector = f; }
	CallbackFunctionIntIntIntInt Vehicle_HasCollided = NULL;
	EXP void SetVehicle_HasCollided_Callback(CallbackFunctionIntIntIntInt f) { Vehicle_HasCollided = f; }
	CallbackFunctionIntInt Vehicle_Forward = NULL;
	EXP void SetVehicle_Forward_Callback(CallbackFunctionIntInt f) { Vehicle_Forward = f; }
	CallbackFunctionIntInt Vehicle_Backward = NULL;
	EXP void SetVehicle_Backward_Callback(CallbackFunctionIntInt f) { Vehicle_Backward = f; }
	CallbackFunctionIntInt Vehicle_Left = NULL;
	EXP void SetVehicle_Left_Callback(CallbackFunctionIntInt f) { Vehicle_Left = f; }
	CallbackFunctionIntInt Vehicle_Right = NULL;
	EXP void SetVehicle_Right_Callback(CallbackFunctionIntInt f) { Vehicle_Right = f; }
	CallbackFunctionIntInt Vehicle_ReleaseForwadBackward = NULL;
	EXP void SetVehicle_ReleaseForwadBackward_Callback(CallbackFunctionIntInt f) { Vehicle_ReleaseForwadBackward = f; }
	CallbackFunctionIntInt Vehicle_ReleaseLeftRight = NULL;
	EXP void SetVehicle_ReleaseLeftRight_Callback(CallbackFunctionIntInt f) { Vehicle_ReleaseLeftRight = f; }
	CallbackFunctionIntInt Vehicle_Handbrake = NULL;
	EXP void SetVehicle_Handbrake_Callback(CallbackFunctionIntInt f) { Vehicle_Handbrake = f; }
	CallbackFunctionIntInt Vehicle_ReleaseHandbrake = NULL;
	EXP void SetVehicle_ReleaseHandbrake_Callback(CallbackFunctionIntInt f) { Vehicle_ReleaseHandbrake = f; }
	CallbackFunctionIntIntFloatVFloatV Vehicle_GetSpeed = NULL;
	EXP void SetVehicle_GetSpeed_Callback(CallbackFunctionIntIntFloatVFloatV f) { Vehicle_GetSpeed = f; }

#pragma endregion

#pragma region Timer2D

	CallbackFunctionIntInt Timer2D_Reset = NULL;
	EXP void SetTimer2D_Reset_Callback(CallbackFunctionIntInt f) { Timer2D_Reset = f; }
	CallbackFunctionIntIntFloat Timer2D_GetTimerTime = NULL;
	EXP void SetTimer2D_GetTimerTime_Callback(CallbackFunctionIntIntFloat f) { Timer2D_GetTimerTime = f; }

#pragma endregion

#pragma region Math

	CallbackFunctionVecVecVecFloatIntBool Ray_Test = NULL;
	EXP void SetRay_Test_Callback(CallbackFunctionVecVecVecFloatIntBool f) { Ray_Test = f; }

#pragma endregion


#pragma region Init
	void AddCommands()
	{
		//
		// Game
		//
		int startcode = (int)AssetType::Game;
		Plugin.AddCommand(COMMAND(++startcode, "Game_Play", Game_Play)); // 10101

		//
		// Level
		//
		startcode = (int)AssetType::Level;
		Plugin.AddCommand(COMMAND(++startcode, "Level_Reload", Level_Reload)); // 70001

		//
		// Spline
		//
		startcode = (int)AssetType::Spline;
		Plugin.AddCommand(COMMAND(++startcode, "Spline_GetPoints", Spline_GetPoints)); // 62601
		Plugin.AddCommand(COMMAND(++startcode, "Spline_GetNearestPoints", Spline_GetNearestPoints)); // 62602
		Plugin.AddCommand(COMMAND(++startcode, "Spline_GetWidth", Spline_GetWidth)); // 62603
		Plugin.AddCommand(COMMAND(++startcode, "Spline_GetWayPercent", Spline_GetWayPercent)); // 62604

		//
		// Vehicle
		//
		startcode = (int)AssetType::WheeledVehicle;
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_GetPosition", Vehicle_GetPosition)); // 61801
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_GetForwardVector", Vehicle_GetForwardVector)); // 61802
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_HasCollided", Vehicle_HasCollided)); // 61803
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_Forward", Vehicle_Forward)); // 61804
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_Backward", Vehicle_Backward)); // 61805
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_Left", Vehicle_Left)); // 61806
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_Right", Vehicle_Right)); // 61807
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_ReleaseForwadBackward", Vehicle_ReleaseForwadBackward)); // 61808
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_ReleaseLeftRight", Vehicle_ReleaseLeftRight)); // 61809
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_Handbrake", Vehicle_Handbrake)); // 61810
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_ReleaseHandbrake", Vehicle_ReleaseHandbrake)); // 61811
		Plugin.AddCommand(COMMAND(++startcode, "Vehicle_GetSpeed", Vehicle_GetSpeed)); // 61812

		//
		// Timer2D
		//
		startcode = (int)AssetType::Timer2D;
		Plugin.AddCommand(COMMAND(++startcode, "Timer2D_Reset", Timer2D_Reset)); // 41001
		Plugin.AddCommand(COMMAND(++startcode, "Timer2D_GetTimerTime", Timer2D_GetTimerTime)); // 41002
																							   
		//
		// Math
		//
		startcode = (int)AssetType::Math;
		Plugin.AddCommand(COMMAND(++startcode, "Ray_Test", Ray_Test)); // 11101
	}

	EXP void Plugin_Init()
	{
		AddCommands();
	}
#pragma endregion

#pragma region Init

	EXP void Init()
	{
		static bool init = false;

		if (!init)
		{
			init = true;
			AddCommands();
			Plugin.Init();
		}
	}

#pragma endregion
}