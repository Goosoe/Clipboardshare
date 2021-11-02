#include <iostream>
#include "DataHandler.h"
#include "../Connector/AConnector.h"
#include "../Ui/CliView.h"
namespace Data {

	/*Broadcasts a message if it's valid (not empty)*/
	void DataHandler::broadcast(const std::string* message) {
		if (connector == nullptr || view == nullptr) {
			std::cout << "The connector or view is not linked to this DataHandler" << std::endl;
			return;
		}
		if (message->empty()) {
			return;
		}
		connector->broadcast(message);
		view->updateScreen(message);
	}

	void DataHandler::handleMessage(const std::string* message) {
		if (message->empty()) {
			return;
		}

		if (isServer) {
			broadcast(message);
		}
		else {
			if (view == nullptr) {
				std::cout << "The view is not connected to this DataHandler" << std::endl;
				return;
			}
			view->updateScreen(message);
			Bridge::SysBridge::sendToClipboard(message);
		}
	}

	void DataHandler::initSocket(const std::string* ip) {
		if (isServer) {
			connector->initServer();
		}
		else {
			connector->initClient(ip);
		}
	}
}