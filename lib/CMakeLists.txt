cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)

set(LIB ${LIB_DIR}/BaseLogger.cpp
        ${LIB_DIR}/StdoutLogger.cpp
        ${LIB_DIR}/StderrLogger.cpp
        ${LIB_DIR}/GlobalFunction.cpp
        ${LIB_DIR}/FileLogger.cpp
        ${LIB_DIR}/Logger.cpp
        ${LIB_DIR}/Form.cpp)

add_library(${LIB_NAME} SHARED ${LIB})

target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})