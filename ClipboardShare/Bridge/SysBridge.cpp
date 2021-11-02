#pragma once
#include "SysBridge.h"
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include "Windows.h"
#include "winuser.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <complex>

namespace Bridge {
	void SysBridge::clearWindow() {
		/*TODO: not safe & only appliable on windows*/
		system("cls");
	}

	void SysBridge::sendToClipboard(const std::string* msg) {
		OpenClipboard(GetDesktopWindow());
		EmptyClipboard();
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, msg->size() + 1);
		if (!hg) {
			CloseClipboard();
			return;
		}
		memcpy(GlobalLock(hg), msg->c_str(), msg->size() + 1);
		GlobalUnlock(hg);
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
	}
}