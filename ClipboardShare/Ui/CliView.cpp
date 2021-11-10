#pragma once
#include "CliView.h"
#include "..\Data\DataHandler.h"

namespace Ui {

	std::mutex CliView::screenLock;

	CliView::CliView(Data::DataHandler* dHandler) {
		setDataHandler(dHandler);
		//must be the last thing being called
		getSetupInput();
	}

	void CliView::updateScreen(const std::string* clipboardMsg) {
		//if (clipboardMsg->empty()) {
		//	clipboardMsg = const_cast<const std::string*>(&oldMessage);
		//}
		Bridge::SysBridge::clearWindow();
		if (isConnected) {
			screenLock.lock();
			if (dHandler->getServerFlag()) {
				std::cout << "HOST" << std::endl;
			}
			else {
				std::cout << "CLIENT" << std::endl;
			}
			//screen.subBanner =
			std::cout << "Clipboard\n> " + *clipboardMsg << std::endl;
			std::cout << "Share to clipboard\n> ";
			screenLock.unlock();
		}
	}

	std::string CliView::readInput() {
		std::string messageToSend;
		std::getline(std::cin, messageToSend);
		//copies the message 
		//oldMessage = std::string(messageToSend);
		return messageToSend;
	}

	void CliView::getSetupInput() {
		bool wrongInput = true;
		if (dHandler == nullptr) {
			std::cout << "DataHandler not defined" << std::endl;
			return;
		}
		while (wrongInput) {
			std::cout << "Which mode do you want to initialize? (h)ost or (c)lient? h/c" << std::endl;
			std::string input = readInput();

			//server
			if (input.compare("h") == 0) {
				dHandler->setServerFlag(true);
				wrongInput = false;
			}
			//client
			else if (input.compare("c") == 0) {
				std::cout << "What IP should it connect to? Press 'l' to localhost" << std::endl;
				input = readInput();
				if (input.compare("l") == 0) {
					//TODO: this sucks
					input = "127.0.0.1";
				}
				wrongInput = false;

			}
			else {
				std::cout << "Wrong input" << std::endl;
			}
			if (!wrongInput) {
				std::thread t = std::thread(
					[this, input]() {
						dHandler->initSocket(&input);
					});
				t.detach();
			}
		}
		updateScreen(&std::string(""));
	}

	void CliView::readInputLoop() {
		std::string input;
		while (1) {
			input = readInput();
			Data::Message msg;
			msg.msg = &input;
			dHandler->handleMessage(&msg);
		}
	}
}