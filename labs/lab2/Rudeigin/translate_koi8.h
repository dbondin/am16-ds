#ifndef TRANSLATE_KOI8
#define TRANSLATE_KOI8
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void KOI8_to_UTF8();
void file_KOI8_to_WIN1251();
void KOI8_to_WIN1251(vector<unsigned int> source, vector<unsigned int> &win);
#endif // TRANSLATE_KOI8

