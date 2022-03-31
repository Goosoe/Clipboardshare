# CMakeList.txt : CMake project for ClipboardShare, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.14)

# Add source to this project's executable.
# add_subdirectory(ClipboardXX)

find_package(Threads REQUIRED)
# find_package(X11 REQUIRED)
# if(NOT X11_FOUND)
#     message("ERROR: x11 not found")
# endif()

# target_link_libraries(ClipboardShare ${CMAKE_THREAD_LIBS_INIT})
#TODO: createlib with either windows or linux libs
#TODO: find packages pthreads and xvn and install

if(WIN32)
    add_executable (ClipboardShare "ClipboardShare.cpp" "Connector/WinConn.cpp"  "Data/DataHandler.cpp" "Ui/CliView.cpp"  "Bridge/SysBridge.cpp")
    target_link_libraries(ClipboardShare wsock32 ws2_32)
elseif(UNIX)
    add_executable (ClipboardShare "ClipboardShare.cpp" "Connector/LinConn.cpp"  "Data/DataHandler.cpp" "Ui/CliView.cpp"  "Bridge/SysBridge.cpp")
    target_link_libraries(ClipboardShare ${CMAKE_THREAD_LIBS_INIT} )
    # target_link_libraries(ClipboardShare ${X11_xcb_LIB})
  #TODO: else deny
endif()
# target_link_libraries(ClipboardShare ClipboardXX)

# TODO: Add tests and install targets if needed.