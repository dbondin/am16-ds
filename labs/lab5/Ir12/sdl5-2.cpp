#include "sdl5hachmap-2.h"
#include "sdl5treemap-2.h"
#include <fstream>
#include <iostream>
using namespace std;

void testhachmap (hachmap<string> & hmap);
void testtreemap (treemap<string> & tmap);

int main (int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Введите имя файла." << endl;
		return 1;
	}
	string filename = argv[1];

	ifstream in (filename.data (), ifstream::binary);

	string strNumber;
	int number = 0;
	string surname;
	string name;

	hachmap<string> map1;
	treemap<string> map2;

	while (1)
	{
		string strNumber = "";
		number = 0;
		string surname = "";
		string name = "";

		getline (in, strNumber, ' ');
		for (unsigned int i = 0;i < strNumber.length();i++)
		{
			if (('0' > strNumber[i]) || ('9' < strNumber[i]))
				throw runtime_error ("неправильный ввод");
			number = number *10 + strNumber[i] - '0';
		}
		getline (in, surname, ' ');
		getline (in, name, '\n');

		map1.insert ( number, strNumber + " " + surname + " " + name);
		map2.insert (surname, strNumber + " " + surname + " " + name);

		char c;
		if (!in.get(c))
			break;
		else 
			in.putback(c);
	}

	testhachmap (map1);
	testtreemap (map2);

	in.close ();
	return 0;
}

void testhashmap (hachmap<string> & hshMap)
{
	cout << "найдено по номеру: " << endl;
	int number = 458952;
	for (int i = 0; i < 11; ++i) {
		cout << hshMap.get(number + i).data () << endl;
	}
	cout << endl;
}

void testtreemap (treemap<string> & trMap)
{
	cout << "найдено \"Ива\" " << endl;
	trMap.print ("Ива");
	cout << endl;
	cout << "найдено \"Иванов\" " << endl;
	cout << trMap.get ("Иванов") << endl;
	cout << endl;
} 
