#include <string>
#include <iostream>
#include <fstream>
#include "cat.h"

using namespace std;

int get_minrun(int n) {
    int r = 0;           // станет 1 если среди сдвинутых битов будет хотя бы 1 ненулевой
    while (n >= 64) {
        r |= n & 1;
            n >>= 1;
    }
    return n + r;
}

//1 vs 2
bool comparing(cat cat1, cat cat2, properties ch) {
    switch(ch) {
        case ID: {
            if(cat1.get_id() > cat2.get_id())       return true;
            else                                    return false;
            break;
        }
        case AGE: {
            if(cat1.get_age() > cat2.get_age())       return true;
            else                                      return false;
            break;
        }
        case NAME: {
            if(cat1.get_name().compare(cat2.get_name()) > 0)        return true;
            else                                                    return false;
            break;
        }
        case BREED: {
            if(cat1.get_breed().compare(cat2.get_breed()) > 0)        return true;
            else                                                      return false;
            break;
        }
        case FOOD: {
            if(cat1.get_food().compare(cat2.get_food()) > 0)        return true;
            else                                                    return false;
            break;
        }
    }
}

void insertion_sort(cat *cats, int start, int end, properties comp){
    for(int i=start+1; i<end+1; ++i) {
        cat temp = cats[i];
        int j;
        for(j = i-1; j >= start && (comparing(cats[j], temp, comp)); --j) {
            cats[j+1] = cats[j];
        }
        cats[j+1] = temp;
    }
}

void merge(cat * cats, int begin_of_first_minrun, int end_of_first_minrun, int begin_of_second_minrun, int end_of_second_minrun, properties comp) {
    int first, second;
    cat temp[end_of_first_minrun - begin_of_first_minrun + 1];

    for(first = begin_of_first_minrun, second = 0; first < end_of_first_minrun+1; ++second, ++first)	{
        temp[second] = cats[first];
    }

    first = begin_of_first_minrun;
    second = begin_of_second_minrun;
    int k = 0;
    while((k < (end_of_first_minrun - begin_of_first_minrun + 1) ) && (second < (end_of_second_minrun+1))) {
        if(comparing(temp[k], cats[second], comp)) cats[first++] = cats[second++];
        else                                       cats[first++] = temp[k++];
    }

    while(k < end_of_first_minrun - begin_of_first_minrun + 1) {
        cats[first++] = temp[k++];
    }

    while(second < (end_of_second_minrun+1)) {
        cats[first++] = cats[second++];
    }
}

void timsort(cat *cats, int numb_of_cats, properties comp) {
    if(numb_of_cats < 64) {
        insertion_sort(cats, 0, numb_of_cats-1, comp);
        return;
    }
    int minrun = get_minrun(numb_of_cats);
    for(int i = 0; i < numb_of_cats; i += minrun) 	{
        insertion_sort(cats, i, ( (i+minrun-1) < (numb_of_cats-1) ? (i+minrun-1) : (numb_of_cats-1)), comp);
    }

    while(minrun < numb_of_cats) {
        for(int i = 0; i < numb_of_cats; i += 2*minrun) {
            merge(cats, i, i+minrun-1, i+minrun, (i+2*minrun-1 < numb_of_cats-1 ? i+2*minrun-1 : numb_of_cats-1), comp);
        }
        minrun = 2*minrun;
    }
}

void print_in_file(string filename, cat *cats, int numb_of_cats) {

    ofstream out(filename, ios_base::trunc);
    out << numb_of_cats;
    for(int i = 0; i < numb_of_cats; ++i) {
        out << cats[i].get_id()    << " "
            << cats[i].get_name()  << " "
            << cats[i].get_age()   << " "
            << cats[i].get_breed() << " "
            << cats[i].get_food()  << std::endl;
    }
    out.close();
}

void init(string filename, cat *cats, int numb_of_cats) {
    ifstream in(filename);
    string buff;
    int temp;
    for(int i = 0; i < numb_of_cats; ++i) {
        in >> temp;
        cats[i].set_id(temp);
        getline(in, buff, ' ');
        cats[i].set_name(buff);
        in >> temp;
        cats[i].set_age(temp);
        getline(in, buff, ' ');
        cats[i].set_breed(buff);
        getline(in, buff, ' ');
        cats[i].set_food(buff);
    }
}

int main() {
    ifstream in("zoo.txt");
    int numb_of_cats;
    in >> numb_of_cats;
    in.close();

    cat * cats = new cat[numb_of_cats];
    init("zoo.txt", cats, numb_of_cats);

    timsort(cats, numb_of_cats, ID);
    print_in_file("id_cats.txt",cats, numb_of_cats);

    timsort(cats, numb_of_cats, NAME);
    print_in_file("name_cats.txt" ,cats, numb_of_cats);

    timsort(cats, numb_of_cats, AGE);
    print_in_file("age_cats.txt" ,cats, numb_of_cats);

    timsort(cats, numb_of_cats, BREED);
    print_in_file("breed_cats.txt", cats, numb_of_cats);

    timsort(cats, numb_of_cats, FOOD);
    print_in_file("food_cats.txt", cats, numb_of_cats);

    delete [] cats;
    in.close();
    return 0;
}

