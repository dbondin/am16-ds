#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>

enum Colors{
    RED,
    BLACK
};

class Rb_tree{
private:
    Colors colors;
    std::string value;
    std::string key;
    Rb_tree *left;
    Rb_tree *right;
    Rb_tree *parent;
public:
    Rb_tree(std::string _value,std::string _key,Colors _colors = RED,Rb_tree *l = NULL,Rb_tree *r = NULL,Rb_tree *p = NULL);
    ~Rb_tree();
    int is_sheet();
    void balans();
    std::string search(std::string _key,const int exactly = 0);
    void add(std::string _value,std::string _key);
};

#include "tree.tpp"
#endif // TREE_HPP

