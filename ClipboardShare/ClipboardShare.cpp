// ClipboardShare.cpp : Defines the entry point for the application.
//

#include <stdio.h>

#include "Data/DataHandler.h"
#include "Ui/CliView.h"

#ifdef _WIN32
#include "Connector/WinConn.h"
#elif __unix__
#include "Connector/LinConn.h"
#endif

int main() {
    // Connector::AConnector *conn = nullptr;
#ifdef _WIN32
    Connector::WinConn conn = Connector::WinConn();
#elif __unix__
    Connector::LinConn conn = Connector::LinConn();
#endif

    Data::DataHandler dHandler = Data::DataHandler(&conn);

    conn.setDataHandler(&dHandler);

    Ui::CliView view = Ui::CliView(&dHandler);

    dHandler.setView(&view);

    view.readInputLoop();

    return 0;
}