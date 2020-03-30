cmake_minimum_required(VERSION 3.15)
project(tcp)

set(CMAKE_CXX_STANDARD 20)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CLIENT "src/test_client.cpp")

set(SERVER "src/test_server.cpp")


#set(LIB_DIR ${DIR}/lib)
#
#add_subdirectory(${LIB_DIR})
#
#target_include_directories(${CLIENT} PUBLIC ${LIB_DIR})
#
#target_include_directories(${SERVER} PUBLIC ${LIB_DIR})
#set(LIB_NAME Log)
#
#target_link_libraries(${TARGET_NAME} PUBLIC ${LIB_NAME})

add_executable(client ${CLIENT})

add_executable(server ${SERVER})
