#pragma once
#include <string>

// #include "../ClipboardXX/include/clipboardxx.hpp"

/**
 * @brief Class that bridges the program with the OS and allows the interaction from the program to the OS.
 *  It verifies the OS and implements the functions appropriately.
 *
 */
namespace Bridge {
class SysBridge {
   public:
    /*Clears the CLI window of the respective OS*/
    static void clearWindow();
    /*sends a string message to the clipboard of the respective OS*/
    static void sendToClipboard(std::string* msg);

   private:
    // static clipboardxx::clipboard board;
};
}  // namespace Bridge