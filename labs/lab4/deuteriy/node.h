#pragma once
#include <iostream>

class Node {
public:
	Node (int n_wt = 0, char n_data = 0, Node* set_left = NULL, Node* set_right = NULL);
	~Node();
	Node* link(Node* right_t);
	int check_leaf();
	int get_wt();
	char get_data();
	Node* get_left();
	Node* get_right();
private:
	int wt;
	char data;
	Node* left;
	Node* right;
};

#include "node.tpp"
