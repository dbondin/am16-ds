#pragma once
#include <iostream>
#include "list.h"

class hash_table {
public:
	hash_table (int size);
	~hash_table ();
	void insert (int key, std::string value);
	std::string search (int key);
private:
	int hash (int key);
	list * data;
	int h_size;
};

#include "hash_table.tpp"