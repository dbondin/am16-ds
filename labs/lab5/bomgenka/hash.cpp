#include "hash.h"
#include <iostream>
#include <string>
_list::_list(int _key, std::string _data, _list *_n, _list *_p) {
    key = _key;
    data = _data;
    n = _n;
    p = _p;
}

hash::hash(){
    head = new _list(-1,"", NULL, NULL);
}

hash::hash(int key, std::string data, _list *n, _list *p) {
    head = new _list(key, data, n, p);
}



hash::~hash() {
    if(head) {
        delete head;
    }
}

void hash::add(int key, std::string data) {
    if (!head) {
        head = new _list(key, data, NULL, NULL);
        return;
    }
    _list *num = head;

    while (num->n)
        num = num->n;
    num->n = new _list(key, data, NULL, num);
}

std::string hash::get(int key) {
    if (!head)
        return "";
    if (head->key == key)
        return head->data;
    _list *num = head;
    while (num = num->n)
        if (num->key == key)
            return num->data;
    return "";
}

hash_table::hash_table(){
    heads = new hash[20];
    size = 20;
}

hash_table::hash_table(int _size) {
    heads = new hash[_size];
    size = _size;
}

hash_table::~hash_table() {
    delete [] heads;
    size = 0;
}

void hash_table::add(int key, std::string data) {
    int buff = h(key);
    heads[buff].add(key, data);
}

std::string hash_table::get(int key) {
    int buff = h(key);
    return heads[buff].get(key);
}

int hash_table::h(int key) {
    return key%size;
}

hash_map::hash_map(){
    table = new hash_table [20];
    size = 20;
}

hash_map::hash_map(int _size) {
    table = new hash_table(_size);
    size = _size;
}

hash_map::~hash_map() {
    delete table;
    size = 0;
}

void hash_map::add(int key, std::string data) {
    table->add(key, data);
}

std::string hash_map::get(int key) {
    return table->get(key);
}
