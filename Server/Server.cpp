#include "Server.h"

void recvData(SOCKET s, int num) {
	char buffer[PACKET_SIZE] = { 0 };
	recv(s, buffer, sizeof buffer, 0);	//Ŭ���̾�Ʈ�� �̸��� �޴´�.
	Client[num].second = buffer;

	while (TRUE) {
		ZeroMemory(buffer, sizeof buffer);
		recv(s, buffer, sizeof buffer, 0);
		std:: cout << Client[num].second << " : " << buffer << std::endl;
		
	}
}

void ACCEPT(SOCKET &s){			//Ŭ���̾�Ʈ�� ���� ���� �����ϴ� �Լ�
	int cnt = 0;
	while (TRUE) {
		Client.push_back(pii(CLIENT(), ""));
		Client[cnt].first.client = accept(s, (SOCKADDR*)&Client[cnt].first.clientaddr, &Client[cnt].first.clientsize);
		Client[cnt].first.number = cnt;
		std::thread(recvData, Client[cnt].first.client, cnt).detach();
		cnt += 1;
	}
}

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = { 0 };
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;

	bind(server, (SOCKADDR*)&addr, sizeof addr);
	listen(server, SOMAXCONN);

	std::thread(ACCEPT, std::ref(server)).detach();
	char name[PACKET_SIZE],
		message[PACKET_SIZE];

	while (TRUE) {
		ZeroMemory(name, sizeof name);
		ZeroMemory(message, sizeof message);
		std::cin >> name >> message;
		for (int i = 0; i < Client.size(); i++) {
			if (!strcmp(Client[i].second.c_str(), name))
				send(Client[i].first.client, message, sizeof message, 0);
		}		
	}
}

/*#include "Server.h"

void recvData(SOCKET s, int num) {
	char buffer[PACKET_SIZE] = { 0 };
	recv(s, buffer, sizeof buffer, 0); //�̸��ޱ�
	Client[num].second = buffer;

	while (TRUE) {
		ZeroMemory(buffer, sizeof buffer);
		recv(s, buffer, sizeof buffer, 0); //�޼����� �޴ºκ�
		std::cout << Client[num].second << " : " << buffer << std::endl;
	}
}

void ACCEPT(SOCKET &s) { //Ŭ���̾�Ʈ���� ������ �����ϴ� �Լ�
	int cnt = 0;
	while (TRUE) {
		Client.push_back(pii(CLIENT(), ""));
		Client[cnt].first.client = accept(s, (SOCKADDR*)&Client[cnt].first.clientaddr, &Client[cnt].first.clientsize);
		Client[cnt].first.number = cnt;
		std::thread(recvData, Client[cnt].first.client, cnt).detach();
		cnt += 1;
	}
}

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = { 0 };
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;

	bind(server, (SOCKADDR*)&addr, sizeof addr);
	listen(server, SOMAXCONN);

	std::thread(ACCEPT, std::ref(server)).detach();

	char name[PACKET_SIZE],
		message[PACKET_SIZE];

	while (TRUE) {
		ZeroMemory(name, sizeof name);
		ZeroMemory(message, sizeof message);
		std::cin >> name >> message;
		for (int i = 0; i < Client.size(); i++)
			if (!strcmp(Client[i].second.c_str(), name))
				send(Client[i].first.client, message, sizeof message, 0);
	}
}
*/