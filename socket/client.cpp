//
// Created by lux on 2025/2/13.
//

#include "scoket.h"

TcpClient::TcpClient(const std::string &server_ip, int server_port) {
    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
}


TcpClient::~TcpClient() {
    closeConnection();
}


void TcpClient::connectToServer() {
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "进程 id =" << std::to_string(getpid()) << "    Connected to server\n";
}

void TcpClient::sendData(const std::string &message) {
    if (send(sockfd, message.c_str(), message.length(), 0) == -1) {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "进程 id =" << std::to_string(getpid()) << "    Message sent: " << message << std::endl;
}

void TcpClient::receiveData() {
    char buffer[1024];
    int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1) {
        perror("Recv failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0'; // Add null terminator
    std::cout << "进程 id =" << std::to_string(getpid())  << "    Received from server: " << buffer << std::endl;
}

void TcpClient::closeConnection() {
    close(sockfd);
}


//int main() {
//    TcpClient client("127.0.0.1", 12000);
//
//    client.connectToServer();
//    client.sendData("Hello, server!");
//    client.receiveData();
//
//    return 0;
//}

