cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

set(LIB ${LIB_DIR}/Connection.cpp
        ${LIB_DIR}/Server.cpp)

add_library(${LIB_NAME} SHARED ${LIB})

target_include_directories(${LIB_NAME} PUBLIC ./include)