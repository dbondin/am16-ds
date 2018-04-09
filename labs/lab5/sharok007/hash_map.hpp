#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <iostream>
#include "map.hpp"
#include "hash_table.hpp"

class Hash_map : public Map<int,std::string>{
private:
    Hash_table *table;
    int size_map;
public:
    Hash_map();
    ~Hash_map();
    void add(int key, std::string value);
    std::string search(int key);
};

#include "hash_map.tpp"
#endif // HASH_MAP_HPP

