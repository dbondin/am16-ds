#include <iostream>
#include <fstream>
#include <stdio.h>
#include "translate_koi8.h"
#include "tables.h"

using namespace std;

void KOI8_to_UTF8() {
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
        out.write((char*)(&koi_to_utf[symbol][0]),sizeof(char));
      }
      else
      {
        out.write((char*)(&koi_to_utf[symbol][0]),sizeof(char));
        out.write((char*)(&koi_to_utf[symbol][1]),sizeof(char));
      }
    }
    in.close();
    out.close();
}

void file_KOI8_to_WIN1251() {
    ofstream out("text.txt", ios_base::binary);
    ifstream in("in.txt", ios_base::binary);
    unsigned int symbol;
    while(in.good())
    {
      symbol=in.get();
      if(in.eof())
          break;
      out.write((char*)(&koi_to_win[symbol]),sizeof(char));
    }
    in.close();
    out.close();
    remove("in.txt");
    rename("text.txt","in.txt");
}

void KOI8_to_WIN1251(vector<unsigned int> source, vector<unsigned int> &win) {
    int i;
    for(i = 0; i < source.size(); ++i) {
        win.push_back(koi_to_win[source[i]]);
    }
}
