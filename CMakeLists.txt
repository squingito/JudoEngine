cmake_minimum_required(VERSION 3.24)
project(judo_engine)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(judo_engine
        ssl_node.hpp DualDynamicArray.cpp DualDynamicArray.hpp JudoServer.cpp JudoServer.hpp)
