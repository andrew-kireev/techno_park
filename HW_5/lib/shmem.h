//
// Created by Andrew Kireev on 26.04.2020.
//

#ifndef SHMEM_SHMEM_H
#define SHMEM_SHMEM_H

#include "Allocator.h"


namespace shmem {

    class Shmemory {

    public:

        explicit Shmemory(const std::size_t size) : size_(size) {
            mmap_ = ::mmap(nullptr, size_, PROT_WRITE | PROT_READ,
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
            if (mmap == MAP_FAILED) {
                throw std::bad_alloc();
            }

            state_ = static_cast<AllocState *>(mmap_);
            state_->start = static_cast<char *>(mmap_) + sizeof(*state_);
            state_->end = static_cast<char* >(mmap_) + size_;
        }

        ~Shmemory() noexcept {
            ::munmap(mmap_, size_);
        }

        template <typename T>
        Allocator<T> get_allocator() {
            return Allocator<T>(state_);

        }

    private:
        void* mmap_;
        AllocState* state_;
        std::size_t size_;
    };

}

#endif //SHMEM_SHMEM_H
