cmake_minimum_required(VERSION 3.15)

project(process)

set(SOURCE_EXE "${PROJECT_SOURCE_DIR}/src/main.cpp")

set(SOURCE_LIB "${PROJECT_SOURCE_DIR}/src/process.cpp" "${PROJECT_SOURCE_DIR}/include/process.h"
        "${PROJECT_SOURCE_DIR}/include/exeption_process.h")

add_library(proc STATIC ${SOURCE_LIB})

add_executable(main ${SOURCE_EXE})

target_include_directories(main PUBLIC ./include)

target_include_directories(proc PUBLIC ./include)

target_link_libraries(main proc)