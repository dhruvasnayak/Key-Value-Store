#ifndef SERVER_H
#define SERVER_H

#include "parser.h"
#include "executor.h"
#include "storage.h"
#include <string>

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();

    void start();

private:
    int port;
    int serverSocket;
    StorageEngine storage;
    Parser parser;
    CommandExecutor executor;

    void handleClient(int clientSocket);
    std::string readLine(int clientSocket);
    void sendResponse(int clientSocket, const std::string& response);
    void closeSocket(int socket);
};

#endif // SERVER_H
