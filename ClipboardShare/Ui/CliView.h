#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

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
	static std::mutex screenLock;
	class CliView {
	public:
		CliView(Data::DataHandler* dHandler);

		void updateScreen(const std::string* clipboardMsg = nullptr);

		void setConnectedFlag(bool isConnected) {
			this->isConnected = isConnected;
		}

		void setDataHandler(Data::DataHandler* dHandler) { this->dHandler = dHandler; };

		std::thread* getViewThread() {
			return inputThread;
		}
		void readInputLoop();

	private:
		Data::DataHandler* dHandler;
		bool isConnected;
		//Screen screen;
		std::thread* inputThread;
		/*std::thread* screenThread;*/

		//concurrency::concurrent_queue<std::string> updateQueue;

		//void screenUpdateThread();
		void clearScreen();
		std::string readInput();
	};
}