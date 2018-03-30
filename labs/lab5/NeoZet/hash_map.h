#pragma once

#include "list.h"

#define SIZE 100

typedef struct hash_table {
	Node* masOfList[SIZE];
	int size; 
} HashTable;

HashTable* initHashTable(int size);
int hash(int key);
char* hash_search(HashTable* hash_table, int key);
void hash_insert(HashTable* hash_table, int key, char* value);