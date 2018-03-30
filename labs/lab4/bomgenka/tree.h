#ifndef TREE
#define TREE
#include <iostream>
using namespace std;

#define NUM_OF_SYMB 256
class tree {
    private:
        tree * left_child;
        tree * right_child;
        unsigned int symbol;
        int weight;
    public:
        tree(tree * _left_child = NULL, tree * _right_child = NULL, unsigned int _symbol = 0, int _weight = 0);
        ~tree();

        tree * get_left_child();
        tree * get_right_child();
        bool is_leaf();
        unsigned int get_symbol();
        int get_weight();
};

union bytec {
    unsigned int number;
    unsigned char bytes[4];
};
#endif // TREE

