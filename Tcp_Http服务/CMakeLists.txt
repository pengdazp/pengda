cmake_minimum_required(VERSION 3.25)
project(Tcp_Http)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tcp_Http main.cpp head/main.h)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")
