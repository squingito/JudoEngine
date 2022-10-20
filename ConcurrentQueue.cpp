//
// Created by squin on 10/19/2022.
//



#include <iostream>
#include "ConcurrentQueue.hpp"

template <typename T>
ConcurrentQueue<T>::ConcurrentQueue() {
    m_size = 0;
    m_head = nullptr;
    m_tail = nullptr;
}

template <typename T>
ConcurrentQueue<T>::~ConcurrentQueue() {
    struct qnode<T>* current = m_head;
    struct qnode<T>* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
size_t ConcurrentQueue<T>::getSize() {
    return m_size;
}

template <typename T>
int32_t ConcurrentQueue<T>::enqueue(T* t_data) {
    struct qnode<T>* new_node = new qnode<T>;
    new_node->data = t_data;
    new_node->next = nullptr;
    std::unique_lock<std::mutex> temp_lock(m_lock);
    if (m_size == 0) {
        m_head = new_node;
        m_tail = new_node;
        m_size = 1;
    } else {
        m_tail->next = new_node;
        m_tail = m_tail->next;
        m_size += 1;
    }
    std::cout << "hedfsnhajkshfd";
    temp_lock.unlock();
    m_empty_sig.notify_one();
    return 0;
}

template <typename T>
int32_t ConcurrentQueue<T>::load(qnode<T>* t_new_nodes, qnode<T>* t_new_nodes_tail, const int32_t* t_num_terms) {
    std::unique_lock<std::mutex> temp_lock(m_lock);
    int num_in = *t_num_terms;

    if (m_size == 0) {
        m_head = t_new_nodes;
        m_tail = t_new_nodes_tail;
    } else {
        m_tail->next = t_new_nodes;
        m_tail = t_new_nodes_tail;
    }
    m_size += num_in;
    temp_lock.unlock();
    for (int i = 0; i < num_in; i++) {
        m_empty_sig.notify_one();
    }
    return 0;

}


template <typename T>
T* ConcurrentQueue<T>::dequeue() {
    std::unique_lock<std::mutex> temp_lock(m_lock);
    while (m_size == 0) {
        m_empty_sig.wait(temp_lock);
    }
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
    temp_lock.unlock();
    return data;
}

template<typename T>
qnode<T> *ConcurrentQueue<T>::dump(int32_t *) {
    struct qnode<T>* out = m_head;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
    return out;
}

int main() {
    ConcurrentQueue<int>* a = new ConcurrentQueue<int>;
    int b = 7;
    a->enqueue(&b);
    delete a;
}
