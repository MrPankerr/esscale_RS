#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning(disable: 4996)

#define PORT 80

using namespace std;

SOCKET Connection;

enum Packet_Employer{
	P_ChatMessege_E,
	P_Closed_E
};

enum Packet{
	P_Worker,
	P_Employer
};

bool ProcessPacket(Packet_Employer packettype)
{
	switch (packettype)
	{
	case P_ChatMessege_E:
	{
		int msg_size;
		recv(Connection, (char*)&msg_size, sizeof(int), NULL);
		char *msg = new char[msg_size + 1];
		msg[msg_size] = '\0';
		recv(Connection, msg, msg_size, NULL);
		cout << msg << endl;

		delete[] msg;
		break;
	}
	case P_Closed_E:
	{
		cout << "Disconect" << endl;
		return false;
	}
	default:
		cout << "Unrecognized packet: " << packettype << endl;
		break;
	}

	return true;
}

void ClientHandler()
{
	Packet_Employer packettype;
	while(true)
	{
		recv(Connection, (char*)&packettype, sizeof(Packet_Employer), NULL);

		if(!ProcessPacket(packettype))
		{
			break;
		}
	}
	closesocket(Connection);
}


int main(int argc, char* argv[])
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Error: faild connect to server.\n";
		return 1;
	}
	cout << "Connected!\n";

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	Packet packettype1 = P_Employer;
	send(Connection, (char*)&packettype1, sizeof(Packet_Employer), NULL);
	string msg1;
	while(true)
	{
		getline(cin, msg1);
		int msg_size = msg1.size();
		Packet_Employer packettype;
		if(msg1 == "end")
		{
			packettype = P_Closed_E;
		}
		else
		{
			packettype = P_ChatMessege_E;
		}
		send(Connection, (char*)&packettype, sizeof(Packet_Employer), NULL);
		send(Connection, (char*)&msg_size, sizeof(int), NULL);
		send(Connection, msg1.c_str(), msg_size, NULL);
		Sleep(10);
	}

	system("pause");
	return 0;
}