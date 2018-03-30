#include "stack.h"
#include "queue.h"
#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char const *argv[])
{
	char inf[256];
	printf("> ");
	fgets(inf, 255, stdin);

	Queue *queue = (Queue*)malloc(sizeof(Queue));
	queue = toPostfix(inf);
	if(queue == NULL) printf("Error! Incorrect input!\n");
	else {
		int s = queue->size;
		printf("\nRESULT: %d\n", calculate(queue));
	}
	free(queue);
}
