#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
#include <stack>
#include<cstring>
using namespace std;
struct cat {
    int id;
    string name;
    int age;
    string breed;
    string food;
};


void menu()
{
    setlocale(LC_ALL, "Russian");
    //system("cls");
    cout << "Меню" << endl;
    cout << "1 Добавить кошку" << endl;
    cout << "2 Удаление кошки из списка" << endl;
    cout << "3 сортировать" << endl;
    cout << "4 загрузить список из файла" << endl;
    cout << "5 вывести весь спиок на экран" << endl;
    cout << "6 Выход" << endl;
}
vector<cat> addcat(vector<cat>  &cont)
{

    cat temp;
    cout <<"id: ";
    cin>> temp.id;
    cout <<"age: ";
    cin>> temp.age;
    cout <<"Name: ";
    cin>> temp.name;
    cout <<"breed: ";
    cin>> temp.breed;
    cout <<"food: ";
    cin>> temp.food;
    cont.push_back(temp);
    return cont;
}
vector<cat> delcat(vector<cat> &cont)
{
    string name_cat;//переменная для записи промежуточных значений слов

    int i = 0;
    cout << "введите имя кошки для удаления: " << endl;
    cin >> name_cat;
    for (auto it = cont.begin(); it != cont.end(); ++it)
    {

        if (cont[i].name == name_cat) cont.erase(cont.begin() +i);
        i++;
    }
    return cont;
}
void print(vector<cat>  &cont)
{
    int cnt=0;
    for (auto it = cont.begin(); it != cont.end(); it++)
    {
        cout << cont[cnt].id << "   ";
        cout << cont[cnt].name << "   ";
        cout << cont[cnt].age << "   ";
        cout << cont[cnt].breed << "   ";
        cout << cont[cnt].food<< endl;
        cnt++;
    }
}
vector<cat> loadIn_cats(vector<cat> &cont)
{
    cat add;//структура для записи данных
    string str;
    cout<<"Enter name file: ";
    cin>>str;
    string path = str+".txt";//название файла хранилища результатов
    str.clear();
    int ch,t=0;
    ifstream fin;//поток записи в файл
    cont.clear();
    fin.open(path);

    if (!fin)
    {
        cout << "can't open this file" << "\n" << endl;
    }
    while ((ch = fin.get()) != EOF) {//пока не конец файла
        if (char(ch) != '\n') {//пока не конец строки считываетм символы
            str += char(ch);
            if (char(ch) == ';'&&t==0)
            {
                add.id=atoi(str.c_str());
                str.clear();
                t++;
            }
            else if (char(ch) == ';'&&t==1)
            {
                add.name=str.substr(0, (str.length()-1));
                str.clear();
                t++;
            }
            else if (char(ch) == ';'&&t==2)
            {
                add.age=atoi(str.c_str());
                str.clear();
                t++;
            }
            else if (char(ch) == ';'&&t==3)
            {
                add.breed=str.substr(0, (str.length()-1));
                str.clear();
                t++;
            }
            else if (char(ch) == ';'&&t==4)
            {
                add.food=str.substr(0, (str.length()-1));
                str.clear();
                t++;
            }
        }
        else//записываем слова в вектор
        {
            cont.push_back(add);
            str.clear();
            t = 0;
            continue;
        }
    }
    fin.close(); //Закрываем файл
    return cont;
}
void loadOf_cats(vector<cat> &cont, string name_file)
{
  string path = name_file+".txt";//название файла хранилища результатов
  cout<<path<<endl;
  int cnt = 0;
  ofstream out (path, std::ofstream::binary);
  for (auto it = cont.begin(); it != cont.end(); it++) {
      out	<< cont[cnt].id << " "
            << cont[cnt].name.data () << " "
            << cont[cnt].age << " "
            << cont[cnt].breed.data () << " "
            << cont[cnt].food.data () << "\n";
      cnt++;
   }
   cnt = 0;
   out.close();
}

