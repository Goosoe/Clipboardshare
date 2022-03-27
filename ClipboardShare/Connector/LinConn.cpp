#include "LinConn.h"
#ifdef __unix__
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <thread>

#include "../Data/DataHandler.h"

namespace Connector {
void LinConn::initServer() {
    int sockfd, clientSocket;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = DEFAULT_PORT;
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while ((clientSocket = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen))) {
        sockets.push_back(clientSocket);
        std::thread t = std::thread([this, clientSocket] {
            receiveLoop(clientSocket);
        });
        t.detach();
    }
    // newsockfd = accept(sockfd,
    //                    (struct sockaddr *)&cli_addr,
    //                    &clilen);
    close(clientSocket);
    close(sockfd);
}

void LinConn::initClient(const std::string *ip) {
    int connectSocket = 0, reader;
    struct sockaddr_in serv_addr;
    char *message = "A message from Client !";
    char buffer[DEFAULT_BUFLEN] = {0};
    if ((connectSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error !");
        return;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = DEFAULT_PORT;
    // Converting IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip->c_str(), &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address ! This IP Address is not supported !\n");
        return;
    }
    if (connect(connectSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed : Can't establish a connection over this socket !");
        return;
    }
    // send(socket, message, strlen(message), 0);
    // printf("\nClient : Message has been sent !\n");
    sockets.push_back(connectSocket);
    receiveLoop(connectSocket);

    // reader = read(connectSocket, buffer, DEFAULT_BUFLEN);
    // printf("%s\n", buffer);
    close(connectSocket);
}

void LinConn::receiveLoop(const int socket) {
    if (!sockets.size() || handler == nullptr) {
        std::cout << "No socket connection or DataHandler defined" << std::endl;
        return;
    }

    char recvbuf[DEFAULT_BUFLEN];
    int iResult;

    do {
        if (!sockets.size() || handler == nullptr) {
            std::cout << "No socket connection or DataHandler defined" << std::endl;
            return;
        }
        bzero(recvbuf, DEFAULT_BUFLEN);
        iResult = read(socket, recvbuf, DEFAULT_BUFLEN - 1);

        // if (n < 0) error("ERROR reading from socket");
        // printf("Here is the message: %s\n", recvbuf);
        // // n = write(socket, "I got your message", 18);
        // if (n < 0) error("ERROR writing to socket");

        // iResult = recv(socket, recvbuf, DEFAULT_BUFLEN, 0);
        if (iResult > 0) {
            std::string msg = std::string(recvbuf).substr(0, iResult);
            while (iResult == DEFAULT_BUFLEN && msg.substr(msg.length() - 3, msg.length() - 1) != Data::NULL_TERMINATOR) {
                iResult = recv(socket, recvbuf, DEFAULT_BUFLEN, 0);
                msg.append(std::string(recvbuf).substr(0, iResult));
            }
            Data::Message message = {&msg, socket, false};
            handler->handleMessage(&message);
        } else {
            iResult = close(socket);
            removeSocket(socket);
        }
    } while (iResult > 0);
}

bool LinConn::broadcast(Data::Message *message) {
    int socket = -1;
    for (int i = 0; i < sockets.size(); i++) {
        socket = sockets.at(i);
        if (socket != message->senderSocketId) {
            send(socket, message->msg->c_str(), message->msg->size(), 0);
        }
    }
    return true;
}

void error(const char *msg) {
    perror(msg);
    exit(1);
}
}  // namespace Connector
#endif
