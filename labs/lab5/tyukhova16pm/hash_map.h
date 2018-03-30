#ifndef HASH_MAP_H
#define HASH_MAP_H
#include <iostream>

using namespace std;
template <class T>
class list {
    private:
        struct listElem {
            int key;
            T value;
            listElem *next;
            listElem *prev;
            listElem (int key, T value, listElem *next, listElem *prev);
            ~listElem () {};
        };
        listElem *head;
    public:
        list();
        list(int key, T value, listElem *next, listElem *prev);
        ~list();
        void add(int key, T value);
        T get(int key);
        virtual T badResult ();
};

template <class T>
T list<T>::badResult()
{
    return "";
}

template <class T>
list<T>::list()
{
    head = new listElem(-1, badResult(), NULL, NULL);
}

template <class T>
list<T>::list(int key, T value, listElem *next, listElem *prev)
{
    head = new listElem(key, value, next, prev);
}

template <class T>
list<T>::listElem::listElem(int _key, T _value, listElem *_next, listElem *_prev)
{
    key = _key;
    value = _value;
    next = _next;
    prev = _prev;
}

template <class T>
list<T>::~list()
{
    if (head) delete head;
}

template <class T>
void list<T>::add(int key, T value)
{
    if (!head) {
        head = new listElem(key, value, NULL, NULL);
        return;
    }
    listElem *counter = head;

    while (counter->next)
        counter = counter->next;
    counter->next = new listElem(key, value, NULL, counter);
}

template <class T>
T list<T>::get(int key)
{
    if (!head)
        return badResult();
    if (head->key == key)
        return head->value;
    listElem *counter = head;
    while (counter = counter->next)
        if (counter->key == key)
            return counter->value;
    return badResult();
}


template <class T>
class hashTable {
    public:
        hashTable();
        hashTable(int size);
        ~hashTable();
        void add(int key, T value);
        T get(int key);
    private:
        list<T> *heads;
        int size;
        int hash(int key);
};

template <class T>
hashTable<T>::hashTable()
{
    heads = new list<T> [20];
    size = 20;
}

template <class T>
hashTable<T>::hashTable(int _size)
{
    heads = new list<T> [_size];
    size = _size;
}

template <class T>
hashTable<T>::~hashTable()
{
    delete [] heads;
    size = 0;
}

template <class T>
void hashTable<T>::add(int key, T value)
{
    int hashed = hash(key);
    heads[hashed].add(key, value);
}

template <class T>
T hashTable<T>::get(int key)
{
    int hashed = hash(key);
    return heads[hashed].get(key);
}

template <class T>
int hashTable<T>::hash(int key)
{
    return key % size;
}


template <class T>
class hashMap {
    public:
        hashMap();
        hashMap(int size);
        ~hashMap();
        void add(int key, T value);
        T get(int key);
    private:
        hashTable<T> *table;
        int size;
};

template <class T>
hashMap<T>::hashMap()
{
    table = new hashTable<T>;
    size = 20;
}

template <class T>
hashMap<T>::hashMap(int _size)
{
    table = new hashTable<T>(_size);
    size = _size;
}

template <class T>
hashMap<T>::~hashMap()
{
    delete table;
    size = 0;
}

template <class T>
void hashMap<T>::add(int key, T value)
{
    table->add(key, value);
}

template <class T>
T hashMap<T>::get(int key)
{
    return table->get(key);
}

#endif // HASH_MAP_H
