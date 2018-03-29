#include <iostream>
#include "tree_map.h"
#include "hash_map.h"
#include <fstream>

void test_hash_map (hash_map & hmap);
void test_tree_map (tree_map & tmap);

int main ()
{
	#ifdef _WIN32
	system ("chcp 1251"); // для отладки в винде.
	#endif

	std::ifstream in ("input.txt", std::ifstream::binary);
	char c;
	std::string str_number;
	int number = 0;
	std::string surname;
	std::string name;

	hash_map hmap;
	tree_map tmap;

	while (in.get(c)) {
		while (('0' <= c) && (c <= '9')) { // читаем номер
			number = number * 10 + c - '0';
			str_number.push_back (c);
			if (!in.get(c)) {
				break;
			}
		}
		while ((' ' == c) && in.get (c)) {
			;
		}
		while (c != ' ') { // читаем фамилию
			surname.push_back (c);
			if (!in.get (c)) {
				break;
			}
		}
		while ((' ' == c) && in.get (c)) {
			;
		}
		while (c != '\n') { // читаем имя
			name.push_back (c);
			if (!in.get (c)) {
				break;
			}
		}
		if (number && surname.size () && name.size ()) {
			hmap.insert (number, str_number + " " + surname + " " + name);
			tmap.insert (surname, str_number + " " + surname + " " + name); // будем считать, что фамилии у всех разные.
		}
		number = 0;
		str_number.clear ();
		surname.clear ();
		name.clear ();
	}

	test_tree_map (tmap);
	test_hash_map (hmap);

	std::cin >> c;

	in.close ();

	return 0;
}

void test_hash_map (hash_map & hmap)
{
	std::cout << "\n hash_map_test \n";
	int number = 271001;
	for (int i = 0; i < 10; ++i) {
		std::cout << hmap[number + i].data () << std::endl;
	}
}

void test_tree_map (tree_map & tmap)
{
	std::cout << "tree_map_test \n";
	std::cout << tmap.search_by_part_of_the_key ("Ива").data ();
	std::cout << std::endl;
}
