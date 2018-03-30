#pragma once

typedef enum color {RED, BLACK} Color;

typedef struct rb_node {
	Color color;
	char *value;
	char *key;
	struct rb_node *left; 
	struct rb_node *right;
	struct rb_node *parent;
} rbNode;


rbNode* init_rb_tree(char *key, char *value);
rbNode* tree_search(rbNode** tree, char *key);
rbNode* tree_insert(rbNode* root, char *key, char *value);
void find_by_pref(rbNode* sub_root, char* key);
int isNil(rbNode* node);