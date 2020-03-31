//
// Created by Andrew Kireev on 30.03.2020.
//


#include <exception>
#include <stdexcept>
#include <zconf.h>
#include <arpa/inet.h>

#include "Connection.h"


namespace server {

    Connection::Connection(std::string ip,int port) : dst_addr(ip), dst_port(port){
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd_ < 0){
            throw std::runtime_error("Ошибка создания сокета");
        }

//        addr.sin_family = AF_INET;
//        addr.sin_port = htons(port); // или любой другой порт...
//        addr.sin_addr.s_addr = htonl(ip);
    }

    ssize_t Connection::write(const void *data, std::size_t len) {
        ssize_t bytes = ::write(STDOUT_FILENO, data, len);
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
        if (is_open_ == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        ssize_t bytes = ::read(STDIN_FILENO, data, len);
        if (bytes == 0) {
            is_open_ = false;
        } else if (bytes < 0) {
            throw std::runtime_error("Метод ничего не смог прочитать");
        }
    }

    void Connection::readExact(void *data, size_t len) {
        if (is_open_ == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        std::size_t read = 0, last_it = 0;
        ssize_t num;
        while (read != len) {
            num = ::read(STDIN_FILENO, static_cast<char *>(data) + read, len - read);
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
        timeout = time;
    }

    void Connection::connect(const std::string& addr, int port) {
        struct sockaddr_in addr_;

        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd_ < 0){
            throw std::runtime_error("Ошибка создания сокета");
        }

        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = ::inet_addr(addr.c_str());
        if(::connect(sockfd_, (struct sockaddr *)&addr_, sizeof(addr_)) < 0){
            throw std::runtime_error("Ошибка соединения");
        }
    }

}