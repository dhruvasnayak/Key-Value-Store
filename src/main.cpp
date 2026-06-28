#include "server.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);

    if (port <= 0 || port > 65535) {
        std::cerr << "ERROR: Invalid port number. Port must be between 1 and 65535" 
                  << std::endl;
        return 1;
    }

    TcpServer server(port);
    server.start();

    return 0;
}
