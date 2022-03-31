#pragma once
#include <string>
#include <vector>

namespace Data {
struct Message;
class DataHandler;
}  // namespace Data

/*
 * Abstract class that all the different Connectors need to extend
 * Creates an interface which is common between all connectors.
 */
namespace Connector {
class AConnector {
   public:
    AConnector(){};
    /*Starts a listener socket and launches threads with sockets connected to clients*/
    virtual void initServer() = 0;
    /*Starts a client socket and tries to connect to the given ip*/
    virtual void initClient(const std::string* ip) = 0;
    /*Broadcasts a message to all registered sockets*/
    virtual bool broadcast(Data::Message* message) = 0;
    /*Connects to a DataHandler object*/
    inline void setDataHandler(Data::DataHandler* handler) { this->handler = handler; };

   protected:
// TODO: why defines?
#define DEFAULT_PORT 8008
#define DEFAULT_BUFLEN 512
    Data::DataHandler* handler = nullptr;
    // socket ID's
    std::vector<int> sockets;
    /*Removes a socket with the specific id from the sockets vector*/
    void removeSocket(const int socketId) {
        for (int i = 0; i < sockets.size(); i++) {
            if (sockets[i] == socketId) {
                sockets.erase(sockets.begin() + i);
                break;
            }
        }
    };
};
}  // namespace Connector