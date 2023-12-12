cmake_minimum_required(VERSION 3.26)
project(SockNet)

set(CMAKE_CXX_STANDARD 20)

add_executable(SockNet main.cpp
        Lib/Ws.cpp
        Lib/Ws.h
        Utils/Utils.cpp
        Utils/Utils.h
        Lib/Wsa.h
        Utils/Singleton.h
        Lib/Socket.inl
        Lib/Socket.h
)
