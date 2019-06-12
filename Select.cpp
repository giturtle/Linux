#include <vector>
#include <iostream>
#include <sys/select.h>
#include "tcpsocket.hpp"

class Select{
    public:
        Select():_max_fd(-1){
            //void FD_ZERO(fd_set *set);
            //清空集合
            FD_ZERO(&_rfds);
        }
        bool Add(TcpSocket &sock) {
            //void FD_SET(int fd, fd_set *set);
            //将指定描述符添加到集合中
            int fd = sock.GetSockFd();
            FD_SET(fd, &_rfds);
            _max_fd = (fd > _max_fd) ? fd : _max_fd;
            return true;
        }
        bool Del(TcpSocket &sock) {
            //void FD_CLR(int fd, fd_set *set);
            //从集合中移除指定的描述符
            int fd = sock.GetSockFd();
            FD_CLR(fd, &_rfds);

            for (int i = _max_fd; i >= 0; i--) {
                //int  FD_ISSET(int fd, fd_set *set);
                //判断描述符是否在集合中
                //从max向前遍历，还在集合中的第一个就是最大的
                if (!FD_ISSET(i, &_rfds)) {
                    continue;
                }
                _max_fd = i;
                break;
            }
            return true;
        }
        bool Wait(std::vector<TcpSocket> &list, int timeout = 3000) {
            //int select(int nfds, fd_set *readfds, fd_set *writefds,
            //  fd_set *exceptfds, struct timeval *timeout);
            //返回值：>0 就绪的描述符个数   ==0 等待超时    <0 监控出错
            fd_set rfds = _rfds;
            struct timeval tv;
            tv.tv_sec = 0;
            tv.tv_usec = timeout * 1000;
            int ret = select(_max_fd + 1, &rfds, NULL, NULL, &tv);
            if (ret < 0) {
                perror("select error");
                return false;
            }else if (ret == 0) {
                std::cout << "timeout!!\n";
                return false;
            }
            //因为select返回后集合中保存的都是就绪的描述符（没有就绪的已经被移除）
            for (int i = 0; i <= _max_fd; i++) {
                if (FD_ISSET(i, &rfds)) {
                    TcpSocket sock;
                    sock.SetSockFd(i);
                    list.push_back(sock);
                }
            }
            return true;
        }
    private:
        fd_set _rfds;
        int _max_fd;
};

int main(){
    TcpSocket sock;
    CHECK_RIGHT(sock.Socket());
    CHECK_RIGHT(sock.Bind("0.0.0.0", 9000));
    CHECK_RIGHT(sock.Listen());

    Select s;
    s.Add(sock);
    while(1) {
        std::vector<TcpSocket> list;
        bool ret = s.Wait(list);
        if (ret == false) {
            continue;
        }
        for (int i = 0; i < list.size(); i++) {
            //遍历就绪列表，若就绪的描述符和监听描述符相等
            //应该获取新连接的客户端socket
            if (list[i].GetSockFd() == sock.GetSockFd()) {
                TcpSocket clisock;
                ret = sock.Accept(clisock);
                if (ret == false) {
                    continue;
                }
                s.Add(clisock);
            }else {
                std::string buf;
                ret = list[i].Recv(buf);
                if (ret == false) {
                    s.Del(list[i]);
                    list[i].Close();
                }
                std::cout << "client say: "<< buf << std::endl;
            }
        }
    }
    sock.Close();
    return 0;
}
