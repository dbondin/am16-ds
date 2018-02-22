#include <fstream>
#include <stdio.h>
#include "table.h"
#include <iostream>

using namespace std;

int frequrent(int arr[1000]) {
    int count[256];
    int symbol;
    int i;
    for(i = 0; i < 256; i++) {
        count[i] = 0;
    }
    for(i = 0; i < 1000; i++) {
        if(arr[i] > 191) {
            count[arr[i]]++;
        }
    }
    for(i = 1; i < 256; i++) {
        if(count[i-1] < count[i]) {
            symbol = count[i];
        }
    }
    return symbol;
}

int identify_code(int arr[1000]) {
    int symbol = frequrent(arr);
    if(symbol == 238)         return 1251;
    else if(symbol == 207)    return 8;
    else                      return 0;
}

int* identify_way_of_decryptor(int source[1000], int way[4], int stop_flag) {
    if (stop_flag >= 3) return way;
    int key = identify_code(source);
    int i;
    if(key == 0) {
        int koi_to_win[1000];
        int win_to_koi[1000];
        int key_win;
        int key_koi;
        for(i = 0; i < 1000; i++) {
            koi_to_win[i] = koi8r_to_win1251[source[i]];
            win_to_koi[i] = win1251_to_koi8r[source[i]];
            stop_flag++;
        }
        key_win = identify_code(koi_to_win);
        key_koi = identify_code(win_to_koi);

        way[stop_flag] = 1251;
        way[3] = key_win;
        if(key_win == 8 || key_win == 1251) {
            return way;
        }
        else if(key_win == 0) {
            identify_way_of_decryptor(koi_to_win, way, stop_flag);
        }

        way[stop_flag] = 8;
        way[3] = key_koi;
        if(key_koi == 8 || key_koi == 1251) {
            return way;
        }
        else if(key_koi == 0) {
            identify_way_of_decryptor(win_to_koi, way, stop_flag);
        }
    }
    else if(key == 8 || key == 1251) {
        way[3] = key;
        return way;
    }

    way[3] = 0;
    return way;
}

void file(int key_code) {
    ifstream in("in.txt");
    ofstream in("out.txt");
    int symbol;
    while(in.good()) {
        symbol = in.get();
        if(key_code == 1251) {
             out.write((char*)(&koi8r_to_win1251[symbol]));
        }
        else if(key_code == 8) {
            out.write( (char*)(win1251_to_koi8r[symbol]));
        }
    }
    in.close();
    out.close();
    remove("in.txt");
    rename("out.txt","in.txt");
}

void file_to_utf(int key_code) {
    ifstream in("in.txt");
    ofstream in("out.txt");
    int symbol;
    while(in.good()) {
        symbol = fgetc(in);
        if(key_code == 1251) {
            out.write((char*)(&win1251_to_utf8[symbol][0]));
            out.write((char*)(&win1251_to_utf8[symbol][1]));
        }
        else if(key_code == 8) {
            out.write((char*)(&koi8r_to_utf8[symbol][0]));
            out.write((char*)(&koi8r_to_utf8[symbol][1]));
        }
     }
    fclose(in);
    fclose(out);
}

void decryptor(int arr[1000]) {
    int way[4];
    int stop_flag = 0;
    way = identify_way_of_decryptor(arr, way, stop_flag);
    int i;
    if(way[3] == 0) {
        cout << "Неизвестная кодировка" << endl;
        return;
    }
    for(i = 0; i < 3; i++) {
        file(way[i]);
    }
    file_to_utf(way[3]);
}



int main() {
    ifstream in("in.txt");
    int arr[1000];
    if(in.good()) {
        int i;
        for(i = 0; i < 1000; i++) {
            arr[i] = in.get();
        }
    }
    else return 0;
    close(in);

    decryptor(arr[1000]);
    return 1;
}
