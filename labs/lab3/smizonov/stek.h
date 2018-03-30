#include <iostream>
#include <cmath>

using namespace std;


template <class d>
class stek {
   d *value;
   int number;
   int size;
     public:
     int get_num();
     int get_size();
     d pop();
     void push(d some);
     d show();
     d show(int n);
     stek(int size);
     stek();
     ~stek();
};

using namespace std;

template <class d>
int stek<d>::get_size()
{
    return size;
}

template <class d>
stek<d>::~stek()
{
    delete []value;
}


template <class d>
int stek<d>::get_num()
{
    return number;
}


template <class d>
stek<d>::stek(int siz)
{
   size=siz;
    value=new d[siz];
   number=0;
}

template <class d>
void stek<d>::push(d val)
{
   value[number]=val;
   number++;
}

template <class d>
d stek<d>::pop()
{

     number=number-1;
     return value[number];

}

template <class d>
d stek<d>::show()
{
   int t=number;
   t--;
    return value[t];
}

template <class d>
d stek<d>::show(int n)
{
   return value[n];
}

template <class d>
stek<d>::stek()
{
    prev=next=value=NULL;
    size=number=0;
}

