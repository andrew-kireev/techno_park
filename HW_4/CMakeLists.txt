cmake_minimum_required(VERSION 3.15)
project(epoll_tcp)

set(CMAKE_CXX_STANDARD 20)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/src)

set(LIB_DIR ${DIR}/lib)

set(LIB_NAME Log)

set(SERVER src/test_server.cpp)

add_subdirectory(${LIB_DIR})

add_executable(server ${SERVER})

target_link_libraries(server  ${LIB_NAME})

