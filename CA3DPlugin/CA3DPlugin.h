//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : CA3DPlugin.h
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 20:54:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#pragma once

#include "Socket.h"
#include "Command.h"

class CA3DPlugin
{
public:
	CA3DPlugin();
	~CA3DPlugin();

	void Init();
	void CheckConnection();
	void AddCommand(COMMAND cmd);

	void SendData(const char* data);
	bool ParsCommand();
	void StepSimulation();

private:
	CSocket Socket;
	CCommand Command;
};

