#include <iostream>
#include <string>
#include "man.h"
#include "table.h"
#include "map_of_table.h"

map_of_table::map_of_table(){
    _table = new table [20];
    size = 20;
}

map_of_table::map_of_table(int _size) {
    _table = new table(_size);
    size = _size;
}

map_of_table::~map_of_table() {
    delete _table;
    size = 0;
}

void map_of_table::set(int key, Man man) {
    std::string value = man.telephone + " " + man.surname + " " + man.name;
    _table->set(key, value);
}

std::string map_of_table::get(int key) {
    return _table->get(key);
}

