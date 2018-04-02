#ifndef HASH_MAP
#define HASH_MAP
#include <iostream>

using namespace std;
template <class H>
class spis {
    private:
        struct spis_chel {
            int key;
            H znach;
            spis_chel *sled;
            spis_chel *pred;
            spis_chel (int key, H znach, spis_chel *sled, spis_chel *pred);
            ~spis_chel () {};
        };
        spis_chel *ist;
    public:
        spis();
        spis(int key, H znach, spis_chel *sled, spis_chel *pred);
        ~spis();
        void add(int key, H znach);
        H get(int key);
        virtual H no_result ();
};

template <class H>
H spis<H>::no_result()
{
    return "";
}

template <class H>
spis<H>::spis()
{
    ist = new spis_chel(-1, no_result(), NULL, NULL);
}

template <class H>
spis<H>::spis(int key, H znach, spis_chel *sled, spis_chel *pred)
{
    ist = new spis_chel(key, znach, sled, pred);
}

template <class H>
spis<H>::spis_chel::spis_chel(int _key, H _znach, spis_chel *_sled, spis_chel *_pred)
{
    key = _key;
    znach = _znach;
    sled = _sled;
    pred = _pred;
}

template <class H>
spis<H>::~spis()
{
    if (ist) delete ist;
}

template <class H>
void spis<H>::add(int key, H znach)
{
    if (!ist) {
        ist = new spis_chel(key, znach, NULL, NULL);
        return;
    }
    spis_chel *counter = ist;

    while (counter->sled)
        counter = counter->sled;
    counter->sled = new spis_chel(key, znach, NULL, counter);
}

template <class H>
H spis<H>::get(int key)
{
    if (!ist)
        return no_result();
    if (ist->key == key)
        return ist->znach;
    spis_chel *counter = ist;
    while (counter = counter->sled)
        if (counter->key == key)
            return counter->znach;
    return no_result();
}


template <class H>
class hash_table {
    public:
        hash_table();
        hash_table(int size);
        ~hash_table();
        void add(int key, H znach);
        H get(int key);
    private:
        spis<H> *head;
        int size;
        int hash(int key);
};

template <class H>
hash_table<H>::hash_table()
{
    head = new spis<H> [20];
    size = 20;
}

template <class H>
hash_table<H>::hash_table(int _size)
{
    head = new spis<H> [_size];
    size = _size;
}

template <class H>
hash_table<H>::~hash_table()
{
    delete [] head;
    size = 0;
}

template <class H>
void hash_table<H>::add(int key, H znach)
{
    int hashed = hash(key);
    head[hashed].add(key, znach);
}

template <class H>
H hash_table<H>::get(int key)
{
    int hashed = hash(key);
    return head[hashed].get(key);
}

template <class H>
int hash_table<H>::hash(int key)
{
    return key % size;
}


template <class H>
class hash_map {
    public:
        hash_map();
        hash_map(int size);
        ~hash_map();
        void add(int key, H znach);
        H get(int key);
    private:
        hash_table<H> *table;
        int size;
};

template <class H>
hash_map<H>::hash_map()
{
    table = new hash_table<H>;
    size = 20;
}

template <class H>
hash_map<H>::hash_map(int _size)
{
    table = new hash_table<H>(_size);
    size = _size;
}

template <class H>
hash_map<H>::~hash_map()
{
    delete table;
    size = 0;
}

template <class H>
void hash_map<H>::add(int key, H znach)
{
    table->add(key, znach);
}

template <class H>
H hash_map<H>::get(int key)
{
    return table->get(key);
}

#endif 