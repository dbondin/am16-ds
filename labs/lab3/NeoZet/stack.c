#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void push(Stack **head, char value)
{
	Stack *tmp = malloc(sizeof(Stack));
	if (tmp == NULL) 
	{
		exit(STACK_OVERFLOW);
	}
	tmp->value = value;
	tmp->next = *head;
	*head = tmp;
}	

char pop(Stack **head)
{
	if(*head == NULL)
	{
		return STACK_UNDERFLOW;
	}	
	Stack *tmp = malloc(sizeof(Stack));
	tmp = *head;
	*head = (*head)->next;
	char value = tmp->value;
	free(tmp);
	return value;	
}


void i_push(IntStack **head, int value)
{
	IntStack *tmp = malloc(sizeof(IntStack));
	if (tmp == NULL) 
	{
		exit(STACK_OVERFLOW);
	}
	tmp->value = value;
	tmp->next = *head;
	*head = tmp;
}	

int i_pop(IntStack **head)
{
	if(*head == NULL)
	{
		return STACK_UNDERFLOW;
	}	
	IntStack *tmp = malloc(sizeof(IntStack));
	tmp = *head;
	*head = (*head)->next;
	int value = tmp->value;
	free(tmp);
	return value;
	
}