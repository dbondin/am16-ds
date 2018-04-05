#ifndef CATS_H
#define CATS_H
#include <iostream>
using namespace std;


//Realization


template <class T>
class stackhere{
public:
    stackhere();
    ~stackhere();
    void push(T value);
    T pop();
    T top();
    int size();
    stackhere & operator<<(T value);
    stackhere & operator>>(T value);
    T * m_data;
private:
    void expand();

    int m_size;
    int m_capacity;
};
template <class T>
stackhere<T>::stackhere()
{
    m_size = 0;
    m_capacity = 8;
    m_data = new T[m_capacity];
}

template <class T>
stackhere<T>::~stackhere()
{
    delete[] m_data;
}

template <class T>
void stackhere<T>::push(T value)
{
    if (m_size == m_capacity) {
        expand ();
    }
    m_data[m_size] = value;
    ++m_size;
}

template <class T>
T stackhere<T>::pop()
{
    if (0 == m_size) {
        cout<<"Perepolneno"<<endl;
    }
    return m_data[--m_size];
}

template <class T>
T stackhere<T>::top()
{
    if (0 == m_size) {
        cout<<"Perepolneno"<<endl;

    }
    return m_data[m_size - 1];
}

template <class T>
int stackhere<T>::size()
{
    return m_size;
}

template <class T>
void stackhere<T>::expand()
{
    m_capacity *= 2;
    T * new_data = new T[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        new_data[i] = m_data[i];
    }
    delete[] m_data;
    m_data = new_data;
}

template <class T>
stackhere<T>&stackhere<T>::operator<<(T value)
{
    push (value);
    return *this;
}

template <class T>
stackhere<T>&stackhere<T>::operator>>(T value)
{
    value = pop ();
    return *this;
}

using namespace std;
struct cat {
    int id;
     string name;
    int age;
     string breed;
     string food;
};

struct massiv {
    cat * ptr;
    int size;
};






int run(int size);
void sort (cat * cats, int size, bool less (cat & cat1, cat & cat2));
void merge (cat * cats1, cat * cats2, int size1, int size2, bool less (cat & cat1, cat & cat2));
void timsort (cat * cats, int size, bool less (cat & cat1, cat & cat2));
void check(stackhere<massiv> stack, bool less (cat & cat1, cat & cat2));
void print_cats ( ofstream & out, cat * cats, int size);



int run(int size)
{
    int flag = 0;
    while (size >= 64) {
        flag |= size & 1;
        size >>= 1;
    }
    return size + flag;
}

void sort (cat * cats, int size, bool less (cat & cat1, cat & cat2))
{
    for (int i = 0; i < size; ++i) {
        for (int j = i; j > 0; --j) {
            if (less (cats[i], cats[i - 1])) {
                cat temp = cats[i - 1];
                cats[i - 1] = cats[i];
                cats[i] = temp;
            }
        }
    }
}

void merge (cat * cats1, cat * cats2, const int size1, const int size2, bool less (cat & cat1, cat & cat2))
{
    int size = (size1 < size2)? size1 : size2;
    cat *newcats = new cat[size1 + size2];
    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < size1 + size2; ++i) {
        if ((i1 < size1) && (i2 < size2)) {
            if (less (cats2[i2], cats1[i1])) {
                newcats[i] = cats2[i2++];
            }
            else {
                newcats[i] = cats1[i1++];
            }
        }
        else {
            if (i1 < size1) {
                newcats[i] = cats1[i1++];
            }
            else if (i2 < size2) {
                newcats[i] = cats2[i2++];
            }
        }
    }

    for (int i = 0; i < size1; ++i) {
        cats1[i] = newcats[i];
    }
    for (int i = 0; i < size2; ++i) {
        cats2[i + size1] = newcats[i];
    }
}

void timsort (cat * cats, int size, bool less (cat & cat1, cat & cat2))
{
    if (size < 64) {
        sort (cats, size, less);
        return;
    }
    int minrun = run(size);


    stackhere<massiv> stack;
    int i = 0;
    while (i < size) {
        if (size - i >= minrun) {

            massiv temp = {&cats[i], 1};
            while ((i + temp.size < size) && !less (cats[i + temp.size], cats[i + temp.size - 1])) {
                ++temp.size;
            }
            if (temp.size < 2) {
                while ((i + temp.size < size) && !less (cats[i + temp.size - 1], cats[i + temp.size])) {
                    ++temp.size;
                }
                for (int j = 0; j < temp.size/2; ++j) {
                    cat c = temp.ptr[j];
                    temp.ptr[j] = temp.ptr[temp.size - j - 1];
                    temp.ptr[temp.size - j - 1] = c;
                }
            }
            if (temp.size < minrun) {
                temp.size = minrun;
            }
            sort (temp.ptr, temp.size, less);

            stack.push(temp);
            check(stack, less);
            i += temp.size;
        }
        else {
            massiv temp = {&cats[i], size - i};
            sort (temp.ptr, temp.size, less);

            stack.push (temp);
            check(stack, less);
            i += temp.size;
        }
    }

    while (stack.size () > 1) {
        massiv mX = stack.pop ();
        massiv mY = stack.pop ();
        merge (mY.ptr, mX.ptr, mY.size, mX.size, less);
        mY.size += mX.size;
        stack.push (mY);
    }

    if (stack.pop ().size != size) {
        cout<<"Wrong"<<endl;
    }
}

void check(stackhere<massiv> stack, bool less (cat & cat1, cat & cat2))
{
    if (stack.size () < 3) {
        return;
    }
    massiv mX = stack.pop ();
    massiv mY = stack.pop ();
    massiv mZ = stack.pop ();
    if ((mX.size > mY.size + mZ.size) && (mY.size > mZ.size)) {
        stack.push (mZ);
        stack.push (mY);
        stack.push (mX);
        return;
    }
    if (mX.size <= mZ.size) {
        merge (mY.ptr, mX.ptr, mY.size, mX.size, less);
        mY.size += mX.size;
        stack.push (mZ);
        stack.push (mY);
        check(stack, less);
    }
    else {
        merge (mZ.ptr, mY.ptr, mZ.size, mY.size, less);
        mZ.size += mY.size;
        stack.push (mZ);
        stack.push (mX);
        check(stack, less);
    }
}

bool ageless (cat & cat1, cat & cat2)
{
    return (cat1.age < cat2.age)? true : false;
}

bool nameless (cat & cat1, cat & cat2)
{
    return (cat1.name.compare (cat2.name) < 0)? true : false;
}

bool breedless (cat & cat1, cat & cat2)
{
    return (cat1.breed.compare (cat2.breed) < 0)? true : false;
}

bool foodless (cat & cat1, cat & cat2)
{
    return (cat1.food.compare (cat2.food) < 0)? true : false;
}

void print_cats ( ofstream & out, cat * cats, int size)
{
    for (int i = 0; i < size; ++i) {
        out	<< cats[i].id << " "
            << cats[i].name.data() << " "
            << cats[i].age << " "
            << cats[i].breed.data() << " "
            << cats[i].food.data() << "\n";
    }
}
#endif // CATS_H
