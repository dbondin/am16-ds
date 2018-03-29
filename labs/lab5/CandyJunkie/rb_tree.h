#pragma once
#include <iostream>

enum rb_node_colors {
	RED,
	BLACK
};

class rb_node {
public:
	rb_node (std::string key, std::string data, rb_node_colors color = RED, rb_node * lchild = NULL, rb_node * rchild = NULL, rb_node * parent = NULL);
	~rb_node ();
	std::string search (std::string part_of_key, const int equal = 0);
	void insert (std::string key, std::string data);
	int is_leaf ();
	void make_tree_good ();
private:
	rb_node_colors color;
	std::string key;
	std::string data;
	rb_node * parent;
	rb_node * lchild;
	rb_node * rchild;
};

#include "rb_tree.tpp"