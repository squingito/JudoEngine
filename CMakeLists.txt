cmake_minimum_required(VERSION 3.24)
project(judo_engine)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ssl)
link_libraries(crypto)

include_directories(.)

add_executable(judo_engine
        DualDynamicArray.cpp DualDynamicArray.hpp JudoServer.cpp JudoServer.hpp LoggyMcLogFace.cpp LoggyMcLogFace.hpp Queue.cpp Queue.hpp ConcurBlockingQueue.cpp ConcurBlockingQueue.hpp ThreadPool.cpp ThreadPool.hpp ssl_node.cpp ssl_node.hpp)
