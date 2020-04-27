//
// Created by Andrew Kireev on 23.04.2020.
//

#ifndef SHMEM_SEMAPHORELOCK_H
#define SHMEM_SEMAPHORELOCK_H

#include "Semaphore.h"

namespace shmem {

    class SemaphoreLock {
    public:
        SemaphoreLock(Semaphore<Allocator>& sem) : sem_(sem){
            sem_.lock();
        }

        ~SemaphoreLock() noexcept {
            sem_.unlock();
        }


    private:
        Semaphore<Allocator> sem_;
    };

}


#endif //SHMEM_SEMAPHORELOCK_H
