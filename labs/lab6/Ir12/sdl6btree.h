#pragma once
#include <fstream>
using namespace std;

template <class K, class V>
class btree 
{
	public:
	btree (string way, int place, int parent);
	btree (K key, V value, string way);
	~btree () {};
	void add (K key, V value);
	V find (K key);
	virtual bool little (K key1, K key2);
	virtual K nokey ();
	virtual V novalue ();
	void findfrom (ofstream & out, K keyfrom, K keyto);
	bool isleaf () const;
	void edittree ();
	btree * loadparent ();
	btree * loadchild (int place);
	btree * load (string way, int label);
	void loadmyself ();
	void save (string way);
	virtual K readkey (ifstream & in);
	virtual V readvalue (ifstream & in);
	virtual void writekey (ofstream & out, K key);
	virtual void writevalue (ofstream & out, V value);
	bool haveparent () const;
	string wayname;
	int mylabel;
private:
	static const int t = 100;
	int size;
	K keys[2 * t - 1];
	V values[2 * t - 1];
	int parentlabel;
	int childslabel[2 * t];
	static int lastlabel;
};

template <class K, class V>
int btree<K, V>::lastlabel = 1;

template <class K, class V>
btree<K, V>::btree (string way, int place, int parent)
{
	size = 0;
	parentlabel = parent;
	for (int i = 0; i < 2 * t - 1; ++i) 
	{
		childslabel[i] = 0;
		keys[i] = nokey ();
		values[i] = novalue ();
	}
	childslabel[2 * t - 1] = 0;
	wayname = way;
	mylabel = place;
}

template <class K, class V>
btree<K, V>::btree (K key, V value, string way)
{
	size = 1;
	parentlabel = 0;
	keys[0] = key;
	values[0] = value;
	childslabel[0] = 0;
	for (int i = 1; i < 2 * t - 1; ++i) 
	{
		childslabel[i] = 0;
		keys[i] = nokey ();
		values[i] = novalue ();
	}
	childslabel[2 * t - 1] = 0;
	wayname = way;
	mylabel = lastlabel;
	++lastlabel;
}

template <class K, class V>
void btree<K, V>::add (K key, V value)
{
	if (isleaf ()) 
	{
		int i = 0;
		for (i = 0; i < size; ++i) 
		{
			if (little (key, keys[i])) 
			{
				for (int j = size; j > i; --j) 
				{
					values[j] = values[j - 1];
					keys[j] = keys[j - 1];
				}
				values[i] = value;
				keys[i] = key;
				break;
			}
		}
		if (i == size) 
		{
			values[i] = value;
			keys[i] = key;
		}
		++size;
		if (size >= 2 * t - 1) 
		{
			edittree ();
		}
		else 
		{
			save (wayname);
		}
	}
	else 
	{
		for (int i = 0; i < size; ++i) 
		{
			if (little (key, keys[i])) 
			{
				btree * child = loadchild (i);
				child->add (key, value);
				child->save (wayname);
				if (child) 
				{
					delete child;
					child = NULL;
				}
				return;
			}
		}
		if (childslabel[0] != 0) 
		{
			btree * child = loadchild (size);
			child->add (key, value);
			child->save (wayname);
			if (child) 
			{
				delete child;
				child = NULL;
			}
		}
		return;
	}
}

template <class K, class V>
void btree<K, V>::edittree ()
{
	btree * newbtree = new btree (wayname, lastlabel, parentlabel);
	++lastlabel;
	for (int i = 0; i < t - 1; ++i) 
	{
		newbtree->keys[i] = keys[t + i];
		keys[t + i] = nokey ();
		newbtree->values[i] = values[t + i];
		values[t + i] = novalue ();
		newbtree->childslabel[i] = childslabel[t + i];
		childslabel[t + i] = 0;
		++newbtree->size;
		--size;
	}
	newbtree->childslabel[t - 1] = childslabel[2 * t - 1];
	childslabel[2 * t - 1] = 0;
	if (parentlabel!= 0) 
	{
		newbtree->save (wayname);	
		btree * parent = loadparent ();
		int psize = parent->size;
		int place = 0;
		for (; place < psize; ++place) 
		{
			if (little (keys[t - 1], parent->keys[place])) 
			{
				break;
			}
		}
		for (int j = psize; j > place; --j) 
		{
			parent->values[j] = parent->values[j - 1];
			parent->keys[j] = parent->keys[j - 1];
			parent->childslabel[j + 1] = parent->childslabel[j];
		}
		parent->values[place] = values[t - 1];
		parent->keys[place] = keys[t - 1];
		parent->childslabel[place + 1] = newbtree->mylabel;
		values[t - 1] = novalue ();
		keys[t - 1] = nokey ();
		--size;
		this->save (wayname);
		++parent->size;
		parent->save (wayname);
		if (parent->size >= 2 * t - 1) 
		{
			parent->edittree ();
		}
		delete parent;
	}
	else 
	{
		btree * parent = new btree (wayname, lastlabel, 0);
		++lastlabel;
		parent->keys[0] = keys[t - 1];
		parent->values[0] = values[t - 1];
		values[t - 1] = novalue ();
		keys[t - 1] = nokey ();
		--size;
		parent->childslabel[0] = mylabel;
		parent->childslabel[1] = newbtree->mylabel;
		++parent->size;
		parentlabel = parent->mylabel;
		newbtree->parentlabel = parent->mylabel;
		newbtree->save (wayname);
		this->save (wayname);
		parent->save (wayname);
		delete parent;
	}
	delete newbtree;
}

