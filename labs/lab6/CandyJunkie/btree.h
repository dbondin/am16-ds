#pragma once
#include <fstream>

template <class K, class V>
class bnode {
public:
	bnode (std::string directory, int pos, int parent);
	bnode (K key, V value, std::string directory);
	~bnode () {};
	void insert (K key, V value);
	V search (K key);
	virtual bool less (K key1, K key2);
	virtual K no_key ();
	virtual V no_value ();
	void search_from_to (std::ofstream & out, K key_from, K key_to);
	bool is_leaf () const;
	void make_tree_good ();
	bnode * load_parent ();
	bnode * load_child (int pos);
	bnode * load (std::string directory, int tag);
	void load_myself ();
	void save_to (std::string directory);
	virtual K read_key (std::ifstream & in);
	virtual V read_value (std::ifstream & in);
	virtual void write_key (std::ofstream & out, K key);
	virtual void write_value (std::ofstream & out, V value);
	bool has_parent () const;
	std::string directory_name;
	int my_tag;
private:
	static const int t = 100;
	int size;
	K keys[2 * t - 1];
	V values[2 * t - 1];
	int parent_tag;
	int childs_tag[2 * t];
	static int last_tag;
};

template <class K, class V>
int bnode<K, V>::last_tag = 1;

template <class K, class V>
bnode<K, V>::bnode (std::string directory, int pos, int parent)
{
	size = 0;
	parent_tag = parent;
	for (int i = 0; i < 2 * t - 1; ++i) {
		childs_tag[i] = 0;
		keys[i] = no_key ();
		values[i] = no_value ();
	}
	childs_tag[2 * t - 1] = 0;
	directory_name = directory;
	my_tag = pos;
}

template <class K, class V>
bnode<K, V>::bnode (K key, V value, std::string directory)
{
	size = 1;
	parent_tag = 0;

	keys[0] = key;
	values[0] = value;
	childs_tag[0] = 0;
	for (int i = 1; i < 2 * t - 1; ++i) {
		childs_tag[i] = 0;
		keys[i] = no_key ();
		values[i] = no_value ();
	}
	childs_tag[2 * t - 1] = 0;
	directory_name = directory;
	my_tag = last_tag;
	++last_tag;
}

template <class K, class V>
void bnode<K, V>::insert (K key, V value)
{
	if (is_leaf ()) {
		int i = 0;
		for (i = 0; i < size; ++i) {
			if (less (key, keys[i])) {
				for (int j = size; j > i; --j) {
					values[j] = values[j - 1];
					keys[j] = keys[j - 1];
				}
				values[i] = value;
				keys[i] = key;
				break;
			}
		}
		if (i == size) {
			values[i] = value;
			keys[i] = key;
		}
		++size;
		if (size >= 2 * t - 1) {
			make_tree_good ();
		}
		else {
			save_to (directory_name);
		}
	}
	else {
		for (int i = 0; i < size; ++i) {
			if (less (key, keys[i])) {
				bnode * child = load_child (i);
				child->insert (key, value);
				child->save_to (directory_name);
				if (child) {
					delete child;
					child = NULL;
				}
				return;
			}
		}
		if (childs_tag[0] != 0) {
			bnode * child = load_child (size);
			child->insert (key, value);
			child->save_to (directory_name);
			if (child) {
				delete child;
				child = NULL;
			}
		}
		return;
	}
}

