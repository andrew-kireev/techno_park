//
// Created by Andrew Kireev on 23.04.2020.
//

#ifndef SHMEM_SHAREDMAP_H
#define SHMEM_SHAREDMAP_H

#include <map>
#include <sys/mman.h>
#include <thread>
#include <memory>


#include "SemaphoreLock.h"
#include "Allocator.h"


namespace shmem {


    template <typename Key, typename Val>
    class SharedMap {
        using value_type = typename std::map<Key, Val>::value_type;
        using c_iter = typename std::map<Key, Val>::iterator;
        using iter = typename std::map<Key, Val>::iterator;
        using semaphore = Semaphore<Allocator>;

        using Map = std::map<Key, Val, std::less<Key>, Allocator<value_type>>;

    public:
         SharedMap() = default;
         ~SharedMap() = default;

         //template <typename T>
        SharedMap(Allocator<Map> allocator):
                sem_(allocator) {
             map_ = allocator.allocate(1);
             std::allocator_traits<Allocator<Map>>::construct(allocator, map_, allocator);
        }



        template<typename key, typename val>
        void insert(const key k, val v) {
            const std::lock_guard<semaphore> lock(sem_);
            map_->insert(std::make_pair(k, v));
        }

//        ~SharedMap(){
//            const std::lock_guard<semaphore> lock(sem_);
//            std::destroy_at(map_);
//        }

        iter begin() {
            return map_->begin();
        }

        c_iter cbegin() const {
            return map_->cbegin();
        }

        iter end() {
            return map_->end();
        }

        c_iter cend() const {
            return map_->cend();
        }


        Val& at(const Key& key){
            const std::lock_guard<semaphore> lock(sem_);
            return map_->at();
        }

        iter erase(const iter it) const{
            const std::lock_guard<semaphore> lock(sem_);
            return map_->erase(it);
        }

        iter insert(const Val& value) {
            const std::lock_guard<semaphore> lock(sem_);
            return map_->insert(value);
        }

        void clear() {
            const std::lock_guard<semaphore> lock(sem_);
            map_->clear();
        }

        Val& operator[](const Key& key) {
            const std::lock_guard<semaphore> lock(sem_);
            return map_->operator[](key);
        }

        size_t size(){
            const std::lock_guard<semaphore> lock(sem_);
            return map_->size();
        }


    private:
        Map* map_;
        mutable Semaphore<Allocator> sem_;
        bool deleted = false;
    };


}


#endif //SHMEM_SHAREDMAP_H
