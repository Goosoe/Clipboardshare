#pragma once
#include<string>
/*Abstract class bridge between the program and OS*/
namespace Bridge {
	class SysBridge {
	public:
		static void clearWindow();
		static void sendToClipboard(const std::string* msg);
	};
}