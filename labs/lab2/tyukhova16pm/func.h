#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "tablici.h"
using namespace std;

    //funccia schetchik simvolov
    int opredelenie(int ashot[500]);
    
    //cp1251->utf8
    void win_utf();

    //koi8-r->utf8
    void koi8r_utf();
    
    //koi8-r->win1251
    void win_koi();
    
    //win1251->koi8-r
    void koi_win();
    
    //peredergivaet simvolu vsyakie
   int shatatel_simvolov(int ashot[500], char mass[3], int iterazia);


#endif // FUNC_H
