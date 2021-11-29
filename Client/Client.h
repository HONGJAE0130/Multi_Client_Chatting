#pragma once
#pragma comment(lib, "ws2_32.lib")

#define _WINSHOCK_DEPRECATED_NO_WARNINGS
#define PORT 8080
#define PACKET_SIZE 1024

#include <iostream>
#include <winSock2.h>
#include <windows.h>
#include <string>	//getline
#include <thread>
#include <cstdlib>

//using namespace std;