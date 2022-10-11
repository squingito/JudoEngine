template <typename T>
DynamicArray<T>::DynamicArray(int64_t (*t_compare)(T*, T*)) {
	m_cap = MIN_DYNAMIC_ARRAY_SIZE;
	m_array = new T[m_cap];
	m_compare = t_compare;
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
	delete m_array;
}

template <typename T>
void DynamicArray<T>::add(T* t_to_add) {
	grow();
	m_array[m_size] = *t_to_add;
	m_size += 1;
	return;
}

template <typename T>
void DynamicArray<T>::grow() {
	if (m_size + 1 == m_cap) {
		m_cap *= 2;
		T* new_array = new T[m_cap];
		for (int i = 0; i < m_size; i++) {
			new_array[i] = m_array[i];
		}
		delete m_array;
		m_array = new_array;
	} 
}

template <typename T>
void DynamicArray<T>::shrink() {
	if (m_size * 2 == m_cap) {
		m_cap /= 2;
		T* new_array = new T[m_cap];
		for (int i = 0; i < m_size; i++) {
			new_array[i] = m_array[i];
		}
		delete m_array;
		m_array = new_array;
	}
}

template <typename T>
void DynamicArray<T>::remove(T* t_data) {
	for (int i = 0; i < m_size; i++) {
		if (m_compare(t_data, &(m_array[i])) == 0) {
			m_array[i] = m_array[m_size - 1];
			m_size -= 1;
			break;
		}
	}
	if (m_cap > 16) {
		shrink();
	}
	return;
}

template <typename T>
T* DynamicArray<T>::getArray() {
	return m_array;
}

template <typename T>
size_t DynamicArray<T>::getSize() {
	return m_size;
}

template <typename T>
T* DynamicArray<T>::find(T t_data) {
	for (int i = 0; i < m_size; i++) {
		if (m_compare(&t_data, &m_array[i]) == 0) {
			return &m_array[i];
		}
	}
	return nullptr;
}
			
			
