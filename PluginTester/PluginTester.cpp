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

	//
	//------------------------------ COMMANDS -------------------------
	//
	const char* command1 = "70001,0"; // Level_Reload																					[TEST OK]

	const char* command2 = "61804,0,0"; // Vehicle_Forward																				[TEST OK]
	const char* command3 = "61805,0,0"; // Vehicle_Backward																				[TEST OK]
	const char* command4 = "61806,0,0"; // Vehicle_Left																					[TEST OK]
	const char* command5 = "61807,0,0"; // Vehicle_Right																				[TEST OK]
	const char* command6 = "61808,0,0"; // Vehicle_ReleaseForwadBackward
	const char* command7 = "61809,0,0"; // Vehicle_ReleaseLeftRight
	const char* command8 = "61810,0,0"; // Vehicle_Handbrake																			[TEST OK]
	const char* command9 = "61811,0,0"; // Vehicle_ReleaseHandbrake
	const char* command10 = "41001,2,0"; // Timer2D_Reset																				[TEST OK]

	const char* command11 = "62601,0,0"; // Spline_GetPoints : all points																[TEST OK]
	const char* command12 = "62602,0,0,4,0.0,92.0,0.0"; // Spline_GetNearestPoints : max points 4, (0.0,92.0,0.0) vehicle position		[TEST OK]

	const char* command13 = "62603,0,0"; // Spline_GetWidth																				[TEST OK]
	const char* command14 = "62604,0,0,60.0,92.0,0.0"; // Spline_GetWayPercent : (60.0,92.0,0.0) vehicle position						[TEST OK]
	const char* command15 = "41002,2,0"; // Timer2D_GetTimerTime : game_screen index is 2 and timer2d index is 0						[TEST OK]

	const char* command16 = "61801,0,0"; // Vehicle_GetPosition																			[TEST OK]
	const char* command17 = "61802,0,0"; // Vehicle_GetForwardVector																	[TEST OK]

	const char* command18 = "61803,0,0,1,2"; // Vehicle_HasCollided, 1 tag id for rivals and 2 for walls, return 0 or 1					[TEST OK]


	const char* command = command15;
	//
	//-----------------------------------------------------------------
	//

	/*send(sock, command1, strlen(command1), 0);
	recv(sock, buffer, sizeof(buffer), 0);

	send(sock, command10, strlen(command10), 0);
	recv(sock, buffer, sizeof(buffer), 0);*/

	while (response)
	{
		send(sock, command, strlen(command), 0);
		std::cout << "Message sent to server\n";

		ZeroMemory(buffer, sizeof(buffer));
		recv(sock, buffer, sizeof(buffer), 0);
		std::cout << "Received from server: " << buffer << std::endl;
	}

	closesocket(sock);
	WSACleanup();


	return 0;
}
