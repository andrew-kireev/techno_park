//
// Created by Andrew Kireev on 30.03.2020.
//
#include <iostream>
#include <sys/epoll.h>
#include <algorithm>
#include <exception.h>

#include "Server.h"

int main() {

    epoll_server::Server server("127.0.0.1", 8081);


    std::string v;
    auto read = [&v, &server](epoll_server::Connection& c)
    {
        v.clear();
        v.resize(1024, ' ');
        int fd = c.get_con();
        ssize_t bytes = c.read(v.data(), v.size() + 1);
        if (bytes <= 0) {
            server.erase_connection(fd);
        }
        else{
            v.shrink_to_fit();
            v.erase(std::remove(v.begin(), v.end(), ' '), v.end());
            v.erase(v.find('\n'));
            std::cout << "Полученно: " << v << std::endl;
            v.push_back('\n');
            server.modify_epoll(c.get_con(), EPOLLOUT);
        }
    };


    auto write = [&v, &server](epoll_server::Connection& c)
    {
        int fd = c.get_con();
        ssize_t bytes = c.write(v.data(), v.size() + 1);
        if (bytes <= 0) {
            server.erase_connection(fd);
        }
        else{
            v.shrink_to_fit();
            v.erase(std::remove(v.begin(), v.end(), ' '), v.end());
            v.erase(v.find('\n'));
            std::cout << "Отправленно: " << v << std::endl;
            v.push_back('\n');
            server.modify_epoll(c.get_con(), EPOLLIN);
        }
    };

    try {
        server.set_handlers(read, write);
        server.event_loop();
    } catch (epoll_server::TcpException& ex){
        std::cerr << ex.what() << std::endl;
        server.event_loop();
    }
    return 0;

}
