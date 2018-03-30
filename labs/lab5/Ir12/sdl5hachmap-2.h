#ifndef HASH_HEADER_
#define HASH_HEADER_
#include <iostream>
#include <string>
#include "sdl5hachtable-2.h"

using namespace std;
template <class T>
hachmap <T>::hachmap()
{
	table = new hachtable<T>;
	size = 20;
}

template <class T>
hachmap <T>::hachmap(int newsize)
{
	table = new hachtable<T>(newsize);
	size = newsize;
}

template <class T>
hachmap <T>::~hachmap()
{
	delete table;
	size = 0;
}

template <class T>
void hachmap <T>::insert(int key, T value)
{
	table->insert(key, value);
}

template <class T>
T hachmap <T>::get(int key)
{
	return table->get(key);
}

#endif
