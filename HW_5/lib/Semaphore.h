//
// Created by Andrew Kireev on 23.04.2020.
//

#ifndef SHMEM_SEMAPHORE_H
#define SHMEM_SEMAPHORE_H

#include <sys/semaphore.h>


#include "Allocator.h"

namespace shmem {


    template <
            template <typename T>
            class Allocator>
    class Semaphore {
    public:

        template <typename T>
        Semaphore(Allocator<T> allocator):
        allocator_(allocator) {

                sem_ = allocator_.allocate(1);
                ::sem_init(sem_, 1, 1);
        }


        ~Semaphore() noexcept {
            ::sem_destroy(sem_);
            allocator_.deallocate(sem_, 1);
        }

        void lock() {
            ::sem_wait(sem_);
        }

        void unlock() {
            ::sem_post(sem_);
        }


    private:
        sem_t* sem_;
        Allocator<sem_t> allocator_;
    };


}

#endif //SHMEM_SEMAPHORE_H
