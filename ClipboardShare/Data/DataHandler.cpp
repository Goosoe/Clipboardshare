#include "DataHandler.h"
namespace Data{
	void DataHandler::broadcast(const std::string* message) {
		//connector->broadcast(message);

	}
	std::string* DataHandler::handleMessage(const std::string* message) {
		return &std::string("a");
	}
//	void DataHandler::subscribeDataHandler(Connector::AConnector* connector) {
//		this->connector = connector;
//	}
}