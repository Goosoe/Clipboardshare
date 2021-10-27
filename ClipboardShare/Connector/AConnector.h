#pragma once
#include <vector>
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<thread>
/*
* Abstract class that all the different Connectors need to extend
* Creates an interface which is common between all connectors.
*/
namespace Connector {
	class AConnector {

	public:
		/*Server constructor*/
		AConnector(){};
		virtual void initServer() = 0;
		virtual void initClient(const std::string* ip) = 0;

	protected:
		#define DEFAULT_PORT "8008"
		#define DEFAULT_BUFLEN 512
		#define SERVER_TO_CLIENT 1
		#define CLIENT_TO_SERVER 0

		
		//std::vector<int> socketsToBroadcast;
		virtual bool broadcast(const std::string& msg) = 0;
		virtual bool disconnect() = 0;

		/*CLIENT FUNCTIONS*/
		virtual void initClientSocketThread(const int typeOfConnection, const std::string* ip) = 0;

		/*SERVER FUNCTIONS*/
		virtual void initServerSocketThread(const void* socket) = 0;
	};
}