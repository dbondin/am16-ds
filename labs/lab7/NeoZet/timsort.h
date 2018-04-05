#pragma once
#include <stdio.h>

typedef enum sort_for {ID, NAME, AGE, BREED, FOOD} Field;

typedef struct cat {
	int id;
	char name[64];
	int age;
	char breed[128];
	char food[32];
} Cat;


int compare_cat (Cat f_cat, Cat s_cat, Field field);
void print_cats(FILE *fd, Cat *cats, int count);

int getMinrun(int sizeArray);
void sort_insert(Cat *cats, int start, int end, Field field);
void merge(Cat *cats, int f_start, int f_end, int s_start, int s_end, Field field);
void timsort(Cat *cats, int size, Field field);