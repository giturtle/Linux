/*=============================================================== 
*   描    述：实现以UdpSocket类封装udp常用操作 
================================================================*/

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSocket{
    public:
        UdpSocket():_sock(-1){}
        ~UdpSocket(){}
        bool Socket() {
            //int socket(int domain, int type, int protocol);
            _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (_sock < 0) {
                perror("socket error");
                return false;
            }
            return true;
        }
        bool Bind(std::string &ip, uint16_t port) {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            //uint16_t htons(uint16_t hostshort);
            addr.sin_port = htons(port);
            //in_addr_t inet_addr(const char *cp);
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            socklen_t len = sizeof(struct sockaddr_in);
            //int bind(int sockfd, struct sockaddr *addr, 
            //  socklen_t addrlen);
            int ret = bind(_sock, (struct sockaddr*)&addr, len);
            if (ret < 0) {
                perror("bind error");
                return false;
            }
            return true;
        }
        bool Recv(std::string &buf, struct sockaddr_in *saddr) {
            //ssize_t recvfrom(int sockfd, void *buf, size_t len, 
            //int flags, struct sockaddr *src_addr, socklen_t *addrlen);
            char tmp[1500] = {0};
            socklen_t len = sizeof(struct sockaddr_in);
            int ret = recvfrom(_sock, tmp, 1500, 0, 
                    (struct sockaddr*)saddr, &len);
            if (ret < 0) {
                perror("recvfrom error");
                return false;
            }
            buf.assign(tmp, ret);
            return true;
        }
        bool Send(std::string &buf, struct sockaddr_in *daddr){
            //ssize_t sendto(int sockfd, const void *buf, size_t len, 
            //int flags, struct sockaddr *dest_addr, socklen_t addrlen);
            socklen_t len = sizeof(struct  sockaddr_in);
            int ret = sendto(_sock, buf.c_str(), buf.size(), 0, 
                    (struct sockaddr*)daddr, len);
            if (ret < 0) {
                perror("sendto error");
                return false;
            }
            return true;
        }
        bool Close() {
            close(_sock);
            _sock = -1;
        }
    private:
        int _sock;
};
