#include <stdexcept>

template <class T>
class stack {
public:
	stack ();
	~stack ();
	void push (T value);
	T pop ();
	T top ();
	int size ();
	calc_stack & operator<<(T value);
	calc_stack & operator>>(T value);
	T * m_data;
private:
	void expand ();

	int _size;
	int _capacity;
+};

template <class T>
stack<T>::stack ()
{
	_size = 0;
	_capacity = 8;
	_data = new T[_capacity];
}

template <class T>
stack<T>::~stack ()
{
	delete[] _data;
}

template <class T>
void stack<T>::push (T value)
{
	if (_size == _capacity) {
		expand ();
	}
	_data[_size] = value;
	++_size;
}

template <class T>
T stack<T>::pop ()
{
	if (0 == _size) {
		throw underflow_error("Стек пуст...");
	}
	return _data[--_size]; 
}

template <class T>
T stack<T>::top ()
{
	if (0 == _size) {
		throw underflow_error ("Стек пуст...");
	}
	return _data[_size - 1];
}

template <class T>
int stack<T>::size ()
{
	return _size;
}

template <class T>
void stack<T>::extend ()
{
	_capacity *= 2;
	T * new_data = new T[_capacity]; 
	for (int i = 0; i < _size; ++i) {
		new_data[i] = _data[i];
	}
	delete[] _data;
	_data = new_data;
}

template <class T>
stack<T> & stack<T>::operator<<(T value)
{
	push (value);
	return *this;
}

template <class T>
stack<T> & stack<T>::operator>>(T value)
{
	value = pop();
	return *this;
} 
