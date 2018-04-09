#pragma once

template <class T>
class stack {
public:
	stack();
	~stack();
	void push(T &value);
	T pop();
	int size();
	stack & operator<<(T value);
	T * s_data;
private:
	void expand();
	int s_size;
	int s_capacity;
};

#include "stack.tpp"
