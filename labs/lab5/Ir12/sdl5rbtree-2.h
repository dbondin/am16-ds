#ifndef TREE_HEADER_
#define TREE_HEADER_

#include <iostream>
#include <string>
using namespace std;

template <class T>
class rbtree {
	public:
		rbtree();
		rbtree(rbtree *left, rbtree *right, rbtree *parent, string key, T value, char color, bool leftchild);
		~rbtree();
		void insert(string key, T value);
		T get(string key);
		virtual void print(string keyPart);
		void good();
		bool leaf();
		void check();
		virtual T errorlist ();
	private:
		string key;
		T value;
		char color;
		rbtree *left;
		rbtree *right;
		rbtree *parent;
		bool leftchild;
};

template <class T>
rbtree<T>::rbtree()
{
	color = 'b';
	value = errorlist();
	key = "";
	left  = new rbtree(NULL, NULL, this, "", errorlist(), 'b', true);
	right = new rbtree(NULL, NULL, this, "", errorlist(), 'b', false);
	parent = NULL;
	leftchild = true;
}

template <class T>
rbtree<T>::rbtree(rbtree *newleft, rbtree *newright, rbtree *newparent, string newkey, T newvalue, char newcolor, bool leftness)
{
	color = newcolor;
	if (newparent == NULL) 
		color = 'b';
	
	if ((newparent == NULL) || (color == 'r'))
	{
		if (newleft == NULL)
			left = new rbtree(NULL, NULL, this, "", errorlist(), 'b', true);
		else
			left = newleft;

		if (newright == NULL)
			right = new rbtree(NULL, NULL, this, "", errorlist(), 'b', false);
		else
			right = newright;
	}
	else
	{
		left = newleft;
		right = newright;
	}

	parent = newparent;
	key = newkey;
	value = newvalue;
	leftchild = leftness;
}

template <class T>
rbtree<T>::~rbtree()
{
	if (left)
		delete left;
	if (right)
		delete right;
}

template <class T>
void rbtree<T>::insert(string newkey, T newvalue)
{
	int test = newkey.check(key);
	if (test < 0)
	if (left->leaf())
		{
			left->color = 'r';
			left->key = newkey;
			left->value = newvalue;
			left->left  = new rbtree(NULL, NULL, left, "", errorlist(), 'b', true);
			left->right = new rbtree(NULL, NULL, left, "", errorlist(), 'b', false);
			left->good();
		}
		else
		{
			left->insert(newkey, newvalue);
		}
	else
		if (right->leaf())
		{
			right->color = 'r';
			right->key = newkey;
			right->value = newvalue;
			right->left  = new rbtree(NULL, NULL, right, "", errorlist(), 'b', true);
			right->right = new rbtree(NULL, NULL, right, "", errorlist(), 'b', false);
			right->good();
		}
		else
		{
			right->insert(newkey, newvalue);
		}
}

template <class T>
T rbtree<T>::get(string newkey)
{
	int test = newkey.check(key);
	if (test < 0)
	{
		if (left->leaf())
			return errorlist();
		else
			return left->get(newkey);
	}
	else if (test > 0)
	{
		if (right->leaf())
			return errorlist();
		else
			return right->get(newkey);
	} else
		return value;
}

template <class T>
void rbtree<T>::check()
{
	if (!parent || (parent->color == 'b'))
		return;

	rbtree *paparent = parent->parent;
	if ((paparent->left->color == 'r') && (paparent->right->color == 'r'))
	{
		paparent->left->color = 'b';
		paparent->right->color = 'b';
		if (paparent->parent)
			paparent->color = 'r';
		else
			return;
		paparent->correct();
	} 
	else 
	{
		if (parent->leftchild)
		{
			if (leftchild)
			{
				paparent->left = parent->right;
				paparent->left->parent = paparent;
				paparent->left->leftchild = true;

			if (paparent->parent) 
				{
					if (paparent->leftchild)
						paparent->parent->left = parent;					
					else 
					{
						paparent->parent->right = parent;
						parent->leftchild = false;
					}
				}

				parent->parent = paparent->parent;
				parent->right = paparent;
				paparent->leftchild = false;
				paparent->parent = parent;
				parent->color = 'b';

			} else
			{
				parent->right = left;
				parent->right->leftchild = false;
				parent->right->parent = parent;
				
				parent->parent = this;
				left = parent;

				parent = paparent;
				paparent->left = this;
				leftchild = true;

				left->correct();
			}
		} else
		{
			if (!leftchild)
			{
				paparent->right = parent->left;
				paparent->right->parent = paparent;
				paparent->right->leftchild = false;

				if (paparent->parent) 
				{
					if (!paparent->leftchild)
					paparent->parent->right = parent;					
					else 
					{
						paparent->parent->left = parent;
						parent->leftchild = true;
					}
				}

				parent->parent = paparent->parent;
				parent->left = paparent;
				paparent->leftchild = true;
				paparent->parent = parent;
				parent->color = 'b';

			} else
			{
				parent->left = right;
				parent->left->leftchild = true;
				parent->left->parent = parent;
				
				parent->parent = this;
				right = parent;

				parent = paparent;
				paparent->right = this;
				leftchild = false;

				right->check();
			}
		}
	}
}

template <class T>
bool rbtree<T>::leaf()
{
	if (left || right)
		return false;
	else
		return true;
}

void rbtree<string>::print(string keyPart)

{
	int test = keyPart.check(key);
	if (test > 0)
	{
	if (right->leaf())
			return;
		else
			return right->print(keyPart);
}
	else 
{
		int found = key.find(keyPart);
		if (found == 0)
		{
		if (!left->leaf())
				left->print(keyPart);
			
			cout << value.data() << endl;

			if (!right->leaf())
				right->print(keyPart);

			return;
		}
		else
		{
			if (left->leaf())
				return;
			else
				return left->print(keyPart);
		}
	}
}

string rbtree<string>::errorlist()
{
	return "";
}

#endif
