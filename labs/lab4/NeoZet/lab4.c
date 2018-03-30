#include <stdlib.h>
#include "huff.h"

int main(int argc, char **argv)
{
	if(argc != 4) 
	{
		printf("Incorrect command!\n");
		printf("Key: ./lab4 [inputFile] [-c|-d] [outputFile] \n-c compress\n-d decompress\n");
		return ERROR;
	}

	FILE *fin;
	FILE *fout;

	if(!(fin = fopen(argv[1], "rb")))
	{
		printf("Couldn't open file %s\n", argv[1]);
		return ERROR;
	}

	if(!(fout = fopen(argv[3], "wb")))
	{
		printf("Couldn't open file %s\n", argv[3]);
		return ERROR;
	}

	Count cnt;
	switch(argv[2][1])
	{
		case 'c':
		{
			if(compress(&cnt, fin, fout) == ERROR)
			{
				printf("Compress error\n");
				return ERROR;
			}
			break;
		}

		case 'd':
		{
			if(decompress(&cnt, fin, fout) == UNKNOWN_FORMAT)
			{
				printf("Unknown file format\n");
				return UNKNOWN_FORMAT;
			}
			break;
		}
	}

	return CORRECT;
}



