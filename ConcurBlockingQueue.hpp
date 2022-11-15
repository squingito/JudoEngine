//
// Created by squin on 10/25/2022.
//

#include <stdlib.h>
#include <mutex>
#include <condition_variable>

#include "Queue.cpp"

#ifndef JUDO_ENGINE_CONCURBLOCKINGQUEUE_HPP
#define JUDO_ENGINE_CONCURBLOCKINGQUEUE_HPP

#ifndef JUDO_QUEUE_NODE
#define JUDO_QUEUE_NODE

template <typename T>
struct qnode {
    T* data;
    struct qnode* next;

};

#endif
#ifndef JUDO_QUEUE_PRIORITY
#define JUDO_QUEUE_PRIORITY
enum priority {
    HIGH = 1,
    LOW = 0
};
#endif
#ifndef JUDO_QUEUE_BLOCK
#define JUDO_QUEUE_BLOCK
enum block {
    BLOCK = 1,
    NONBLOCK = 0
};
#endif

template <typename T>
class ConcurBlockingQueue {

public:
    int32_t enqueue(T*, priority);
    T* dequeue(priority, block);
    size_t getSize();
    int32_t dump(qnode<T>**, qnode<T>**, priority, block);
    int32_t load(void**, void**, int32_t, priority);
    ConcurBlockingQueue(void (*dstr)(T*));
    ~ConcurBlockingQueue();

private:
    std::mutex m_data;
    std::mutex m_next_to_access;
    std::mutex m_low_prio_access;
    std::condition_variable m_con;
    Queue<T>* m_queue = nullptr;

};


#endif //JUDO_ENGINE_CONCURBLOCKINGQUEUE_HPP
