#pragma once
#include "CliView.h"
#include "..\Data\DataHandler.h"

namespace Ui {

	CliView::CliView(Data::DataHandler* dHandler) {
		bool wrongInput = true;
		setDataHandler(dHandler);
		if (dHandler == nullptr) {
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
					[this, dHandler, input]() {
						dHandler->initProgram(&input);
					});
				t.detach();
			}
		}
		updateScreen(&std::string(""));
	}

	void CliView::updateScreen(const std::string* clipboardMsg) {

		screenLock.lock();
		if (isConnected) {
			if (dHandler->getServerFlag()) {
				std::cout << "\n\n\nHOST\n";
			}
			else {
				std::cout << "\n\n\nCLIENT\n";
			}
			//screen.subBanner =
			std::cout << "\n\n";
			std::cout << "Clipboard\n> " + *clipboardMsg + "\n";
			std::cout << "Share to clipboard\n> ";
		}
		screenLock.unlock();
	}

	std::string CliView::readInput() {
		std::string messageToSend;
		std::getline(std::cin, messageToSend);
		return messageToSend;
	}

	void CliView::readInputLoop() {
		std::string input;
		while (1) {
			input = readInput();
			dHandler->broadcast(&input);
		}
	}

	void CliView::clearScreen() {
		/*TODO: not safe*/
		system("cls");
	}

}