cmake_minimum_required(VERSION 3.26)
project(SockNet)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Lib)
add_subdirectory(Utils)

add_executable(SockNet main.cpp)

target_link_libraries(SockNet PUBLIC Socket Utils)
