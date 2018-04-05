#ifndef MAP_OF_TABLE_H
#define MAP_OF_TABLE_H

#include <iostream>
#include <string>
#include "table.h"
#include "man.h"

class map_of_table {
private:
    table * _table;
    int size;
public:
    map_of_table();
    map_of_table(int size);
    ~map_of_table();
    void set(int key, Man man);
    std::string get(int key);
};

#endif
