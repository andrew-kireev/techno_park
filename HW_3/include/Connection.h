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
        friend class Server;

        Connection(std::string ip, const uint16_t port);

        ~Connection() noexcept;

        size_t write(const void *data, size_t size);

        size_t read(void *data, size_t size);

        void close();

        [[nodiscard]] bool is_opened() const;

        void writeExact(const void *data, size_t size);

        void readExact(void *data, size_t size);

        void set_timeout(int time);

        void connect(const std::string& addr, uint16_t port);

        void send_size(const size_t& data);

        void recv_size(size_t& data);

    private:
        Connection(int sock_fd, const sockaddr_in& sock_info);
        
        int sockfd_;
        std::string dst_addr_;
        uint16_t dst_port_;
        bool is_open_ = false;
    };


}


#endif //TCP_CONNECTION_H
