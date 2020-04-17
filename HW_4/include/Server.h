//
// Created by Andrew Kireev on 30.03.2020.
//

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>
#include <functional>
#include <unordered_map>

#include "Connection.h"

namespace epoll_server {

    class Server {
        using callback = std::function<void(Connection&)>;
    public:
        Server(const std::string& ip, uint16_t port);

        ~Server() noexcept;

        void close();

        void set_handlers(callback callback_read, callback callback_write);

        Connection accept();

        void open(const std::string& ip, int port);

        void set_max_connection(int num_connections = 128);

        void create_epoll();

        void add_epoll(int fd,  uint32_t events);

        void event_loop();

        void accept_clients();

        void handle_client(int fd, uint32_t event);

        void close_epoll();

        void erase_connection(int con);

        void modify_epoll(int fd, uint32_t events);

    private:
        int listenfd_;
        int epoll_;
        std::unordered_map<int, Connection> connects_;
        callback callback_read_;
        callback callback_write_;
        bool server_stat_ = false;
        bool epoll_stat = false;
        size_t max_connection_ = 128;
    };


}
#endif //TCP_SERVER_H
