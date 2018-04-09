#include <iostream>
#include <string>
#include "tree_map.h"
#include "tree.h"
#include "man.h"

tree_map::tree_map(){
    root = NULL;
}

tree_map::~tree_map(){
    delete root;
}

void tree_map::set(std::string key, Man man) {
    std::string data = man.telephone + " " + man.surname + " " + man.name;
    if (!root)
        root = new tree(BLACK, "", "", NULL, NULL, NULL, true);
    else
        root->set(key, data);
}

std::string tree_map::get(std::string key) {
    if (!root)
        return "";
    else
        return root->get(key);
}

void tree_map::search_and_print(std::string key) {
    if (!root)
        return;
    root->search_and_print(key);
}
