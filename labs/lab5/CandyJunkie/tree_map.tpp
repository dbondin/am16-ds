#pragma once

tree_map::tree_map ()
{
	root = NULL;
	m_size = 0;
}

tree_map::~tree_map ()
{
	delete root;
	root = NULL;
}

void tree_map::insert (std::string key, std::string value)
{
	if (!root) {
		root = new rb_node (key, value, BLACK, NULL, NULL, NULL);
		++m_size;
	}
	else {
		root->insert (key, value);
		++m_size;
	}
}

std::string tree_map::search (std::string key)
{
	if (root) {
		return root->search (key, 1);
	}
	else {
		std::cout << "Пусто.\n";
		return "";
	}
}

std::string tree_map::search_by_part_of_the_key (std::string part_of_the_key)
{
	if (root) {
		return root->search (part_of_the_key);
	}
	else {
		std::cout << "Пусто.\n";
		return "";
	}
}

std::string tree_map::operator[] (std::string key)
{
	return search (key);
}

int tree_map::size ()
{
	return m_size;
}
