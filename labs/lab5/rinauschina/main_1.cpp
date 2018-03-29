#include "treeMap.h"
#include "hashMap.h"
#include <fstream>
#include <iostream>
using namespace std;

void testHashMap (hashMap<string> & hmap);
void testTreeMap (treeMap<string> & tmap);

int main (int argc, char **argv)
{
	if (argc < 2)
	{
		cout << "Write a name of file to read." << endl;
		return 1;
	}
	string inputFilename = argv[1];

	ifstream in (inputFilename.data (), ifstream::binary);

	string strNumber;
	int number = 0;
	string surname;
	string name;

	hashMap<string> map1;
	treeMap<string> map2;

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
				throw runtime_error ("wrong input");
			number = number *10 + strNumber[i] - '0';
		}
		getline (in, surname, ' ');
		getline (in, name, '\n');

		map1.add ( number, strNumber + " " + surname + " " + name);
		map2.add (surname, strNumber + " " + surname + " " + name);

		char c;
		if (!in.get(c))
			break;
		else 
			in.putback(c);
	}

	testHashMap (map1);
	testTreeMap (map2);

	in.close ();
	return 0;
}

void testHashMap (hashMap<string> & hshMap)
{
	cout << "----- testing hashMap -----" << endl;
	cout << "----- getting guys from number 408138 to 408147 -----" << endl;
	int number = 408138;
	for (int i = 0; i < 10; ++i) {
		cout << hshMap.get(number + i).data () << endl;
	}
	cout << endl;
}

void testTreeMap (treeMap<string> & trMap)
{
	cout << "----- testing treeMap -----" << endl;
	cout << "----- getting all starting with \"Vas\" -----" << endl;
	trMap.printCoincidental ("Vas");
	cout << endl;
	cout << "----- getting \"Petrov\" -----" << endl;
	cout << trMap.get ("Petrov") << endl;
	cout << endl;
}