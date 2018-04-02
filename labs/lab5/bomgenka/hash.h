#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>

struct _list {
    int key;
    std::string data;
    struct _list *n;
    struct _list *p;
    _list(int key, std::string data, _list *_n, _list *_p);
    _list() {

    }
};

class hash {
    private:
        _list ex;
        _list *head;
    public:
        hash();
        hash(int key, std::string data, _list *n, _list *p);
        ~hash();
        void add(int key, std::string data);
        std::string get(int key);
};


class hash_table {
private:
    hash *heads;
    int size;
    int h(int key);
public:
    hash_table(int _size);
    hash_table();
    ~hash_table();
    void add(int key, std::string data);
    std::string get(int key);

};

class hash_map {
private:
    hash_table *table;
    int size;
public:
    hash_map();
    hash_map(int size);
    ~hash_map();
    void add(int key, std::string data);
    std::string get(int key);

};
#endif // HASH_H


