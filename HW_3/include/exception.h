//
// Created by Andrew Kireev on 12.04.2020.
//

#ifndef TCP_EXCEPTION_H
#define TCP_EXCEPTION_H

#include <string>
#include <exception>

class TcpException : public std::exception{
public:
    explicit TcpException(std::string msg) : msg_(std::move(msg)) {};

    const char* what() const noexcept {
        return msg_.c_str();
    };
private:
    std::string msg_;
};

#endif //TCP_EXCEPTION_H
