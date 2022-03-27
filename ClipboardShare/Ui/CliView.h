#pragma once
#include <string>
#include <mutex>


namespace Data {
	class DataHandler;
};

namespace Ui {
	
	//Abstract CLI class that the cmd and bash will need to implement
	class CliView {
	public:

		CliView(Data::DataHandler* dHandler);
		/*Updates the screen with the message received*/
		void updateScreen(const std::string* clipboardMsg = nullptr);
		/*Setter for the flag that identifies if the client is connected to a server*/
		void setConnectedFlag(bool isConnected) { this->isConnected = isConnected; }
		/*Connects to a DataHandler object*/
		void setDataHandler(Data::DataHandler* dHandler) { this->dHandler = dHandler; };
		/*Starts the loop that is always reading input whenever given. Best used in a separate thread*/
		void readInputLoop();

	private:
		Data::DataHandler* dHandler;
		bool isConnected;
		static std::mutex screenLock;
		/*Specific part of the code where it reads the input*/
		std::string readInput();
		/*Starts the setup questions and gets the necessary input to start the client */
		void getSetupInput();
	};
}