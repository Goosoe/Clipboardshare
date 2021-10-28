#pragma once
#include <string>
#include <vector>
#include <iostream>

//namespace Data {
//	class DataHandler;
//};

namespace Ui {
	struct Screen {
		std::string banner = "ClipBoard";
		std::string subBanner = "\n";
		std::vector<std::string*> lines;
	};

	//Abstract CLI class that the cmd and bash will need to implement
	class CliView {
	public:
		CliView(Data::DataHandler* dHandler);

		void updateScreen(const std::string* clipboardMsg = nullptr);

		void setConnectedFlag(bool isConnected) {
			this->isConnected = isConnected;
		};

		void setServerFlag(bool isServer) {
			this->isServer = isServer;
		};

		void setDataHandler(Data::DataHandler* dHandler) { this->dHandler = dHandler; };

	private:
		Data::DataHandler* dHandler;
		bool isConnected;
		bool isServer;
		Screen screen;


		/*This works for Linux & Windows apparently*/
		void clearScreen() { std::cout << "\033[2J\033[1;1H"; };

		std::string* readInput();

		void readInputThread();
	};
}