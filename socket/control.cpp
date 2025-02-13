//
// Created by lux on 2025/2/13.
//

#include "scoket.h"

void signal_handler(int sig) {
    // 释放资源、关闭socket等操作
    std::cout <<"进程 id =" << std::to_string(getpid())  <<    " Received signal " << sig << ", exiting..." << std::endl;
    exit(0);
}


void run_server() {
    signal(SIGTERM, signal_handler);
    TcpServer server;
    while (true) {
        server.acceptConnection();
    }
}

void run_client() {
    TcpClient client("127.0.0.1", 12000);
    client.connectToServer();
    client.sendData("Test message from client");
    client.receiveData();
}

void start_run() {
    //启动服务器进程
    pid_t server_pid = fork();
    if (server_pid == 0) {
        run_server();
        exit(0);
    } else {
        sleep(3);  // 等待服务器启动
        run_client();
    }
    // 新增回收逻辑
    kill(server_pid, SIGTERM); // 先发送终止信号
    waitpid(server_pid, nullptr, 0); // 等待子进程结束
}
