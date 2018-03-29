#pragma once
#include <iostream>
#include "hash_table.h"
#include "map.h"

class hash_map : public map<int, std::string> {
public:
	hash_map ();
	~hash_map ();
	void insert (int key, std::string value);
	std::string search (int key);
	std::string operator[] (int key);
	int size ();
private:
	hash_table * hashes;
	int m_size;
};

#include "hash_map.tpp"