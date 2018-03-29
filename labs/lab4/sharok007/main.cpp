#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "node.hpp"

using namespace std;

void BuildTable(Node *root);//строим таблицу символ-код,для удобства записи в файл
Node* Root(int *arr);//находим вершину дерева

union big_end{
    unsigned int bytes;
    unsigned char byte[4];
};

vector <bool> code; //здесь будем хранить коды символов
map<char, vector<bool> > table; //таблица символ-код

//для удобства сортировки
struct Compare{
    bool operator()(Node* l,Node* r) const{
        return l->getQuan() < r->getQuan();
    }
};



int main()
{
    cout << "1.Упаковать\n2.Распаковать\nВыбирите действие: ";
    int a;
    cin>>a;
    if(1 == a){

        char name_input[256];
        char name_output[256];
        cout << "Введите название файла,который нужно упаковать: ";
        cin >> name_input;
        ifstream file(name_input,ios::binary);
        int arr[256]={0};
        unsigned char str;
        while(!file.eof()){
            str = file.get();
            if(!file.eof()){
                ++arr[str];
            }
        }
        Node *p = Root(arr);
        BuildTable(p);
        file.clear();
        file.seekg(0);

        cout << "Введите имя файла,в который нужно сохранить результат: ";
        cin >> name_output;
        ofstream out(name_output,ios::binary);
        out << "HF16";
        for (int i = 0; i < 256; ++i) {
            big_end bg;
            bg.bytes = (unsigned int)arr[i];
            out.put(bg.byte[3]);
            out.put(bg.byte[2]);
            out.put(bg.byte[1]);
            out.put(bg.byte[0]);
        }
        int count = 0;
        char buf = 0;
        while(!file.eof()){
            char c = file.get();
            vector <bool> x = table[c];
            for(unsigned int i = 0; i < x.size(); ++i){
                buf = buf | x[i]<<(7-count);
                ++count;
                if(8 == count){
                    count = 0;
                    out << buf;
                    buf = 0;
                }
            }
        }
        out.close();
        file.close();
    }
    if(2 == a){

        char name_input[256];
        char name_output[256];
        int arr[256];
        cout << "Введите имя файла,который нужно распаковать: ";
        cin >> name_input;
        ifstream in(name_input,ios::binary);
        cout << "Введите имя файла,в который нужно сохранить результат: ";
        cin >> name_output;
        ofstream out(name_output,ios::binary);
        char byte;
        string HF16 = "HF16";
        for (int i = 0; i < 4; ++i) {
            in.get (byte);
            if (byte != HF16[i]) {
                cerr << "Неверный формат файла\n";
                return 1;
            }
        }
        for (int i = 0; i < 256; ++i) {
            unsigned int stat = 0;
            for (int j = 0; j < 4; ++j) {
                in.get (byte);
                stat |= (unsigned char)byte;
                stat <<= 8;
            }
            stat >>= 8;
            arr[i] = stat;
        }
        Node *root = Root(arr);
        Node *p = root;
        int count = 0;
        byte = in.get();
        while(!in.eof()){
            bool b = byte & (1<<(7-count));
            if(b)
                p = p->getRight();
            else {
                p = p->getLeft();
            }
            if(p->getLeft() == NULL && p->getRight() == NULL){
                out << p->getSymbol();
                p = root;
            }
            ++count;
            if(count == 8){
                count = 0;
                byte = in.get();
            }
        }
        in.close();
        out.close();
    }
    return 0;
}

Node* Root(int *arr){
    list<Node*> statist;
    for(int i = 0; i < 256; ++i){
        Node *statistic = new Node;
        statistic->setQuan(arr[i]);
        statistic->setSymbol((char)i);
        statist.push_back(statistic);
    }
    while(statist.size() !=1){
        statist.sort(Compare());
        Node *SonLeft = statist.front();
        statist.pop_front();
        Node *SonRight = statist.front();
        statist.pop_front();
        Node *parent = new Node(SonLeft,SonRight);
        statist.push_back(parent);
    }
    Node *root = statist.front();
    return root;
}

void BuildTable(Node *root){
    if(root->getLeft() !=NULL){
        code.push_back(0);
        BuildTable(root->getLeft());
    }
    if(root->getRight() !=NULL){
        code.push_back(1);
        BuildTable(root->getRight());
    }
    if(root->getLeft() == NULL && root->getRight() == NULL){
        table[root->getSymbol()] = code;
    }
    code.pop_back();
}
