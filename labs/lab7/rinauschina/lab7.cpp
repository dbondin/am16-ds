#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"
using namespace std;

struct Cats{
	int id;
	string name;
	int age;
	string breeds;
	string lovefood;
};

struct mas{
	Cats *ptr;
	int size;
};

int getSize(int size);
void INSERT(Cats *cats, int size, bool swap(cat & cat1, cat & cat2));
void MERGE(Cats *cats1, Cats *cats2, int s1, int s2, bool swap(cat & cat1, cat & cat2));
void TIM(Cats * cats, int size, bool swap(cat & cat1, cat & cat2));
void func(stack<mas>stack, bool swap(cat & cat1, cat & cat2));
void PRINTCAT(ofstream & out, Cats * cats, int size);

void INSERT(Cats * cats, int size, bool swap(cat & cat1, cat & cat2))
{
	for (int i = 0; i < size; ++i) 
	{
		for (int j = i; j > 0; --j) 
		{
			if (swap(cats[i], cats[i - 1])) 
			{
				cat temp = cats[i - 1];
				cats[i - 1] = cats[i];
				cats[i] = temp;
			}
		}
	}
}

int getSize(int size)
{
	int flag = 0; 
	while (size >= 64) {
		flag |= size & 1;
		size >>= 1;
	}
	return size + flag;
}

void MERGE(Cats * cats1, Cats * cats2, const int size1, const int size2, bool swap(cat & cat1, cat & cat2))
{
	int size = (size1 < size2)? size1 : size2;
	Cats *newcats = new cat[size1 + size2];
	int i1 = 0;
	int i2 = 0;
	for (int i = 0; i < size1 + size2; ++i) {
		if ((i1 < size1) && (i2 < size2)) {
			if (swap(cats2[i2], cats1[i1])) {
				newcats[i] = cats2[i2++];
			}
			else {
				newcats[i] = cats1[i1++];
			}
		}
		else {
			if (i1 < size1) {
				newcats[i] = cats1[i1++];
			}
			else if (i2 < size2) {
				newcats[i] = cats2[i2++];
			}
		}
	}

	for (int i = 0; i < size1; ++i) {
		cats1[i] = newcats[i];
	}
	for (int i = 0; i < size2; ++i) {
		cats2[i + size1] = newcats[i];
	}
}

void TIM(Cats *cats, int size, bool swap(cat & cat1, cat & cat2))
{
	if (size < 64) {
		INSERT(cats, size, swap);
		return;
	}
	int minrun = get_minrun (size);


	stack<mas> stack;
	int i = 0;
	while (i < size) {
		if (size - i >= minrun) {

			mas temp = {&cats[i], 1};
			while ((i + temp.size < size) && !swap(cats[i + temp.size], cats[i + temp.size - 1])) 
			{ 
				++temp.size;
			}
			if (temp.size < 2) {
				while ((i + temp.size < size) && !swap(cats[i + temp.size - 1], cats[i + temp.size])) 
				{ 
					++temp.size;
				}
				for (int j = 0; j < temp.size/2; ++j) 
				{ 
					cat c = temp.ptr[j];
					temp.ptr[j] = temp.ptr[temp.size - j - 1];
					temp.ptr[temp.size - j - 1] = c;
				}
			}
			if (temp.size < minrun) {
				temp.size = minrun;
			}
			INSERT(temp.ptr, temp.size, less);

			stack.push (temp);
			func(stack, less);
			i += temp.size;
		}
		else {
			massiv temp = {&cats[i], size - i};
			insert_sort (temp.ptr, temp.size, less);

			stack.push (temp);
			func(stack, less);
			i += temp.size;
		}
	}

	while (stack.size () > 1) {
		massiv mX = stack.pop ();
		massiv mY = stack.pop ();
		merge (mY.ptr, mX.ptr, mY.size, mX.size, less);
		mY.size += mX.size;
		stack.push (mY);
	}
}

void func(stack<massiv> stack, bool swap(cat & cat1, cat & cat2))
{
	if (stack.size () < 3) {
		return;
	}
	massiv mX = stack.pop ();
	massiv mY = stack.pop ();
	massiv mZ = stack.pop ();
	if ((mX.size > mY.size + mZ.size) && (mY.size > mZ.size)) {
		stack.push (mZ);
		stack.push (mY);
		stack.push (mX);
		return;
	}
	if (mX.size <= mZ.size) {
		merge (mY.ptr, mX.ptr, mY.size, mX.size, less);
		mY.size += mX.size;
		stack.push (mZ);
		stack.push (mY);
		func(stack, less);
	}
	else {
		merge (mZ.ptr, mY.ptr, mZ.size, mY.size, less);
		mZ.size += mY.size;
		stack.push (mZ);
		stack.push (mX);
		func(stack, less);
	}
}

bool ageswap(cat & cat1, cat & cat2)
{
	return (cat1.age < cat2.age)? true : false;
}

bool nameswap(cat & cat1, cat & cat2)
{
	return (cat1.name.compare (cat2.name) < 0)? true : false;
}

bool breedswap(cat & cat1, cat & cat2)
{
	return (cat1.breed.compare (cat2.breed) < 0)? true : false;
}

bool foodswap(cat & cat1, cat & cat2)
{
	return (cat1.food.compare (cat2.food) < 0)? true : false;
}

void PRINTCAT(ofstream & out, Cats *cats, int size)
{
	for (int i = 0; i < size; ++i) {
		out	<< cats[i].id << " " 
			<< cats[i].name.data () << " " 
			<< cats[i].age << " " 
			<< cats[i].breed.data () << " " 
			<< cats[i].food.data () << "\n";
	}
}

int main ()
{
	#ifdef _WIN32
	system ("chcp 1251"); 
	#endif

	ifstream in ("cats.txt", ifstream::binary);
	stack <cat> cats;

	int catnum = 0;

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

		for (unsigned int i = 0; i < strid.length(); i++) {
		 id = id * 10 + strid[i] - '0';
		}

		for (unsigned int i = 0; i < strage.length(); i++) {
			if (('0' > strage[i]) || ('9' < strage[i]))
				throw runtime_error ("wrong input");
			age = age * 10 + strage[i] - '0';
		}

		Cats *newcat = new cat;
		newcat->age = age;
		newcat->breed = breed;
		newcat->name = name;
		newcat->food = food;
		newcat->id = id;

		cats << *newcat;
		++catnum;

		char c;
		if (!in.get(c))
			break;
		else 
			in.putback(c);
	}

	in.close ();

	ofstream out("name.txt", ofstream::binary);
	TIM(cats._data, cats.size (), nameswap);

	PRINTCAT(out, cats._data, cats.size ());
	out.close ();

	out.open ("age.txt", ofstream::binary);
	TIM(cats._data, cats.size (), ageswap);
	PRINTCAT(out, cats._data, cats.size ());
	out.close ();

	out.open ("breed.txt", ofstream::binary);
	TIM(cats._data, cats.size (), breedswap);
	PRINTCAT(out, cats._data, cats.size ());
	out.close ();

	out.open ("food.txt", ofstream::binary);
	TIM(cats._data, cats.size (), foodswap);
	PRINTCAT(out, cats._data, cats.size ());
	out.close ();

	return 0;
} 
