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
	struct Message {
		std::string* msg;
		int senderSocket = -1;
		bool toSend = true;
	};

	class DataHandler {
	public:
		DataHandler(Connector::AConnector* connector = nullptr, bool isServer = false) {
			setConnector(connector);
			this->isServer = isServer;
		}

		void handleMessage(Message* message);
		void setConnector(Connector::AConnector* connector) { this->connector = connector; };
		void setView(Ui::CliView* view) { this->view = view; };
		void initSocket(const std::string* ip = nullptr);
		void setServerFlag(const bool isServer) { this->isServer = isServer; };
		bool getServerFlag() const { return isServer; };
	private:
		bool isServer;
		Connector::AConnector* connector = nullptr;
		Ui::CliView* view = nullptr;
		void broadcast(Message* message);
		//updates the client view and clipboard with the values from the message
		void updateClient(Message* message);
	};
}