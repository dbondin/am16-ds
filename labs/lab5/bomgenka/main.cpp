#include <iostream>
#include <fstream>
#include <string>
#include "hash.h"
#include "red_black_tree.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "Error" << endl;
        return 0;
    }
    string input = argv[1];
    ifstream in(input, ios_base::binary);
    int num = 0;
    hash_map h_map;
    tree_map t_map;

    while(in.good()) {
       string number = "";
       num = 0;
       string surname = "";
       string name = "";
       getline (in, number, ' ');
       for (unsigned int i = 0; i < number.length(); ++i) {
        num = num *10 + number[i] - '0';
       }
       getline (in, surname, ' ');
       getline (in, name, '\n');

       h_map.add(num, number + " " + surname + " " + name);
       t_map.add(surname, number + " " + surname + " " + name);
    }

    int top, bottom;
    cout << "Введите границы поиска: верхняя нижняя" << endl;
    cin >> top;
    cin >> bottom;
    for (int i = 0; i < (top-bottom); ++i) {
        cout << h_map.get(bottom + i).data() << endl;
    }

    string str_begin;
    cout << "Введите начало" << endl;
    cin >> str_begin;
    t_map.search(str_begin);

    string str_name;
    cout << "Введите имя" << endl;
    cin >> str_name;
    t_map.get(str_name);
    in.close ();
    return 0;
}

