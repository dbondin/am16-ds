#include <iostream>
#include <fstream>
#include <string>
#include "calc_stack.h"

struct cat {
	int id;
	std::string name;
	int age;
	std::string breed;
	std::string food;
};

struct massiv {
	cat * ptr;
	int size;
};

int get_minrun (int size);
void insert_sort (cat * cats, int size, bool less (cat & cat1, cat & cat2));
void merge (cat * cats1, cat * cats2, int size1, int size2, bool less (cat & cat1, cat & cat2));
void timsort (cat * cats, int size, bool less (cat & cat1, cat & cat2));
void check_if_merge_is_needed_and_merge_if_needed (calc_stack<massiv> stack, bool less (cat & cat1, cat & cat2));
void print_cats (std::ofstream & out, cat * cats, int size);

void insert_sort (cat * cats, int size, bool less (cat & cat1, cat & cat2))
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

int get_minrun (int size)
{
	int flag = 0; /* станет 1 если среди сдвинутых битов будет хотя бы 1 ненулевой */
	while (size >= 64) {
		flag |= size & 1;
		size >>= 1;
	}
	return size + flag;
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

void timsort (cat * cats, int size, bool less (cat & cat1, cat & cat2))
{
	if (size < 64) {
		insert_sort (cats, size, less);
		return;
	}
	int minrun = get_minrun (size);


	calc_stack<massiv> stack;
	int i = 0;
	while (i < size) {
		if (size - i >= minrun) {

			massiv temp = {&cats[i], 1};
			while ((i + temp.size < size) && !less (cats[i + temp.size], cats[i + temp.size - 1])) { // пока <=
				++temp.size;
			}
			if (temp.size < 2) {
				while ((i + temp.size < size) && !less (cats[i + temp.size - 1], cats[i + temp.size])) { // пока >=
					++temp.size;
				}
				for (int j = 0; j < temp.size/2; ++j) { // меняем все местами.
					cat c = temp.ptr[j];
					temp.ptr[j] = temp.ptr[temp.size - j - 1];
					temp.ptr[temp.size - j - 1] = c;
				}
			}
			if (temp.size < minrun) {
				temp.size = minrun;
			}
			insert_sort (temp.ptr, temp.size, less);

			stack.push (temp);
			check_if_merge_is_needed_and_merge_if_needed (stack, less);
			i += temp.size;
		}
		else {
			massiv temp = {&cats[i], size - i};
			insert_sort (temp.ptr, temp.size, less);

			stack.push (temp);
			check_if_merge_is_needed_and_merge_if_needed (stack, less);
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
		//throw std::runtime_error ("Кого-то потеряли.");
	}
}

void check_if_merge_is_needed_and_merge_if_needed (calc_stack<massiv> stack, bool less (cat & cat1, cat & cat2))
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
		check_if_merge_is_needed_and_merge_if_needed (stack, less);
	}
	else {
		merge (mZ.ptr, mY.ptr, mZ.size, mY.size, less);
		mZ.size += mY.size;
		stack.push (mZ);
		stack.push (mX);
		check_if_merge_is_needed_and_merge_if_needed (stack, less);
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

void print_cats (std::ofstream & out, cat * cats, int size)
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
	system ("chcp 1251"); // для отладки в винде.
	#endif

	std::ifstream in ("cats.txt", std::ifstream::binary);
	calc_stack<cat> cats;

	int catnum = 0;

	while (1) {

		std::string strid = "";
		int id = 0;
		std::string name = "";
		std::string strage = "";
		int age = 0;
		std::string breed = "";
		std::string food = "";

		std::getline (in, strid, ' ');
		std::getline (in, name, ' ');	
		std::getline (in, strage, ' ');
		std::getline (in, breed, ' ');
		std::getline (in, food, '\n');

		for (unsigned int i = 0; i < strid.length(); i++) {
			if (('0' > strid[i]) || ('9' < strid[i]))
				throw std::runtime_error ("wrong input");
			id = id * 10 + strid[i] - '0';
		}

		for (unsigned int i = 0; i < strage.length(); i++) {
			if (('0' > strage[i]) || ('9' < strage[i]))
				throw std::runtime_error ("wrong input");
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

	std::ofstream out ("name.txt", std::ofstream::binary);
	timsort (cats.m_data, cats.size (), nameless);

	print_cats (out, cats.m_data, cats.size ());
	out.close ();

	out.open ("age.txt", std::ofstream::binary);
	timsort (cats.m_data, cats.size (), ageless);
	print_cats (out, cats.m_data, cats.size ());
	out.close ();

	out.open ("breed.txt", std::ofstream::binary);
	timsort (cats.m_data, cats.size (), breedless);
	print_cats (out, cats.m_data, cats.size ());
	out.close ();

	out.open ("food.txt", std::ofstream::binary);
	timsort (cats.m_data, cats.size (), foodless);
	print_cats (out, cats.m_data, cats.size ());
	out.close ();

	return 0;
}