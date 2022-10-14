//
// Created by squin on 10/11/2022.
//

#ifndef JUDO_ENGINE_DUALDYNAMICARRAY_HPP
#define JUDO_ENGINE_DUALDYNAMICARRAY_HPP

#include <cstdint>

#include <stdlib.h>

#define MIN_DDA_SIZE 16;

template <typename T, typename N>
class DualDynamicArray {
public:
    DualDynamicArray(int32_t (*t_compare)(T*, T*));
    ~DualDynamicArray();
    void add(T*, N*);
    void remove(T*);
    int32_t find(T*);
    T* getFromFirstByIndex(int32_t t_index);
    N* getFromSecondByIndex(int32_t t_index);
    T* getFirstArray();
    N* getSecondArray();
    size_t getSize();
    void protocol(struct pollfd*, struct ssl_node*);




private:
    size_t m_size = 0;
    size_t m_cap = 0;
    T* m_first_array = nullptr;
    N* m_second_array = nullptr;
    int32_t (*m_compare)(T*, T*);

    void grow();
    void shrink();

};


#endif //JUDO_ENGINE_DUALDYNAMICARRAY_HPP
