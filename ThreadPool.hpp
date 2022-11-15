//
// Created by squin on 10/28/2022.
//

#ifndef JUDO_ENGINE_THREADPOOL_HPP
#define JUDO_ENGINE_THREADPOOL_HPP


#include <vector>
#include <thread>
#include <cmath>
#include "JudoServer.hpp"



class ThreadPool {
public:

    ThreadPool(void (*t_dstr_one)());

private:
    std::vector<std::thread> m_threads;
    int32_t m_max_num_threads;
    int32_t* m_thread_scaling = nullptr;
    int32_t* m_active_threads = nullptr;
    judo::JudoServer m_server;


    void makeDefaultScaling_();
};


#endif //JUDO_ENGINE_THREADPOOL_HPP
