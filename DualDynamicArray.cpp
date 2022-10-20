//
// Created by squin on 10/11/2022.
//

#include "DualDynamicArray.hpp"

template <typename T, typename N>
DualDynamicArray<T,N>::DualDynamicArray(int32_t (*t_compare)(T*, T*)) {
    m_cap = MIN_DDA_SIZE;
    m_first_array = new T[m_cap];
    m_second_array = new N[m_cap];
    m_compare = t_compare;
}

template <typename T, typename N>
DualDynamicArray<T,N>::~DualDynamicArray() {
    delete[] m_first_array;
    delete[] m_second_array;
}

template <typename T, typename N>
void DualDynamicArray<T,N>::grow() {
    if (m_size + 1 > m_cap) {
        size_t new_cap = 2 * m_cap;
        T* new_first_array = new T[new_cap];
        N* new_second_array = new N[new_cap];
        for (int32_t i = 0; i < ((int) m_size); i++) {
            new_first_array[i] = m_first_array[i];
            new_second_array[i] = m_second_array[i];
        }
        delete m_first_array;
        m_first_array = new_first_array;
        delete m_second_array;
        m_second_array = new_second_array;
        m_cap = new_cap;
    }
}

template <typename T, typename N>
void DualDynamicArray<T,N>::shrink() {
    if ((m_size == m_cap / 2) && (m_size > 16)) {
        size_t new_cap = m_cap / 2;
        T* new_first_array = new T[new_cap];
        N* new_second_array = new N[new_cap];
        for (int32_t i = 0; i < ((int) m_size); i++) {
            new_first_array[i] = m_first_array[i];
            new_second_array[i] = m_second_array[i];
        }
        delete m_first_array;
        m_first_array = new_first_array;
        delete m_second_array;
        m_second_array = new_second_array;
        m_cap = new_cap;
    }
}

template <typename T, typename N>
void DualDynamicArray<T,N>::add(T* t_thing_one, N* t_thing_two) {
    this->grow();
    m_first_array[m_size] = *t_thing_one;
    m_second_array[m_size] = *t_thing_two;
    m_size += 1;
}

template <typename T, typename N>
int32_t DualDynamicArray<T,N>::find(T* t_thing_one) {
    for (int i = 0; i < ((int) m_size); i++) {
        if (m_compare(t_thing_one, &(m_first_array[i])) == 0) return i;
    }
    return -1;
}

template <typename T, typename N>
void DualDynamicArray<T,N>::remove(T* t_thing_one) {
    int32_t index = this->find(t_thing_one);
    if (index != -1) {
        m_first_array[index] = m_first_array[m_size - 1];
        m_second_array[index] = m_second_array[m_size - 1];
        m_size -= 1;
        this->shrink();
    }
}

template <typename T, typename N>
T* DualDynamicArray<T,N>::getFromFirstByIndex(int32_t t_index) {
    return &(m_first_array[t_index]);
}

template <typename T, typename N>
N* DualDynamicArray<T,N>::getFromSecondByIndex(int32_t t_index) {
    return &(m_second_array[t_index]);
}

template <typename T, typename N>
N* DualDynamicArray<T,N>::getSecondArray() {
    return m_second_array;
}

template <typename T, typename N>
T* DualDynamicArray<T,N>::getFirstArray() {
    return m_first_array;
}

template <typename T, typename N>
size_t DualDynamicArray<T,N>::getSize() {
    return m_size;
}