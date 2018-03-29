#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORRECT 0
#define ERROR -1
#define UNKNOWN_FORMAT 1
#define COUNT_OF_SYMBOLS 257
#define ESC (COUNT_OF_SYMBOLS-1)
#define NOT_SYMBOL COUNT_OF_SYMBOLS

#define GET_BIT(item, pos) (item >> (7 - pos)) & 1
#define SET_BIT(item, bit, pos) item &= ~(1 << (7 - pos)); item |= (bit << (7 - pos))


typedef struct count_of_code_symbols{
	unsigned long countOfUncode;
	unsigned long countOfEncode;
} Count;

typedef struct tree_node {
	struct tree_node *left;
	struct tree_node *right;
	struct tree_node *parent;
	unsigned long weight;
	unsigned int symbol;
	unsigned int number;
} TreeNode;

typedef struct buffer {
	unsigned char buff;
	unsigned int pos;
	unsigned long counter;
	FILE* output;
} Buffer;

int compress(Count *cnt, FILE *input, FILE *output);
int decompress(Count *cnt, FILE *input, FILE *output);

