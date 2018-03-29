#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node* initList(int key, char* value)
{
	Node *head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	head->key = key;
	head->value = value;

	return head;
}

void addNode(Node** head, int key, char* value)
{
	Node *tmp = (*head);
	Node *newNode = (Node*)malloc(sizeof(Node));
	while((*head)->next != NULL)
	{
		(*head) = (*head)->next;
	}
	(*head)->next = newNode;
	newNode->next = NULL;
	newNode->key = key;
	newNode->value = value;
	(*head) = tmp;
}

Node* findNode(Node* head, int key)
{
	Node* tmp = head;
	while(tmp)
	{
		if(tmp->key == key) return tmp;
		else tmp = tmp->next;
	}
	if(tmp == NULL) return NULL;	
}

void delNode(Node** head, int key)
{
	
	if((*head)->key == key) 
	{
		if((*head)->next) 
		{
			Node *tmp = (*head);
			free(*head);
			(*head) = (*head)->next;
		}
		else {
			free(*head);
		}
		return;
	}

	Node *tmpHead = (*head);

	while((*head)->next->key != key)
	{
		(*head) = (*head)->next;
		if((*head)->next == NULL) break;
	}

	Node *tmp = (*head)->next;
	(*head)->next = (*head)->next->next;
	free(tmp);
	(*head)->next = tmp->next;
	(*head) = tmpHead;
}
