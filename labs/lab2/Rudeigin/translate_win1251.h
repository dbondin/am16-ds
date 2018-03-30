#ifndef TRANSLATE_WIN1251
#define TRANSLATE_WIN1251
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void WIN1251_to_UTF8();
void file_WIN1251_to_KOI8();
void WIN1251_to_KOI8(vector<unsigned int> source, vector<unsigned int> &koi);
#endif // TRANSLATE_WIN1251

