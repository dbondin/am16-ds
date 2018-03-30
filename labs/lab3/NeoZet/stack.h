#pragma once

#define STACK_UNDERFLOW 1
#define STACK_OVERFLOW 2

typedef struct stack {
	char value;
	struct stack *next;
} Stack;

void push(Stack **stack, char value);
char pop(Stack **stack);

typedef struct int_stack {
	char value;
	struct int_stack *next;
} IntStack;

void i_push(IntStack **stack, int value);
int i_pop(IntStack **stack);