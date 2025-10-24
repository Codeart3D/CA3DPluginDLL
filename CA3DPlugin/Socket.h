//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : Socket.h
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 20:22:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#pragma once

#include <winsock2.h>

#define MAX_BUFFER 2048

class CSocket
{
public:
	CSocket();
	~CSocket();

	void CloseConnection();
	void End();

	bool CheckConnection();
	char* Recive();
	void Send(const char* message);
	
public:
	char buffer[MAX_BUFFER];

private:
	SOCKET clientSocket;
	SOCKET serverSocket;

	sockaddr_in clientAddr;
	sockaddr_in serverAddr;

	WSADATA wsaData;
};

