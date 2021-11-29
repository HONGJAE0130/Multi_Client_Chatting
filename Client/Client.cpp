#include "Client.h"

void recvData(SOCKET &s){
	char buffer[PACKET_SIZE];
	while (TRUE) {
		ZeroMemory(buffer, sizeof buffer);
		recv(s, buffer, sizeof buffer, 0);
		std::cout << "Server : "<< buffer << std::endl;
	}
}

int main()
{
	char IP[PACKET_SIZE] = { 0 },
		name[PACKET_SIZE] = { 0 };

	std::cout << "�̸��� �Է��ϼ��� : ";
	std::cin >> name;
	std::cout << "�����Ǹ� �Է��ϼ��� : " ;
	std::cin >> IP;

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = { 0 };
	addr.sin_addr.s_addr = inet_addr(IP);
	addr.sin_port = PORT;
	addr.sin_family = AF_INET;

	while (connect(server, (SOCKADDR*)&addr, sizeof addr));
	send(server, name, sizeof name, 0); // �̸� ������

	std::thread(recvData, std::ref(server)).detach();
	
	//string str;

	while (TRUE) {		
		ZeroMemory(name, sizeof name);
		std::cout << "�޼����� �Է��ϼ��� : ";
		std::cin >> name;
		// for (int i = 0; i < sizeof str.c_str(); i++) name[i] = str[i];
		send(server, name, sizeof name, 0);
	}
	
}
/*
#include "Client.h"

void recvData(SOCKET &s){
   char buffer[PACKET_SIZE];
   while (TRUE) {
	  ZeroMemory(buffer, sizeof buffer);
	  recv(s, buffer, sizeof buffer, 0);
	  cout << buffer << endl;
   }
}

int main()
{
   char IP[PACKET_SIZE] = { 0 };
   char name[PACKET_SIZE] = { 0 };

   cout << "�̸��� �Է��ϼ��� : ";
   cin >> name;
   cout << "�����Ǹ� �Է��ϼ��� : " ;
   cin >> IP;

   WSADATA wsa;
   WSAStartup(MAKEWORD(2, 2), &wsa);

   SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   SOCKADDR_IN addr = { 0 };
   addr.sin_addr.s_addr = inet_addr(IP);
   addr.sin_port = PORT;
   addr.sin_family = AF_INET;

   while (connect(server, (SOCKADDR*)&addr, sizeof addr));
   send(server, name, sizeof name, 0); // �̸� ������

   thread(recvData, ref(server)).detach();

   string str;

   while (TRUE) {
	  ZeroMemory(name, sizeof name);
	  cout << "�޼����� �Է��ϼ��� : ";
	  cin >> name;
	  // for (int i = 0; i < sizeof str.c_str(); i++) name[i] = str[i];
	  send(server, name, sizeof name, 0);
   }
}
*/