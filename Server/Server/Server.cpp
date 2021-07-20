#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

using namespace std;

SOCKET Connections[100];
int Counter = 0;

void ClientHardler(int index) {
	char msg[256];
	while (true) {
		recv(Connections[index], msg, sizeof(msg), NULL);
		for (int i = 0; i < Counter; i++) {
			if (i == index) {
				continue;
			}

			send(Connections[i], msg, sizeof(msg), NULL);
		}
	}



}

int main(int argc, char* argv()) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0){
		cout << "Error" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET; // семество интернет протоколов

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);

	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	listen(sListen, SOMAXCONN);

	SOCKET newConnection;

	for (int i = 0; i < 100; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

		if (newConnection == 0) {
			cout << "Error" << endl;
		}
		else {
			cout << "Client Connection" << endl;
			char msg[256] = "Hello, server is working!";
			send(newConnection, msg, sizeof(msg), NULL);

			Connections[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHardler, (LPVOID)(i), NULL, NULL);
		}
	}

	return 0;
}

