#pragma once
#include "AConnector.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


namespace Connector {
	class WinConn : public AConnector {
	public:
		void initServer() override;
		void initClient(const std::string* ip) override;
		bool broadcast(const std::string* msg) override;
	
	protected:

	private:
		void receiveLoop(const int socket);
		bool disconnect();
	};
}
