#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#ifndef CSTDINT_H
#define CSTDINT_H
#include <cstdint>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#define MIN_DYNAMIC_ARRAY_SIZE 16

template <typename T>
class DynamicArray {
public:
	DynamicArray(int64_t (*t_compare)(T*, T*));
	~DynamicArray();
	void add(T*);
	void remove(T*);
	T* find(T);
	T* getArray();
	size_t getSize();
	

private:
	size_t m_size = 0;
	size_t m_cap = 0;
	T* m_array = nullptr;
	int64_t (*m_compare)(T*, T*);

	void grow();
	void shrink();
};

#include "DynamicArray.cpp"

#endif
