//
// Created by Andrew Kireev on 30.03.2020.
//

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <string>

#include "Connection.h"

namespace server {

    class Server {
    public:
        Server(const std::string& ip, uint16_t port);

        ~Server() noexcept;

        void close();

        Connection accept();

        void open(const std::string& ip, int port);

        void set_max_connection(int num_connections);

    private:
        int listenfd_;
        bool server_stat_ = false;
        size_t max_connection_ = 1;
    };


}
#endif //TCP_SERVER_H
