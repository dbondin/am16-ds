#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

using namespace std;

int min_id(huffman_tree **trees) {
    int m_weight = -1;
    int min = 0;
    for (int i = 0; i < 256; ++i) {
        if((trees[i]->get_weight() < m_weight) || (m_weight == -1))
            if (trees[i]) {
                min = i;
                m_weight = trees[i]->get_weight();
        }
    }
    return min;
}

huffman_tree * make_node(huffman_tree *left_child, huffman_tree *right_child) {
    huffman_tree * node = new huffman_tree(left_child, right_child, 0, left_child->get_weight() + right_child->get_weight());
    return node;
}

huffman_tree * make_huffman_tree(huffman_tree **forest) {
    for (int trees = 256; trees > 1; --trees) {
        huffman_tree * left_tree = forest[min_id(forest)];
        for (int i = min_id(forest); i < 256; ++i)  forest[i] = forest[i + 1];
        forest[255] = NULL;
        huffman_tree *right_tree = forest[min_id(forest)];
        for (int i = min_id(forest); i < 255; ++i)  forest[i] = forest[i + 1];
        forest[255] = make_node(left_tree, right_tree);
    }
    return forest[255];
}

void way(huffman_tree * _tree, string *codes, string buff){
    if (_tree->get_left()) {
        buff += '0';
        way(_tree->get_left(), codes, buff);
        buff.pop_back();
    }
    if (_tree->get_right()) {
        buff += '1';
        way(_tree->get_right(), codes, buff);
        buff.pop_back();
    }
    else if (_tree->is_leaf()) {
        codes[_tree->get_symbol()] = buff;
    }
}

huffman_tree *uncode(huffman_tree * Huffman_tree, string str)
{
    huffman_tree * counter = Huffman_tree;
        for (unsigned int i = 0; i < str.size(); ++i) {
            if (str[i] == '0') {
                counter = counter->get_left();
                if (counter->is_leaf()) {
                    return counter;
                }
            }
            else {
                counter = counter->get_right();
                if (counter->is_leaf()) {
                    return counter;
                }
            }
        }
    return NULL;
}

void uncompress(huffman_tree *_tree, string input, string output, string * codes)
{
    ifstream in(input);
    ofstream out(output);
    string rem;
    int file_size = _tree->get_weight();
    char symbol;
    int size = 0;
    string new_byte;
    while (in.get(symbol)) {
        if (size >= file_size) {
            break;
        }
        for (int i = 7; i >= 0; --i) {
            if(symbol & (0x1 << i)) new_byte += "1";
            else new_byte += "0";
        }

        rem += new_byte;
        new_byte.clear ();
        huffman_tree * uncoding;
        while (uncoding = uncode(_tree, rem)) {
            char letter = (char)uncoding->get_symbol();
            out.put (letter);
            ++size;
            if (size == file_size) {
                break;
            }
            rem.erase(0, codes[(unsigned char)letter].size ());
        }
    }

}

huffman_tree::huffman_tree(huffman_tree *l, huffman_tree *r, char sym, int w) {
        left = l;
        right = r;
        symbol = sym;
        weight = w;
}

huffman_tree::~huffman_tree() {
        if(left)  delete left;
        if(right) delete right;
    }

bool huffman_tree::is_leaf() {
        if ((left == NULL) && (right == NULL)) return true;
        else                                   return false;
}

huffman_tree * huffman_tree::get_left() {
    return left;
}

huffman_tree * huffman_tree::get_right() {
    return right;
}
int huffman_tree::get_weight() {
    return weight;
}

char huffman_tree::get_symbol() {
    return symbol;
}
