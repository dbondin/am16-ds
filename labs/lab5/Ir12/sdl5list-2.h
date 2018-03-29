#ifndef HASH_HEADER_
#define HASH_HEADER_
#include <iostream>
#include <string>
using namespace std;

template <class T>
class list 
{
	public:
		struct list1 
		{
			int key;
			T value;
			list1 *next;
			list1 *pred;
			list1 (int key, T value, list1 *next, list1 *pred);
			~list1 () {};
		};
		list1 *head;
		list();
		list(int key, T value, list1 *next, list1 *pred);
		~list();
		void insert(int key, T value);
		T get(int key);	
		virtual T errorlist();
};

template <class T>
list<T>::list()
{
	head = new list1(-1, errorlist(), NULL, NULL);
}

template <class T>
list<T>::list(int key, T value, list1 *next, list1 *pred)
{
	head = new list1(key, value, next, pred);
}

template <class T>
list<T>::list1::list1(int newkey, T newvalue, list1 *newnext, list1 *newpred)
{
	key = newkey;
	value = newvalue;
	next = newnext;
	pred = newpred;
}

template <class T>
list<T>::~list()
{
	if (head) 
	delete head;
}

template <class T>
void list<T>::insert(int key, T value)
{
	if (!head) 
	{
		head = new list1(key, value, NULL, NULL);
		return;
	}
	list1 *kolvo = head;
	
	while (kolvo->next)
		kolvo = kolvo->next;
		kolvo->next = new list1(key, value, NULL, kolvo);
}

template <class T>
T list<T>::get(int key)
{
	if (!head)
		return errorlist();
	if (head->key == key)
		return head->value;
	listElem *kolvo = head;
	while (counter = kolvo->next)
		if (counter->key == key)
			return kolvo->value;
	return errorlist();
}	

string list<string>::errorlist()
{
	return "";
}

#endif
