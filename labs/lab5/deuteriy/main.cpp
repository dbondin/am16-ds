#include <iostream>
#include <string>
#include "tree.h"
#include "hash.h"
#include <fstream>

void test_on_hash(hash& hmap)
{
	cout << "\n Hash \n";
	int number = 271001;
	for (int i = 0; i < 10; ++i) 
	{
		cout << hmap[number + i].data() << endl;
	}
}

void test_on_tree(tree& tmap)
{
	cout << "Tree \n";
	cout << tmap.search_part("Ива").data();
	cout << endl;
}

int main()
{
	ifstream in ("input.txt", ifstream::binary);
	char c;
	string str_mob;
	int mob = 0;
	string surname;
	string name;
	hash hmap;
	tree tmap;

	while (in.get(c)) {
		while (('0' <= c) && (c <= '9')) 
		{
			mob = mob * 10 + c - '0';
			str_mob.push_back(c);
			if (!in.get(c))
			{
				break;
			}
		}
		while ((' ' == c) && in.get (c)) 
		{
			;
		}
		while (c != ' ') 
		{
			surname.push_back (c);
			if (!in.get(c)) 
			{
				break;
			}
		}
		while ((' ' == c) && in.get (c)) 
		{
			;
		}
		while (c != '\n') 
		{
			name.push_back (c);
			if (!in.get (c)) 
			{
				break;
			}
		}
		if (mob && surname.size() && name.size()) 
		{
			hmap.add(mob, str_mob + " " + surname + " " + name);
			tmap.add(surname, str_mob + " " + surname + " " + name);
		}
		mob = 0;
		str_mob.clear();
		surname.clear();
		name.clear();
	}
	test_on_tree(tmap);
	test_on_hash(hmap);
	cin >> c;
	in.close ();
	return 0;
}
