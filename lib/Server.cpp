//
// Created by Andrew Kireev on 30.03.2020.
//

#include "Server.h"
#include <exception>
#include <stdexcept>
#include <zconf.h>
#include <arpa/inet.h>

namespace server {

    Server::Server(std::string ip, int port) {
        listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (listenfd_ < 0) {
            throw std::runtime_error("Ошибка создание сокета");
        }

        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        if (::inet_aton(ip.c_str(), &addr_.sin_addr) == 0){

}
        if (bind(listenfd_, (struct sockaddr *) &addr_, sizeof(addr_)) < 0) {
            throw std::runtime_error("Ошибка bind");
        }
        listen(listenfd_, max_connection_);
        server_stat = true;
    }

    void Server::close(){
        if(::close(listenfd_) < 0){
            throw std::runtime_error("Ошибка закрытия сервера");
        }
        server_stat = false;
    }

    Connection Server::accept(){
        sockaddr_in client_addr;
        int sock = ::accept(listenfd_, (struct sockaddr *)&client_addr,
                            reinterpret_cast<socklen_t *>(sizeof(client_addr)));
        if(sock < 0){
            throw std::runtime_error("Ошибка соединения");
        }
        Connection con(ip_, addr_.sin_port);
        return con;
    }

    void Server::open(std::string ip, int port){
        Server(ip, port);
    }

    void Server::set_max_connection(int num_connections){
        max_connection_ = num_connections;
    }
}
