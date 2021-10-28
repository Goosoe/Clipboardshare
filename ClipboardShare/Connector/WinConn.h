#pragma once
#include "AConnector.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

namespace Connector {
	class WinConn : public AConnector {
	public:
		/*Windows server constructor*/
		WinConn();
		void initServer() override;
		void initClient(const std::string* ip) override;
		bool broadcast(const std::string* msg) override;
		void subscribeDataHandler(Data::DataHandler* handler) override;
	
	protected:
		void receiveThread(const int socket) override;

	private:
		//TODO: auxiliary function - Remove/Move to on CLIView implementation
		void requestLocalInput();
		void initClientSocket(const std::string* ip = nullptr);
		bool disconnect();
	};
}
