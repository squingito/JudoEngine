//
// Created by squin on 10/28/2022.
//

#include "ThreadPool.hpp"

void ThreadPool::makeDefaultScaling_() {
    m_thread_scaling = new int32_t[m_max_num_threads - 1];
    for (int32_t i = 1; i < m_max_num_threads; i++) {
        m_thread_scaling[i - 1] = 5 * std::pow(2, i);
    }
}