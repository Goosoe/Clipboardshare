#pragma once
#include<string>
/*Abstract class bridge between the program and OS*/
namespace Bridge {
	class SysBridge {
	public:
		/*Clears the CLI window of the respective OS*/
		static void clearWindow();
		/*sends a string message to the clipboard of the respective OS*/
		static void sendToClipboard(const std::string* msg);
	};
}