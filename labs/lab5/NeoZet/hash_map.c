#include "hash_map.h"
#include <stdio.h>
#include <stdlib.h>

HashTable* initHashTable(int size)
{
	HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
	hash_table->size = SIZE;
	
	return hash_table;
}

int hash(int key)
{
	return key % SIZE;
}

char* hash_search(HashTable* hash_table, int key)
{
	int hashIndex = hash(key);
	return findNode(hash_table->masOfList[hashIndex], key)->value;
}

void hash_insert(HashTable* hash_table, int key, char* value)
{
	int hashIndex = hash(key);
	if(hash_table->masOfList[hashIndex] == NULL)
	{	
		hash_table->masOfList[hashIndex] = initList(key, value);
	}
	else {
		addNode(&(hash_table->masOfList[hashIndex]), key, value);	
	}
}
