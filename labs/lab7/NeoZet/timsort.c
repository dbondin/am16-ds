#include "timsort.h"
#include <string.h>
#include <stdio.h>

/*
	\return 1:  f_cat > s_cat
	\return -1: f_cat < s_cat
	\return 0:  f_cat == s_cat
*/
int compare_cat (Cat f_cat, Cat s_cat, Field field) 
{
	switch(field)
	{
		case ID:
		{
			if(f_cat.id > s_cat.id) return 1;
			else if(f_cat.id < s_cat.id) return -1;
			else return 0;
			break;
		}

		case NAME:
		{
			return strcmp(f_cat.name, s_cat.name);
			break;
		}

		case AGE:
		{
			if(f_cat.age > s_cat.age) return 1;
			else if(f_cat.age < s_cat.age) return -1;
			else return 0;
			break;
		}
		case BREED:
		{
			return strcmp(f_cat.breed, s_cat.breed);
			break;
		}
		case FOOD:
		{
			return strcmp(f_cat.food, s_cat.food);
			break;
		}
	}
}


void print_cats(FILE *fd, Cat *cats, int count)
{
	int i;
	fprintf(fd, "%d\n", count);
	for (i=0; i<count; i++)
	{
		fprintf(fd, "%d ", cats[i].id);
		fputs(cats[i].name, fd);
		fprintf(fd, " %d ", cats[i].age);
		fputs(cats[i].breed, fd);
		fputc(' ', fd);
		fputs(cats[i].food, fd);
		fputc('\n', fd);
	}
}


int getMinrun(int sizeArray)
{
	int tmp = 0;
	while(sizeArray >= 64)
	{
		tmp |= sizeArray & 1;
		sizeArray >>= 1;
	}
	return sizeArray + tmp;
}

void sort_insert(Cat *cats, int start, int end, Field field)
{
	int i;
	for(i=start+1; i<end+1; ++i)
	{
		Cat tmp = cats[i];
		int j = i-1;		
		while(j >= start && (compare_cat(cats[j], tmp, field) > 0))
		{
			cats[j+1] = cats[j]; 
			--j;
		}
		cats[j+1] = tmp;
	}
}


void merge(Cat *cats, int f_start, int f_end, int s_start, int s_end, Field field)
{
	int f_size = f_end - f_start + 1;
	int s_size = s_end - s_start + 1;

	Cat tmp[f_size];

	int f, s;
	for(s=0, f = f_start; f < f_start+f_size; ++s, ++f)
	{
		tmp[s] = cats[f];
	}

	f = f_start;
	s = s_start;
	int k = 0;
	while((k < f_size) && (s < s_start+s_size))
	{
		if(compare_cat(tmp[k], cats[s], field) <= 0)
		{
			cats[f++] = tmp[k++];
		}
		else {
			cats[f++] = cats[s++];	
		}
	}

	while(k < f_size)
	{
		cats[f++] = tmp[k++];
	}

	while(s < s_start+s_size)
	{
		cats[f++] = cats[s++];	
	}
}

void timsort(Cat *cats, int size, Field field)
{
	if(size < 64)
	{
		sort_insert(cats, 0, size-1, field);
		return;
	}	

	int minrun = getMinrun(size);
	int i;
	for(i = 0; i < size; i += minrun)
	{
		sort_insert(cats, i, (i+minrun-1 < size-1 ? i+minrun-1 : size-1), field);
	}

	while(minrun < size)
	{
		for(i = 0; i < size; i += 2*minrun)
		{
			merge(cats, i, i+minrun-1, i+minrun, (i+2*minrun-1 < size-1 ? i+2*minrun-1 : size-1), field);
		}
		minrun = 2*minrun;
	}
}