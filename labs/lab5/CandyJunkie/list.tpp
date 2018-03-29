#pragma once


list::list ()
{
	head = NULL;
}

list::~list ()
{
	list_elem * temp;
	while (head) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

void list::insert (int key, std::string value)
{
	if (!head) {
		head = new list_elem{key, value, NULL};
	}
	else {
		list_elem * temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new list_elem{key, value, NULL};
	}
}

std::string list::search (int key)
{
	list_elem * temp = head;
	while (temp) {
		if (key == temp->key) {
			return temp->value;
		}
		else {
			temp = temp->next;
		}
	}

	std::cout << "Ничего не нашли\n";
	return "";
}
