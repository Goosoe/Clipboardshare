# CMakeList.txt : CMake project for ClipboardShare, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(Threads REQUIRED)
# Add source to this project's executable.


# target_link_libraries(ClipboardShare ${CMAKE_THREAD_LIBS_INIT})
#TODO: createlib with either windows or linux libs

if(WIN32)
    add_executable (ClipboardShare "ClipboardShare.cpp" "Connector/WinConn.cpp"  "Data/DataHandler.cpp" "Ui/CliView.cpp"  "Bridge/SysBridge.cpp")
    target_link_libraries(ClipboardShare wsock32 ws2_32)
elseif(UNIX)
    add_executable (ClipboardShare "ClipboardShare.cpp" "Connector/LinConn.cpp"  "Data/DataHandler.cpp" "Ui/CliView.cpp"  "Bridge/SysBridge.cpp")
    target_link_libraries(ClipboardShare ${CMAKE_THREAD_LIBS_INIT})
  #TODO: else deny
endif()
# TODO: Add tests and install targets if needed.