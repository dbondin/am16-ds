#ifndef HASH_HEADER_
#define HASH_HEADER_
#include <iostream>
#include <string>
#include "sdl5list-2.h"
using namespace std;

template <class T>
class hachtable {
	public:
		hachtable();
		hachtable(int size);
		~hachtable();
		void insert(int key, T value);
		T get(int key);
	private:
		list<T> *heads;
		int size;
		int hach(int key);
};

template <class T>
hachtable<T>::hachtable()
{
	heads = new list<T> [20];
	size = 20;
}

template <class T>
hachtable<T>::hachtable(int newsize)
{
	heads = new list<T> [newsize];
	size = newsize;
}

template <class T>
hachtable<T>::~hachtable()
{
	delete [] heads;
	size = 0;
}

template <class T>
void hachtable<T>::insert(int key, T value)
{
	int hached = hach(key);
	heads[hashed].insert(key, value);
}

template <class T>
T hachtable<T>::get(int key)
{
	int hached = hach(key);
	return heads[hached].get(key);
}

template <class T>
int hachtable<T>::hach(int key)
{
	return key % size;
}


#endif
