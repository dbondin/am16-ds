#pragma once

list::list()
{
	head = NULL;
}

list::~list()
{
	elem* tmp;
	while (head) 
	{
		tmp = head->next;
		delete head;
		head = tmp;
	}
}

void list::add(int key, string value)
{
	if (!head) {
		head = new elem {key, value, NULL};
	}
	else 
	{
		elem* tmp = head;
		while (tmp->next) 
		{
			tmp = tmp->next;
		}
		tmp->next = new elem{key, value, NULL};
	}
}

string list::search(int key)
{
	elem* tmp = head;
	while (tmp) 
	{
		if (key == tmp->key) 
		{
			return tmp->value;
		}
		else 
		{
			tmp = tmp->next;
		}
	}
	cout << "Не найдено!\n";
	return "";
}
