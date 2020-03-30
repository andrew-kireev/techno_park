//
// Created by Andrew Kireev on 29.03.2020.
//

#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include <cstdio>
#include <sys/types.h>
#include <netinet/in.h>


namespace server {

    class Connection {
    public:
        Connection(int ip,int port);

        void write(const void *data, size_t size);

        void read(void *data, size_t size);

        void close();

        bool is_opened() const;

        ssize_t writeExact(const void *data, size_t size);

        ssize_t readExact(void *data, size_t size);

        void set_timout(int time);

        void connect(int addr,int port);


    private:
        int sockfd_;
        int src_addr;
        int dst_addr;
        int src_port;
        int dst_port;
        bool is_open_ = false;
        int timeout = 0;

    };


}


#endif //TCP_CONNECTION_H
