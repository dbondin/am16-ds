#pragma once
#include <iostream>
#include "list_for_table.h"

class table {
public:
	table(int size);
	~table();
	void add(int key, string value);
	string search(int key);
private:
	int hash_key(int key);
	list* data;
	int h_size;
};

#include "table_for_hash.tpp"
