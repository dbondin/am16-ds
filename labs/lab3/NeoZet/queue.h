#pragma once

#define QUEUE_UNDERFLOW 1
#define QUEUE_OVERFLOW 2

typedef struct element {
	char value;
	struct element *next;
} Element;

typedef struct queue {
	int size;
	Element *head;
	Element *tail;
} Queue;

void enqueue(Queue *queue, char value);
char dequeue(Queue *queue);