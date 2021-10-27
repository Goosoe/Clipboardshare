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
	protected:
		bool broadcast(const std::string& msg) override;
		bool disconnect() override;

		void initClientSocketThread(const int typeOfConnection, const std::string* ip = nullptr) override;
		void initServerSocketThread(const void* socket) override;

	private:
		//TODO: auxiliary function - Remove on CLIView implementation
		void requestLocalInput();
		std::vector<SOCKET> socketsToBroadcast;
	};
}
