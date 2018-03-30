#include "bin_tree.h"


Node::Node (int new_weight, char new_letter, Node * set_lchild, Node * set_rchild)
{
	weight = new_weight;
	letter = new_letter;
	lchild = set_lchild;
	rchild = set_rchild;
}

Node::~Node ()
{
	if (lchild) {
		delete lchild;
	}
	if (rchild) {
		delete rchild;
	}
}

Node * Node::merge_as_left_subtree_with (Node * right_subtree) {
	Node *new_root = new Node (weight + right_subtree->weight, 0, this, right_subtree);
	return new_root;
}

int Node::is_leaf ()
{
	return (rchild || lchild) ? 0 : 1;
}

int Node::get_weight ()
{
	return weight;
}

char Node::get_letter ()
{
	return letter;
}

Node * Node::get_lchild ()
{
	return lchild;
}

Node * Node::get_rchild ()
{
	return rchild;
}