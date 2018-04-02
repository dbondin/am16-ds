#include <iostream>
#include <fstream>
#include <string>
#include "cat.h"

using namespace std;
struct cat {
	int id;
	string name;
	int age;
	string breed;
	string food;
};

struct massiv {
	cat * ptr;
	int size;
};

int get(int size);
void sort(cat * cats, int size, bool less (cat & cat1, cat & cat2));
void merge (cat * cats1, cat * cats2, int size1, int size2, bool less (cat & cat1, cat & cat2));
void tim_sort(cat * cats, int size, bool less (cat & cat1, cat & cat2));
void prov (calc_stack<massiv> stack, bool less (cat & cat1, cat & cat2));
void show(ofstream & out, cat * cats, int size);

int get(int size)
{
	int flag = 0; 
	while (size >= 64) {
		flag |= size & 1;
		size >>= 1;
	}
	return size + flag;
}

void sort (cat * cats, int size, bool less (cat & cat1, cat & cat2))
{
	for (int i = 0; i < size; ++i) {
		for (int j = i; j > 0; --j) {
			if (less (cats[i], cats[i - 1])) {
				cat temp = cats[i - 1];
				cats[i - 1] = cats[i];
				cats[i] = temp;
			}
		}
	}
}

void merge (cat * cats1, cat * cats2, const int size1, const int size2, bool less (cat & cat1, cat & cat2))
{
	int size = (size1 < size2)? size1 : size2;
	cat *newcats = new cat[size1 + size2];
	int i1 = 0;
	int i2 = 0;
	for (int i = 0; i < size1 + size2; ++i) {
		if ((i1 < size1) && (i2 < size2)) {
			if (less (cats2[i2], cats1[i1])) {
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

void tim_sort(cat * cats, int size, bool less (cat & cat1, cat & cat2))
{
	if (size < 64) {
		sort (cats, size, less);
		return;
	}
	int min = get(size);


	calc_stack<massiv> stack;
	int i = 0;
	while (i < size) {
		if (size - i >= min) {

			massiv temp = {&cats[i], 1};
			while ((i + temp.size < size) && !less (cats[i + temp.size], cats[i + temp.size - 1])) { 
				++temp.size;
			}
			if (temp.size < 2) {
				while ((i + temp.size < size) && !less (cats[i + temp.size - 1], cats[i + temp.size])) { 
					++temp.size;
				}
				for (int j = 0; j < temp.size/2; ++j) { 
					cat c = temp.ptr[j];
					temp.ptr[j] = temp.ptr[temp.size - j - 1];
					temp.ptr[temp.size - j - 1] = c;
				}
			}
			if (temp.size < min) {
				temp.size = min;
			}
			sort (temp.ptr, temp.size, less);

			stack.push (temp);
			prov(stack, less);
			i += temp.size;
		}
		else {
			massiv temp = {&cats[i], size - i};
			sort (temp.ptr, temp.size, less);

			stack.push (temp);
			prov (stack, less);
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

	if (stack.pop ().size != size) {
		
	}
}

void prov (calc_stack<massiv> stack, bool less (cat & cat1, cat & cat2))
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
		prov (stack, less);
	}
	else {
		merge (mZ.ptr, mY.ptr, mZ.size, mY.size, less);
		mZ.size += mY.size;
		stack.push (mZ);
		stack.push (mX);
		prov (stack, less);
	}
}

bool ageless (cat & cat1, cat & cat2)
{
	return (cat1.age < cat2.age)? true : false;
}

bool nameless (cat & cat1, cat & cat2)
{
	return (cat1.name.compare (cat2.name) < 0)? true : false;
}

bool breedless (cat & cat1, cat & cat2)
{
	return (cat1.breed.compare (cat2.breed) < 0)? true : false;
}

bool foodless (cat & cat1, cat & cat2)
{
	return (cat1.food.compare (cat2.food) < 0)? true : false;
}

void show(ofstream & out, cat * cats, int size)
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
	
	ifstream in ("cats.txt", ifstream::binary);
	calc_stack<cat> cats;

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
			if (('0' > strid[i]) || ('9' < strid[i]))
				throw runtime_error ("wrong input");
			id = id * 10 + strid[i] - '0';
		}

		for (unsigned int i = 0; i < strage.length(); i++) {
			if (('0' > strage[i]) || ('9' < strage[i]))
				throw runtime_error ("wrong input");
			age = age * 10 + strage[i] - '0';
		}

		cat * newcat = new cat;
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

	ofstream out ("name.txt", ofstream::binary);
	tim_sort (cats.m_data, cats.size (), nameless);

	show (out, cats.m_data, cats.size ());
	out.close ();

	out.open ("age.txt", ofstream::binary);
	tim_sort (cats.m_data, cats.size (), ageless);
	show (out, cats.m_data, cats.size ());
	out.close ();

	out.open ("breed.txt", ofstream::binary);
	tim_sort (cats.m_data, cats.size (), breedless);
	show (out, cats.m_data, cats.size ());
	out.close ();

	out.open ("food.txt", ofstream::binary);
	tim_sort (cats.m_data, cats.size (), foodless);
	show (out, cats.m_data, cats.size ());
	out.close ();

	return 0;
}
