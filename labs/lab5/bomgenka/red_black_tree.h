#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H
#include <iostream>
#include <string>

using namespace std;

enum colour { BLACK, RED };

class red_black_tree {
private:
    colour color;
    string data;
    string key;
    red_black_tree *left_child;
    red_black_tree *right_child;
    red_black_tree *parent;
    bool lchild;
public:
    red_black_tree(colour _color = BLACK, string _data = "", string _key = "", red_black_tree *_left_child = NULL, red_black_tree *_right_child = NULL, red_black_tree *_parent = NULL, bool _lchild = false);
    ~red_black_tree();
    void mga();
    void add(string key, string _data);
    bool is_nill();
    string get(string key);

    virtual void search(string key);
};


class tree_map {
private:
    red_black_tree *root;
public:
    tree_map();
    ~tree_map();
    void add(string key, string data);
    string get(string key);
    virtual void search(string key);
};

#endif // RED_BLACK_TREE_H
