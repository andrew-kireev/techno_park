//
// Created by Andrew Kireev on 30.03.2020.
//
#include <iostream>
#include <sys/epoll.h>

#include "Server.h"

int main() {

    auto read = [](server::Connection& c){
        std::string msg;
        msg.resize(5);
        ssize_t bytes =  c.read(msg.data(), msg.size());
        msg.shrink_to_fit();
        std::cout << "Received " << bytes << " bytes " <<  msg << std::endl;
    };
    auto write = [](server::Connection& c){
        std::string s;
        std::cin >> s;
        c.write(s.data(), s.size());
    };
    server::Server server("127.0.0.1", 8082, read, write);
    try {
        server.event_loop();
    } catch (...){
        server.event_loop();
    }
    return 0;

}
