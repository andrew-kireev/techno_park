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
        Connection(std::string ip, uint16_t port);

        Connection(int& sock_fd, const sockaddr_in& sock_info);

        ~Connection() noexcept;

        ssize_t write(const void *data, size_t size);

        ssize_t read(void *data, size_t size);

        void close();

        bool is_opened() const;

        void writeExact(const void *data, size_t size);

        void readExact(void *data, size_t size);

        void set_timeout(int time);

        void connect(const std::string& addr, uint16_t port);

        void send_size(const size_t& data);

        void recv_size(size_t& data);

    private:
        int sockfd_;
        std::string dst_addr;
        uint16_t dst_port;
        bool is_open_ = false;
    };


}


#endif //TCP_CONNECTION_H
