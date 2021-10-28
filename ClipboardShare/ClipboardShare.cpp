// ClipboardShare.cpp : Defines the entry point for the application.
//

#include "ClipboardShare.h"
#include <stdio.h>

//TODO: temporary before having cli
//void readInput(Data::DataHandler& dHandler) {
//	do {
//		std::string messageToSend;
//		std::cout << "What do you want to send to clipboard?" << std::endl << "> ";
//		std::getline(std::cin, messageToSend);
//		dHandler.broadcast(&messageToSend);
//		//TODO: WHILE TRUE
//	} while (1);
//}

int main(){
	std::string input;
	bool wrongInput = true;
	Connector::WinConn conn = Connector::WinConn() ;
	Data::DataHandler dHandler = Data::DataHandler(&conn);
	conn.setDataHandler(&dHandler);
	Ui::CliView view = Ui::CliView(&dHandler);
	

	
	//readInput(dHandler);
		
	//std::cin.get();
	//return 0;
}


