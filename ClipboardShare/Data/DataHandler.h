#pragma once
#include<string>
namespace Data {
	class DataHandler {
	public:
		DataHandler(bool isServer = false) { this->isServer = isServer; }
		void broadcast(const std::string* message);
		std::string* handleMessage(const std::string* message);
		//void subscribeDataHandler(AConnector* connector);

		//std::string* 
	private:
		bool isServer;
		//AConnector* connector;
	};
}