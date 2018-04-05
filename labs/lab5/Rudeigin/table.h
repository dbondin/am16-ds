#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include "m_list.h"
#include "list.h"

class table {
private:
    list *nodes;
    int size;
public:
    table(int _size);
    table();
    ~table();
    int del(int key);
    void set(int key, std::string data);
    std::string get(int key);
};

#endif

