#ifndef TIMSORT_H
#define TIMSORT_H

#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>

using namespace std;

namespace cat
{
    // Константы для сортировки котов :)
    const int CatSortUnsort = 0;        // Без сортировки, как есть
    const int CatSortNumber = 1;        // Сортировка по номеру
    const int CatSortName   = 2;        // Сортировка по имени
    const int CatSortAge    = 3;        // Сортировка по возрасту
    const int CatSortBreed  = 4;        // Сортировка по породе
    const int CatSortFood   = 5;        // Сортировка по еде
}

// Структура описания кошки :)
struct CatInfo
{
    int     number;         // Номер
    string  name;           // Кличка
    int     age;            // Возраст
    string  breed;          // Порода
    string  food;           // Что ест

    // Конструктор по умолчанию
    CatInfo()
    {
        number = 0;
        name = "";
        age = 0;
        breed = "";
        food = "";
    }

    // Конструктор копирования по указателю
    CatInfo(CatInfo *v)
    {
        number = v->number;
        name = v->name;
        age = v->age;
        breed = v->breed;
        food = v->food;
    }

    ~CatInfo()
    {
        name.clear();
        breed.clear();
        food.clear();
    }

    int getIntProperty(int idx)
    {
        switch(idx)
        {
            case cat::CatSortNumber: return number;
            case cat::CatSortAge: return age;
        }
        return 0;
    }

    string getStrProperty(int idx)
    {
        switch(idx)
        {
            case cat::CatSortName: return name;
            case cat::CatSortBreed: return breed;
            case cat::CatSortFood: return food;
        }
        return "";
    }

    string toString(void)
    {
        char buffer[48];
        string outV = "";

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%d", number);

        outV = outV + buffer;
        outV = outV + ";" + name + ";";

        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "%d", age);

        outV = outV + buffer;
        outV = outV + ";" + breed + ";" + food;

        return outV;
    }
};

class TimSort
{
private:
    int _sortType;

    // Структура интервала
    struct segment
    {
        int beg;        // Индекс первого элемента
        int len;        // Длина интервала

        segment() { }
        segment(int b, int l) : beg(b), len(l) { }
    };

    const int dX = 1;
    const int dY = 2;
    const int dZ = 3;

public:
    TimSort() { };
    ~TimSort() { };

    int sortType(void) const { return _sortType; }
    void sortType(int v) { _sortType = v; }

    void sort(vector<CatInfo *> &mas);

private:
    // Вычисление минимального размера упорядоченной последовательности, должен быть в диапазоне (32,64]
    inline int getMainSize(int n)
    {
        auto r = 0;
        while(n >= 64)
        {
            n >>= 1;
            r |= n & 1;
        }
        return n + r;
    }

    void selectionSort(vector<CatInfo *> &mas, int beg, int last);
    void merge(vector<CatInfo *> &mas, vector<segment> &seg, bool isXY, vector<CatInfo *> &tmp);
    void try_merge(vector<CatInfo *> &mas, vector<segment> &seg, vector<CatInfo *> &tmp, bool is_merge = false);
    vector<CatInfo *>::iterator great(vector<CatInfo *>::iterator first, vector<CatInfo *>::iterator last, CatInfo *value);
};

#endif // TIMSORT_H
