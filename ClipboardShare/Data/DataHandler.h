#pragma once
#include<string>
namespace Connector{
	class AConnector;
}
namespace Data {
	class DataHandler {
	public:
		DataHandler(bool isServer = false) { this->isServer = isServer; }
		void broadcast(const std::string* message);
		void handleMessage(const std::string* message);
		void setConnector(Connector::AConnector* connector) { this->connector = connector; };
		void setServerFlag(const bool isServer) { this->isServer = isServer; };
		//std::string* 
	private:
		bool isServer;
		Connector::AConnector* connector = nullptr;
	};
}