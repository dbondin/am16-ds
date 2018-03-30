#pragma once

template <class T>
class stack {
public:
	stack();
	~stack ();
	void push (T &value);
	T pop();
	T last();
	int size();
	
private:
	void expand();

	int s_size;
	int s_capacity;
	T * s_data;
};

#include "stack.tpp"
