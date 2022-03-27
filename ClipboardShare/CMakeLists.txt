# CMakeList.txt : CMake project for ClipboardShare, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ClipboardShare "ClipboardShare.cpp" "Connector/AConnector.h" "Connector/WinConn.cpp" "Connector/WinConn.h" "Connector/LinConn.cpp" "Connector/LinConn.h" "Data/DataHandler.h" "Data/DataHandler.cpp" "Ui/CliView.h" "Ui/CliView.cpp" "Bridge/SysBridge.h" "Bridge/SysBridge.cpp"   )
if(WIN32)
  target_link_libraries(ClipboardShare wsock32 ws2_32)
endif()
# TODO: Add tests and install targets if needed.
