//
// Created by Andrew Kireev on 30.03.2020.
//


#include <exception>

#include "Connection.h"


namespace server {

    Connection::Connection(int ip,int port) : src_addr(ip), src_port(port){
        sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
        if(sock < 0){
            throw std::runtime_error("Ошибка создания сокета");
        }

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port); // или любой другой порт...
        addr.sin_addr.s_addr = htonl(ip);
    }

    void Connection::write(const void *data, std::size_t len) {
        ssize_t bytes = ::write(stdout_, data, len);
        if(bytes < 0){
            throw std::runtime_error("Write не смог ничего написать");
        }
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

    void Connection::read(void *data, std::size_t len) {
        if (in_is_readable == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        ssize_t bytes = ::read(stdin_, data, len);
        if (bytes == 0) {
            in_is_readable = false;
        } else if (bytes < 0) {
            throw std::runtime_error("Метод ничего не смог прочитать");
        }
    }

    void Connection::readExact(void *data, size_t len) {
        if (in_is_readable == false){
            throw std::runtime_error("Дескриптор вывода закрыт");
        }

        std::size_t read = 0, last_it = 0;
        ssize_t num;
        while (read != len) {
            num = ::read(stdin_, static_cast<char *>(data) + read, len - read);
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
        if(::close(listenfd_) < 0){
            throw std::runtime_error("Ошибка закрытия сервера");
        }
        is_open_ = false;
    }

    bool is_open() const{
        return is_open_;
    }

    void set_timeout(int time){
        timeout = time;
    }

}