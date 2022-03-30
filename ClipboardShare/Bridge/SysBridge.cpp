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

// #include "Windows.h"
// #include "winuser.h"

// #elif __unix__
/*UNIX INCLUDES*/

// #endif
namespace Bridge {

#ifdef _WIN32
/*WINDOWS IMPLEMENTATION*/
void SysBridge::clearWindow() {
    /*TODO: not safe & only appliable on windows*/
    system("cls");
}

// void SysBridge::sendToClipboard(const std::string* msg) {
//     OpenClipboard(GetDesktopWindow());
//     EmptyClipboard();
//     HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, msg->size() + 1);
//     if (!hg) {
//         CloseClipboard();
//         return;
//     }
//     /*TODO: hmmm*/
//     memcpy(GlobalLock(hg), msg->c_str(), msg->size() + 1);
//     GlobalUnlock(hg);
//     SetClipboardData(CF_TEXT, hg);
//     CloseClipboard();
//     GlobalFree(hg);
// }
#elif __unix__
/*UNIX IMPLEMENTATION*/
void SysBridge::clearWindow() {
    system("clear");
}
#endif

void SysBridge::sendToClipboard(std::string* msg) {
    board << msg->c_str();
}

// clipboardxx::clipboard SysBridge::getClipboardInstance(){
//     if
// }

}  // namespace Bridge
