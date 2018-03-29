#pragma once
#include <iostream>
#include <string>

using namespace std;

enum colors {
	red,
	black
};

class rb{
public:
	rb(string key, string data, colors color = red, rb* left = NULL, rb* right = NULL, rb* parent = NULL);
	~rb();
	string search(string part, const int equal = 0);
	void add(string key, string data);
	int is_leaf();
	void optim();
private:
	colors color;
	string key;
	string data;
	rb* parent;
	rb* left;
	rb* right;
};

#include "rb_for_tree.tpp"
