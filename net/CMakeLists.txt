cmake_minimum_required(VERSION 2.8)
project(zsocket C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Werror -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

cmake_policy(SET CMP0015 NEW)
include_directories(base_socket)
link_directories(base_socket)

add_subdirectory(base_socket)
add_subdirectory(select)
#add_subdirectory(poll)
#add_subdirectory(epoll)

#add_executable(sock_test socket_test.c)
#target_link_libraries(sock_test base_sock)
