#pragma once
#include <stdexcept>

template <class T>
class stackcat {
public:
	stackcat ();
	~stackcat ();
	void push (T value);
	T pop ();
	T top ();
	int size ();
	stackcat & operator<<(T x);
	stackcat & operator>>(T x);
	T * st;
private:
	void expand ();

	int size1;
	int maxstack;
};


template <class T>
stackcat<T>::stackcat ()
{
	size1 = 0;
	maxstack = 8;
	st = new T[maxstack];
}

template <class T>
stackcat<T>::~stackcat ()
{
	delete[] st;
}

template <class T>
void stackcat<T>::push (T x)
{
	if (size1 == maxstack) 
	{
		expand ();
	}
	st[size1] = x;
	++size1;
}

template <class T>
T stackcat<T>::pop ()
{
	return st[--size1]; 
}

template <class T>
T stackcat<T>::top ()
{
	return st[size1 - 1];
}

template <class T>
int stackcat<T>::size ()
{
	return size1;
}

template <class T>
void stackcat<T>::expand ()
{
	maxstack *= 2;
	T * newst = new T[maxstack]; 
	for (int i = 0; i < size1; ++i) {
		newst[i] = st[i];
	}
	delete[] st;
st = newst;
}

template <class T>
stackcat<T> & stackcat<T>::operator<<(T x)
{
	push (x);
	return *this;
}

template <class T>
stackcat<T> & stackcat<T>::operator>>(T x)
{
	x = pop ();
	return *this;
}
