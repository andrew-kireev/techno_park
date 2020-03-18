cmake_minimum_required(VERSION 3.15)
project(process)

set(SOURCE_EXE src/main.cpp)

set(SOURCE_LIB src/process.cpp)

add_library(proc STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_link_libraries(main proc)