#include <iostream>
#include <fstream>
#include <string>
#include "sdl7.h"
using namespace std;
class Cat 
{
	public:
	int id;
	string name;
	int age;

	string breed;
	string food;
};

class Data 
{
	public:
	Cat * ptr;
	int size;
};

int minsize (int size);
void replace (Cat * Cats, int size, bool little (Cat & Cat1, Cat & Cat2));
void change (Cat * Cats1, Cat * Cats2, int size1, int size2, bool little (Cat & Cat1, Cat & Cat2));
void sort (Cat * Cats, int size, bool little (Cat & Cat1, Cat & Cat2));
void ismerge (stackcat<Data> stack, bool little (Cat & Cat1, Cat & Cat2));
void print (ofstream & out, Cat * Cats, int size);

void replace (Cat * Cats, int size, bool little (Cat & Cat1, Cat & Cat2))
{
	for (int i = 0; i < size; ++i) 
	{
		for (int j = i; j > 0; --j) 
		{
			if (little (Cats[i], Cats[i - 1])) 
			{
				Cat var = Cats[i - 1];
				Cats[i - 1] = Cats[i];
				Cats[i] = var;
			}
		}
	}
}

int minsize (int size)
{
	int c = 0; 
	while (size >= 64) 
	{
		c |= size & 1;
		size >>= 1;
	}
	return size + c;
}

void change (Cat * Cats1, Cat * Cats2, const int size1, const int size2, bool little (Cat & Cat1, Cat & Cat2))
{
	int size = (size1 < size2)? size1 : size2;
	Cat *newCats = new Cat[size1 + size2];
	int i1 = 0;
	int i2 = 0;
	for (int i = 0; i < size1 + size2; ++i) 
	{
		if ((i1 < size1) && (i2 < size2)) 
		{
			if (little (Cats2[i2], Cats1[i1])) 
			{
				newCats[i] = Cats2[i2++];
			}
			else 
			{
				newCats[i] = Cats1[i1++];
			}
		}
		else 
		{
			if (i1 < size1) 
			{
				newCats[i] = Cats1[i1++];
			}
			else if (i2 < size2) 
			{
				newCats[i] = Cats2[i2++];
			}
		}
	}

	for (int i = 0; i < size1; ++i) 
	{
		Cats1[i] = newCats[i];
	}
	for (int i = 0; i < size2; ++i) 
	{
		Cats2[i + size1] = newCats[i];
	}
}

void sort (Cat * Cats, int size, bool little (Cat & Cat1, Cat & Cat2))
{
	if (size < 64) 
	{
		replace (Cats, size, little);
		return;
	}
	int mins = minsize (size);


	stackcat<Data> stack;
	int i = 0;
	while (i < size) 
	{
		if (size - i >= mins) 
		{
			Data var = {&Cats[i], 1};
			while ((i + var.size < size) && !little (Cats[i + var.size], Cats[i + var.size - 1])) 
			{ 
				++var.size;
			}
			if (var.size < 2) 
			{
				while ((i + var.size < size) && !little (Cats[i + var.size - 1], Cats[i + var.size])) 
				{
					++var.size;
				}
				for (int j = 0; j < var.size/2; ++j) 
				{
					Cat k = var.ptr[j];
					var.ptr[j] = var.ptr[var.size - j - 1];
					var.ptr[var.size - j - 1] = k;
				}
			}
			if (var.size < mins) 
			{
				var.size = mins;
			}
			replace (var.ptr, var.size, little);

			stack.push (var);
			ismerge (stack, little);
			i += var.size;
		}
		else 
		{
			Data var = {&Cats[i], size - i};
			replace (var.ptr, var.size, little);

			stack.push (var);
			ismerge (stack, little);
			i += var.size;
		}
	}

	while (stack.size () > 1) 
	{
		Data n1 = stack.pop ();
		Data n2 = stack.pop ();
		change (n1.ptr, n2.ptr, n1.size, n2.size, little);
		n1.size += n2.size;
		stack.push (n1);
	}
}

void ismerge (stackcat<Data> stack, bool little (Cat & Cat1, Cat & Cat2))
{
	if (stack.size () < 3) 
	{
		return;
	}
	Data n1 = stack.pop ();
	Data n2 = stack.pop ();
	Data n3 = stack.pop ();
	if ((n1.size > n2.size + n3.size) && (n2.size > n3.size)) 
	{
		stack.push (n3);
		stack.push (n2);
		stack.push (n1);
		return;
	}
	if (n1.size <= n3.size) 
	{
		change (n1.ptr, n2.ptr, n1.size, n2.size, little);
		n1.size += n2.size;
		stack.push (n3);
		stack.push (n1);
		ismerge (stack, little);
	}
	else 
	{
		change (n3.ptr, n2.ptr, n3.size, n2.size, little);
		n3.size += n2.size;
		stack.push (n3);
		stack.push (n2);
		ismerge (stack, little);
	}
}

bool agelittle (Cat & Cat1, Cat & Cat2)
{
	return (Cat1.age < Cat2.age)? true : false;
}

bool namelittle (Cat & Cat1, Cat & Cat2)
{
	return (Cat1.name.compare (Cat2.name) < 0)? true : false;
}

bool breedlittle (Cat & Cat1, Cat & Cat2)
{
	return (Cat1.breed.compare (Cat2.breed) < 0)? true : false;
}

bool foodlittle (Cat & Cat1, Cat & Cat2)
{
	return (Cat1.food.compare (Cat2.food) < 0)? true : false;
}

void print (std::ofstream & out, Cat * Cats, int size)
{
	for (int i = 0; i < size; ++i) {
		out	<< Cats[i].id << " " 
			<< Cats[i].name.data () << " " 
			<< Cats[i].age << " " 
			<< Cats[i].breed.data () << " " 
			<< Cats[i].food.data () << "\n";
	}
}

int main ()
{

	ifstream in ("cats.txt", ifstream::binary);
	stackcat<Cat> Cats;

	int Catnum = 0;

	while (1) {

		string strid = "";
		int id = 0;
		string name = "";
		string strage = "";
		int age = 0;
		string breed = "";
		string food = "";

		getline (in, strid, ' ');
		getline (in, name, ' ');	
		getline (in, strage, ' ');
		getline (in, breed, ' ');
		getline (in, food, '\n');

		Cat * newCat = new Cat;
		newCat->age = age;
		newCat->breed = breed;
		newCat->name = name;
		newCat->food = food;
		newCat->id = id;

		Cats << *newCat;
		++Catnum;
		char c;
		if (!in.get(c))
			break;
		else 
			in.putback(c);
	}

	in.close ();

	ofstream out ("name.txt", ofstream::binary);
	sort (Cats.st, Cats.size (), namelittle);

	print (out, Cats.st, Cats.size ());
	out.close ();

	out.open ("age.txt", ofstream::binary);
	sort (Cats.st, Cats.size (), agelittle);
	print (out, Cats.st, Cats.size ());
	out.close ();

	out.open ("breed.txt", ofstream::binary);
	sort (Cats.st, Cats.size (), breedlittle);
	print (out, Cats.st, Cats.size ());
	out.close ();

	out.open ("food.txt", ofstream::binary);
	sort (Cats.st, Cats.size (), foodlittle);
	print (out, Cats.st, Cats.size ());
	out.close ();

	return 0;
}
