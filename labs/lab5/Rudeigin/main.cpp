#include <iostream>
#include <fstream>
#include <string>
#include "map_of_table.h"
#include "tree_map.h"

using namespace std;

int main(int argc, char **argv) {
   if (argc < 2) {
        cout << "Укажите файл: ./prog_name filename.txt" << endl;
        return 0;
    }
    string input = argv[1];
    ifstream in(input, ios_base::binary);
    int num = 0;
    map_of_table mhash;
    tree_map mtree;

    Man man;
    while(in.good()) {
        man.telephone = "";
        man.surname = "";
        man.name = "";
        num = 0;
        getline (in, man.telephone, ' ');
        for (unsigned int i = 0; i < man.telephone.length(); ++i) {
            num = num *10 + man.telephone[i] - '0';
        }
        getline (in, man.surname, ' ');
        getline (in, man.name, '\n');
        mhash.set(num, man);
        mtree.set(man.surname, man);
    }
    int key;
    cout << "[1] По номерам \n[2]По начальным буквам/имени \n Выход - любая другая кнопка" << endl;
    cin >> key;
    switch(key) {
        case 1: {
            int high, low;
            cout << "Введите от какого и до какого номера вывести данные:" << endl;
            cout << "От ";
            cin >> low;
            cout << "до ";
            cin >> high;
            for (int i = 0; i < (high-low); ++i) {
                cout << mhash.get(low + i).data() << endl;
            }
            break;
        }
        case 2: {
            string str;
            cout << "Введите начало" << endl;
            cin >> str;
            mtree.search_and_print(str);

            str = "";
            cout << "Введите имя" << endl;
            cin >> str;
            mtree.get(str);
            break;
        }
        default:
            break;
    }
    return 0;
}
