#pragma once
#include<string>
namespace Connector{
	class AConnector;
}
namespace Ui{
	class CliView;
}

namespace Data {
	class DataHandler {
	public:
		DataHandler(Connector::AConnector* connector = nullptr, bool isServer = false) {
			setConnector(connector);
			this->isServer = isServer;
		}

		void broadcast(const std::string* message);
		void handleMessage(const std::string* message);
		void setConnector(Connector::AConnector* connector) { this->connector = connector; };
		void setView(Ui::CliView* view) { this->view = view; };
		void initProgram(const std::string* ip = nullptr);
		void setServerFlag(const bool isServer) { this->isServer = isServer; };
		bool getServerFlag() const { return isServer; };
	private:
		bool isServer;
		Connector::AConnector* connector = nullptr;
		Ui::CliView* view = nullptr;
	};
}