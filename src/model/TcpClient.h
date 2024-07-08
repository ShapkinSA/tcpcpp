//
// Created by stepan on 24.06.2024.
//

#ifndef TCP_TCPCLIENT_H
#define TCP_TCPCLIENT_H


#include <string>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
#include <atomic>

class TcpClient {
public:
    std::string ip = "127.0.0.1";
    int port = 5566;

    int client_sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer_rec[1024];
    char buffer_send[1024];
    int n;

    std::atomic_bool connectedToServer{false};

    std::thread waitingConnectionTask;
    std::thread responseThread;

    TcpClient(std::string ip, int port);

    void connectToServer();

    void waitServerResponseMessages();

    void sendMessage(const std::string &obj);

    void createSocket();

};


#endif //TCP_TCPCLIENT_H
