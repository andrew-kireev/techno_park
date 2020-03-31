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
        Server(std::string ip, int port);

        void close();

        Connection accept();

        void open(std::string ip, int port);

        void set_max_connection(int num_connections);

    private:
        int listenfd_;
        std::string ip_;
        bool server_stat = false;
        size_t max_connection_ = 1;
        struct sockaddr_in addr_;
    };


}
#endif //TCP_SERVER_H
