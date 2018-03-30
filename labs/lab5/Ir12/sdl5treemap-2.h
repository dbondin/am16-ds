#include <iostream>
#include <string>
#include "sdl5rbtree-2.h"

using namespace std;

template <class T>
class treemap {
	public:
		treemap();
		~treemap();
		void insert(string key, T value);
		T get(string key);
		virtual void print(string keyPart);
		virtual T errorlist();
	private:
	rbtree<T> *root;
};

template <class T>
treemap<T>::treemap()
{
	root = NULL;
}

template <class T>
treemap<T>::~treemap()
{
	delete root;
}

template <class T>
void treemap<T>::insert(string key, T value)
{
	if (!root)
		root = new rbtree<T>(NULL, NULL, NULL, key, value, 'b', true);
	else
		root->insert(key, value);
}

template <class T>
T treemap<T>::get(string key)
{
	if (!root)
		return errorlist();
	else
		return root->get(key);
}

void treemap<string>::print(string keyPart)
{
	if (!root)
		return;
	root->print(keyPart);
}

string treemap<string>::errorlist()
{
return "";
}

