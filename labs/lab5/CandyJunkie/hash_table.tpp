#pragma once

hash_table::hash_table (int size)
{
	h_size = size;
	data = new list[size];
}

hash_table::~hash_table ()
{
	delete[] data;
}

void hash_table::insert (int key, std::string value)
{
	int index = hash (key);
	data[index].insert (key, value);
}

std::string hash_table::search (int key)
{
	int index = hash (key);
	return data[index].search (key);
}

int hash_table::hash (int key) {
	return key % h_size;
}