// ClipboardShare.cpp : Defines the entry point for the application.
//

#include <stdio.h>

#ifdef _WIN32
#include "Connector/WinConn.h"
#elif __unix__
#include "Connector/LinConn.h"
#endif

#include "Data/DataHandler.h"
#include "Ui/CliView.h"


int main() {
    //Connector::AConnector *conn = nullptr;
#ifdef _WIN32
    Connector::WinConn conn = Connector::WinConn();
#elif __unix__
    conn = &Connector::LinConn conn();
#endif
 
    Data::DataHandler dHandler(&conn);

    conn.setDataHandler(&dHandler);

    Ui::CliView view(&dHandler);

    dHandler.setView(&view);

    view.readInputLoop();

    return 0;
}
