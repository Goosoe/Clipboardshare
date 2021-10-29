// ClipboardShare.cpp : Defines the entry point for the application.
//

#include "ClipboardShare.h"
#include <stdio.h>
#include <thread>
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

	Connector::WinConn conn = Connector::WinConn() ;
	Data::DataHandler dHandler = Data::DataHandler(&conn);
	conn.setDataHandler(&dHandler);
	Ui::CliView view = Ui::CliView(&dHandler);
	dHandler.setView(&view);
	
	view.readInputLoop();
	//waits for the ui input thread to finish
	//view.getViewThread()->join();
	//readInput(dHandler);
		
	//std::cin.get();
	//return 0;
}