template <class K, class V>
V btree<K, V>::find (K key)
{
	for (int i = 0; i < size; ++i) 
	{
		if (little (key, keys[i])) 
		{
			if (childslabel[i]) 
			{
				btree * child = loadchild (i);
				V value = child->find (key);
				delete child;
				return value;
			}
			else 
			{
				return novalue ();
			}
		}
		else if (little (keys[i], key)) 
		{
			continue;
		}
		else 
		{ 
			return values[i];
		}	
	}
	if (childslabel[size]) 
	{
		btree * child = loadchild (size);
		V value = child->find (key);
		delete child;
		return value;
	}
	else 
	{
		return novalue ();
	}
}

template <class K, class V>
void btree<K, V>::findfrom (ofstream & out, K keyfrom, K keyto)
{
	if (!(little (keyto, nokey ()) || little (nokey (), keyto))) 
	{
		for (int i = 0; i < size; ++i) 
		{
			if (little (keyfrom, keys[i])) 
			{ 
				if (childslabel[i]) 
				{
					btree * child = loadchild (i);
					child->findfrom (out, keyfrom, keyto);
					writevalue (out, values[i]);
					out << endl;
					delete child;
				}
				else 
				{
					writevalue (out, values[i]);
					out << endl;
				}
			}
			else if (little (keys[i], keyfrom)) 
			{
				continue;
			}
			else 
			{ 
				writevalue (out, values[i]);
				out << endl;
			}	
		}
		if (childslabel[size]) 
		{
			btree * child = loadchild (size);
			child->findfrom (out, keyfrom, keyto);
			delete child;
		}
	}
	else 
	{
		if (little (keyto, keyfrom)) 
		{
			return;
		}
		for (int i = 0; i < size; ++i) 
		{
			if (little (keyfrom, keys[i])) 
			{ 
				if (childslabel[i]) 
				{
					btree * child = loadchild (i);
					child->findfrom (out, keyfrom, keyto);
					delete child;
				}
				if (little (keyto, keys[i])) 
				{ 
					return;
				}
				writevalue (out, values[i]);
				out << endl;
			}
			else if (little (keys[i], keyfrom)) 
			{ 
				continue;
			}
			else 
			{ 
				writevalue (out, values[i]);
				out << endl;
			}
		}
		if (childslabel[size]) 
		{
			if (little (keys[size - 1], keyto)) 
			{
				btree * child = loadchild (size);
				child->findfrom (out, keyfrom, keyto);
				delete child;
			}
		}
	}
}

template <class K, class V>
bool btree<K, V>::isleaf () const
{
	return (childslabel[0] == 0)? true : false;
}
 
template <class K, class V>
btree<K, V> * btree<K, V>::load (string way, int label)
{
	char strlabel[10];
	poi(label, strlabel, 10);
	string filename = way + "\\" + way + strlabel + ".txt";
	ifstream in (filename.data (), ifstream::binary);
	int nsize = 0;
	int nleaf = 1;
	int nparentlabel = 0;
	in >> nsize;
	in >> nleaf;
	in >> nparentlabel;

	btree * newbtree = new btree (way, label, nparentlabel);
	newbtree->size = nsize;
	newbtree->parentlabel = nparentlabel;

	for (int i = 0; i < nsize; ++i) 
	{
		newbtree->keys[i] = readkey (in);
		newbtree->values[i] = readvalue (in);
	}
	if (nleaf == 0) 
	{
		for (int i = 0; i < nsize + 1; ++i) 
		{
			in >> newbtree->childslabel[i];
		}
	}
	in.close ();
	return newbtree;
}

template <class K, class V>
btree<K, V> * btree<K, V>::loadchild (int place)
{
	return load (wayname, childslabel[place]);
}

template <class K, class V>
btree<K, V> * btree<K, V>::loadparent ()
{
	return load (wayname, parentlabel);
}

template <class K, class V>
void btree<K, V>::loadmyself ()
{
	btree * my = load (wayname, mylabel);
	int oldsize = size;
	size = my->size;

	for (int i = 0; i < size; ++i) 
	{
		keys[i] = my->keys[i];
		values[i] = my->values[i];
	}
	for (int i = size; i < oldsize; ++i) 
	{
		keys[i] = nokey ();
		values[i] = novalue ();
	}
	if (!my->isleaf ()) 
	{
		for (int i = 0; i < size + 1; ++i) 
		{
			childslabel[i] = my->childslabel[i];
		}
		for (int i = size + 1; i < oldsize + 1; ++i) 
		{
			childslabel[i] = NULL;
		}
	}
	parentlabel = my->parentlabel;
	delete my;
}


template <class K, class V>
void btree<K, V>::save (string way)
{
	char strlabel[10];
	poi(mylabel, strlabel, 10);
	string filename = way + "\\" + way + strlabel + ".txt";
	ofstream out (filename.data (), ofstream::binary);
	out << size;
	out << ' ';
	if (isleaf ()) 
	{
		out << 1;
	}
	else 
	{
		out << 0;
	}
	out << ' ';
	out << parentlabel;
	out << endl;
	
	for (int i = 0; i < size; ++i) 
	{
		writekey (out, keys[i]);
		out << " ";
		writevalue (out, values[i]);
		out << endl;
	}

	if (!isleaf ()) 
	{
		for (int i = 0; i < size + 1; ++i) 
		{
			out << childslabel[i] << endl;
		}
	}
	out.close ();
}

template <class K, class V>
bool btree<K, V>::haveparent () const
{
	return (parentlabel == 0)? false : true;
}