template <class K, class V>
void bnode<K, V>::make_tree_good ()
{
	bnode * new_bnode = new bnode (directory_name, last_tag, parent_tag);
	++last_tag;
	for (int i = 0; i < t - 1; ++i) {
		new_bnode->keys[i] = keys[t + i];
		keys[t + i] = no_key ();
		new_bnode->values[i] = values[t + i];
		values[t + i] = no_value ();
		new_bnode->childs_tag[i] = childs_tag[t + i];
		childs_tag[t + i] = 0;

		++new_bnode->size;
		--size;
	}
	new_bnode->childs_tag[t - 1] = childs_tag[2 * t - 1];
	childs_tag[2 * t - 1] = 0;
	if (parent_tag!= 0) {
		new_bnode->save_to (directory_name);	

		bnode * parent = load_parent ();
		int psize = parent->size;
		int pos = 0;
		for (; pos < psize; ++pos) {
			if (less (keys[t - 1], parent->keys[pos])) {
				break;
			}
		}
		for (int j = psize; j > pos; --j) {
			parent->values[j] = parent->values[j - 1];
			parent->keys[j] = parent->keys[j - 1];
			parent->childs_tag[j + 1] = parent->childs_tag[j];
		}
		parent->values[pos] = values[t - 1];
		parent->keys[pos] = keys[t - 1];
		parent->childs_tag[pos + 1] = new_bnode->my_tag;
		values[t - 1] = no_value ();
		keys[t - 1] = no_key ();
		--size;
		this->save_to (directory_name);

		++parent->size;
		parent->save_to (directory_name);
		if (parent->size >= 2 * t - 1) {
			parent->make_tree_good ();
			}
		delete parent;
	}
	else {
		bnode * parent = new bnode (directory_name, last_tag, 0);
		++last_tag;
		parent->keys[0] = keys[t - 1];
		parent->values[0] = values[t - 1];
		values[t - 1] = no_value ();
		keys[t - 1] = no_key ();
		--size;
		parent->childs_tag[0] = my_tag;
		parent->childs_tag[1] = new_bnode->my_tag;
		++parent->size;
		parent_tag = parent->my_tag;
		new_bnode->parent_tag = parent->my_tag;

		new_bnode->save_to (directory_name);
		this->save_to (directory_name);
		parent->save_to (directory_name);

		delete parent;
	}
	delete new_bnode;
}

template <class K, class V>
V bnode<K, V>::search (K key)
{
	for (int i = 0; i < size; ++i) {
		if (less (key, keys[i])) {
			if (childs_tag[i]) {
				bnode * child = load_child (i);
				V value = child->search (key);
				delete child;
				return value;
			}
			else {
				return no_value ();
			}
		}
		else if (less (keys[i], key)) {
			continue;
		}
		else { // случай равенства
			return values[i];
		}	
	}
	if (childs_tag[size]) {
		bnode * child = load_child (size);
		V value = child->search (key);
		delete child;
		return value;
	}
	else {
		return no_value ();
	}
}

template <class K, class V>
void bnode<K, V>::search_from_to (std::ofstream & out, K key_from, K key_to)
{
	if (!(less (key_to, no_key ()) || less (no_key (), key_to))) { // Если нет ограничения справа
		for (int i = 0; i < size; ++i) {
			if (less (key_from, keys[i])) { // если key_from < ключа, то выводим левого ребенка и значение по ключу.
				if (childs_tag[i]) {
					bnode * child = load_child (i);
					child->search_from_to (out, key_from, key_to);
					write_value (out, values[i]);
					out << std::endl;
					delete child;
				}
				else {
					write_value (out, values[i]);
					out << std::endl;
				}
			}
			else if (less (keys[i], key_from)) {
				continue;
			}
			else { // случай равенства
				write_value (out, values[i]);
				out << std::endl;
			}	
		}
		if (childs_tag[size]) {
			bnode * child = load_child (size);
			child->search_from_to (out, key_from, key_to);
			delete child;
		}
	}
	else {
		if (less (key_to, key_from)) {
			return;
		}
		for (int i = 0; i < size; ++i) {
			if (less (key_from, keys[i])) { // Если key_from < ключа, то мы в любом случае смотрим левого ребенка, даже если > key_to
				if (childs_tag[i]) {
					bnode * child = load_child (i);
					child->search_from_to (out, key_from, key_to);
					delete child;
				}
				if (less (key_to, keys[i])) { // Если ключ > key_to, то дальше идти смысла нет.
					return;
				}
				write_value (out, values[i]);
				out << std::endl;
			}
			else if (less (keys[i], key_from)) { // Если key_from > ключа, идем дальше.
				continue;
			}
			else { // Если key_from == ключу, смысла смотреть ребенка нет
				write_value (out, values[i]);
				out << std::endl;
			}
		}
		if (childs_tag[size]) {
			if (less (keys[size - 1], key_to)) {
				bnode * child = load_child (size);
				child->search_from_to (out, key_from, key_to);
				delete child;
			}
		}
	}
}

