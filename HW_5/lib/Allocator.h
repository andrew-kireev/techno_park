//
// Created by Andrew Kireev on 23.04.2020.
//

#ifndef SHMEM_ALLOCATOR_H
#define SHMEM_ALLOCATOR_H

#include "cstdint"
#include <new>

namespace shmem{


    struct AllocState{
        char* start;
        char* end;
    };


    template<typename Type>
    class Allocator {
    public:
        using value_type = Type;

        Allocator(AllocState* state) : state_(state){
        }

        template <typename T>
        Allocator(const Allocator<T>& other) noexcept :
                                state_(other.state_) {
        }
        template<typename T>
        friend class Allocator;

        Type* allocate(std::size_t n) {
            char* result = state_->start;
            if (result + sizeof(Type) * n > state_->end) {
                throw std::bad_alloc();
            }
            state_->start += sizeof(Type) * n;
            return reinterpret_cast<Type*>(result);
        }


        void deallocate(Type* p, std::size_t n) noexcept {
            if (state_->start - n * sizeof(Type) == reinterpret_cast<char*>(p))
                state_->start -= n * sizeof(Type);
        }

    private:

        AllocState* state_;
    };


}

#endif //SHMEM_ALLOCATOR_H
