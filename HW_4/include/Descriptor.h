//
// Created by andrew on 18.04.2020.
//

#ifndef EPOLL_TCP_DESCRIPTOR_H
#define EPOLL_TCP_DESCRIPTOR_H


namespace epoll_server {

    class Descriptor {
    public:
        explicit Descriptor(const int fd) noexcept;

        Descriptor() = default;

        Descriptor(Descriptor&& other) noexcept;

        ~Descriptor() noexcept;

        Descriptor& operator=(const int fd);

        operator int() const noexcept;

        void close() noexcept;

    private:
        int fd_ = -1;
    };

}
#endif //EPOLL_TCP_DESCRIPTOR_H
