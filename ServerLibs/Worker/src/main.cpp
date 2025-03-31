#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <Worker.hpp>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#define PORT 80

using namespace std;

bool ProcessPacket(int index, Packet_Worker packettype, int count, SOCKET* Connect)
{
	switch (packettype)
	{
	case P_ChatMessege_W:
	{
		int msg_size;
		recv(Connect[index], (char*)&msg_size, sizeof(int), NULL);
		char *msg = new char[msg_size + 1];
		msg[msg_size] = '\0';

		recv(Connect[index], msg, msg_size, NULL);

		for(int i = 0; i < count; i++)
		{
			if(i == index){ continue; }

			Packet_Worker msgtype = P_ChatMessege_W;
			send(Connect[i], (char*)&msgtype, sizeof(Packet_Worker), NULL);
			send(Connect[i], (char*)&msg_size, sizeof(int), NULL);
			send(Connect[i], msg, msg_size, NULL);
		}
		delete[] msg;

		break;
	}
	case P_Closed_W:
	{
		cout << "Disconected: Client" << index + 1 << endl;
		Packet_Worker msgtype = P_Closed_W;
		send(Connect[index], (char*)&msgtype, sizeof(Packet_Worker), NULL);
		closesocket(Connect[index]);
		return false;
	}
	default:
		cout << "Unrecognized packet: " << packettype << endl;
		break;
	}

	return true;
}