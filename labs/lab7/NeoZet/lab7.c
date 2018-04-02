#include "timsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fd = fopen("Cats.txt", "r");

	int numberOfCats;
	fscanf(fd, "%d", &numberOfCats);
	Cat *cats = (Cat*)malloc(numberOfCats*sizeof(Cat));
	char line[256];
	int i = 0;
	fgetc(fd);
	while(!feof(fd))
	{
		fgets(line, 255, fd);
		cats[i].id = atoi(strtok(line, " "));
		strcpy(cats[i].name, strtok(NULL, " "));
		cats[i].age = atoi(strtok(NULL, " "));
		strcpy(cats[i].breed, strtok(NULL, " "));
		strcpy(cats[i].food, strtok(NULL, " \n"));
		i++;
	}
	fclose(fd);
	
	FILE *ids = fopen("byId", "w");
	FILE *names = fopen("byName", "w");
	FILE *ages = fopen("byAge", "w");
	FILE *breeds = fopen("byBreed", "w");
	FILE *foods = fopen("byFood", "w");

	timsort(cats, numberOfCats, ID);
	print_cats(ids,cats, numberOfCats);
	
	timsort(cats, numberOfCats, NAME);
	print_cats(names ,cats, numberOfCats);

	timsort(cats, numberOfCats, AGE);
	print_cats(ages ,cats, numberOfCats);

	timsort(cats, numberOfCats, BREED);
	print_cats(breeds, cats, numberOfCats);

	timsort(cats, numberOfCats, FOOD);
	print_cats(foods, cats, numberOfCats);

	fclose(ids);
	fclose(names);
	fclose(ages);
	fclose(breeds);
	fclose(foods);
}