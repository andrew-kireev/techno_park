//
// Created by Andrew Kireev on 30.03.2020.
//


#include <exception>
#include <zconf.h>
#include <arpa/inet.h>
#include <iostream>

#include "Connection.h"


namespace server {

    Connection::Connection(std::string ip, uint16_t port) : dst_addr(std::move(ip)), dst_port(port), is_open_(true){
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd_ < 0){
            throw std::runtime_error("Ошибка создания сокета");
        }
        connect(dst_addr, port);
    }

    Connection::Connection(int& sockfd, const sockaddr_in& sock): sockfd_(sockfd),
                                                                 dst_port(sock.sin_port), is_open_(true){
        if(sockfd_ < 0){
            throw std::runtime_error("Ошибка создания сокета");
        }
        sockfd = -1;
    }


    Connection::~Connection() noexcept{
        try {
            close();
        } catch (std::runtime_error& er){
            std::cerr << "Ошибка закрытия дескриптора" << er.what() << std::endl;
        }
    }

    ssize_t Connection::write(const void *data, std::size_t len) {
        ssize_t bytes = ::write(sockfd_, data, len);
        if(bytes < 0){
            throw std::runtime_error("Write не смог ничего написать");
        }
        return bytes;
    }

    void Connection::writeExact(const void *data, size_t len) {
        ssize_t wr = 0, last_it = 0;
        while (wr != len) {
            wr += write(static_cast<const char*>(data) + wr, len - wr);
            if (wr == last_it) {
                throw std::runtime_error("Полученно недостаточное количество байт для записи");
            }
            last_it = wr;
        }
    }

    ssize_t Connection::read(void *data, std::size_t len) {
        if (!is_open_){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        ssize_t bytes = ::read(sockfd_, data, len);
        if (bytes == 0) {
            is_open_ = false;
        } else if (bytes < 0) {
            throw std::runtime_error("Метод ничего не смог прочитать");
        }
        return bytes;
    }

    void Connection::readExact(void *data, size_t len) {
        if (!is_open_){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        std::size_t read = 0, last_it = 0;
        ssize_t num;
        while (read != len) {
            num = ::read(sockfd_, static_cast<char *>(data) + read, len - read);
            if(num < 0 && read == 0){
                throw std::runtime_error("Невозможно ничего прочитать");
            }
            read += num;
            if (read == last_it) {
                throw std::runtime_error("Полученно недостаточное количество байт для чтения");
            }
            last_it = read;
        }
    }

    void Connection::close(){
        if(::close(sockfd_) < 0){
            throw std::runtime_error("Ошибка закрытия сервера");
        }
        is_open_ = false;
    }

    bool Connection::is_opened() const {
        return is_open_;
    }

    void Connection::set_timeout(int time){
        timeval timeout{time, .tv_usec = 0};
        if (setsockopt(sockfd_,
                       SOL_SOCKET,
                       SO_RCVTIMEO,
                       &timeout,
                       sizeof(timeout)) < 0){
            throw std::runtime_error("Ошибка установления timeout");
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
        is_open_ = true;
        struct sockaddr_in addr_{};
        dst_addr = addr;

        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = ::inet_addr(addr.c_str());
        if(::connect(sockfd_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0){
            throw std::runtime_error("Ошибка соединения");
        }
    }

}