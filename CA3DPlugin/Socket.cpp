//-------------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//    File      : Socket.cpp
//    Project   : CodeArt Engine
//    Authors   : Ali Salmanizadegan, Dr. Seyed Navid Hosseini
//    Date      : 2025-07-13
//    Time      : 20:22:00
//    Copyright : (c) CODEART ENGINE Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//-------------------------------------------------------------------------------

#include <iostream>

#include "stdafx.h"
#include "Socket.h"

#define PORT 8080
#pragma comment(lib, "ws2_32.lib")

CSocket::CSocket()
{
	buffer[0] = '\0';
	connected = false;
}

CSocket::~CSocket()
{
	CloseConnection();
}

void CSocket::CloseConnection()
{
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
}

void CSocket::End()
{
	closesocket(clientSocket);
}

bool CSocket::CheckConnection()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, 1);

	int clientSize = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

	if (clientSocket == INVALID_SOCKET)
		return false;

	connected = true;

	return true;
}

char * CSocket::Recive()
{
	ZeroMemory(buffer, sizeof(buffer));
	int result = recv(clientSocket, buffer, sizeof(buffer), 0);

	if (result == 0)
	{
		// Connection closed by peer
		connected = false;
		CloseConnection();
		CheckConnection();
	}
	else if (result < 0)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
		{
			// Error occurred, connection likely broken
			connected = false;
			CloseConnection();
			CheckConnection();
		}
	}

	return &buffer[0];
}

void CSocket::Send(const char * message)
{
	send(clientSocket, message, strlen(message), 0);
}

bool CSocket::IsConnected()
{
	return connected;
}
