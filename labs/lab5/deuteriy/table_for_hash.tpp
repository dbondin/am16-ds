#pragma once

table::table(int size)
{
	h_size = size;
	data = new list[size];
}

table::~table()
{
	delete[] data;
}

void table::add(int key, string value)
{
	int index = hash_key(key);
	data[index].add(key, value);
}

string table::search(int key)
{
	int index = hash_key(key);
	return data[index].search(key);
}

int table::hash_key(int key) 
{
	return key % h_size;
}
