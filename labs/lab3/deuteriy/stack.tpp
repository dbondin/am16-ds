template <class T>
stack<T>::stack ()
{
	s_size = 0;
	s_capacity = 8;
	s_data = new T[s_capacity];
}

template <class T>
stack<T>::~stack ()
{
	delete[] s_data;
}

template <class T>
void stack<T>::push(T &value)
{
	if (s_size == s_capacity) 
	{
		expand();
	}
	s_data[++s_size] = value;
}

template <class T>
T stack<T>::pop()
{
	if (0 == s_size) 
	{
		return 0;
	}
	return s_data[--s_size];
}

template <class T>
T stack<T>::last()
{
	return s_data[s_size];
}

template <class T>
int stack<T>::size()
{
	return s_size;
}

template <class T>
void stack<T>::expand()
{
	s_capacity *= 2;
	T * ns_data = new T[s_capacity];
	for (int i = 0; i < s_size; ++i) {
		ns_data[i] = s_data[i];
	}
	delete[] s_data;
	s_data = ns_data;
}
