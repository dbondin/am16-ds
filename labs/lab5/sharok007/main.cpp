#include <iostream>
#include <fstream>
#include "hash_map.hpp"
#include "tree_map.hpp"

using namespace std;

void test_hash(Hash_map &map1);
void test_tree(Map_tree &map2);

int main()
{
    char name_file[32];
    cout << "Введите название справочника: ";
    cin >> name_file;
    ifstream in(name_file,ios::binary);
    if(!in){
        cout << "Нет такого справочника" << endl;
        return 1;
    }
    char c;
    string name;
    string surname;
    int hash_number = 0;
    string tree_number;

    Hash_map map_hash;
    Map_tree tree_map;

    while(in.get(c)){
        while (('0' <= c) && (c <= '9')) {
            hash_number = hash_number*10 + c-'0';
            tree_number.push_back(c);
            if(!in.get(c)){
                break;
            }
        }
        while(' ' == c && in.get(c)){
            ;
        }
        while(c !=' '){
            surname.push_back(c);
            if(!in.get(c)){
                break;
            }
        }
        while(' ' == c && in.get(c)){
            ;
        }
        while(c !='\n'){
            name.push_back(c);
            if(!in.get(c)){
                break;
            }
        }
        if(hash_number && name.size() && surname.size()){
            map_hash.add(hash_number,tree_number + " " + surname + " " + name);
            tree_map.add(surname,tree_number + " " + surname + " " + name);
        }
        hash_number = 0;
        tree_number.clear();
        surname.clear();
        name.clear();
    }
    test_hash(map_hash);
    test_tree(tree_map);
    
    in.close();
    return 0;
}

void test_hash(Hash_map &map1){
    cout << "Поиск по номеру:" <<endl;
    int number = 654321;
    string result;
    result = map1.search(number);
    cout << result << endl;
}

void test_tree(Map_tree &map2){
    cout << "Поиск по фамилии: " << endl;
    cout << map2.partial_search("Лет").data();
    cout << endl;
}