void ins_sort (vector<cat>  &cont, bool (*lambda)(const cat& a, const cat& b))
{

    int vector_size=cont.size();
    for (int i = 1; i < vector_size;i++) {
        for (int j = i; (j > 0)&&(lambda(cont[j],cont[j-1])); j--) {

            cat add=cont[j-1];
            cont[j-1] = cont[j];
            cont[j] = add;
        }
     }
}


void merge_sort (vector<cat>  &cats_a, vector<cat>  &cats_b, bool (*lambda)(const cat& a, const cat& b))// sort marge
{
    const int N1=cats_a.size(),N2=cats_b.size();
    vector<cat> Ncats;
    cat c,b;
    Ncats.resize(N1+N2);
    int i = 0, j = 0;
    int cnt1=0,cnt2=0;
    for (int i = 0; i < N1 + N2; ++i) {
        if ((cnt1 < N1) && (cnt2 < N2)) {
        if (lambda (cats_b[cnt2], cats_a[cnt1])) {
                Ncats[i] = cats_b[cnt2++];
            }
            else {
                Ncats[i] = cats_a[cnt1++];
            }
        }
        else {
            if (cnt1 < N1) {
                Ncats[i] = cats_a[cnt1++];
            }
            else if (cnt2 < N2) {
                Ncats[i] = cats_b[cnt2++];
            }
        }
    }
    for (int p = 0; p < N1; ++p) {
        cats_a[p] = Ncats[p];
    }
    for (int p = 0; p < N2; ++p) {
        cats_b[p + N1] = Ncats[p];
    }
}
void Swap_merge ( stack<vector<cat>> &stack_vectors,bool (*lambda)(const cat& a, const cat& b))
{
    vector<cat> A= stack_vectors.top();
    stack_vectors.pop();
    vector<cat> B= stack_vectors.top();
    stack_vectors.pop();
    vector<cat> C= stack_vectors.top();
    stack_vectors.pop();
    if ((A.size() > (B.size() + C.size())) && (B.size() > C.size())) {
        stack_vectors.push (C);
        stack_vectors.push (B);
        stack_vectors.push (A);

    }
    if (A.size() <= C.size()) {

        merge_sort (B, A,lambda);
        B.insert(B.end(), A.begin(),A.end());

        stack_vectors.push (C);
        stack_vectors.push (B);
        Swap_merge (stack_vectors, lambda);
    }
    else {
        merge_sort (C, B, lambda);
        C.insert(C.end(), B.begin(),B.end());

        stack_vectors.push(C);
        stack_vectors.push(A);
        Swap_merge (stack_vectors, lambda);
    }
    return;
}
void timSort(vector<cat>  &cont,bool (*lambda)(const cat& a, const cat& b))
{
    stack<vector<cat>> stack_vectors_cats;

    cat c;
    vector<cat> cat_r;

    int counter=0;
    int i=0;
    int N=cont.size();
    int mRUN;
    int point = 0;

    while (N >= 64) {
        point |= N & 1;
        N >>= 1;
       }
    mRUN= N + point;

    if (N < 64) {
            ins_sort (cont, lambda);
            return;
    }

    while (i<N) {
        if (N - i >= mRUN) {
                    cat_r.erase(cat_r.begin(),cat_r.end());
                    cat_r.push_back(cont[i]);
                    counter=1;
                    while (((i + cat_r.size()) < N) && !lambda (cont[i + cat_r.size()], cont[i + (cat_r.size()-1)])) {
                        cat_r.push_back(cont[i+counter]);
                        counter++;

                    }                    
                    counter=1;
                    if (cat_r.size() < 2) {
                        while (((i + cat_r.size()) < N) && !lambda (cont[i + cat_r.size() - 1], cont[i + cat_r.size()])) {
                            cat_r.push_back(cont[i+counter]);
                            counter++;
                        }
                        for (int j = 0; j < (cat_r.size()/2); ++j) {
                            c = cat_r[j];
                            cat_r[j] = cat_r[cat_r.size() - j - 1];
                            cat_r[cat_r.size() - j - 1] = c;
                        }
                    }
                    counter=1;
                    if (cat_r.size() < mRUN) {
                        while (cat_r.size() != mRUN) {
                            cat_r.push_back(cont[i+counter]);
                            counter++;
                        }
                    }
                    ins_sort (cat_r, lambda);
                    stack_vectors_cats.push(cat_r);
                    if (stack_vectors_cats.size () > 3) {
                        Swap_merge (stack_vectors_cats, lambda);
                    }
                    i += cat_r.size();
        }
        else {
                    cat_r.erase(cat_r.begin(),cat_r.end());
                    counter=0;
                    while (cat_r.size() != (N-i)) {
                        cat_r.push_back(cont[i+counter]);
                        counter++;
                    }
                    ins_sort(cat_r,lambda);

                    stack_vectors_cats.push (cat_r);

                    if (stack_vectors_cats.size () > 3) Swap_merge (stack_vectors_cats, lambda);
                    i += cat_r.size();
        }
    }
    cont.erase(cont.begin(),cont.end());
    cat_r.erase(cat_r.begin(),cat_r.end());
    while (stack_vectors_cats.size()!=0) {
        cat_r=stack_vectors_cats.top();
        stack_vectors_cats.pop();
        cont.insert(cont.begin(),cat_r.begin(),cat_r.end());
        cat_r.erase(cat_r.begin(),cat_r.end());
    }
}

