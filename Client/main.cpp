#include "Base64Wrapper.h"
#include "RSAWrapper.h"
#include "AESWrapper.h"

#include <iostream>
#include <string>
#include <iomanip>

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include "Action.h"

#include <chrono>
#include <thread>

#pragma comment(lib, "ws2_32.lib")


int main() {
	Action handler;
	std::string ip_addr;
	uint16_t port;
	if (!handler.getServerInfo(ip_addr, port))
		exit(1);
	char uuid[CLIENT_ID_SIZE] = { 0 };
	char username[USER_LENGTH] = { 0 };
	char AESEncrypted[ENC_AES_LEN] = { 0 };
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData); 	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in sa = { 0 };
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);	
	inet_pton(AF_INET, ip_addr.c_str(), &sa.sin_addr); 

	//handler.registerUser(sock, &sa, uuid);
	bool is_new_user = handler.registerUser(sock, &sa, uuid);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	handler.sendFile(sock, &sa, uuid, AESEncrypted, is_new_user);
	
	WSACleanup();
	return 0;
}