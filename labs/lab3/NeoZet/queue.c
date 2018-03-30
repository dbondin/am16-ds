#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void enqueue(Queue *queue, char value)
{
	Element *tmp = (Element*)malloc(sizeof(Element));
	if(tmp == NULL) 
	{
		exit(QUEUE_OVERFLOW);
	}

	if(queue->head == NULL)
	{ 
		queue->head = (Element*)malloc(sizeof(Element));
		queue->tail = (Element*)malloc(sizeof(Element));	
		queue->head->value = value;
		queue->head->next = queue->tail;
		queue->tail = queue->head;
		queue->size++;
	}
	else {
		tmp->value = value;
		queue->tail->next = tmp;
		queue->tail = tmp;
		queue->size++;
	}
}

char dequeue(Queue *queue)
{
	if(queue->head == NULL)
	{
		return QUEUE_UNDERFLOW;
	}
	char value = queue->head->value;
	Element *tmp = (Element*)malloc(sizeof(Element));
	tmp = queue->head;
	queue->head = queue->head->next;
	free(tmp);
	queue->size--;
	return value;
}



