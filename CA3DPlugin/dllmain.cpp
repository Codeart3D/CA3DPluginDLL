// dllmain.cpp : Defines the entry point for the DLL application.
#include "targetver.h"
#include "stdafx.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define EXP __declspec(dllexport)

// Windows Header Files
#include <typeinfo>
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
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

typedef void(*CallbackFunctionVoid)();
typedef void(*CallbackFunctionInt)(int);
typedef void(*CallbackFunctionIntInt)(int, int);
typedef void(*CallbackFunctionIntIntFloat)(int, int, float *);
typedef void(*CallbackFunctionIntIntIntFloat)(int, int, int &, float *);

extern "C"
{
#pragma region Level

	CallbackFunctionInt Level_Reset = NULL;
	EXP void SetLevel_Reset_Callback(CallbackFunctionInt f) { Level_Reset = f; }
	CallbackFunctionInt Level_Reload = NULL;
	EXP void SetLevel_Reload_Callback(CallbackFunctionInt f) { Level_Reload = f; }

#pragma endregion

#pragma region Spline

	CallbackFunctionIntIntIntFloat Spline_GetPoints = NULL;
	EXP void SetSpline_GetPoints_Callback(CallbackFunctionIntIntIntFloat f) { Spline_GetPoints = f; }

#pragma endregion

#pragma region Vehicle

	CallbackFunctionIntIntFloat Vehicle_GetPosition = NULL;
	EXP void SetVehicle_GetPosition_Callback(CallbackFunctionIntIntFloat f) { Vehicle_GetPosition = f; }
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

#pragma endregion

#pragma region Simulation

	EXP void StepSimulation(float delta_time)
	{
		int level_index = 0;
		int vehicle_index = 0;

		Vehicle_Right(level_index, vehicle_index);
		Vehicle_Forward(level_index, vehicle_index);
	}

#pragma endregion
}