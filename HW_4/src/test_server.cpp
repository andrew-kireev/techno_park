//
// Created by Andrew Kireev on 30.03.2020.
//
#include <iostream>
#include <sys/epoll.h>
#include <exception.h>

#include "Server.h"

int main() {

    epoll_server::Server server("127.0.0.1", 8081);


    std::string v;
    auto read = [&v, &server](epoll_server::Connection& c)
    {
        ssize_t bytes = c.read_buffer(v.data());
        if (bytes <= 0) {
            server.erase_connection(c);
        }
        else{
            server.modify_epoll(c.get_con(), EPOLLOUT);
        }
    };

    auto write = [&v, &server](epoll_server::Connection& c)
    {
        ssize_t bytes = c.write_buffer(v.size() + 1);
        if (bytes <= 0) {
            server.erase_connection(c);
        }
        else{
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
