//
// Created by squin on 11/16/2022.
//

#ifndef JUDO_ENGINE_PRIORITYQUEUE_H
#define JUDO_ENGINE_PRIORITYQUEUE_H

#include <mutex>
#include <condition_variable>
#include "Queue.cpp"

enum priority {
    HIGH = 1,
    LOW = 0
};

enum block {
    BLOCK = 1,
    NONBLOCK = 0
};

template <typename T>
struct dumpNode {
    qnode<T>* head;
    qnode<T>* tail;
    int32_t num;
};

template <typename T>
class PriorityQueue {
public:
    T* dequeue(priority, block);
    int32_t enqueue(T*, int32_t, priority);
    size_t getSize();
    struct dumpNode<T>* dump(int32_t*);
    int32_t load(struct dumpNode<T>*, int32_t);
    PriorityQueue(void (*dstr)(T));
    ~PriorityQueue();

private:
    Queue<T>** m_list = nullptr;
    std::mutex m_data;
    std::mutex m_next_to_access;
    std::mutex m_low_prio_access;
    std::condition_variable m_con;
    int32_t m_lowest_prio;
    int32_t m_size;
};


#endif //JUDO_ENGINE_PRIORITYQUEUE_H
