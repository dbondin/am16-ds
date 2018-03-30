#include "queue.h"
#include "stack.h"
#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int isOperator(char symbol)
{
	if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^' || symbol == '(' || symbol == ')')
	{
		return 1;
	}
	else {
		return 0;
	}
}

int priorityOfOperation(char operation)
{
	switch(operation)
	{
		case '(':
		return 1;

		case ')':
		return 1;

		case '+':
		return 2;

		case '-':
		return 2;

		case '*':
		return 3;

		case '/':
		return 4;

		case '^':
		return 5;

		default: return 0;
	}
}

int isDigit(char symbol)
{
	if(symbol >= 48 && symbol <= 57)
	{
		return 1;
	}
	else {
		return 0;
	}
}

Queue* toPostfix(char* infix)
{
	int i;
	int len = 0;
	Queue *lexemes = (Queue*)malloc(sizeof(Queue));
	for(i=0; infix[i] != '\0'; i++)
	{
		if(isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')')
		{
			if(infix[i] == '-' && (isOperator(infix[i-1]) || i == 0) && isDigit(infix[i+1]))
			{
				enqueue(lexemes, '!');
				continue;
			}
			enqueue(lexemes, '|');	
		}
		enqueue(lexemes, infix[i]);
		++len;
	}

	char* p = (char*)malloc(sizeof(char)*len);
	Stack *supStack = NULL;
	Queue* postfix = (Queue*)malloc(sizeof(Queue)*len);

	char lexem;
	int s = lexemes->size;
	
	int rBr = 0; 
	int lBr = 0;

	for(i=0; i<s; ++i)
	{
		lexem = dequeue(lexemes);
		if(lexem == '|')
		{
			enqueue(postfix, lexem);
		}

		else if(lexem == '!')
		{
			enqueue(postfix, '!');
		}

		else if(isDigit(lexem))
		{
			enqueue(postfix, lexem);
		}

		else if(isOperator(lexem))
		{
			char operation;
			if(lexem == '(') 
			{
				push(&supStack, lexem);
				lBr++;
			}
			else if(lexem == ')')
			{
				operation = pop(&supStack);
				while(operation != '(' && operation != 1)
				{
					enqueue(postfix, operation);
					operation = pop(&supStack);
				}
				rBr++;
			}

			else {
				if(supStack != NULL)
				{
					operation = pop(&supStack);				 
					if(priorityOfOperation(operation) >= priorityOfOperation(lexem))
					{
						enqueue(postfix, operation);
					}
					else {
						push(&supStack, operation);
					}
				}
				push(&supStack, lexem);
			}	

		}
	}
	if(lBr != rBr) 
	{
		postfix = NULL;
	}
	else {
		while(supStack != NULL)
		{
			enqueue(postfix, pop(&supStack));
		}
	}

	return postfix;
}	

int calculate(Queue* postfix)
{
	IntStack *store = NULL;
	int a, b;
	int res = 0;
	char sup[16];
	char _a[16] = {0};
	char _b[16] = {0};
	int i = 0;
	char lexem;
	int s = postfix->size;
	int k;
	for(k=0; k<s; k++)
	{
		lexem = dequeue(postfix);

		if(isDigit(lexem) || lexem == '!')
		{
			while(lexem != '|' && !isOperator(lexem))
			{
				if(lexem == '!')
				{
					sup[i] = '-';
				}
				else {
					sup[i] = lexem;
				}
				lexem = dequeue(postfix);
				++i;
			}
			i_push(&store, atoi(sup));
			i=0;
			memset(sup, 0, sizeof(sup));
		}

		if(isOperator(lexem))
		{
			b = i_pop(&store);
			a = i_pop(&store);

			switch(lexem)
			{
				case '+': 
				res = a+b; 
				break;

				case '-': 
				res = a-b; 
				break;

				case '*': 
				res = a*b; 
				break;

				case '/': 
				res = (int)a/b; 
				break;

				case '^': 
				res = (int)pow(a,b); 
				break;				
			}

			i_push(&store, res);
		}
	}
	return i_pop(&store);
}