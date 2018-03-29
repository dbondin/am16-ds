#include <fstream>
#include <string>
#include <iostream>
#include "tree_map.h"
#include "hash_map.h"

using namespace std;

void HashMap(hashMap<string> & hmap);
void TreeMap(treeMap<string> & tmap);

int main (int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Pls type $./HASH 1.txt" << endl;
        return 1;
    }
    string inputFilename = argv[1];
    ifstream in (inputFilename.data (), ifstream::binary);

    int number = 0;

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
    HashMap (map1);
    TreeMap (map2);
    in.close ();
    return 0;
}

void HashMap(hashMap<string> & hshMap)
{
    cout << "Show number in radius 789452-789456"<< endl;
    int number = 789452;
    for (int i = 0; i < 14; ++i) {
        cout << hshMap.get(number + i).data () << endl;
    }
}

void TreeMap(treeMap<string> & trMap)
{
    cout << "Show all guys starring with 'Br'" << endl;
    trMap.printCoincidental ("Br");

    cout<<"/////"<<endl;

    cout << "Show all 'Neal'" << endl;
    cout << trMap.get ("Neal") << endl;
}
