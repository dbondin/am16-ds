#pragma once
#include <iostream>
#include <string>
#include "rb_for_tree.h"
#include "map.h"

class tree : public map<string, string> {
public:
	tree();
	~tree();
	void add(std::string key, std::string value);
	string search(string key);
	string search_part (string part);
	string operator[](string key);
	int size();
private:
	rb* root;
	int m_size;
};

#include "tree.tpp"
