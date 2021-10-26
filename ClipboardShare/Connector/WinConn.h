#pragma once
#include "AConnector.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
namespace Connector {
	class WinConn : public AConnector{
	private:
		#define DEFAULT_BUFLEN 512
	protected:
			WSADATA wsaData;
			int iResult = 0;

		public:
			WinConn();
			bool broadcast(const std::string* message) override;
			bool disconnect() override;
			int startClient(const std::string* ip) override;
			int startHost() override;
	};
}
