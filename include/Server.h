//
// Created by Andrew Kireev on 30.03.2020.
//

#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <exception>

#include "Connection.h"

namespace server {

    class Server {
    public:
        Server(int ip, int port);

        void close();

        Connection accept();

        void open(int ip, int port);

        void set_max_connection(int num_connections);

    private:
        int listenfd_;
        bool server_stat = false;
        struct sockaddr_in addr_;
    };


}
#endif //TCP_SERVER_H
