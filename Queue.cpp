//
// Created by squin on 10/19/2022.
//



#include <iostream>
#include "Queue.hpp"

template <typename T>
Queue<T>::Queue(void (*dstr)(T*)) {
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
    m_destr = dstr;
}

template <typename T>
Queue<T>::~Queue() {
    struct qnode<T>* current = m_head;
    struct qnode<T>* next;
    while (current != nullptr) {
        if (m_destr != nullptr) {
            m_destr(next->data);
        }
        next = current->next;

        delete current;
        current = next;
    }
}

template <typename T>
size_t Queue<T>::getSize() {
    return m_size;
}

template <typename T>
int32_t Queue<T>::enqueue(T* t_data) {
    struct qnode<T>* new_node = new qnode<T>;
    new_node->data = t_data;
    new_node->next = nullptr;
    if (m_size == 0) {
        m_head = new_node;
        m_tail = new_node;
        m_size = 1;
    } else {
        m_tail->next = new_node;
        m_tail = m_tail->next;
        m_size += 1;
    }
    return 0;
}

template <typename T>
int32_t Queue<T>::load(void** t_new_nodes, void** t_new_nodes_tail, int32_t t_num_terms) {
    if (t_num_terms <= 0) return -1;
    if (m_size == 0) {
        m_head = *((qnode<T>**) t_new_nodes);
        m_tail = *((qnode<T>**) t_new_nodes_tail);
    } else {
        m_tail->next = *((qnode<T>**) t_new_nodes);
        m_tail = *((qnode<T>**) t_new_nodes_tail);
    }
    m_size += t_num_terms;
    return 0;
}


template <typename T>
T* Queue<T>::dequeue() {
    T* data = m_head->data;
    if (m_size == 1) {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
    } else {
        struct qnode<T>* to_del = m_head;
        m_head = m_head->next;
        delete to_del;
        m_size -= 1;
    }
    return data;
}

template<typename T>
int32_t Queue<T>::dump(qnode<T>** t_head_ptr, qnode<T>** t_tail_ptr) {
    *t_head_ptr = m_head;
    *t_tail_ptr = m_tail;
    m_head = nullptr;
    m_tail = nullptr;
    int32_t size_out = m_size;
    m_size = 0;
    return size_out;
}
/*
int main() {
    Queue<int>* a = new Queue<int>;
    int b = 7;
    a->enqueue(&b);
    delete a;
}
*/