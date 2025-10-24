//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : CA3DPlugin.cpp
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 20:54:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#include "stdafx.h"
#include "CA3DPlugin.h"
#include <thread>

#define MAX_PART 50

void SecondThread(CA3DPlugin* plugin)
{
	plugin->CheckConnection();

	while (true)
	{
		plugin->StepSimulation();
	}
}

CA3DPlugin::CA3DPlugin()
{
}

CA3DPlugin::~CA3DPlugin()
{
}

void CA3DPlugin::Init()
{
	std::thread StreamThread(SecondThread, this);
	StreamThread.detach();
}

void CA3DPlugin::CheckConnection()
{
	Socket.CheckConnection();
}

void CA3DPlugin::AddCommand(COMMAND cmd)
{
	Command.AddCommand(cmd);
}

void CA3DPlugin::SendData(const char* data)
{
	Socket.Send(data);
}

char* CA3DPlugin::ParsCommand()
{
	// Wait for recive command
	char* command = Socket.Recive();

	if (!command[0])
		return NULL;

	// Pars command
	int i = 0;
	int j = 0;
	int counter = 0;
	char* Part[MAX_PART];

	Part[0] = command;

	while (command[i] && counter < MAX_PART)
	{
		if (command[i] == ',')
		{
			if (i > 0)
			{
				command[i] = '\0';
				Part[++counter] = &command[i + 1];
			}
		}

		i++;
	}

	// Check and run command
	return Command.RunCommand(Part);
}

void CA3DPlugin::StepSimulation()
{
	char* response = ParsCommand();

	if (response)
		SendData(response);
	else
		SendData("Failed!");
}
