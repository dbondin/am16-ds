#pragma once

hash::hash()
{
	hashes = new table(100);
	m_size = 0;
}

hash::~hash()
{
	delete hashes;
}

void hash::add(int key, string value)
{
	hashes->add(key, value);
	++m_size;
}

string hash::search(int key)
{
	if (!m_size) 
	{
		cout << "Пусто\n";
		return "";
	}
	return hashes->search(key);
}

string hash::operator[](int key)
{
	return search(key);
}
