#include "rb_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_nil(rbNode *node)
{
	if(node == NULL)
	{
		node = (rbNode*)malloc(sizeof(rbNode));
	}

	node->color = BLACK;
	node->value = NULL; 
	node->key = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
}

int isNil(rbNode* node)
{
	if(node->color == BLACK && node->left == NULL && node->right == NULL) return 1;
	else return 0;
}

rbNode* find_root(rbNode* node)
{
	while(node->parent != NULL)
	{
		node = node->parent;
	}
	if(node->color != BLACK) node->color = BLACK;
	return node;
}

rbNode* init_rb_tree(char *key, char *value)
{
	rbNode* root = (rbNode*)malloc(sizeof(rbNode));
	root->color = BLACK;
	root->value = value;
	root->key = key;
	root->left = (rbNode*)malloc(sizeof(rbNode));
	root->right = (rbNode*)malloc(sizeof(rbNode));
	root->parent = NULL;
	set_nil(root->left);
	root->left->parent = root;
	set_nil(root->right);
	root->right->parent = root;
	return root;
}


rbNode* grandfather(rbNode* node)
{
	if(node == NULL || node->parent == NULL) return NULL;
	else return node->parent->parent;
}

rbNode* uncle(rbNode* node)
{
	rbNode *grFather = grandfather(node);
	if(grFather == NULL) return NULL;
	
	if(grFather->left == node->parent) return grFather->right;
	else return grFather->left;
} 

void rotate_left(rbNode* node)
{
	rbNode* tmp = node->right;
	tmp->parent = node->parent;
	if(tmp->parent != NULL)
	{
		if(tmp->parent->left == node)
		{
			tmp->parent->left = tmp;
		}
		else {
			tmp->parent->right = tmp;
		}
	}

	node->right = tmp->left;
	if(tmp->left != NULL)
	{ 
		tmp->left->parent = node;
	}
	tmp->left = node;
	node->parent = tmp;
}


void rotate_right(rbNode* node)
{
	rbNode* tmp = node->left;
	tmp->parent = node->parent;
	if(node->parent != NULL)
	{
		if(node->parent->left == node)
		{
			node->parent->left = tmp;
		}
		else {
			node->parent->right = tmp;
		}
	}

	node->left = tmp->right;
	if(tmp->right != NULL)
	{
		tmp->right->parent = node;
	}
	tmp->right = node;
	node->parent = tmp;
}


rbNode* tree_balansing(rbNode* newNode)
{
	rbNode* uncle_newNode = uncle(newNode);
	rbNode* grandfath_newNode = grandfather(newNode);
	while((newNode->parent->color == RED) && (newNode->parent != NULL) && (newNode->color != BLACK))
	{
		if(newNode->parent == NULL)
		{
			newNode->color = BLACK;
		}	
		else if(newNode->parent->color == BLACK) return NULL;
		else if((uncle_newNode != NULL) && (uncle_newNode->color == RED))
		{
			newNode->parent->color = BLACK;
			uncle_newNode->color = BLACK;
			grandfath_newNode->color = RED;
		}
		else if((newNode->parent->right == newNode) && (newNode->parent == grandfath_newNode->left))
		{
			rotate_left(newNode->parent);
			newNode = newNode->left;
		}
		else if((newNode->parent->left == newNode) && (newNode->parent == grandfath_newNode->right))
		{
			rotate_right(newNode->parent);
			newNode = newNode->right;
		}
		else {
			newNode->parent->color = BLACK;
			grandfath_newNode->color = RED;
			if((newNode->parent->left == newNode) && (newNode->parent == grandfath_newNode->left))
			{
				rotate_right(grandfath_newNode);
			}
			else if((newNode->parent->right == newNode) && (newNode->parent == grandfath_newNode->right)){
				rotate_left(grandfath_newNode);
			}
		}
	}
	return newNode;
}

rbNode* tree_search(rbNode** root, char *key)
{
	rbNode *tmp = (*root);
	int i = 0;
	int keyLen = strlen(key);
	do {
		if(key[i] < (*root)->key[i])
		{
			(*root) = (*root)->left;
		}
		else if(key[i] > (*root)->key[i])
		{
			(*root) = (*root)->right;
		}
		else ++i;

	} while(i < keyLen && !(isNil((*root))));
	
	rbNode *sw = (*root);
	(*root) = tmp;
	return sw;
}

rbNode* tree_insert(rbNode* root, char *key, char* value)
{
	if(root == NULL)
	{ 
		root = init_rb_tree(key, value);
	}
	else {
		rbNode *newNode = (rbNode*)malloc(sizeof(rbNode));
		newNode = tree_search(&root, key);
		newNode->color = RED;
		newNode->value = value;
		newNode->key = key;
		newNode->left = (rbNode*)malloc(sizeof(rbNode));
		newNode->right = (rbNode*)malloc(sizeof(rbNode));
		set_nil(newNode->left);
		newNode->left->parent = newNode;
		set_nil(newNode->right);
		newNode->right->parent = newNode;
		root = find_root(tree_balansing(newNode));
	}
	return root;
}

void find_by_pref(rbNode* sub_root, char* key)
{
	if(strstr(sub_root->value, key))
	{
		printf("%s\n", sub_root->value);
	}
	if(!isNil(sub_root->left))
	{
		find_by_pref(sub_root->left, key);
	}

	if(!isNil(sub_root->right))
	{
		find_by_pref(sub_root->right, key);
	}
}