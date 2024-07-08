//
// Created by stepan on 24.06.2024.
//

#include "TcpClient.h"

TcpClient::TcpClient(std::string ip, int port) : port(port), ip(std::move(ip)) {}

void TcpClient::connectToServer() {
    if (!connectedToServer) {
        waitingConnectionTask = std::thread([this]() {
            createSocket();
            int isConnected = true;
            while (true) {
                if (!connectedToServer) {
                    printf("Trying to connect to server by ip %s and port %d\n", ip.c_str(), port);
                    isConnected = connect(client_sock, (struct sockaddr *) &addr, sizeof(addr));
                }
                if (!connectedToServer && isConnected==0) {
                    printf("Successfully connected to server by ip %s and port %d\n", ip.c_str(), port);
                    waitServerResponseMessages();
                    connectedToServer = true;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        });
        waitingConnectionTask.detach();
    } else {

    }
}

void TcpClient::waitServerResponseMessages() {
    responseThread = std::thread([this]() {
        while (true) {
            bzero(buffer_rec, 1024);
            recv(client_sock, buffer_rec, sizeof(buffer_rec), 0);
            if (strlen(buffer_rec) == 0) {
                printf("Server with ip %s and port %d was disconnected\n", ip.c_str(), port);
                close(client_sock);
                createSocket();
                break;
            }
        }
        connectedToServer = false;
    });
    responseThread.detach();
    connectedToServer = true;
}

void TcpClient::sendMessage(const std::string &obj) {
    if (connectedToServer) {
        bzero(buffer_send, 1024);
        obj.copy(buffer_send, obj.length());
        //TODO need to connection with java (last byte is "\n")
        buffer_send[strlen(buffer_send)] = 0xA;
        send(client_sock, buffer_send, strlen(buffer_send), 0);
    } else {
        printf("Cannot send the message. No tcp connection with socket ip %s and port %d\n", ip.c_str(), port);
    }
}

void TcpClient::createSocket() {
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
}
