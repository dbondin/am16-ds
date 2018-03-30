#include <iostream>
#include <fstream>
#include <vector>
#include "translate_koi8.h"
#include "translate_win1251.h"

using namespace std;

/*
  * Берём значения 232-242 для win1251 и 201-211 для koi8.
  * В эти промежутки входят самые часто встречающиеся символы русского алфавита и среднее значение символов.
  * Среднее значение вычислялось по символам в маленьком регистре, т.к. они в обычном тексте встречаются чаще, чем заглавные.
  */
  int identify(vector<unsigned int> &in) {
    int i;
    int sum = 0;//сумма всех символов с 128 по 255
    int num = 0;//количество символов
    int average = 0;//среднее значение встретившихся в тексте символов

    for(i = 0; i < in.size(); ++i) {
        if(in[i] > 191 && in[i] < 256) {//cj 191 yfxbyf.ncz ,erds heccrjuj fkafdbnf
            sum += in[i];
            num++;
        }
    }
    average = sum/num;
    if(average > 231 && average < 243)      return 1251;//win1251
    else if(average > 200 && average < 212) return 8;//koi8
    else                                    return 0;//не известно
  }

vector<unsigned int> load() {
    vector<unsigned int> source;
    unsigned char symbol;
    int limit = 0;//будем считывать 1024 элементов, если файл меньше, то сколько есть. Для анализа этого достаточно.

    ifstream in("in.txt");
    while(in.good()) {
        in >> symbol;
        limit++;
        source.push_back((unsigned int)symbol);
        if (limit == 1024) break;
    }
    in.close();
    return source;
}

void decryptor(int way[3]) {
    int i;
    for(i = 0; i < 3; i++){
        if(way[i] == 1251)      file_KOI8_to_WIN1251();
        else if(way[i] == 8)    file_WIN1251_to_KOI8();
    }
}

int decode(vector<unsigned int> source, int (&win_way)[3], int num) {
    int key = identify(source);
    if(key == 8)
    {
        KOI8_to_UTF8();
        return 1;
   }
    else if(key == 1251)
    {
        WIN1251_to_UTF8();
        return 1;
    }
    if(num > 3) return 0;

    int win_key;
    int koi_key;
    vector<unsigned int> koi8;
    vector<unsigned int> win1251;
    int koi_way[3];

    KOI8_to_WIN1251(source, win1251);
    win_key = identify(win1251);
    win_way[num] = 1251;

    if(win_key == 8)
    {
        decryptor(win_way);
        KOI8_to_UTF8();
        return 1;
    }
    else if(win_key == 1251)
    {
        decryptor(win_way);
        WIN1251_to_UTF8();
        return 1;
    }
    else if(win_key == 0)
    {
        ++num;
        decode(win1251, win_way, num);
    }

    WIN1251_to_KOI8(source, koi8);
    koi_key = identify(koi8);
    koi_way[num] = 8;

    if(koi_key == 8)
    {
        decryptor(koi_way);
        KOI8_to_UTF8();
        return 1;
    }
    else if(koi_key == 1251)
    {
        decryptor(koi_way);
        WIN1251_to_UTF8();
        return 1;
    }
    else if(koi_key == 0)
    {
        decode(koi8, koi_way, num);
    }
}

int main() {
    vector<unsigned int> source = load();
    int way[3] = { 0, 0, 0 };
    decode(source, way, 0);
    return 0;
}
