cmake_minimum_required(VERSION 3.24)
project(judo_engine)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ssl)
link_libraries(crypto)

include_directories(.)

add_executable(judo_engine
        ssl_node.hpp DualDynamicArray.cpp DualDynamicArray.hpp JudoServer.cpp JudoServer.hpp LoggyMcLogFace.cpp LoggyMcLogFace.hpp ConcurrentQueue.cpp ConcurrentQueue.hpp)
