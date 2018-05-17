cmake_minimum_required(VERSION 3.10)
project(untitled3)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled3 client.c)
find_package(Threads REQUIRED)
target_link_libraries(untitled3 Threads::Threads)