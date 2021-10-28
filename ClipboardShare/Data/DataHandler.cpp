#include "DataHandler.h"
#include "../Connector/AConnector.h"
#include <iostream>
namespace Data{
	void DataHandler::broadcast(const std::string* message) {
		if (connector == nullptr) {
			//TODO:ERROR
			return;
		}
		std::cout << "DEBUG: broadcasting msg: " << *message << std::endl;
		connector->broadcast(message);
	}

	void DataHandler::handleMessage(const std::string* message) {
		//TODO: Send to CLI & put in clipboard
		std::cout << "DEBUG: Handling msg: " << *message << std::endl;
		if (isServer){ 
			broadcast(message);
		}
	}
}