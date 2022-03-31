#pragma once
#include "AConnector.h"

namespace Connector {
class LinConn : public AConnector {
   public:
    LinConn(){};
    void initServer() override;
    void initClient(const std::string* ip) override;
    bool broadcast(Data::Message* message) override;

   protected:
   private:
    void receiveLoop(const int socket);
    bool disconnect();
};
}  // namespace Connector
