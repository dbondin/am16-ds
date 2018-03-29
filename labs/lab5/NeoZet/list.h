#pragma once

typedef struct node {
	int key;
	char* value;
	struct node *next;
} Node;

Node* initList(int key, char* value);
void addNode(Node** head, int key, char* value);
Node* findNode(Node* head, int key);
void delNode(Node** head, int key);
