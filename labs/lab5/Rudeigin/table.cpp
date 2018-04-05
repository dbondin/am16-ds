#include <iostream>
#include <string>
#include "m_list.h"
#include "list.h"
#include "table.h"

table::table(){
    nodes = new list[20];
    size = 20;
}

table::table(int _size) {
    nodes = new list[_size];
    size = _size;
}

table::~table() {
    delete [] nodes;
    size = 0;
}

void table::set(int key, std::string data) {
    int buff = del(key);
    nodes[buff].set(key, data);
}

int table::del(int key) {
    return key%size;
}

std::string table::get(int key) {
    int buff = del(key);
    return nodes[buff].get(key);
}
