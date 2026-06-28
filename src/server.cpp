#include "server.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

TcpServer::TcpServer(int port) 
    : port(port), serverSocket(-1), executor(storage) {}

TcpServer::~TcpServer() {
    if (serverSocket != -1) {
        closeSocket(serverSocket);
    }
}

void TcpServer::closeSocket(int socket) {
    if (socket != -1) {
        close(socket);
    }
}

std::string TcpServer::readLine(int clientSocket) {
    std::string line;
    char buffer[1];

    while (read(clientSocket, buffer, 1) > 0) {
        if (buffer[0] == '\n') {
            break;
        }
        if (buffer[0] != '\r') {
            line += buffer[0];
        }
    }

    return line;
}

void TcpServer::sendResponse(int clientSocket, const std::string& response) {
    std::string fullResponse = response + "\n";
    send(clientSocket, fullResponse.c_str(), fullResponse.length(), 0);
}

void TcpServer::handleClient(int clientSocket) {
    std::string command;

    while ((command = readLine(clientSocket)) != "") {
        if (command.empty()) {
            continue;
        }

        // Parse and execute command
        Command parsedCommand = parser.parse(command);
        std::string response = executor.execute(parsedCommand);

        // Send response
        sendResponse(clientSocket, response);
    }

    closeSocket(clientSocket);
}

void TcpServer::start() {
    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "ERROR: Could not create socket" << std::endl;
        return;
    }

    // Set socket options to reuse address
    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, 
                   &opt, sizeof(opt)) < 0) {
        std::cerr << "ERROR: Could not set socket options" << std::endl;
        closeSocket(serverSocket);
        return;
    }

    // Create address structure
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // Bind socket
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, 
             sizeof(serverAddr)) < 0) {
        std::cerr << "ERROR: Could not bind to port " << port << std::endl;
        closeSocket(serverSocket);
        return;
    }

    // Listen for connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "ERROR: Could not listen on port " << port << std::endl;
        closeSocket(serverSocket);
        return;
    }

    std::cout << "Server started on port " << port << std::endl;

    // Accept clients
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, 
                                  (struct sockaddr*)&clientAddr, 
                                  &clientAddrLen);
        if (clientSocket < 0) {
            std::cerr << "ERROR: Could not accept client connection" << std::endl;
            continue;
        }

        std::cout << "Client connected from " 
                  << inet_ntoa(clientAddr.sin_addr) << ":"
                  << ntohs(clientAddr.sin_port) << std::endl;

        handleClient(clientSocket);

        std::cout << "Client disconnected" << std::endl;
    }

    closeSocket(serverSocket);
}
