# ClipboardShare 
Born from necessity to share clipboards between computers in the same local network and the challenge to make as lightweight as possible. This program allows two or more computers to connect to each other, through sockets. Using a master/slave architecture connection, it is possible to share strings between all computers and automatically send them to the clipboards. The UI is console based. Initially, the objective was to run this on Windows but in order to challenge myself, I've also made it run in Unix machines.

## Future plans: 
- Learn about X11 for Linux clipboard
- Improve CLI UI quality
- QoL upgrades
- Fault handling if master fails

## Requirements:
- Cmake
- Linux: pthreads, xcb

# Running:
To run this program, just use cmake build and run the output file