//
// Created by stepan on 21.06.2024.
//

#include <iostream>
#include <utility>
#include "TcpServer.h"

TcpServer::TcpServer(std::string ip, int port) : port(port), ip(std::move(ip)) {}

void TcpServer::start() {

    serverStatus = true;

    serverThread = std::thread([this] {

        server_sock = socket(AF_INET, SOCK_STREAM, 0);

        if (server_sock < 0) {
            perror("[-]Socket error");
            exit(1);
        }
        printf("[+]TCP server socket created.\n");

        memset(&server_addr, '\0', sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

        n = bind(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if (n < 0) {
            perror("[-]Bind error");
            exit(1);
        }
        printf("[+]Bind to the port number: %d\n", port);

        listen(server_sock, N);
        printf("Listening...\n");

        socklen_t addr_size = sizeof(client_addr);
        while (serverStatus) {
            int client_sock = accept(server_sock, (struct sockaddr *) &client_addr, &addr_size);

            if (client_sock == -1) {
                printf("error");

                std::cout << strerror(errno) << std::endl;
                exit(0);
            }

            std::thread([=]  {
                printf("[+]Client ip %s connected.\nNumber of connections %d\n",(char *) inet_ntoa((struct in_addr) client_addr.sin_addr), ++numberOfCurrentConnections);
                addClientCloseConnectionListener(client_sock, client_addr);
            }).detach();
        }
    });

    serverThread.detach();

}

void TcpServer::addClientCloseConnectionListener(int client_sock, sockaddr_in &client_addr) {
    char buffer[1024];
    while (true) {
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);

        if (strlen(buffer) == 0) {
            printf("Client with ip %s was disconnected\nNumber of connections %d\n",(char *) inet_ntoa((struct in_addr) client_addr.sin_addr), --numberOfCurrentConnections);
            close(client_sock);
            break;
        }

        printf("message from client with ip %s : %s\n", (char *) inet_ntoa((struct in_addr) client_addr.sin_addr),buffer);
        MessageBox mb;
        bool isParse = Serialization<MessageBox>::fromJson(buffer,mb);
        if(isParse){
            if(typeHandlers.count(mb.eventType)){
                typeHandlers.at(mb.eventType)(mb.payload);
            }
        }
    }
}
