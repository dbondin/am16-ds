#include "huff.h"

void delete_tree(TreeNode *tree)
{
	if(tree == NULL)
		return;

	delete_tree(tree->left);
	delete_tree(tree->right);

	free(tree);
}

int init_tree(TreeNode **tree, TreeNode *symbolMas[])
{
	(*tree) = malloc(sizeof(TreeNode));
	if((*tree) == NULL)
		return 0;

	(*tree)->weight = 0;
	(*tree)->symbol = ESC;
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	(*tree)->parent = NULL;
	(*tree)->number = 0;
	symbolMas[ESC] = (*tree);

	return 1;
}

int add_subtree(TreeNode *symbolMas[], unsigned int symbol)
{
	TreeNode* escape = symbolMas[ESC];
	TreeNode* left = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* right = (TreeNode*)malloc(sizeof(TreeNode));

	if(left == NULL || right == NULL)
	{
		free(left);
		free(right);
		return 0;
	}

	escape->left = left;
	escape->right = right;
	escape->symbol = NOT_SYMBOL;

	left->parent = escape;
	right->parent = escape;
	left->left = NULL;
	left->right = NULL;
	right->left = NULL;
	right->right = NULL;
	left->symbol = ESC;
	left->weight = 0;
	left->number = escape->number + 2;

	right->symbol = symbol;
	right->weight = 0;
	right->number = escape->number + 1;

	symbolMas[ESC] = left;
	symbolMas[symbol] = right;
	symbolMas[COUNT_OF_SYMBOLS + escape->number/2] = escape;

	return 1;
}

void update_tree(TreeNode *symbolMas[], unsigned int c)
{
	TreeNode* updTree = symbolMas[c];

	while(updTree != NULL)
	{
		TreeNode* minNodeNumber = updTree;
		for(int i=0; i < 2*COUNT_OF_SYMBOLS; ++i)
		{
			TreeNode *current = symbolMas[i];
			if(current != NULL && current->weight == updTree->weight && current->number < minNodeNumber->number)
			{
				minNodeNumber = current;
			}
		}
		if(minNodeNumber != updTree && minNodeNumber != updTree->parent)
		{
			TreeNode *tmpParent = updTree->parent;
			unsigned int tmpNumber = updTree->number;

			if(updTree->parent->right == updTree)
			{
				updTree->parent->right = minNodeNumber;
			}
			else {
				updTree->parent->left = minNodeNumber;
			}

			if(minNodeNumber->parent->right == minNodeNumber)
			{
				minNodeNumber->parent->right = updTree;
			}
			else {
				minNodeNumber->parent->left = updTree;
			}

			updTree->parent = minNodeNumber->parent;
			updTree->number = minNodeNumber->number;
			minNodeNumber->parent = tmpParent;
			minNodeNumber->number = tmpNumber;
		}

		updTree->weight++;
		updTree = updTree->parent;
	}
}

void flush_buffer(Buffer *buffer)
{
	fprintf(buffer->output, "%c", buffer->buff);
	buffer->pos = 0;
	buffer->buff = 0;
	buffer->counter++;
}

void encode_symbol(TreeNode *node, Buffer *buffer)
{
	int bit;
	char code[COUNT_OF_SYMBOLS/8 + 1] = {0};
	int code_pos = 0;

	// save code in inverted order
	while(node->parent != NULL)
	{
		bit = (node == node->parent->right);
		SET_BIT(code[code_pos/8], bit, code_pos % 8);
		code_pos++;
		node = node->parent;
	}

	while(code_pos > 0)
	{
		code_pos--;
		bit = GET_BIT(code[code_pos/8], code_pos % 8);
		SET_BIT(buffer->buff, bit, buffer->pos);
		buffer->pos++;

		if(buffer->pos == 8)
			flush_buffer(buffer);
	}
}

void buffSymbol(char c, Buffer *buffer)
{
	int bit;	
	for(int i=0; i<8; ++i)
	{
		bit = GET_BIT(c, i);
		SET_BIT(buffer->buff, bit, buffer->pos);
		buffer->pos++;

		if(buffer->pos == 8)
		{
			flush_buffer(buffer);
		}
	}
}


int compress(Count *cnt, FILE *input, FILE *output)
{
	cnt->countOfEncode = 0;
	cnt->countOfUncode = 0;
	int c;
	Buffer buffCode;

	buffCode.pos = 0;
	buffCode.counter = 0;
	buffCode.buff = 0;
	buffCode.output = output;

	TreeNode* symbolMas[2*COUNT_OF_SYMBOLS] = {NULL};
	TreeNode* tree = NULL;

	if(!init_tree(&tree, symbolMas))
		return ERROR;

	fputs("HF16", output);
	while((c = fgetc(input)) != EOF)
	{
		if(symbolMas[c] == NULL)
		{
			if(cnt->countOfUncode != 0)
			{
				encode_symbol(symbolMas[ESC], &buffCode);
			}

			if(!add_subtree(symbolMas, c))
			{
				delete_tree(tree);
				return ERROR;
			}
			buffSymbol(c, &buffCode);
		}
		else { 
			encode_symbol(symbolMas[c], &buffCode);
		}
		cnt->countOfUncode++;
		update_tree(symbolMas, c);
	}
	encode_symbol(symbolMas[ESC], &buffCode);

	if(buffCode.pos != 0)
	{
		fprintf(output, "%c", buffCode.buff);
		buffCode.counter++;
	}

	delete_tree(tree);
	cnt->countOfEncode = buffCode.counter;

	return CORRECT;
}

int decompress(Count *cnt, FILE *input, FILE *output)
{
	char hf16[5];
	fgets(hf16, 5, input);
	if(strncmp(hf16, "HF16", 4) != 0) return UNKNOWN_FORMAT;

	cnt->countOfEncode = 0;
	cnt->countOfUncode = 0;
	int c;

	Buffer buffChar;

	buffChar.pos = 0;
	buffChar.counter = 0;
	buffChar.buff = 0;
	buffChar.output = output;

	TreeNode* symbolMas[2*COUNT_OF_SYMBOLS] = {NULL};
	TreeNode* tree = NULL;

	if(!init_tree(&tree, symbolMas))
		return ERROR;

	int bit;
	int esc = 1;
	TreeNode* node = tree;

	while((c = fgetc(input)) != EOF)
	{
		for(int i=0; i<8; ++i)
		{
			bit = GET_BIT(c, i);
			if(esc == 1)
			{
				SET_BIT(buffChar.buff, bit, buffChar.pos);
				buffChar.pos++;

				if(buffChar.pos == 8)
				{
					if(!add_subtree(symbolMas, buffChar.buff))
					{
						delete_tree(tree);
						return ERROR;
					}

					update_tree(symbolMas, buffChar.buff);
					flush_buffer(&buffChar);
					esc = 0;
					cnt->countOfUncode++;
				}
				continue;
			}

			node = (bit == 1 ? node->right : node->left);
			if(node == NULL)
			{
				delete_tree(tree);
				return ERROR;
			}
			if(node->symbol == ESC)
			{
				esc = 1;
				node = tree;
			}
			else if(node->symbol < ESC)
			{
				cnt->countOfUncode++;
				fprintf(output, "%c", node->symbol);
				update_tree(symbolMas, node->symbol);
				node = tree;
			}
		}
		cnt->countOfEncode++;
	}
	delete_tree(tree);
	return esc == 1 ? CORRECT : ERROR;
}
