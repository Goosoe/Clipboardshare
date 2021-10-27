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
		virtual bool broadcast(const std::string& msg) = 0;
		virtual void subscribeDataHandler(Data::DataHandler* handler);

	protected:
		#define DEFAULT_PORT "8008"
		#define DEFAULT_BUFLEN 512
		bool isServer = false;
		//std::vector<int> socketsToBroadcast;
		//notifySubscribers()
		//std::vector<subscribers> (processID?)
		//virtual bool disconnect() = 0;
		//virtual void receiveThread() = 0;
		/*CLIENT FUNCTIONS*/

	};
}