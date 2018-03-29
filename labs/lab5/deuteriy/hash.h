#pragma once
#include <iostream>
#include "table_for_hash.h"
#include "map.h"

class hash : public map<int, string> {
public:
	hash();
	~hash();
	void add(int key, std::string value);
	string search(int key);
	string operator[](int key);
	int size();
private:
	hash* hashes;
	int m_size;
};

#include "hash.tpp"
