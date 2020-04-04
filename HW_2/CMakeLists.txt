cmake_minimum_required(VERSION 3.15)

project(Logger)

set(CMAKE_CXX_STANDARD 20)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(INC_DIR ${DIR}/include)

set(SRC_DIR ${DIR}/src)

set(LIB_DIR ${DIR}/lib)

set(LIB_NAME Log)

set(TARGET_NAME lib.o)

set(MAIN ${SRC_DIR}/main.cpp)

add_subdirectory(${LIB_DIR})


add_executable(${TARGET_NAME} ${MAIN})

target_link_libraries(${TARGET_NAME} PUBLIC ${LIB_NAME})

target_include_directories(${TARGET_NAME} PUBLIC ${LIB_DIR})