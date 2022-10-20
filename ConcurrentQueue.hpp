//
// Created by squin on 10/19/2022.
//

#include <stdlib.h>
#include <mutex>
#include <condition_variable>

#ifndef JUDO_ENGINE_CONCURENTQUEUE_HPP
#define JUDO_ENGINE_CONCURENTQUEUE_HPP



template <typename T>
struct qnode {
    T* data;
    struct qnode* next;

};


template <typename T>
class ConcurrentQueue {
public:
    int32_t enqueue(T*);
    T* dequeue();
    size_t getSize();
    qnode<T>* dump(int32_t*);
    int32_t load(qnode<T>*, qnode<T>*, const int32_t*);
    ConcurrentQueue();
    ~ConcurrentQueue();

private:
    size_t m_size = 0;
    struct qnode<T>* m_head = nullptr;
    struct qnode<T>* m_tail = nullptr;
    std::mutex m_lock;
    std::condition_variable m_empty_sig;


};


#endif //JUDO_ENGINE_CONCURENTQUEUE_HPP
