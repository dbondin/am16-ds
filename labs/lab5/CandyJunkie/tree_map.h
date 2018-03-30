#pragma once
#include <iostream>
#include "rb_tree.h"
#include "map.h"

class tree_map : public map<std::string, std::string> {
public:
	tree_map ();
	~tree_map ();
	void insert (std::string key, std::string value);
	std::string search (std::string key);
	std::string search_by_part_of_the_key (std::string part_of_the_key);
	std::string operator[] (std::string key);
	int size ();
private:
	rb_node * root;
	int m_size;
};

#include "tree_map.tpp"