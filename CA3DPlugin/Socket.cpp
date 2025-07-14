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

	return true;
}

char * CSocket::Recive()
{
	int clientSize = sizeof(clientAddr);
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

	if (clientSocket == INVALID_SOCKET)
		return nullptr;

	buffer[0] = '\0';
	recv(clientSocket, buffer, sizeof(buffer), 0);

	return &buffer[0];
}

void CSocket::Send(const char * message)
{
	send(clientSocket, message, strlen(message), 0);
}