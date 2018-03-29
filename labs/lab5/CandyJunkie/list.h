#pragma once
#include <iostream>

class list {
public:
	list ();
	~list ();
	void insert (int key, std::string value);
	std::string search (int key);
private:
	struct list_elem {
		int key;
		std::string value;
		list_elem * next;
	};
	list_elem * head;
};

#include "list.tpp"