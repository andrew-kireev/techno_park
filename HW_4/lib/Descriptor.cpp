//
// Created by andrew on 18.04.2020.
//
#include <utility>
#include <unistd.h>

#include <Descriptor.h>


namespace epoll_server{

    Descriptor::Descriptor(const int fd) noexcept : fd_(fd){}

    Descriptor::Descriptor(Descriptor&& other) noexcept :
                fd_(std::exchange(other.fd_, -1)){}

    Descriptor::~Descriptor() noexcept{
        close();
    }

    void Descriptor::close() noexcept {
        if(fd_ != -1) {
            try{
                ::close(fd_);
            } catch (...) {
            }
        }
        fd_ = -1;
    }

    Descriptor::operator int() const noexcept{
        return fd_;
    }

    Descriptor& Descriptor::operator=(const int fd){
        close();
        fd_ = fd;
        return *this;
    }



}