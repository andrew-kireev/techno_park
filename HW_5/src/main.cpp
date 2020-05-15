#include <iostream>
#include <sys/wait.h>
#include <unistd.h>


#include "SharedMap.h"
#include "shmem.h"

int SIZE = 6048;

int main() {

    shmem::Shmemory shared_momory(SIZE);

    using string = std::basic_string<char, std::char_traits<char>,
            shmem::Allocator<char>>;

    auto alloc = shared_momory.get_allocator<std::pair<string, string>>();
    shmem::SharedMap<string, string > map(alloc);
    std::cout << "Hello, World!" << std::endl;
    int pid = ::fork();
    if (pid == 0) {

        map.insert(string ("child1", alloc), string("1", alloc));
        map.insert(string ("child2", alloc), string("2", alloc));
        map.insert(string ("child3", alloc), string("3", alloc));
        map.insert(string ("child4", alloc), string("4", alloc));
        map.insert(string ("child5", alloc), string("5", alloc));

    }
    else {
        map.insert(string ("parent1", alloc), string("1", alloc));
        map.insert(string ("parent2", alloc), string("2", alloc));
        map.insert(string ("parent3", alloc), string("3", alloc));
        map.insert(string ("parent4", alloc), string("4", alloc));
        map.insert(string ("parent5", alloc), string("5", alloc));
        ::waitpid(pid, nullptr, 0);
    }
    if (pid != 0) {
        for (const auto& item : map) {

            std::cout << item.first << " : " << item.second << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }


    if (pid == 0) {

        std::cout << "CHILD" << std::endl;
        map.erase(map.begin());
        map.erase(map.begin());
        for (const auto& item : map) {

            std::cout << item.first << " : " << item.second << std::endl;
        }

        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;

    }
    else {
        std::cout << "PARENT" << std::endl;
        map.erase(prev(map.end()));
        map.erase(prev(map.end()));
        for (const auto& item : map) {

            std::cout << item.first << " : " << item.second << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        ::waitpid(pid, nullptr, 0);
    }

    return 0;
}
