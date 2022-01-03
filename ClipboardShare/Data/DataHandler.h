#pragma once
#include<string>
#include "../Bridge/SysBridge.h"

namespace Connector {
	class AConnector;
}
namespace Ui {
	class CliView;
}

namespace Data {
	static const std::string NULL_TERMINATOR = "\0";
	/*Used to hold the necessary data to successfully send a message and broadcast it if necessary*/
	struct Message {
		//If message is created locally, change this value only
		std::string* msg;
		int senderSocketId = -1;
		bool toBroadcast = true;
	};
	/*Central class that processes all the data and distributes the jobs between the other classes*/
	class DataHandler {
	public:
		DataHandler(Connector::AConnector* connector = nullptr, bool isServer = false) {
			setConnector(connector);
			this->isServer = isServer;
		}
		/*Used to process messages received from a socket or locally through the CLI*/
		void handleMessage(Message* message);
		/*Connects to a AConnector object*/
		void setConnector(Connector::AConnector* connector) { this->connector = connector; };
		/*Connects to a CLIView object*/
		void setView(Ui::CliView* view) { this->view = view; };
		/*Invokes the connector to initialize a socket connection with the given ip*/
		void initSocket(const std::string* ip = nullptr);
		/*Sets the flag used to identify if this client is the Host/Server*/
		void setServerFlag(const bool isServer) { this->isServer = isServer; };
		/*Gets the flag that defines if this client is the Host/Server*/
		bool getServerFlag() const { return isServer; };
	private:
		bool isServer;
		Connector::AConnector* connector = nullptr;
		Ui::CliView* view = nullptr;
		/*Invokes the connector to broadcast a message*/
		void broadcast(Message* message);
		/*updates the client view and clipboard with the values from the message*/
		void updateClient(Message* message);
	};
}