#pragma once
#pragma comment(lib, "ws2_32.lib")	//링커

#define PORT 8080
#define PACKET_SIZE 1024

#include <iostream>			//c++ 표준 입출력 
#include <winSock2.h>		// winsock
#include <windows.h>		// Zeromemory
#include <vector> 
#include <utility> // pair
#include <thread>
#include <cstdlib>			//cs
#include <string>


//using namespace std;

class CLIENT {
public:
	SOCKET client;
	SOCKADDR_IN clientaddr = { 0 };
	int clientsize = sizeof clientaddr;
	int number = -1;
	CLIENT() { }
}; 

typedef std::pair<CLIENT, std::string> pii;

std::vector<pii> Client;