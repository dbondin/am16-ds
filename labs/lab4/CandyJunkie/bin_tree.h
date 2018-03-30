#pragma once
#include <iostream>

class Node {
public:
	Node (int new_weight = 0, char new_letter = 0, Node * set_lchild = NULL, Node * set_rchild = NULL);
	~Node ();
	Node * merge_as_left_subtree_with (Node * right_subtree);
	int is_leaf ();
	int get_weight ();
	char get_letter ();
	Node * get_lchild ();
	Node * get_rchild ();
private:
	int weight;
	char letter;
	Node * lchild;
	Node * rchild;
};

#include "bin_tree.tpp"