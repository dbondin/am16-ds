#pragma once

int isOperator(char symbol);

int priorityOfOperation(char operation);

int isDigit(char symbol);

Queue* toPostfix(char* infix);

int calculate(Queue* postfix);