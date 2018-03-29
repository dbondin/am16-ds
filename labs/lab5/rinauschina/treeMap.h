#ifndef TREE_HEADER_
#define TREE_HEADER_

#include <iostream>
#include <string>
using namespace std;

////////////////////////////////RB tree///////////////////////////////

template <class T>
class treeNode {
	public:
		treeNode();
		treeNode(treeNode *left, treeNode *right, treeNode *parent, string key, T value, char color, bool is_left_child);
		~treeNode();
		void add(string key, T value);
		T get(string key);
		virtual void printCoincidental(string keyPart);
		void correct();
		bool isLeaf();
		virtual T badResult ();
	private:
		string key;
		T value;
		char color;
		treeNode *left;
		treeNode *right;
		treeNode *parent;
		bool is_left_child;
};

template <class T>
treeNode<T>::treeNode()
{
	color = 'b';
	value = badResult();
	key = "";
	left  = new treeNode(NULL, NULL, this, "", badResult(), 'b', true);
	right = new treeNode(NULL, NULL, this, "", badResult(), 'b', false);;
	parent = NULL;
	is_left_child = true;
}

template <class T>
treeNode<T>::treeNode(treeNode *_left, treeNode *_right, treeNode *_parent, string _key, T _value, char _color, bool leftness)
{
	color = _color;
	if (_parent == NULL)
		color = 'b';
	
	if ((_parent == NULL) || (color == 'r'))
	{
		if (_left == NULL)
			left = new treeNode(NULL, NULL, this, "", badResult(), 'b', true);
		else
			left = _left;

		if (_right == NULL)
			right = new treeNode(NULL, NULL, this, "", badResult(), 'b', false);
		else
			right = _right;
	}
	else
	{
		left = _left;
		right = _right;
	}

	parent = _parent;
	key = _key;
	value = _value;
	is_left_child = leftness;
}

template <class T>
treeNode<T>::~treeNode()
{
	if (left)
		delete left;
	if (right)
		delete right;
}

template <class T>
void treeNode<T>::add(string _key, T _value)
{
	int comparison = _key.compare(key);
	if (comparison < 0)
		if (left->isLeaf())
		{
			left->color = 'r';
			left->key = _key;
			left->value = _value;
			left->left  = new treeNode(NULL, NULL, left, "", badResult(), 'b', true);
			left->right = new treeNode(NULL, NULL, left, "", badResult(), 'b', false);
			left->correct();
		}
		else
		{
			left->add(_key, _value);
		}
	else
		if (right->isLeaf())
		{
			right->color = 'r';
			right->key = _key;
			right->value = _value;
			right->left  = new treeNode(NULL, NULL, right, "", badResult(), 'b', true);
			right->right = new treeNode(NULL, NULL, right, "", badResult(), 'b', false);
			right->correct();
		}
		else
		{
			right->add(_key, _value);
		}
}

template <class T>
T treeNode<T>::get(string _key)
{
	int comparison = _key.compare(key);
	if (comparison < 0)
	{
		if (left->isLeaf())
			return badResult();
		else
			return left->get(_key);
	}
	else if (comparison > 0)
	{
		if (right->isLeaf())
			return badResult();
		else
			return right->get(_key);
	} else
		return value;
}

template <class T>
void treeNode<T>::correct()
{
	if (!parent || (parent->color == 'b'))
		return;

	treeNode *paparent = parent->parent;
	if ((paparent->left->color == 'r') && (paparent->right->color == 'r'))
	{
		paparent->left->color = 'b';
		paparent->right->color = 'b';
		if (paparent->parent)
			paparent->color = 'r';
		else
			return;
		paparent->correct();
	} else 
	{
		if (parent->is_left_child)
		{
			if (is_left_child)
			{
				paparent->left = parent->right;
				paparent->left->parent = paparent;
				paparent->left->is_left_child = true;

				if (paparent->parent) 
				{
					if (paparent->is_left_child)
						paparent->parent->left = parent;					
					else 
					{
						paparent->parent->right = parent;
						parent->is_left_child = false;
					}
				}

				parent->parent = paparent->parent;
				parent->right = paparent;
				paparent->is_left_child = false;
				paparent->parent = parent;
				parent->color = 'b';

			} else
			{
				parent->right = left;
				parent->right->is_left_child = false;
				parent->right->parent = parent;
				
				parent->parent = this;
				left = parent;

				parent = paparent;
				paparent->left = this;
				is_left_child = true;

				left->correct();
			}
		} else
		{
			if (!is_left_child)
			{
				paparent->right = parent->left;
				paparent->right->parent = paparent;
				paparent->right->is_left_child = false;

				if (paparent->parent) 
				{
					if (!paparent->is_left_child)
						paparent->parent->right = parent;					
					else 
					{
						paparent->parent->left = parent;
						parent->is_left_child = true;
					}
				}

				parent->parent = paparent->parent;
				parent->left = paparent;
				paparent->is_left_child = true;
				paparent->parent = parent;
				parent->color = 'b';

			} else
			{
				parent->left = right;
				parent->left->is_left_child = true;
				parent->left->parent = parent;
				
				parent->parent = this;
				right = parent;

				parent = paparent;
				paparent->right = this;
				is_left_child = false;

				right->correct();
			}
		}
	}
}

template <class T>
bool treeNode<T>::isLeaf()
{
	if (left || right)
		return false;
	else
		return true;
}

void treeNode<string>::printCoincidental(string keyPart)
{
	int comparison = keyPart.compare(key);
	if (comparison > 0)
	{
		if (right->isLeaf())
			return;
		else
			return right->printCoincidental(keyPart);
	}
	else 
	{
		int found = key.find(keyPart);
		if (found == 0)
		{
			if (!left->isLeaf())
				left->printCoincidental(keyPart);
			
			cout << value.data() << endl;

			if (!right->isLeaf())
				right->printCoincidental(keyPart);

			return;
		}
		else
		{
			if (left->isLeaf())
				return;
			else
				return left->printCoincidental(keyPart);
		}
	}
}

string treeNode<string>::badResult()
{
	return "";
}

////////////////////////////////RB tree///////////////////////////////

template <class T>
class treeMap {
	public:
		treeMap();
		~treeMap();
		void add(string key, T value);
		T get(string key);
		virtual void printCoincidental(string keyPart);
		virtual T badResult();
	private:
		treeNode<T> *root;
};

template <class T>
treeMap<T>::treeMap()
{
	root = NULL;
}

template <class T>
treeMap<T>::~treeMap()
{
	delete root;
}

template <class T>
void treeMap<T>::add(string key, T value)
{
	if (!root)
		root = new treeNode<T>(NULL, NULL, NULL, key, value, 'b', true);
	else
		root->add(key, value);
}

template <class T>
T treeMap<T>::get(string key)
{
	if (!root)
		return badResult();
	else
		return root->get(key);
}

void treeMap<string>::printCoincidental(string keyPart)
{
	if (!root)
		return;
	root->printCoincidental(keyPart);
}

string treeMap<string>::badResult()
{
	return "";
}


#endif