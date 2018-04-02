#ifndef TREE_MAP_HPP
#define TREE_MAP_HPP

#include <iostream>
#include "map.hpp"
#include "tree.hpp"

class Map_tree : public Map<std::string,std::string>{
private:
    Rb_tree * root;
public:
    Map_tree();
    ~Map_tree();
    std::string search(std::string key);
    std::string partial_search(std::string key);
    void add(std::string key, std::string value);
};

#include "tree_map.tpp"
#endif // TREE_MAP_HPP

