#pragma once
#include "CliView.h"
#include "..\Data\DataHandler.h"
#include <thread>
namespace Ui {

	CliView::CliView(Data::DataHandler* dHandler) {
		bool wrongInput = true;
		setDataHandler(dHandler);
		if (dHandler == nullptr) {
			return;
		}
		while (wrongInput) {
			std::cout << "Which mode do you want to initialize? (h)ost or (c)lient? h/c" << std::endl;
			std::string input = *readInput();

			//server
			if (input.compare("h") == 0) {
				dHandler->setServerFlag(true);
				wrongInput = false;
			}
			//client
			else if (input.compare("c") == 0) {
				std::cout << "What IP should it connect to? Press 'l' to localhost" << std::endl;
				input = *readInput();
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
				std::thread t = std::thread([&dHandler, &input] {
					dHandler->initProgram(&input);
					});
				t.detach();

			}
		}
		std::thread t = std::thread([this] {
			readInputThread();
			});
		t.detach();

	}

	void CliView::updateScreen(const std::string* clipboardMsg) {
		//TODO:No bueno solution. Unnecessary cleanups
		screen.lines.clear();
		clearScreen();

		if (isConnected) {
			if (isServer) {
				screen.banner = "HOST\n";
			}
			else {
				screen.banner = "CLIENT\n";
			}
			//screen.subBanner =
			screen.lines.push_back(&screen.banner);
			screen.lines.push_back(&screen.subBanner);
			screen.lines.push_back(&std::string("Clipboard\n> " + *clipboardMsg));
			screen.lines.push_back(&std::string("Share to clipboard\n> "));
		}
	}

	std::string* CliView::readInput() {
		std::string messageToSend;
		std::getline(std::cin, messageToSend);
		return &messageToSend;
	}

	void CliView::readInputThread() {
		while (1) {
			dHandler->broadcast(readInput());
		}
	}
}


