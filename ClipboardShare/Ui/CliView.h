#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include "../Bridge/SysBridge.h"

namespace Data {
	class DataHandler;
};

namespace Ui {
	//struct Screen {
	//	std::string banner = "ClipBoard";
	//	std::string subBanner = "\n";
	//	std::vector<std::string> lines;
	//};
	//Abstract CLI class that the cmd and bash will need to implement
	class CliView {
	public:

		CliView(Data::DataHandler* dHandler);
		void updateScreen(const std::string* clipboardMsg = nullptr);
		void setConnectedFlag(bool isConnected) { this->isConnected = isConnected; }
		void setDataHandler(Data::DataHandler* dHandler) { this->dHandler = dHandler; };
		void readInputLoop();

	private:
		Data::DataHandler* dHandler;
		bool isConnected;
		static std::mutex screenLock;
		//std::vector<std::string*> oldMessages;
		//std::string oldMessage;

		std::string readInput();
		void getSetupInput();
	};
}