#pragma once

template <class T>
class calc_stack {
public:
	calc_stack ();
	~calc_stack ();
	void push (T value);
	T pop ();
	T top ();
	int size ();
	calc_stack & operator<<(T value);
	calc_stack & operator>>(T value);
	T * m_data;
private:
	void expand ();

	int m_size;
	int m_capacity;
};

#include "calc_stack.tpp"
