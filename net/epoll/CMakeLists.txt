cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(epoll_svr epoll_svr.c)
target_link_libraries(epoll_svr base_sock)
