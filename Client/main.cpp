// Name: Or Badani

#include "Base64Wrapper.h"
#include "RSAWrapper.h"
#include "AESWrapper.h"

#include <iostream>
#include <string>
#include <iomanip>

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <Windows.h>
#include "Client.h"

#include <chrono>
#include <thread>

#pragma comment(lib, "ws2_32.lib")


int main() {
	try {
	Client handler;
	FileHandler fHandler;
	std::string ip_addr;
	uint16_t port;
	if (!handler.getServerInfo(ip_addr, port))
		exit(1);
	char uuid[CLIENT_ID_SIZE] = { 0 };
	char username[USER_LENGTH] = { 0 };
	char AESEncrypted[ENC_AES_LEN] = { 0 };
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (ret != 0) {
		throw std::runtime_error("WSAStartup Failed");
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		throw std::runtime_error("Failed to create socket");
	}

	struct sockaddr_in sa = { 0 };
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);	
	inet_pton(AF_INET, ip_addr.c_str(), &sa.sin_addr); 
	bool is_new_user;

	if (fHandler.isExistent(ME_INFO)) {
		is_new_user = handler.loginUser(sock, &sa, username, uuid, AESEncrypted);
	}
	else if (fHandler.isExistent(TRANSFER_INFO)) { // Should always exist, if not it will be caught in lines 26-28 in main()
		is_new_user = handler.registerUser(sock, &sa, uuid);
	}
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		throw std::runtime_error("Failed to create socket");
	}
	handler.sendFile(sock, &sa, uuid, AESEncrypted, is_new_user);
	
	WSACleanup();
}
catch (const std::exception& e) {
	std::cerr << "Exception caught: " << e.what() << std::endl;
	WSACleanup();
	return 1; // Return an error code
}
return 0;
};
