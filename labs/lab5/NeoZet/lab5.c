#include "list.h"
#include "hash_map.h"
#include "rb_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *fd = fopen("data.txt", "rb");
	if(!fd) {
		printf("Can't open file\n");
		return 0;
	}
	
	printf("Key: [-n|-p]\n\t-n поиск по номеру(Hash)\n\t-p поиск по начау фамилии(RB-tree)\n");
	if(argc != 2) {
		printf("Input error\n");
		return 0;
	}

	switch(argv[1][1])
	{
		case 'n':
		{
			int numbers[10];
			char names[10][64];	
			int i;
			for(i=0; !feof(fd); ++i)		
			{	
				fscanf(fd, "%d", &numbers[i]);
				fgets(names[i], 64, fd);
			}
			HashTable* h_tab = initHashTable(SIZE);
			for(;i>=0;i--)
			{
				hash_insert(h_tab, numbers[i], names[i]);
			}

			int number;
			printf("Enter number: ");
			scanf("%d", &number);
			printf("Name: %s\n", hash_search(h_tab, number));
			break;
		}

		case 'p':
		{
			char names[10][55];
			char data[10][64];
			int i;
			for(i=0; !feof(fd); ++i)		
			{	
				fscanf(fd, "%s", data[i]);
				fgetc(fd);
				fgets(names[i], 55, fd);
				strcat(data[i], " ");
				strcat(data[i], names[i]);
			}

			int k;
			rbNode* root = init_rb_tree(names[0], data[0]);
			for(k=1; k<i; ++k)
			{
				tree_insert(root, names[k], data[k]);
			}

			char pref[32];
			printf("Enter pref: ");
			fscanf(stdin, "%s", pref);
			find_by_pref(root, pref);
		}
	}

}