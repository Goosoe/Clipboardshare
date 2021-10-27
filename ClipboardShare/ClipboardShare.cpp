// ClipboardShare.cpp : Defines the entry point for the application.
//

#include "ClipboardShare.h"
#include <stdio.h>

int main(){
	std::string input;
	bool wrongInput = true;
	Connector::WinConn conn = Connector::WinConn() ;
	while (wrongInput) {
		std::cout << "Which mode do you want to initialize? (h)ost or (c)lient? h/c" << std::endl;
		std::getline(std::cin, input);
		//server
		if (input.compare("h") == 0) {
			conn.initServer();
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
			//needs to sent input like this because its the only way the
			//information is replicated and not lost when getting out of scope
			conn.initClient(&input);
			wrongInput = false;
		
		}
		else {
			std::cout << "Wrong input" << std::endl;
		}
	}
	std::cin.get();
	return 0;
}
