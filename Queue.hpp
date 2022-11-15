//
// Created by squin on 10/19/2022.
//

#include <stdlib.h>


#ifndef JUDO_ENGINE_CONCURENTQUEUE_HPP
#define JUDO_ENGINE_CONCURENTQUEUE_HPP

#ifndef JUDO_QUEUE_NODE
#define JUDO_QUEUE_NODE

template <typename T>
struct qnode {
    T* data;
    struct qnode* next;

};

#endif

template <typename T>
class Queue {
public:
    int32_t enqueue(T*);
    T* dequeue();
    size_t getSize();
    int32_t dump(qnode<T>**, qnode<T>**);
    int32_t load(void**, void**, const int32_t);
    Queue(void (*dstr)(T*));
    ~Queue();

private:
    size_t m_size = 0;
    struct qnode<T>* m_head = nullptr;
    struct qnode<T>* m_tail = nullptr;
    void (*m_destr)(T*);



};


#endif //JUDO_ENGINE_CONCURENTQUEUE_HPP
