#pragma once

tree::tree()
{
	root = NULL;
	m_size = 0;
}

tree::~tree()
{
	delete root;
	root = NULL;
}

void tree::add(string key, string value)
{
	if (!root) {
		root = new rb(key, value, black, NULL, NULL, NULL);
		++m_size;
	}
	else {
		root->add(key, value);
		++m_size;
	}
}

string tree::search(string key)
{
	if (root) {
		return root->search(key, 1);
	}
	else 
	{
		cout << "Пусто\n";
		return "";
	}
}

string tree::search_part(string part)
{
	if (root) 
	{
		return root->search(part);
	}
	else 
	{
		cout << "Пусто\n";
		return "";
	}
}

string tree::operator[](string key)
{
	return search(key);
}

int tree::size()
{
	return m_size;
}
