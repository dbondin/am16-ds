#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include "list.hpp"

class Hash_table{
private:
    int size_table;
    List *data;
    int hash(int key);
public:
    Hash_table(int size);
    ~Hash_table();
    void add(int key,std::string value);
    std::string search(int key);
};

#include "hash_table.tpp"
#endif // HASH_TABLE_HPP

