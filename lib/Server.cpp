//
// Created by Andrew Kireev on 30.03.2020.
//

#include "include/Server.h"

namespace server {

    Server::Server(int ip, int port) {
        listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if (listener < 0) {
            throw std::runtime_error("Ошибка создание сокета");
        }

        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = htonl(ip);
        if (bind(listenfd_, (struct sockaddr *) &addr_, sizeof(addr_)) < 0) {
            throw std::runtime_error("Ошибка bind");
        }
        listen(listenfd_, 1);
        server_stat = true;
    }

    void Server::close(){
        if(::close(listenfd_) < 0){
            throw std::runtime_error("Ошибка закрытия сервера");
        }
        server_stat = false;
    }

    Connection Server::accept(){
        int sock = accept(listener, NULL, NULL);
        if(sock < 0){
            throw std::runtime_error("Ошибка соединения");
        }
        Connction con(addr_.sin_addr.s_addr, addr_.sin_port);
        return con;
    }

    void Server::open(int ip, int port){
        Server(ip, port);
    }

    void Server::set_max_connection(int num_connections){

    }
}
