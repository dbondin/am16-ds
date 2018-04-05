#include <fstream>
#include <string>
#include <iostream>
#include "tree_map.h"
#include "Hash_map.h"

using namespace std;

void hash_Map(hash_map<string> & hmap);
void tree_Map(tree_map<string> & tmap);

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Write name file" << endl;
        return 1;
    }
    string input_file = argv[1];
    ifstream in (input_file.data (), ifstream::binary);

    int number = 0;
    hash_map<string> map1;
    tree_map<string> map2;

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
                throw runtime_error ("Uncorrect number");
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
    hash_Map (map1);
    tree_Map (map2);
    in.close ();
    return 0;
}

void hash_Map(hash_map<string> & hshMap)
{
    cout << "Show number in radius 123456-123466"<< endl;
    int number = 123456;
    for (int i = 0; i < 14; ++i) {
        cout << hshMap.get(number + i).data () << endl;
    }
}

void tree_Map(tree_map<string> & trMap)
{
    cout << "Show all people starring with 'Iva'" << endl;
    trMap.printCoincidental ("Iva");

    cout << "Show all 'Pet'" << endl;
    cout << trMap.get("Pet") << endl;
}
