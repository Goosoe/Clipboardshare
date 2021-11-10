#include <iostream>
#include "DataHandler.h"
#include "../Connector/AConnector.h"
#include "../Ui/CliView.h"
namespace Data {

	/*Broadcasts a message if it's valid (not empty)*/
	void DataHandler::broadcast(Message* message) {

		connector->broadcast(message);
		updateClient(message);
	}


	void DataHandler::handleMessage(Message* message) {
		if (connector == nullptr || view == nullptr) {
			std::cout << "The connector or view is not linked to this DataHandler" << std::endl;
			return;
		}

		if (message->msg->empty()) {
			return;
		}
		if (message->toBroadcast || isServer) {
			broadcast(message);
		}
		else {
			updateClient(message);
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
	
	void DataHandler::updateClient(Message* message) {
		view->updateScreen(message->msg);
		Bridge::SysBridge::sendToClipboard(message->msg);
	}
}