#pragma once
#include <vector>
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include"AnswerType.h"
#include"MessageType.h"
/*
* Abstract class that all the different Connectors need to override
* Creates an interface which is common between all connectors.
*/
namespace Connector {
	class AConnector {

	public:
		#define DEFAULT_PORT "8008"
		virtual bool broadcast(const std::string* message) = 0;
		virtual bool disconnect() = 0;
		virtual int connectToServer(const std::string* ip) = 0;
		virtual int prepareServerSocket() = 0;
		//virtual bool sendTo(const std::string* ip, std::string* message);

	protected:
		//bool isHost;
		//const std::string* ip;
		std::vector<const std::string*> connections;
		
		///*Constructor for the server*/
		//AConnector(const bool isHost = true) {
		//	this->isHost = true; 
		//};

		/*Constructor for the client*/
		//AConnector() { 
		//	this->isHost = false;
		//	this->ip = ip;
		//};

		void addConnection(const std::string* ip) { connections.push_back(ip); };

		void removeConnection(const std::string* ipToRemove) {
			for (int i = 0; i < connections.size(); i++) {
				if (connections.at(i)->compare(*ipToRemove) == 0) {
					//TODO: Check if it erases correctly
					connections.erase(connections.begin() + i);
					break;
				}
			}
		};
	};
}