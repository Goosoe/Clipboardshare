# CMakeList.txt : CMake project for ClipboardShare, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ClipboardShare "ClipboardShare.cpp" "ClipboardShare.h"  "Connector/AConnector.h" "Connector/WinConn.cpp" "Connector/MessageType.h" "Connector/AnswerType.h" "Connector/WinConn.h")
if(WIN32)
  target_link_libraries(ClipboardShare wsock32 ws2_32)
endif()
# TODO: Add tests and install targets if needed.
