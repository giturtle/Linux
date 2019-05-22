/*=============================================================== 
*   描    述：基于封装的TcpSocket类完成tcp服务端程序 
*       1. 创建套接字
*       2. 绑定地址信息
*       3. 开始监听
*       4. 获取已经连接成功的客户端socket
*       5. 接收数据
*       6. 发送数据
*       7. 关闭套接字
================================================================*/

#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include "tcpsocket.hpp"

void sigcb(int no){
    while (waitpid(-1, NULL, WNOHANG) > 0);
}
int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("./tcp_srv ip  port\n");
        return -1;
    }

    signal(SIGCHLD, sigcb);
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);

    TcpSocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind(ip, port));
    CHECK_RET(sock.Listen());

    while(1) {
        TcpSocket clisock;
        struct sockaddr_in cliaddr;
        //accept是阻塞获取已经完成的连接
        if (sock.Accept(clisock, &cliaddr) == false) {
            continue;
        }
        printf("new connect client:%s:%d\n", 
                inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

        int pid = fork();
        if (pid == 0) {
            while(1){
                std::string buf;
                clisock.Recv(buf);
                printf("client say:%s\n", buf.c_str());

                buf.clear();
                std::cout<<"server say:";
                fflush(stdout);
                std::cin>>buf;
                clisock.Send(buf);
            }
        }
        clisock.Close();
    }
    sock.Close();
    return 0;
}
