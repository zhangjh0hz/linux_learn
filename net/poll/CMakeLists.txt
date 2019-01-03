cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(poll_svr poll_svr.c)
target_link_libraries(poll_svr base_sock)
