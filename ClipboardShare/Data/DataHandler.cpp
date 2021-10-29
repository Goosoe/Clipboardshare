#include <iostream>
#include "DataHandler.h"
#include "../Connector/AConnector.h"
#include "../Ui/CliView.h"
namespace Data {
	void DataHandler::broadcast(const std::string* message) {
		if (connector == nullptr || view == nullptr) {
			std::cout << "The connector or view is not linked to this DataHandler" << std::endl;
			return;
		}
		//std::cout << std::endl << "sending message: " << *message << std::endl;
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
				std::cout << "The view is not connected to this DataHandler" << std::endl;
				return;
			}
			view->updateScreen(message);
		}
	}
	void DataHandler::initProgram(const std::string* ip) {
		if (isServer) {
			connector->initServer();
		}
		else {
			connector->initClient(ip);
		}
	}
}