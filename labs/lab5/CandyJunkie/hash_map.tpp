#pragma once

hash_map::hash_map ()
{
	hashes = new hash_table (100);
	m_size = 0;
}

hash_map::~hash_map ()
{
	delete hashes;
}

void hash_map::insert (int key, std::string value)
{
	hashes->insert (key, value);
	++m_size;
}

std::string hash_map::search (int key)
{
	if (!m_size) {
		std::cout << "Пусто.\n";
		return "";
	}
	return hashes->search (key);
}

std::string hash_map::operator[] (int key)
{
	return search (key);
}
