// ClipboardShare.cpp : Defines the entry point for the application.
//

#include <stdio.h>
#include"Connector/WinConn.h"
#include"Data/DataHandler.h"
#include"Ui/CliView.h"
int main(){
	Connector::WinConn conn = Connector::WinConn() ;

	Data::DataHandler dHandler = Data::DataHandler(&conn);

	conn.setDataHandler(&dHandler);

	Ui::CliView view = Ui::CliView(&dHandler);

	dHandler.setView(&view);
	
	view.readInputLoop();

	return 0;
}


