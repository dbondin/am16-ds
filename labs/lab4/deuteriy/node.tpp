#include "node.h"

Node::Node(int n_wt, char n_data, Node* set_left, Node* set_right)
{
	wt = n_wt;
	data = n_data;
	left = set_left;
	right = set_right;
}

Node::~Node()
{
	if (left) 
	{
		delete left;
	}
	if (right) 
	{
		delete right;
	}
}

Node* Node::link(Node* right_t) 
{
	Node *n_root = new Node(wt + right_t->wt, 0, this, right_t);
	return n_root;
}

int Node::check_leaf ()
{
	if (right || left)
	{
		return 0;
	}
	else
	{
		return 1;
	}	
}

int Node::get_wt()
{
	return wt;
}

char Node::get_data()
{
	return data;
}

Node* Node::get_left()
{
	return left;
}

Node* Node::get_right()
{
	return right;
}
