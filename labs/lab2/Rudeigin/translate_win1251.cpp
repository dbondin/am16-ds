#include <iostream>
#include <fstream>
#include <stdio.h>
#include "translate_win1251.h"
#include "tables.h"

using namespace std;

void WIN1251_to_UTF8() {
    ofstream out("text_utf8.txt", ios_base::binary);
    ifstream in("in.txt", ios_base::binary);
    unsigned int symbol;
    while(in.good())
    {
      symbol=in.get();
      if(in.eof())
          break;
      if(symbol < 128)
      {
        out.write((char*)(&win_to_utf[symbol][0]),sizeof(char));
      }
      else
      {
        out.write((char*)(&win_to_utf[symbol][0]),sizeof(char));
        out.write((char*)(&win_to_utf[symbol][1]),sizeof(char));
      }
    }
    in.close();
    out.close();
}

void file_WIN1251_to_KOI8() {
    ofstream out("text.txt", ios_base::binary);
    ifstream in("in.txt", ios_base::binary);
    unsigned int symbol;
    while(in.good())
    {
      symbol=in.get();
      if(in.eof())
          break;
      out.write((char*)(&win_to_koi[symbol]),sizeof(char));
    }
    in.close();
    out.close();
    remove("in.txt");
    rename("text.txt","in.txt");
}

void WIN1251_to_KOI8(vector<unsigned int> source, vector<unsigned int> &koi) {
    int i;
    for(i = 0; i < source.size(); ++i) {
        koi.push_back(win_to_koi[source[i]]);
    }
}
