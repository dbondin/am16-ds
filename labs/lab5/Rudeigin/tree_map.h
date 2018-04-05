#pragma once

#include <iostream>
#include <string>
#include "man.h"
#include "tree.h"

class tree_map {
private:
    tree *root;
public:
    tree_map();
    ~tree_map();
    void set(std::string key, Man man);
    std::string get(std::string key);
    virtual void search_and_print(std::string key);
};
