#ifndef EPOLL_H
#define EPOLL_H

class Epoll {
public:
    constexpr int PORT;
    constexpr int MAX_EVENTS;
    constexpr int BUFFER_SIZE;
    int initilize();
    void run(int serverFd);
    void close(int serverFd);

    void registerSocker(int fd, EventType events);
    void unregisterSocket(int fd);
    void modifySocketEvent(int fd, EventType events);

private:
    void processEvents();
    void handleNewConnection(int fd);
    void handleClientRead(int fd);
    void handleClientWrite(int fd);
    void handleDisconnect(int fd);
    void cleanUpIdleConnections();
};

#endif // EPOLL_H