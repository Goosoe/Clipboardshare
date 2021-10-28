#include <iostream>
#include "DataHandler.h"
#include "../Connector/AConnector.h"
#include "../Ui/CliView.h"
namespace Data {
	void DataHandler::broadcast(const std::string* message) {
		if (connector == nullptr || view == nullptr) {
			//TODO:ERROR
			return;
		}
		connector->broadcast(message);
		view->updateScreen(message);
	}

	void DataHandler::handleMessage(const std::string* message) {
		//TODO: Send to CLI & put in clipboard
		std::cout << std::endl << "Received message: " << *message << std::endl;
		if (isServer) {
			broadcast(message);
		}
		else {
			if (view == nullptr) {
				//TODO:ERROR
				return;
			}
			view->updateScreen(message);
		}
	}
	void DataHandler::initProgram(std::string* ip = nullptr) {
		if (isServer) {
			connector->initServer();
		}
		else {
			connector->initClient(ip);
		}
	}
}