#include "SysBridge.h"

#include <stdio.h>

// #ifdef _WIN32
/*WINDOWS INCLUDES*/
// #include <conio.h>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "Windows.h"
#include "winuser.h"

// #elif __unix__
/*UNIX INCLUDES*/

// #endif
namespace Bridge {

/*WINDOWS IMPLEMENTATION*/
#ifdef _WIN32
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
/*UNIX IMPLEMENTATION*/
#elif __unix__
void SysBridge::clearWindow() {
    system("clear");
}

void SysBridge::sendToClipboard(const std::string* msg) {
    // TODO: X11 is hard
    // https://github.com/Arian8j2/ClipboardXX
}

#endif
}  // namespace Bridge