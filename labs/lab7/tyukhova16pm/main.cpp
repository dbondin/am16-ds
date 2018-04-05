#include <fstream>
#include <string>
#include "cats.h"

int main ()
{
    ifstream in ("cats.txt",  ifstream::binary);
    stackhere<cat> cats;

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
                cout<<"Wrong"<<endl;
            id = id * 10 + strid[i] - '0';
        }

        for (unsigned int i = 0; i < strage.length(); i++) {
            if (('0' > strage[i]) || ('9' < strage[i]))
                cout<<"Wrong"<<endl;
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

    ofstream out ("name.txt",  ofstream::binary);
    timsort (cats.m_data, cats.size (), nameless);

    print_cats (out, cats.m_data, cats.size ());
    out.close ();

    out.open ("age.txt",  ofstream::binary);
    timsort (cats.m_data, cats.size (), ageless);
    print_cats (out, cats.m_data, cats.size ());
    out.close ();

    out.open ("breed.txt",  ofstream::binary);
    timsort (cats.m_data, cats.size (), breedless);
    print_cats (out, cats.m_data, cats.size ());
    out.close ();

    out.open ("food.txt",  ofstream::binary);
    timsort (cats.m_data, cats.size (), foodless);
    print_cats (out, cats.m_data, cats.size ());
    out.close ();

    return 0;
}
