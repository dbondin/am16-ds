#include <iostream>
#include <fstream>
#include <string>

#include "stack.h"

using namespace std;

class cat {
public:
	int id;
	string name;
	int age;
	string breed;
	string food;
};

class massif {
public:
	cat* ptr;
	int size;
};

int getMinrun(int size)
{
	int r = 0;
	while (size >= 64) {
		r |= size & 1;
		size >>= 1;
	}
	return size + r;
}

void insertionSort(cat* cats, int size, bool anyless(cat& cat1, cat& cat2))
{
	cat tmp; 
	for (int i = 0; i < size; ++i) {
		for (int j = i; j > 0; --j) {
			if (anyless(cats[i], cats[i - 1])) 
			{
				tmp = cats[i - 1];
				cats[i - 1] = cats[i];
				cats[i] = tmp;
			}
		}
}
}

void merge(cat* cats1, cat* cats2, int size1, int size2, bool anyless(cat& cat1, cat& cat2))
{
	cat *n_cats = new cat[size1+size2]; 
	int i1 = 0;
	int i2 = 0;
	for (int i = 0; i < size1 + size2; ++i) 
	{
		if ((i1 < size1) && (i2 < size2)) 
		{
			if (anyless(cats2[i2], cats1[i1])) 
			{
				n_cats[i] = cats2[i2++];
			}
			else 
			{
				n_cats[i] = cats1[i1++];
			}
		}
		else 
		{
			if (i1 < size1) 
			{
				n_cats[i] = cats1[i1++];
			}
			else 
			{
				if (i2 < size2) 
				{
					n_cats[i] = cats2[i2++];
				}
			}
		}
	}
	for (int i = 0; i < size1; ++i) 
	{
		cats1[i] = n_cats[i];
	}
	for (int i = 0; i < size2; ++i) 
	{
		cats2[i + size1] = n_cats[i];
	}
}

void needMerge(stack<massif> stack, bool anyless(cat& cat1, cat& cat2))
{
	if (stack.size() < 3) 
	{
		return;
	}
	massif m1 = stack.pop();
	massif m2 = stack.pop();
	massif m3 = stack.pop();
	if ((m1.size > m2.size + m3.size) && (m2.size > m3.size)) 
	{
		stack.push(m3);
		stack.push(m2);
		stack.push(m1);
		return;
	}
	if (m1.size <= m2.size) 
	{
		merge (m2.ptr, m1.ptr, m2.size, m1.size, anyless);
		m2.size += m1.size;
		stack.push(m3);
		stack.push(m2);
		needMerge(stack, anyless);
	}
	else 
	{
		merge (m3.ptr, m2.ptr, m3.size, m2.size, anyless);
		m3.size += m2.size;
		stack.push(m3);
		stack.push(m1);
		needMerge(stack, anyless);
	}
}

void timSort(cat* cats, int size, bool anyless(cat& cat1, cat& cat2))
{
	if (size < 64) 
	{
		insertionSort(cats, size, anyless);
		return;
	}
	int minrun = getMinrun(size);
	
	stack<massif> stack;
	int i = 0;
	while (i < size) 
	{
		if (size - i >= minrun) 
		{
			massif tmp = {&cats[i], 1};
			while ((i + tmp.size < size) && !anyless(cats[i + tmp.size], cats[i + tmp.size - 1]))
			{
				++tmp.size;
			}
			if (tmp.size < 2) 
			{
				while ((i + tmp.size < size) && !anyless(cats[i + tmp.size], cats[i + tmp.size - 1])) 
				{ 
					++tmp.size;
				}
				for (int j = 0; j < tmp.size/2; ++j) 
				{
					cat c = tmp.ptr[j];
					tmp.ptr[j] = tmp.ptr[tmp.size - j - 1];
					tmp.ptr[tmp.size - j - 1] = c;
				}
			}
			if (tmp.size < minrun) 
			{
				tmp.size = minrun;
			}
			insertionSort(tmp.ptr, tmp.size, anyless);
			stack.push(tmp);
			needMerge(stack, anyless);
			i += tmp.size;
		}
		else 
		{
			massif tmp = {&cats[i], size - i};
			insertionSort(tmp.ptr, tmp.size, anyless);
			stack.push(tmp);
			needMerge(stack, anyless);
			i += tmp.size;
		}
	}

	while (stack.size() > 1) 
	{
		massif m1 = stack.pop();
		massif m2 = stack.pop();
		merge (m2.ptr, m1.ptr, m2.size, m1.size, anyless);
		m2.size += m1.size;
		stack.push(m2);
	}

	if (stack.pop ().size != size) 
	{
		throw runtime_error ("Ошибка");
	}
}

//Сравнения:

bool ageless(cat& cat1, cat& cat2)
{
	return (cat1.age < cat2.age)? true : false;
}

bool nameless(cat& cat1, cat& cat2)
{
	return (cat1.name.compare(cat2.name) < 0)? true : false;
}

bool breedless (cat& cat1, cat& cat2)
{
	return (cat1.breed.compare(cat2.breed) < 0)? true : false;
}

bool foodless (cat& cat1, cat& cat2)
{
	return (cat1.food.compare(cat2.food) < 0)? true : false;
}



void dataOutput(ofstream& out, cat* cats, int size)
{
	for (int i = 0; i < size; ++i) 
	{
		out << cats[i].id << " " << cats[i].name.data() << " " << cats[i].age << " " << cats[i].breed.data() << " " << cats[i].food.data() << endl;
	}
}

int main()
{
	ifstream in ("cats.txt", ifstream::binary);
	stack<cat> cats;

	int number = 0;

	while (1) {
		string string_id = "";
		int id = 0;
		string name = "";
		string string_age;
		int age = 0;
		string breed = "";
		string food = "";

		getline(in, string_id, ' ');
		getline(in, name, ' ');	
		getline(in, string_age, ' ');
		getline(in, breed, ' ');
		getline(in, food, '\n');

		for (unsigned int i = 0; i < string_id.length(); i++) {
			if (('0' > string_id[i]) || ('9' < string_id[i]))
			{
				throw runtime_error ("Неправильный ввод");
			}
			id = id * 10 + string_id[i] - '0';
		}

		for (unsigned int i = 0; i < string_age.length(); i++) {
			if (('0' > string_age[i]) || ('9' < string_age[i]))
			{
				throw runtime_error ("Неправильный ввод");
			}
			age = age * 10 + string_age[i] - '0';
		}

		cat* n_cat = new cat;
		n_cat->id = id;
		n_cat->name = name;
		n_cat->age = age;
		n_cat->breed = breed;
		n_cat->food = food;

		cats << *n_cat;
		++number;

		char c;
		if (!in.get(c))
		{
			break;
		}		
		else 
		{
			in.putback(c);
		}
	}

	in.close();

	ofstream out("name.txt", ofstream::binary);
	timSort(cats.s_data, cats.size(), nameless);

	dataOutput(out, cats.s_data, cats.size());
	out.close();

	out.open("age.txt", ofstream::binary);
	timSort(cats.s_data, cats.size(), ageless);

	dataOutput(out, cats.s_data, cats.size());
	out.close();

	out.open("breed.txt", ofstream::binary);
	timSort(cats.s_data, cats.size(), breedless);

	dataOutput(out, cats.s_data, cats.size());
	out.close();

	out.open("food.txt", ofstream::binary);
	timSort(cats.s_data, cats.size(), foodless);

	dataOutput(out, cats.s_data, cats.size());
	out.close();

	return 0;
}
