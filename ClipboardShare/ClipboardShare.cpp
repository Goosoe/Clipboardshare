// ClipboardShare.cpp : Defines the entry point for the application.
//

#include "ClipboardShare.h"
#include <stdio.h>

int main(){
	char mode;
	bool wrongInput = true;
	Connector::AConnector *conn = new Connector::WinConn();
	while (wrongInput) {
		std::cout << "Which mode do you want to initialize? (h)ost or (c)lient? h/c" << std::endl;
		std::cin >> mode;
		//server
		if (mode == 'h') {
			conn->startHost();
			wrongInput = false;
		}
		//client
		else if (mode == 'c') {
			std::cout << "What IP should it connect to? Press 'l' to localhost" << std::endl;
			std::string ip;
			std::cin >> ip;
			if (ip.compare("l") == 0) {
				//TODO: this sucks
				ip = "127.0.0.1";
			}
				conn->startClient(&ip);
				wrongInput = false;
		
		}
		else {
			std::cout << "Wrong input" << std::endl;
		}
	}
	std::cin.get();
	return 0;
}
