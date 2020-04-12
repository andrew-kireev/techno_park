//
// Created by Andrew Kireev on 30.03.2020.
//

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>
#include <functional>
#include <unordered_map>

#include "Connection.h"

namespace server {

    class Server {
    public:
        Server(const std::string& ip, uint16_t port, std::function<void(Connection&)> callback_read,
               std::function<void(Connection&)> callback_write);

        ~Server() noexcept;

        void close();

        Connection accept();

        void open(const std::string& ip, int port);

        void set_max_connection(int num_connections = 128);

        void create_epoll();

        void add_epoll(int fd,  uint32_t events);

        void event_loop();

        void accept_clients();

        void handle_client(int fd, uint32_t event);

    private:
        int listenfd_;
        int epoll_;
        std::unordered_map<int, Connection> connects_;
        std::function<void(Connection&)> callback_read_;
        std::function<void(Connection&)> callback_write_;
        bool server_stat_ = false;
        size_t max_connection_ = 128;
    };


}
#endif //TCP_SERVER_H
