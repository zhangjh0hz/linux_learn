cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(press_test_fork press_test.c)
target_link_libraries(press_test_fork base_sock)
