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
	char buffer[2048] = { 0 };

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (true)
	{
		int res = connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

		if (res != 0)
		{
			std::cerr << "Connection failed\n";
			Sleep(500);
		}
		else
			break;
	}

	int response = 1;

	//
	//------------------------------ COMMANDS -------------------------
	//
	const char* commands[20];
	commands[0] = "70001,0"; // Level_Reload																						[TEST OK]

	commands[1] = "61804,0,0"; // Vehicle_Forward																					[TEST OK]
	commands[2] = "61805,0,0"; // Vehicle_Backward																					[TEST OK]
	commands[3] = "61806,0,0"; // Vehicle_Left																						[TEST OK]
	commands[4] = "61807,0,0"; // Vehicle_Right																						[TEST OK]
	commands[5] = "61808,0,0"; // Vehicle_ReleaseForwadBackward
	commands[6] = "61809,0,0"; // Vehicle_ReleaseLeftRight
	commands[7] = "61810,0,0"; // Vehicle_Handbrake																					[TEST OK]
	commands[8] = "61811,0,0"; // Vehicle_ReleaseHandbrake
	commands[9] = "41001,2,0"; // Timer2D_Reset																						[TEST OK]

	commands[10] = "62601,0,0"; // Spline_GetPoints : all points																	[TEST OK]
	commands[11] = "62602,0,0,4,0.0,92.0,0.0"; // Spline_GetNearestPoints : max points 4, (0.0,92.0,0.0) vehicle position			[TEST OK]

	commands[12] = "62603,0,0"; // Spline_GetWidth																					[TEST OK]
	commands[13] = "62604,0,0,60.0,92.0,0.0"; // Spline_GetWayPercent : (60.0,92.0,0.0) vehicle position							[TEST OK]
	commands[14] = "41002,2,0"; // Timer2D_GetTimerTime : game_screen index is 2 and timer2d index is 0								[TEST OK]

	commands[15] = "61801,0,0"; // Vehicle_GetPosition																				[TEST OK]
	commands[16] = "61802,0,0"; // Vehicle_GetForwardVector																			[TEST OK]

	commands[17] = "61803,0,0,1,2"; // Vehicle_HasCollided, 1 tag id for rivals and 2 for walls, return 0 or 1						[TEST OK]

	commands[18] = "11101,5.93,92.37,0.93,1.0,0.0,0.0,50.0"; // origin(0.0,0.0,0.0), normal direction(1.0,0.0,0.0), distance 50.0	[TEST OK]
	commands[19] = "61812,0,0"; // Vehicle_GetSpeed																					[TEST OK]

	//
	//-----------------------------------------------------------------
	//

	while (response)
	{
		int idx = rand() % 20;

		/*if (idx == 0)
			idx = 1;*/

		std::cout << "Response Command " << idx << " : ";
		ZeroMemory(buffer, sizeof(buffer));
		send(sock, commands[idx], strlen(commands[idx]), 0);
		recv(sock, buffer, sizeof(buffer), 0);
		std::cout << buffer << std::endl;
	}

	closesocket(sock);
	WSACleanup();


	return 0;
}
