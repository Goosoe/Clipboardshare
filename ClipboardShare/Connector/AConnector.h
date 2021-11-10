#pragma once
#include <vector>
#include <string>

namespace Data{
	struct Message;
	class DataHandler;
}

/*
* Abstract class that all the different Connectors need to extend
* Creates an interface which is common between all connectors.
*/
namespace Connector {
	class AConnector {

	public:
		AConnector(){};
		virtual void initServer() = 0;
		virtual void initClient(const std::string* ip) = 0;
		virtual bool broadcast(Data::Message* message) = 0;
		virtual void setDataHandler(Data::DataHandler* handler) { this->handler = handler; };

	protected:
		#define DEFAULT_PORT "8008"
		#define DEFAULT_BUFLEN 512
		Data::DataHandler* handler = nullptr;
		//socket ID's
		std::vector<int> sockets;
	};
}