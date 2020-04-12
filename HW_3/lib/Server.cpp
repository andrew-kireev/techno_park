//
// Created by Andrew Kireev on 30.03.2020.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "Server.h"
#include "exception.h"

namespace server {

    Server::Server(const std::string& ip, uint16_t port) {
        open(ip, port);
    }

    Server::~Server() noexcept{
        try {
            close();
        } catch (std::runtime_error& er){
            std::cerr << "close failed" << er.what() << std::endl;
        }
    }

    void Server::close(){
        if(listenfd_ != -1 && !server_stat_) {
            if (::close(listenfd_) < 0) {
                throw TcpException("server close failed");
            }
        }
        server_stat_ = false;
    }

    Connection Server::accept(){
        sockaddr_in client_addr{};
        socklen_t size = sizeof(client_addr);
        int sock = ::accept(listenfd_, reinterpret_cast<sockaddr*>(&client_addr), &size);
        if(sock < 0){
            throw TcpException("connection failed");
        }
        return Connection(sock, client_addr);
    }


    void Server::open(const std::string& ip, int port){
        listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (listenfd_ < 0) {
            throw TcpException("creating socket failed");
        }

        struct sockaddr_in addr{};

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        if (bind(listenfd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
            close();
            throw TcpException("bind failed");
        }
        set_max_connection(max_connection_);
        server_stat_ = true;
    }


    void Server::set_max_connection(int num_connections){
        max_connection_ = num_connections;
        listen(listenfd_, max_connection_);
    }
}
