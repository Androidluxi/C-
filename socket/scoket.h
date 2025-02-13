//
// Created by lux on 2025/2/13.
//

#ifndef C___LEARN_SCOKET_H
#define C___LEARN_SCOKET_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <csignal>
#include <sys/wait.h>    // 补充waitpid

#define PORT 12000     // 端口
#define BUFFER_SIZE 1024

class TcpClient {
private:
    int sockfd;
    struct sockaddr_in server_addr;

public:
    TcpClient(const std::string &server_ip, int server_port);

    ~TcpClient();

    void connectToServer();

    void sendData(const std::string &message);

    void receiveData();

    void closeConnection();
};


class TcpServer {
private:
    int server_fd;

public:
    TcpServer();

    ~TcpServer();

    void acceptConnection();
};


void run_server();
void run_client();

void start_run();
#endif //C___LEARN_SCOKET_H
