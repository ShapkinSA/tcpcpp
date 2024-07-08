//
// Created by stepan on 21.06.2024.
//

#ifndef TCP_TCPSERVER_H
#define TCP_TCPSERVER_H

#include <string>
#include <thread>
#include <csignal>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <typeindex>
#include "../messageBoxModel/MessageBox.h"

#define N 5

class TcpServer {

public:
    int port;
    int numberOfCurrentConnections = 0;
    std::string ip;
    bool serverStatus;
    std::thread serverThread;
    int server_sock;
    struct sockaddr_in server_addr, client_addr;
    int n;

    std::map<std::string, std::function<void(const std::string & msg)>> typeHandlers;

    template<typename T>
    void setHandler(const std::string &type, std::function<void(T)> fun){
        typeHandlers[type] = [fun](const std::string & msg){
            T var;
            bool isParse = Serialization<T>::fromJson(msg,var);
            if(isParse)
                fun(var);
        };
    }


    TcpServer(std::string ip, int port);

    void start();

    void addClientCloseConnectionListener(int client_sock, sockaddr_in &client_addr);
};
#endif //TCP_TCPSERVER_H
