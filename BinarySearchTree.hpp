
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H


#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#ifndef CSTDINT_H
#define CSTDINT_H
#include <cstdint>
#endif

template <typename T>
struct tnode {
	T* data;
	struct tnode<T>* left;
	struct tnode<T>* right;
};

template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree(int32_t (*t_compare)(T*, T*), void (*t_destructor)(T*));
	~BinarySearchTree();
	void insert(T*);
	void remove(T*);
	T* find(T*);

private:
	struct tnode<T>* m_head = nullptr;
	size_t m_size = 0;
	int32_t (*m_compare)(T*, T*);
	void (*m_destructor)(T*);


	void eraser(struct tnode<T>*);
	void balance();
	struct tnode<T>* balance_(struct tnode<T>**, uint64_t, uint64_t);
	void fillArray(struct tnode<T>**);
	void fillArray_(struct tnode<T>**, struct tnode<T>*, uint64_t*);
};


#include "BinarySearchTree.cpp"

#endif
