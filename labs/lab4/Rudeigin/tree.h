#ifndef TREE
#define TREE
#include <iostream>

class huffman_tree {
private:
    huffman_tree * left;
    huffman_tree * right;
    char symbol;
    int weight;
public:
    huffman_tree(huffman_tree *l = NULL, huffman_tree *r = NULL, char sym = 0, int w = 0);
    ~huffman_tree();
    bool is_leaf();

    huffman_tree * get_left();
    huffman_tree * get_right();
    int get_weight();
    char get_symbol();
};

union bytec {
    unsigned int number;
    unsigned char bytes[4];
};

huffman_tree * make_node(huffman_tree * left_child, huffman_tree * right_child);
int min_id(huffman_tree ** trees);
huffman_tree * make_huffman_tree(huffman_tree **forest);
void way(huffman_tree *_tree, std::string *codes, std::string current_code);
huffman_tree * decode(huffman_tree * big_tree, std::string str);
void uncompress(huffman_tree *_tree, std::string input, std::string output, std::string * codes);
#endif // TREE
