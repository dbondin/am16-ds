#pragma once

rb::rb(string new_key, string new_data, colors new_color, rb* set_left, rb* set_right, rb* set_parent)
{
	color = new_color;
	key = new_key;
	data = new_data;
	left = set_left;
	right = set_right;
	parent = set_parent;
	if (NULL == parent) {
		color = black;
	}
}

rb::~rb()
{
	if (left) {
		delete left;
		left = NULL;
	}
	if (right) {
		delete right;
		right = NULL;
	}
}

string rb::search(string part, const int equal) 
{
	if (key.compare(part) < 0) {
		if (right) {
			return right->search(part);
		}
		else 
		{
			return "";
		}
	}
	else 
	{
		int found = key.find(part);
		string from_left;
		string from_right;
		if (0 == found) {
			if (1 == equal) {
				if (key.compare(part) == 0) 
				{ 
					return data;
				}
				else 
				{
					return "";
				}
			}
			if (left) {
				from_left = left->search(part);
			}
			if (from_left.size () > 0) {
				from_left += "\n";
			}
			from_left += data;
			if (right) {
				from_right = right->search(part);
			}
			if ((from_right.size () > 0)) {
				from_left += "\n";
			}
			from_left += from_right;
			return from_left;
		}
		else 
		{
			if (left) 
			{
				return left->search (part);
			}
			else 
			{
				return "";
			}
		}
	}
}

void rb::add(string new_key, string new_data)
{
	if (key.compare(new_key) < 0) 
	{
		if (right) 
		{
			right->add(new_key, new_data);
		}
		else 
		{
			rb* new_node = new rb(new_key, new_data, red, NULL, NULL, this);
			right = new_node;
			new_node->optim();
		}
	}
	else 
	{
		if (left) {
			left->add(new_key, new_data);
		}
		else 
		{
			rb* new_node = new rb(new_key, new_data, red, NULL, NULL, this);
			left = new_node;
			new_node->optim();
		}
	}
}

int rb::is_leaf() 
{
	if (left || right)
	{
		return 0;
	}
	else
	{
		return 1;
	}	
}

void rb::optim()
{
	if (parent->color == black) { 
		return;
	}
	rb* grand = parent->parent;
	if (grand->left && grand->right && (grand->left->color == red) && (grand->right->color == red)) 
	{ 
		grand->left->color = black;
		grand->right->color = black;
		if (grand->parent == NULL) 
		{ 
			return;
		}
		grand->color = red;
		grand->optim();
	}
	else 
	{ 
		if (parent->key.compare(grand->key) < 0) { 
			if (key.compare (parent->key) > 0) { 
				parent->right = left;
				if (left) {
					left->parent = parent;
				}
				parent->parent = this;
				left = parent;
				parent = grand;
				grand->left = this;
				left->optim();
			}
			else 
			{
				grand->left = parent->right;
				if (parent->right) {
					parent->right->parent = grand;
				}
				if (grand->parent) {
					if (grand->key.compare(grand->parent->key) > 0) 
					{
						grand->parent->right = parent;
					}
					else {
						grand->parent->left = parent;
					}
				}
				parent->parent = grand->parent;
				parent->right = grand;
				grand->parent = parent;
				parent->color = black;
			}
		}
		else 
		{ 
			if (key.compare (parent->key) > 0) { 
				grand->right = parent->left;
				if (parent->left) {
					parent->left->parent = grand;
				}
				if (grand->parent) {
					if (grand->key.compare (grand->parent->key) > 0) { 
						grand->parent->right = parent;
					}
					else {
						grand->parent->left = parent;
					}
				}
				parent->parent = grand->parent;
				parent->left = grand;
				grand->parent = parent;
				parent->color = black;
			}
			else 
			{ 
				parent->left = right;
				if (right) {
					right->parent = parent;
				}
				parent->parent = this;
				right = parent;
				parent = grand;
				grand->right = this;
				right->optim();
			}
		}
	}
}
