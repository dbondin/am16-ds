#include <tree.h>
#include <iostream>

using namespace std;

tree::tree(tree * _left_child, tree * _right_child, unsigned int _symbol , int _weight) {
    left_child = _left_child;
    right_child = _right_child;
    symbol = _symbol;
    weight = _weight;
}

tree::~tree() {
    if(left_child != NULL) delete left_child;
    if(right_child != NULL) delete right_child;
}

tree * tree::get_left_child() {
    return left_child;
}

tree * tree::get_right_child(){
    return right_child;
}

unsigned int tree::get_symbol() {
    return symbol;
}

int tree::get_weight() {
    return weight;
}

bool tree::is_leaf() {
    if ( (left_child != NULL) || (right_child != NULL) )
        return false;
    else
        return true;
}