template <class K, class V>
bool bnode<K, V>::is_leaf () const
{
	return (childs_tag[0] == 0)? true : false;
}

/* ----------------------------------------------------------------------------------------*
 * Формат хранения нода в файле:
 * - Три числа через пробел: размер (кол-во ключей), является ли листом (1 - да, 0 - нет), тег родителя.
 * - Далее идет size строк такого формата: ключ, значение.
 * - Далее, если не лист, идет size + 1 строк с тегами детей.
 * ----------------------------------------------------------------------------------------*/

template <class K, class V>
bnode<K, V> * bnode<K, V>::load (std::string directory, int tag)
{
	char strtag[10];
	_itoa_s(tag, strtag, 10);
	std::string filename = directory + "\\" + directory + strtag + ".txt";
	std::ifstream in (filename.data (), std::ifstream::binary);
	int nsize = 0;
	int nleaf = 1;
	int nparent_tag = 0;
	in >> nsize;
	in >> nleaf;
	in >> nparent_tag;

	bnode * new_bnode = new bnode (directory, tag, nparent_tag);
	new_bnode->size = nsize;
	new_bnode->parent_tag = nparent_tag;

	for (int i = 0; i < nsize; ++i) {
		new_bnode->keys[i] = read_key (in);
		new_bnode->values[i] = read_value (in);
	}
	if (nleaf == 0) {
		for (int i = 0; i < nsize + 1; ++i) {
			in >> new_bnode->childs_tag[i];
		}
	}
	in.close ();
	return new_bnode;
}

template <class K, class V>
bnode<K, V> * bnode<K, V>::load_child (int pos)
{
	return load (directory_name, childs_tag[pos]);
}

template <class K, class V>
bnode<K, V> * bnode<K, V>::load_parent ()
{
	return load (directory_name, parent_tag);
}

template <class K, class V>
void bnode<K, V>::load_myself ()
{
	bnode * my = load (directory_name, my_tag);
	int old_size = size;
	size = my->size;

	for (int i = 0; i < size; ++i) {
		keys[i] = my->keys[i];
		values[i] = my->values[i];
	}
	for (int i = size; i < old_size; ++i) {
		keys[i] = no_key ();
		values[i] = no_value ();
	}
	if (!my->is_leaf ()) {
		for (int i = 0; i < size + 1; ++i) {
			childs_tag[i] = my->childs_tag[i];
		}
		for (int i = size + 1; i < old_size + 1; ++i) {
			childs_tag[i] = NULL;
		}
	}
	parent_tag = my->parent_tag;
	delete my;
}

/* ----------------------------------------------------------------------------------------*
 * Формат хранения нода в файле:
 * - Три числа через пробел: размер (кол-во ключей), является ли листом (1 - да, 0 - нет), тег родителя.
 * - Далее идет size строк такого формата: ключ, значение (через пробел).
 * - Далее, если не лист, идет size + 1 строк с тегами детей.
 * ----------------------------------------------------------------------------------------*/

template <class K, class V>
void bnode<K, V>::save_to (std::string directory)
{
	char strtag[10];
	_itoa_s(my_tag, strtag, 10);
	std::string filename = directory + "\\" + directory + strtag + ".txt";
	std::ofstream out (filename.data (), std::ofstream::binary);
	out << size;
	out << ' ';
	//out << (is_leaf ())? 1 : 0;
	if (is_leaf ()) {
		out << 1;
	}
	else {
		out << 0;
	}
	out << ' ';
	out << parent_tag;
	out << std::endl;
	
	for (int i = 0; i < size; ++i) {
		write_key (out, keys[i]);
		out << " ";
		write_value (out, values[i]);
		out << std::endl;
	}

	if (!is_leaf ()) {
		for (int i = 0; i < size + 1; ++i) {
			out << childs_tag[i] << std::endl;
		}
	}
	out.close ();
}

template <class K, class V>
bool bnode<K, V>::has_parent () const
{
	return (parent_tag == 0)? false : true;
}


