//
// Created by Andrew Kireev on 30.03.2020.
//

#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/epoll.h>


#include "Server.h"
#include "exception.h"

namespace epoll_server {

    using std::make_pair;

    Server::Server(const std::string& ip, uint16_t port){
        open(ip, port);
    }

    Server::~Server() noexcept{
        try {
            close();
        } catch (TcpException& er){
            std::cerr << "close failed" << er.what() << std::endl;
        }
    }

    void Server::set_handlers(callback callback_read, callback callback_write){
        callback_read_ = std::move(callback_read);
        callback_write_ = std::move(callback_write);
    }

    void Server::close(){
        listenfd_.close();
        epoll_.close();
    }


    Connection Server::accept(){
        sockaddr_in client_addr{};
        socklen_t size = sizeof(client_addr);
        int sock = ::accept(listenfd_, reinterpret_cast<sockaddr*>(&client_addr), &size);
        if(sock < 0){
            throw TcpException("connecting failed");
        }
        return Connection(sock, client_addr);
    }


    void Server::open(const std::string& ip, int port){
        listenfd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        if (listenfd_ < 0) {
            throw TcpException("socket creating failed");
        }

        struct sockaddr_in addr{};

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        if (bind(listenfd_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0) {
            throw TcpException("Ошибка bind");
        }
        set_max_connection(max_connection_);

        create_epoll();
    }

    void Server::create_epoll(){
        int temp_epoll = epoll_create(1);
        if(temp_epoll < 0){
            throw TcpException("error crating epoll");
        }
        epoll_ = temp_epoll;
        add_epoll(listenfd_, EPOLLIN | EPOLLOUT);
    }


    void Server::add_epoll(int fd,  uint32_t events){
        epoll_event event{};
        event.data.fd = fd;
        event.events = events;
        if(epoll_ctl(epoll_, EPOLL_CTL_ADD, fd, &event) < 0){
            throw TcpException("epoll_ctl error");
        }
        connects_.emplace(fd, Connection(fd));
    }

    void Server::event_loop(){
        epoll_event events[max_connection_];

        while(true){
            int nfds = epoll_wait(epoll_, events, max_connection_, -1);
            if(nfds < 0){
                if(errno == EINTR) continue;
                throw TcpException("epoll wait failed");
            }

            for(int n = 0; n < nfds; ++n){
                int fd = events[n].data.fd;
                uint32_t event = events[n].events;

                if(fd == listenfd_){
                    accept_clients();
                } else{
                    handle_client(fd, event);
                }
            }
        }
    }


    void Server::accept_clients(){
        sockaddr_in cliaddr{};
        socklen_t clilen = sizeof(cliaddr);
        int fd;

        while(true){
            fd = accept4(listenfd_, (sockaddr*)&cliaddr, &clilen, SOCK_NONBLOCK);
            if(fd < 0){
                if(errno == EINTR)
                    continue;
                else if (errno == EAGAIN || errno == EWOULDBLOCK)
                    return;
                else
                    throw TcpException("accept4 failed");
            }
            add_epoll(fd, EPOLLOUT);
        }
    }

    void Server::handle_client(int fd, uint32_t event){
        if(event & EPOLLHUP || event & EPOLLERR){
            connects_.erase(fd);
            return;
        }
        if (event & EPOLLIN) {
            callback_read_(connects_.at(fd));
        } else if (event & EPOLLOUT) {
            callback_write_(connects_.at(fd));
        }
    }


    void Server::set_max_connection(int num_connections){
        max_connection_ = num_connections;
        if(listen(listenfd_, max_connection_) < 0){
            throw TcpException("listen failed");
        }
    }

    void Server::modify_epoll(int fd, uint32_t events){
        epoll_event event{};
        event.data.fd = fd;
        event.events = events;

        if (epoll_ctl(epoll_, EPOLL_CTL_MOD, fd, &event) < 0) {
            throw TcpException("epoll_ctl error");
        }
    }


    void Server::erase_connection(const Connection& con){
        connects_.erase(con.get_con());
    }
}





