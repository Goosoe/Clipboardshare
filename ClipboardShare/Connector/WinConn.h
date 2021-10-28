#pragma once
#include "AConnector.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include<thread>


namespace Connector {
	class WinConn : public AConnector {
	public:
		/*Windows server constructor*/
		//WinConn();
		/*The init classes are supposed to be initialized in a thread*/
		void initServer() override;
		void initClient(const std::string* ip) override;
		bool broadcast(const std::string* msg) override;
	
	protected:

	private:
		void receiveLoop(const int socket);
		bool disconnect();
	};
}
