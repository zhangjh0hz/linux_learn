cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
add_executable(select_svr select_svr.c)
target_link_libraries(select_svr base_sock)

