//
// Created by Andrew Kireev on 30.03.2020.
//


#include <exception>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#include "Connection.h"
#include "exception.h"



namespace epoll_server {


    Connection::Connection(const std::string& ip, uint16_t port) : dst_addr_(ip), dst_port_(port){
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd_ < 0){
            close();
            throw TcpException("socket creating error");
        }
        connect(dst_addr_, port);
    }

    Connection::Connection(int sockfd, const sockaddr_in& sock): sockfd_(sockfd),
                                                                 dst_port_(sock.sin_port){
    }

    Connection::Connection(int fd) : sockfd_(fd){}

    Connection::Connection(Descriptor&& fd) : sockfd_(std::move(fd)){}


    Connection::~Connection() noexcept{
        try {
            if(!is_opened()) {
                close();
            }
        } catch (TcpException& er){
            std::cerr << "closing fail" << er.what() << std::endl;
        }
    }

    size_t Connection::write(const void *data, std::size_t len) {
        if(sockfd_ == -1){
            throw TcpException("closed descriptor");
        }
        ssize_t bytes = ::write(sockfd_, data, len);


        if (bytes < 0){
            if (errno == EAGAIN || errno == EWOULDBLOCK){
                return 0;
            }
            throw TcpException("could not write anything");
        }
        is_readable = true;
        return bytes;
    }



    void Connection::writeExact(const void *data, size_t len) {
        size_t wr = 0, last_it = 0;
        while (wr != len) {
            wr += write(static_cast<const char*>(data) + wr, len - wr);
            if (wr == last_it) {
                throw TcpException("received not enough to write");
            }
            last_it = wr;
        }
    }

    size_t Connection::write_buffer(size_t size){
        buffer.resize(size);
        write(buffer.data(), size);
        buffer_ws = buffer;
        is_readable = true;
        return buffer.size();
    }
    size_t Connection::read_buffer(const void *data){
        read(buffer.data(), buffer.size());
        is_readable = false;
        return buffer.size();
    }

    size_t Connection::read(void *data, std::size_t len) {
        if (!is_readable || sockfd_ == -1){
            throw TcpException("closed descriptor");
        }
        ssize_t bytes = ::read(sockfd_, data, len);


        if (bytes < 0){
            is_readable = false;
            if (errno == EAGAIN || errno == EWOULDBLOCK){
                return 0;
            }
            throw TcpException("could not read anything");
        }

        if (bytes == 0) {
            is_readable = false;
        }

        return bytes;
    }

    void Connection::readExact(void *data, size_t len) {
        std::size_t read = 0, last_it = 0;
        size_t num;
        while (read != len) {
            num = ::read(sockfd_, static_cast<char *>(data) + read, len - read);
            if(num < 0 && read == 0){
                throw TcpException("could not read anything");
            }
            read += num;
            if (read == last_it) {
                throw TcpException("received not enough to read");
            }
            last_it = read;
        }
    }

    void Connection::close(){
        if(sockfd_ != -1) {
            sockfd_ = -1;
            if (::close(sockfd_) < 0) {
                throw TcpException("close failedyyyyyyyy");
            }
        }
        sockfd_ = -1;
    }

    bool Connection::is_opened() const {
        if(sockfd_ != -1) return true;
        return false;
    }

    void Connection::set_timeout(int time){
        timeval timeout{time, .tv_usec = 0};
        if (setsockopt(sockfd_,
                       SOL_SOCKET,
                       SO_RCVTIMEO,
                       &timeout,
                       sizeof(timeout)) < 0){
            throw TcpException("timeout failed");
        }

    }

    void Connection::send_size(const size_t& data)
    {
        writeExact(&data, sizeof(size_t));
    }

    void Connection::recv_size(size_t& data)
    {
        readExact(&data, sizeof(size_t));
    }

    void Connection::connect(const std::string& addr, uint16_t port) {
        struct sockaddr_in addr_{};
        dst_addr_ = addr;

        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = ::inet_addr(addr.c_str());
        if(::connect(sockfd_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0){
            close();
            throw TcpException("connecting failed");
        }
    }

    int Connection::get_con() const {
        return sockfd_;
    }

    std::string Connection::get_buffer() const{
        return buffer_ws;
    }


}