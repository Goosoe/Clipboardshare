// ClipboardShare.cpp : Defines the entry point for the application.
//

#include "ClipboardShare.h"
#include <stdio.h>
Connector::WinConn conn;
Data::DataHandler dHandler;

//TODO: temporary before having cli
void requestLocalInput(Data::DataHandler& dHandler) {
	do {
		std::string messageToSend;
		std::cout << "What do you want to send to clipboard?" << std::endl << "> ";
		std::getline(std::cin, messageToSend);
		dHandler.broadcast(&messageToSend);
		//TODO: WHILE TRUE
	} while (1);
}

int main(){
	std::string input;
	bool wrongInput = true;
	Connector::WinConn conn = Connector::WinConn() ;
	Data::DataHandler dHandler = Data::DataHandler();
	conn.setDataHandler(&dHandler);
	dHandler.setConnector(&conn);


	while (wrongInput) {
		std::cout << "Which mode do you want to initialize? (h)ost or (c)lient? h/c" << std::endl;
		std::getline(std::cin, input);
		//server
		if (input.compare("h") == 0) {
			dHandler.setServerFlag(true);
			std::thread t = std::thread([&conn] {
				conn.initServer();
			});
			t.detach();
			wrongInput = false;
		}
		//client
		else if (input.compare("c") == 0) {
			std::cout << "What IP should it connect to? Press 'l' to localhost" << std::endl;
			std::getline(std::cin, input);
			if (input.compare("l") == 0) {
				//TODO: this sucks
				input = "127.0.0.1";
			}
			std::thread t = std::thread([&conn, &input] {
				conn.initClient(&input);
			});
			t.detach();
			wrongInput = false;
		
		}
		else {
			std::cout << "Wrong input" << std::endl;
		}
	}
	requestLocalInput(dHandler);
		
	std::cin.get();
	return 0;
}


