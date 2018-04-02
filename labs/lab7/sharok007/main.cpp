#include <iostream>
#include <fstream>
#include"stack.hpp"

using namespace std;

struct cats{
    int index;
    string name;
    int age;
    string breed;
    string like_food;
};

struct array{
    cats *cat;
    int size;
};

int minrun(int size);
void timsort(cats *cat,int size,bool less(cats &cat1,cats &cats2));
void insert_sort(cats *cat,int size,bool less(cats &cat1,cats &cats2));
void print(cats *cat,int size,ofstream &out);
void merger(cats *cat1,cats *cat2,int size_cat1,int size_cat2,bool less(cats & _cat1,cats & _cats2));
void merge_tim(Stack<array> stack,bool less(cats & _cat1,cats & _cats2));

bool comparison_age(cats &cat1,cats &cat2){
    return (cat1.age < cat2.age) ? true:false;
}

bool comparison_name(cats &cat1,cats &cat2){
    return (cat1.name.compare(cat2.name) < 0) ? true:false;
}
bool comparison_breed(cats &cat1,cats &cat2){
    return (cat1.breed.compare(cat2.breed) < 0) ? true:false;
}
bool comparison_food(cats &cat1,cats &cat2){
    return (cat1.like_food.compare(cat2.like_food) < 0) ? true:false;
}

int main()
{
    ifstream in("cat.txt",ios::binary);
    Stack <cats> cat;
    int number_cat;
    while(1){
        string index = "";
        int _index = 0;
        string age = "";
        int _age = 0;
        string name = "";
        string breed = "";
        string like_food = "";

        getline(in,index,' ');
        getline(in,name,' ');
        getline(in,age,' ');
        getline(in,breed,' ');
        getline(in,like_food,'\n');
        for(unsigned int i=0;i<index.length();++i){
            if(('0' > index[i]) || (index[i] >'9')){
                cout << "Неверный id" << endl;
                return 1;
            }
            _index = _index*10 + index[i]-'0';
        }
        for(unsigned int i=0;i<age.length();++i){
            if(('0' > index[i]) || (index[i] > '9')){
                cout << "Неверный возраст" << endl;
                        return 1;
            }
            _age = _age*10 + age[i]-'0';
        }
        cats *new_cat = new cats;
        new_cat->index = _index;
        new_cat->name = name;
        new_cat->age = _age;
        new_cat->breed = breed;
        new_cat->like_food = like_food;
        cat.push(*new_cat);
        ++number_cat;
        char c;
        if(!in.get(c)){
            break;
        }
        else{
            in.putback(c);
        }
    }

    in.close();

    ofstream out("name.txt",ios::binary);
    timsort(cat.data,cat.getSize(),comparison_name);
    print(cat.data,cat.getSize(),out);
    out.close();

    out.open("age.txt",ios::binary);
    timsort(cat.data,cat.getSize(),comparison_age);
    print(cat.data,cat.getSize(),out);
    out.close();

    out.open("breed.txt",ios::binary);
    timsort(cat.data,cat.getSize(),comparison_breed);
    print(cat.data,cat.getSize(),out);
    out.close();

    out.open("food.txt",ios::binary);
    timsort(cat.data,cat.getSize(),comparison_food);
    print(cat.data,cat.getSize(),out);
    out.close();

    return 0;
}

int minrun(int size){
    int run = 0;
    while (size >= 64) {
        run |= size & 1;
        size >>= 1;
    }
    return size + run;
}

void print(cats *cat, int size, ofstream &out){
    for(int i = 0;i < size;++i){
        out << cat[i].index << " "
            << cat[i].name << " "
            << cat[i].age << " "
            << cat[i].breed << " "
            << cat[i].like_food << "\n";
    }
}

void insert_sort(cats *cat, int size, bool less(cats &cat1, cats &cat2)){
    for(int i = 1;i < size;++i){
        for(int j = i;j > 0;--j){
            if(less(cat[j],cat[j-1])){
                cats temp = cat[j-1];
                cat[j-1] = cat[j];
                cat[j] = temp;
            }
        }
    }
}

void merge_tim(Stack<array> stack, bool less(cats &cat1, cats &cat2)){
    if(stack.getSize() < 3){
        return;
    }
    array X = stack.pop();
    array Y = stack.pop();
    array Z = stack.pop();
    if((X.size > Y.size + Z.size) && Y.size > Z.size){
        stack.push(Z);
        stack.push(Y);
        stack.push(X);
        return;
    }
    if(X.size <= Z.size){
        merger(Y.cat,X.cat,Y.size,X.size,less);
        Y.size += X.size;
        stack.push(Z);
        stack.push(Y);
        merge_tim(stack,less);
    }
    else{
        merger(Y.cat,Z.cat,Y.size,Z.size,less);
        Y.size += Z.size;
        stack.push(X);
        stack.push(Y);
        merge_tim(stack,less);
    }
}

void merger(cats *cat1, cats *cat2, int size_cat1, int size_cat2, bool less(cats & _cat1, cats & _cat2)){
    cats *new_cat = new cats[size_cat1+size_cat2];
    int i1 = 0;
    int i2 = 0;
    for(int i = 0;i < size_cat1 + size_cat2;++i){
        if((i1 < size_cat1) && (i2 < size_cat2)){
            if(less(cat2[i2],cat1[i1])){
                new_cat[i] = cat2[i2++];
            }
            else{
               new_cat[i] = cat1[i1++];
            }
        }
        else {
            if(i1 < size_cat1){
                new_cat[i] = cat1[i1++];
            }
            else if(i2 < size_cat2){
                new_cat[i] = cat2[i2++];
            }

        }
    }
    for(int i = 0;i < size_cat1;++i){
        cat1[i] = new_cat[i];
    }
    for(int i = 0;i < size_cat2;++i){
        cat2[i+size_cat1] = new_cat[i];
    }
}

void timsort(cats *cat, int size, bool less(cats &cat1, cats &cat2)){
    if(size < 64){
        insert_sort(cat,size,less);
        return;
    }
    int minr = minrun(size);
    Stack<array> stack;
    int i = 0;
    while(i < size){
        if(size - i >= minr){
            array temp = {&cat[i],1};
            while((i + temp.size <size) && !less(cat[temp.size+i],cat[temp.size+i-1])){
                ++temp.size;
            }
            if(2 > temp.size){
                while((i + temp.size <size) && !less(cat[temp.size+i],cat[temp.size+i-1])){
                    ++temp.size;
                }
                for(int j = 0;j < (temp.size/2);++j){
                    cats temp_cat = temp.cat[j];
                    temp.cat[j] = temp.cat[temp.size-1-j];
                    temp.cat[temp.size-1-j] = temp_cat;
                }
            }
            if(temp.size < minr){
                temp.size = minr;
            }
            insert_sort(temp.cat,temp.size,less);
            stack.push(temp);
            merge_tim(stack,less);
            i+=temp.size;
        }
        else{
            array temp = {&cat[i],size - i};
            insert_sort(temp.cat,temp.size,less);
            stack.push(temp);
            merge_tim(stack,less);
            i+=temp.size;
        }
    }
    while(stack.getSize()>1){
        array X = stack.pop();
        array Y = stack.pop();
        merger(Y.cat,X.cat,Y.size,X.size,less);
        Y.size +=X.size;
        stack.push(Y);
    }
}
