//
// Created by lux on 2025/2/13.
//
#include "scoket.h"

TcpServer::TcpServer() {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "进程 id =" << std::to_string(getpid())<<"    Socket creation failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout <<"进程 id =" << std::to_string(getpid())<< "    Server is listening on port " << PORT << std::endl;
}

TcpServer::~TcpServer() {
    close(server_fd);
}

void TcpServer::acceptConnection() {
    sockaddr_in address;
    int addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen);
    if (new_socket < 0) {
        std::cerr << "进程 id =" << std::to_string(getpid())  <<"   Accept failed" << std::endl;
        return;
    }

    char buffer[BUFFER_SIZE];
    int valread = read(new_socket, buffer, BUFFER_SIZE);
    std::cout << "进程 id =" << std::to_string(getpid()) <<"    Message from client: " << buffer << std::endl;

    const char *response = "Hello,from server";
    send(new_socket, response, strlen(response), 0);
    std::cout <<"进程 id =" << std::to_string(getpid())  << "    Response sent to client" << std::endl;

    close(new_socket);
}


//int main() {
//     TcpServer server;
//    while (true) {
//        server.acceptConnection();
//    }
//    return 0;
//}