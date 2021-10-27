#pragma once
#include "WinConn.h"
#include <iostream>


namespace Connector {

	struct addrinfo* result = NULL, * ptr = NULL, hints;


	WinConn::WinConn() : AConnector() {
	
	}


	bool WinConn::broadcast(const std::string& msg) {
		for each (SOCKET socket in socketsToBroadcast) {
			send(socket, msg.c_str(), msg.size(), 0);
		}
		return true;
	}
	bool WinConn::disconnect() {
		return false;
	}

	void WinConn::initServer() {
		//TODO: this must change when CLIView is introduced
		std::thread inputThread = std::thread([this] {
			requestLocalInput();
		});

		WSADATA wsaData;
		int iResult;

		SOCKET listenSocket = INVALID_SOCKET;
		SOCKET clientSocket = INVALID_SOCKET;

		struct addrinfo* result = NULL;
		struct addrinfo hints;

		int iSendResult;
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen = DEFAULT_BUFLEN;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return;
		}

		// Create a SOCKET for connecting to server
		listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (listenSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		// Setup the TCP listening socket
		iResult = bind(listenSocket, result->ai_addr, (int) result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(listenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(result);

		//Listener listening for connections
		iResult = listen(listenSocket, SOMAXCONN);
		if (iResult == SOCKET_ERROR) {
			printf("listen failed with error: %d\n", WSAGetLastError());
			closesocket(listenSocket);
			WSACleanup();
			return;
		}
		//Waiting for connections
		while ((clientSocket = accept(listenSocket, NULL, NULL))) {
			
			std::thread t = std::thread([this, clientSocket] {
				initServerSocketThread(&clientSocket);
			});
			t.detach();
			//TODO:add to list 
		}
		//t.join/(

		// No longer need server socket
		closesocket(listenSocket);

		// shutdown the connection since we're done
		iResult = shutdown(clientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(clientSocket);
			WSACleanup();
			return;
		}

		// cleanup
		inputThread.join();
		closesocket(clientSocket);
		WSACleanup();
	}
	
	void WinConn::initClient(const std::string* ip) {
		
		std::thread t = std::thread([this, ip] {
			initClientSocketThread(SERVER_TO_CLIENT, ip);
		});
		std::thread t1 = std::thread([this, ip] {
			initClientSocketThread(CLIENT_TO_SERVER, ip);
		});
		//TODO:
		t1.detach();
		t.join();
		
	}
		
	
	void WinConn::initClientSocketThread(const int typeOfConnection, const std::string* ip) {

		char recvbuf[DEFAULT_BUFLEN];
		WSADATA wsaData;
		SOCKET connectSocket = INVALID_SOCKET;
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;


		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return;
		}

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(ip->c_str(), DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed with error: %d\n", iResult);
			WSACleanup();
			return;
		}

		// Attempt to connect to an address until one succeeds
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
			// Create a SOCKET for connecting to server
			connectSocket = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (connectSocket == INVALID_SOCKET) {
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return;
			}

			// Connect to server.
			iResult = connect(connectSocket, ptr->ai_addr, (int) ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR) {
				closesocket(connectSocket);
				connectSocket = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (connectSocket == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return;
		}

		//communicates to the server the desired type of connection
		iResult = send(connectSocket, std::to_string(typeOfConnection).c_str(), std::to_string(typeOfConnection).size(), 0);
		//if SERVER_TO_CLIENT
		if (typeOfConnection) {
			do {
				//waits for broadcasts
				iResult = recv(connectSocket, recvbuf, DEFAULT_BUFLEN, 0);
				if (iResult >= 0) {
					printf("\nReceived Message: %s\n", std::string(recvbuf).substr(0, iResult).c_str());
					//TODO: copy to clipboard
				}
				else
					break;
				//TODO: WHILE TRUE
			} while (1);
		}
		else {
			do {
				std::string messageToSend = std::to_string(typeOfConnection);
				std::cout << "What do you want to send to clipboard?" << std::endl << "> ";
				std::getline(std::cin, messageToSend);
				iResult = send(connectSocket, messageToSend.c_str(), messageToSend.size(), 0);
				if (iResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(connectSocket);
					WSACleanup();
					return;
				}
				//TODO: WHILE TRUE
			} while (1);
		}
		

		// shutdown the connection since no more data will be sent
		iResult = shutdown(connectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(connectSocket);
			WSACleanup();
			return;
		}

		// cleanup
		closesocket(connectSocket);
		WSACleanup();
	}


	void WinConn::initServerSocketThread(const void* socket) {
		SOCKET clientSock = *(SOCKET*) socket;
		char recvbuf[DEFAULT_BUFLEN];

		int iResult = recv(clientSock, recvbuf, DEFAULT_BUFLEN, 0);

		if (iResult == SOCKET_ERROR) {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(clientSock);
			WSACleanup();
			return;
		}
		//	std::cout << std::string(recvbuf).substr(0, iResult) << std::endl;
		std::string msg = std::string(recvbuf).substr(0, iResult);
		
		//IF SERVER_TO_CLIENT CONNECTION
		if (std::stoi(msg)) {
			socketsToBroadcast.push_back(clientSock);
		}
		//else CLIENT_TO_SERVER CONNECTION
		else{
			do {
				iResult = recv(clientSock, recvbuf, DEFAULT_BUFLEN, 0);
				if (iResult >= 0) {
					printf("\nReceived Message: %s\n", std::string(recvbuf).substr(0, iResult).c_str());
					broadcast(std::string(recvbuf).substr(0, iResult));
				}
				//TODO: WHILE TRUE
			} while (1);
		}
	}

	void WinConn::requestLocalInput() {
		do {
			std::string messageToSend = std::to_string(CLIENT_TO_SERVER);
			std::cout << "What do you want to send to clipboard?" << std::endl << "> ";
			std::getline(std::cin, messageToSend);
			broadcast(messageToSend);
			//TODO: WHILE TRUE
		} while (1);
	}
}