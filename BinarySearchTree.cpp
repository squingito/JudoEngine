

template <typename T>
BinarySearchTree<T>::BinarySearchTree(int32_t (*t_compare)(T*, T*), void (*t_destructor)(T*)) {
	m_compare = t_compare;
	m_destructor = t_destructor;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	eraser(m_head);
}

template <typename T>
void BinarySearchTree<T>::eraser(struct tnode<T>* t_input_node) {
	if (t_input_node == nullptr) {
		return;
	}
	eraser(t_input_node->left);
	eraser(t_input_node->right);
	m_destructor(t_input_node->data);
	delete t_input_node;
	m_size -= 1;
}

template <typename T>
void BinarySearchTree<T>::fillArray(tnode<T>** t_input_array) {
	uint64_t index = 0;
	filArray(t_input_array, m_head, &index);
}


template <typename T>
void BinarySearchTree<T>::fillArray_(struct tnode<T>** t_input_array, struct tnode<T>* t_input_tnode, uint64_t* t_index) {
	if (t_input_tnode == nullptr) {
		return;
	}

	filArray_(t_input_array, t_input_tnode->left, t_index);
	
	t_input_array[*t_index] = t_input_tnode;
	*t_index = (*t_index) + 1;

	fillArray_(t_input_array, t_input_tnode->right, t_index);
	
	return;
}

template <typename T>
void BinarySearchTree<T>::balance() {
	tnode<T>** nodes = new tnode<T>*[m_size];
	fill_array(nodes);
	m_head = _balance(nodes, 0, m_size - 1);
	delete[] nodes;
	return;
}

template <typename T>
struct tnode<T>* BinarySearchTree<T>::balance_(struct tnode<T>** t_input_array, uint64_t t_left, uint64_t t_right) {
	if (t_left == t_right) {
		t_input_array[t_left]->left = nullptr;
		t_input_array[t_left]->right = nullptr;
		return t_input_array[t_left];
	} else {
		uint64_t mid = (t_right + t_left) / 2;
		t_input_array[mid]->left = balance(t_input_array, t_left, mid - 1);
		t_input_array[mid]->right = balance(t_input_array, mid + 1, t_right);
		return t_input_array[mid];
	}
}

template <typename T>
void BinarySearchTree<T>::insert(T* t_input_data) {
	struct tnode<T>* new_node = new struct tnode<T>;
	new_node->data = t_input_data;
	new_node->left = nullptr;
	new_node->right = nullptr;

	struct tnode<T>* current = m_head;
	if (m_size == 0) {
		m_head = new_node;
		m_size += 1;
	}
	while (true) {
		if (compare(new_node->data, current->data) < 0) {
			if (current->left == nullptr) {
				current->left = new_node;
				break;
			} else {
				current = current->left;
			}
		} else {
			if (current->right == nullptr) {
				current->rigth = new_node;
				break;
			} else {
				current = current->right;
			}
		}
	}
	m_size += 1;
	double num = log2(m_size + 1);
	if ((num - floor(num) == 0) && m_size >= 15) {
		balance();
	}
	return;
}

template <typename T>
void BinarySearchTree<T>::remove(T* t_to_remove) {
	struct tnode<T>* current = m_head;
	struct tnode<T>** cur_ptr;
	if (m_size != 0) {
		cur_ptr = &m_head;
	} else {
		return;
	}
	struct tnode<T> hold;
	struct tnode<T>* to_del = nullptr;
	while (current != nullptr) {
		int64_t val = compare(t_to_remove, current->data);
		if (val == 0) {
			to_del = current;
			*cur_ptr = current->right;
			hold = current->left;
			if (hold != nullptr) {
				struct tnode<T>* transverse = current->right;
				while (transverse->left != nullptr) {
					transverse->left = hold;
				}
			}
			break;
		} else if (val < 0) {
			if (current->left != nullptr) {
				cur_ptr = &(current->right);
			}
			current = current->right;
		}
	}
	if (to_del != nullptr) {
		m_destructor(to_del->data);
		delete to_del;
		m_size -= 1;
	}
	double num = log2(m_size + 1);
	if ((num - floor(num) == 0) && m_size >= 15) {
		balance();
	}
	return;
}

template <typename T>
T* BinarySearchTree<T>::find(T* t_data) {
	struct tnode<T>* current = m_head;
	while (current != nullptr) {
		int64_t val = compare(t_data, current->data);
		if (val == 0) {
			return current->data;
		} else if (val < 0) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return nullptr;
}


		
