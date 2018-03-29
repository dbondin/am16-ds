#include <iostream>

class Node {
public:
	Node();
    Node(Node *left,Node *right, Node *parent, int size, char znach);
    ~Node();
    int quan();
    char sym();
    int leaf();
    Node *get_leftchild();
    Node *get_rightchild();
    Node *get_parent();
private:
	Node * tree_parent;
	Node * left_child;
	Node * right_child;
	int num;
	char symbol;
};

Node::Node(){
    right_child=left_child=NULL;
    num=symbol=0;
}

Node::Node ( Node *left, Node *right, Node *parent, int size, char znach)

{
    
	left_child = left;
	right_child = right;
	tree_parent = parent;
	num = size;
	symbol = znach;
}

Node::~Node()
{
	if (right_child) {
		delete right_child;
	}
	if (left_child) {
		delete left_child;
	}
}

Node *merge(Node *get_leftchild, Node *get_rightchild)
{
	return new Node(get_leftchild, get_rightchild, NULL, get_leftchild->quan() + get_rightchild->quan(), 0);
}

int Node::leaf()
{
	return (right_child || left_child) ? 0 : 1;
}

int Node::quan()
{
	return num;
}

char Node::sym()
{
	return symbol;
}

Node * Node::get_leftchild()
{
	return left_child;
}

Node * Node::get_rightchild ()
{
	return right_child;
}

Node * Node::get_parent ()
{
	return tree_parent;
}


