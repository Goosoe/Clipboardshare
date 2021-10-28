#pragma once
#include <vector>
#include<string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include<thread>
#include "../Data/DataHandler.h"
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
		virtual bool broadcast(const std::string* msg) = 0;
		virtual void subscribeDataHandler(Data::DataHandler* handler) = 0;

	protected:
		#define DEFAULT_PORT "8008"
		#define DEFAULT_BUFLEN 512
		bool isServer = false;
		Data::DataHandler* handler;
		//socket ID's
		std::vector<int> sockets;
		
		virtual void receiveThread(const int socket) = 0;
		
		//std::vector<int> socketsToBroadcast;
		//notifySubscribers()
		//std::vector<subscribers> (processID?)
		//virtual bool disconnect() = 0;
		/*CLIENT FUNCTIONS*/

	};
}