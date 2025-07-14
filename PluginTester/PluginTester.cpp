// PluginTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main() 
{
	WSADATA wsaData;
	SOCKET sock;
	sockaddr_in serverAddr;
	char buffer[1024] = { 0 };
	const char* command = "Vehicle_Forward,0,0";

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) != 0) 
	{
		std::cerr << "Connection failed\n";
		return 1;
	}

	int response = 1;

	while (response)
	{
		send(sock, command, strlen(command), 0);
		std::cout << "Message sent to server\n";

		recv(sock, buffer, sizeof(buffer), 0);
		std::cout << "Received from server: " << buffer << std::endl;

		
		//std::cin >> response;
	}

	closesocket(sock);
	WSACleanup();
	

	return 0;
}
