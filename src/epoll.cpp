#include "epoll.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Epoll::PORT = 8080;
Epoll::MAX_EVENTS = 64;
Epoll::BUFFER_SIZE = 1024;

int Epoll::initilize() {
    
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);

    if(serverFd < 0) {
        std::cout << "ERROR: socket creation failed" << std::endl;
        return 0;
    }

    int opt = 1;
    setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    bind(serverFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    // Decide on the maximum number ofconnections (2nd parameter of listen) that can be queued for this socket.

    listen(serverFd, 5);

    return serverFd;
}

void Epoll::run(int serverFd) {
    // Implementation of the event loop using epoll

    int epollFd = epoll_create1(0);

    epoll_event event{};

    event.events = EPOLLIN;
    event.data.fd = serverFd;

    epoll_ctl(epollFd, EPOLL_CTL_ADD, serverFd, &event);

    epoll_event events[MAX_EVENTS];

    while(true) {

        int ready = epoll_wait(epollFd, events, MAX_EVENTS, -1);

        for(int i =0; i < ready; i++){
            if(events[i].data.fd = serverFd) {
                handleNewConnection(serverFd);  
            } 
            else {
                char buffer[BUFFER_SIZE];
                int bytesRead = read(events[i].data.fd, buffer, BUFFER_SIZE);
                if(bytesRead <= 0) {
                    handleDisconnect(events[i].data.fd);
                } else {
                    handleClientRead(events[i].data.fd);
                }
            }
        }
    }
}

void Epoll::close(int serverFd) {
    close(serverFd);
}