int main()
{
    vector<cat> cats;
    int imenu=0;
    while (true)
    {
        menu();//вывод меню программы
        cin >> imenu;
        switch (imenu)
        {
            case 1://добавить слово в словарь
            {
                addcat(cats);
                imenu = 0;
                continue;
            }
            case 2://удаление слова из словаря
            {

                delcat(cats);
                imenu = 0;
                continue;
            }
            case 3://сортировать
            {

                bool (*lambda1)(const cat& a, const cat& b) = [](const cat& a, const cat& b) {return a.id < b.id;};
                timSort(cats,lambda1);
                loadOf_cats(cats,"id");

                bool (*lambda2)(const cat& a, const cat& b) = [](const cat& a,const cat& b) {return a.name < b.name;};
                timSort(cats,lambda2);
                loadOf_cats(cats,"name");

                bool (*lambda3)(const cat& a, const cat& b) = [](const cat& a, const cat& b) {return a.age < b.age;};
                timSort(cats,lambda3);
                loadOf_cats(cats,"age");

                bool (*lambda4)(const cat& a, const cat& b) = [](const cat& a, const cat& b) {return a.breed < b.breed;};
                timSort(cats,lambda4);
                loadOf_cats(cats,"breed");

                bool (*lambda5)(const cat& a, const cat& b) = [](const cat& a, const cat& b) {return a.food < b.food;};
                timSort(cats,lambda5);
                loadOf_cats(cats,"food");
                /*
                sort(cats.begin(),cats.end(),[](const cat& a,const cat& b) {return a.id < b.id;});
                loadOf_cats(cats,"id");

                sort(cats.begin(),cats.end(),[](const cat& a,const cat& b) {return a.name < b.name;});
                loadOf_cats(cats,"name");

                sort(cats.begin(),cats.end(),[](const cat& a,const cat& b) {return a.age < b.age;});
                loadOf_cats(cats,"age");


                sort(cats.begin(),cats.end(),[](const cat& a,const cat& b) {return a.breed < b.breed;});
                loadOf_cats(cats,"breed");

                sort(cats.begin(),cats.end(),[](const cat& a,const cat& b) {return a.food < b.food;});
                loadOf_cats(cats,"food");
                */
                imenu = 0;
                continue;
            }
            case 4://считывание из файла
            {
                loadIn_cats(cats);
                imenu = 0;
                continue;
            }
            case 5://вывод вектора на экран
            {
                print(cats);
                imenu = 0;
                continue;
            }
            case 6://выход из программы
            {

                return 0;
            }            
        }

    }
}
