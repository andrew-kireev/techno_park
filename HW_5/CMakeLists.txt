cmake_minimum_required(VERSION 3.15)
project(shmem)



set(CMAKE_CXX_STANDARD 14)

add_executable(example src/main.cpp)

target_include_directories(example PUBLIC lib)


#target_link_libraries(shmem_example  ${LIB_NAME})