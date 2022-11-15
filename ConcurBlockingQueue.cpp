//
// Created by squin on 10/25/2022.
//

#include "ConcurBlockingQueue.hpp"

template <typename T>
ConcurBlockingQueue<T>::ConcurBlockingQueue(void (*dstr)(T*)) {
    m_queue = new Queue<T>(dstr);
}

template <typename T>
ConcurBlockingQueue<T>::~ConcurBlockingQueue() {
    delete m_queue;
}

template <typename T>
int32_t ConcurBlockingQueue<T>::enqueue(T* t_in, priority t_prio) {
    if (t_prio == HIGH) {
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();
        // do the thing, store in var
        m_queue->enqueue(t_in);
        m_con.notify_one();

        m_data_lock.unlock();
    } else {
        std::unique_lock<std::mutex> m_low_lock(m_low_prio_access);
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();

        m_queue->enqueue(t_in);

        m_data_lock.unlock();
        m_low_lock.unlock();
    }
    return 0;
}

template <typename T>
T* ConcurBlockingQueue<T>::dequeue(priority t_prio, block t_block) {
    T* out;
    if (t_prio == HIGH) {
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();
        // do the thing, store in var

        if (m_queue->getSize() == 0) {
            if (t_block == NONBLOCK) {
                m_data_lock.unlock();
                return nullptr;
            } else {
                while (m_queue->getSize() == 0) {
                    m_con.wait(m_data_lock);
                }
            }
        }
        out = m_queue->dequeue();

        m_data_lock.unlock();
    } else {
        std::unique_lock<std::mutex> m_low_lock(m_low_prio_access);
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();

        if (m_queue->getSize() == 0) {
            if (t_block == NONBLOCK) {
                m_data_lock.unlock();
                return nullptr;
            } else {
                while (m_queue->getSize() == 0) {
                    m_con.wait(m_data_lock);
                }
            }
        }
        out = m_queue->dequeue();

        m_data_lock.unlock();
        m_low_lock.unlock();
    }
    return out;
}

template <typename T>
int32_t ConcurBlockingQueue<T>::dump(qnode<T>** t_head, qnode<T>** t_tail, priority t_prio, block t_block) {
    int32_t ret;
    if (t_prio == HIGH) {
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();
        // do the thing, store in var
        int32_t size = m_queue->getSize();

        if (size == 0) {
            if (t_block == NONBLOCK) {
                m_data_lock.unlock();
                return 0;
            } else {
                while (m_queue->getSize() == 0) {
                    m_con.wait(m_data_lock);
                }
            }
        }
        ret = m_queue->dump(t_head, t_tail);
        m_data_lock.unlock();
    } else {
        std::unique_lock<std::mutex> m_low_lock(m_low_prio_access);
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();

        if (m_queue->getSize() == 0) {
            if (t_block == NONBLOCK) {
                m_data_lock.unlock();
                m_low_lock.unlock();
                return 0;
            } else {
                while (m_queue->getSize() == 0) {
                    m_con.wait(m_data_lock);
                }
            }
        }
        ret = m_queue->dump(t_head, t_tail);

        m_data_lock.unlock();
        m_low_lock.unlock();
    }
    return ret;
}

template <typename T>
int32_t ConcurBlockingQueue<T>::load(void** t_head, void** t_tail, int32_t t_num_in, priority t_prio) {
    int ret;
    if (t_num_in <= 0) {
        return -1;
    }
    if (t_prio == HIGH) {
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();
        // do the thing, store in var
        ret = m_queue->load((struct qnode<T>)t_head, (struct qnode<T>) t_tail, t_num_in);
        m_con.notify_one();

        m_data_lock.unlock();
    } else {
        std::unique_lock<std::mutex> m_low_lock(m_low_prio_access);
        std::unique_lock<std::mutex> m_next_lock(m_next_to_access);
        std::unique_lock<std::mutex> m_data_lock(m_data);
        m_next_lock.unlock();

        ret = m_queue->load(t_head, t_tail, t_num_in);
        m_con.notify_one();

        m_data_lock.unlock();
        m_low_lock.unlock();
    }
    return ret;
}

template <typename T>
size_t ConcurBlockingQueue<T>::getSize() {
    return m_queue->getSize();
}

/*
int main() {
    ConcurBlockingQueue<int>* a = new ConcurBlockingQueue<int>(nullptr);
    int b = 7;
    int d = 8;
    int c = 19;
    a->enqueue(&b, HIGH);
    a->enqueue(&c, HIGH);
    a->enqueue(&d, HIGH);
    struct qnode<int>* h = a->dump(HIGH, NONBLOCK);
    std::cout << *a->dequeue(HIGH, NONBLOCK);
}
 */