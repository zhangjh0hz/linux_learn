cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(press_test_thread_timer press_test.c)
target_link_libraries(press_test_thread_timer base_sock pthread rt)
