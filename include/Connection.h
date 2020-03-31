//
// Created by Andrew Kireev on 29.03.2020.
//

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <cstdio>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>


namespace server {

    class Connection {
    public:
        Connection(std::string ip, int port);

        ssize_t write(const void *data, size_t size);

        ssize_t read(void *data, size_t size);

        void close();

        bool is_opened() const;

        void writeExact(const void *data, size_t size);

        void readExact(void *data, size_t size);

        void set_timeout(int time);

        void connect(const std::string& addr, int port);


    private:
        int sockfd_;
        std::string src_addr;
        std::string dst_addr;
        int src_port;
        int dst_port;
        bool is_open_ = false;
        int timeout = 0;

    };


}


#endif //TCP_CONNECTION_H
