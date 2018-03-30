#pragma once
#include <iostream>

class list {
public:
	list();
	~list();
	void add(int key, string value);
	string search (int key);
private:
	struct elem 
	{
		int key;
		string value;
		elem* next;
	};
	elem* head;
};

#include "list_for_table.tpp"
