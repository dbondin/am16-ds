#include<iostream>
#include<string>
 
using namespace std;

template <typename t>
class stack
{
private:
    t *stackPtr; 
    int size; 
public:
    stack(int size);
    ~stack(); 
    bool empty();
    void push(const t); 
    t pop(); 
    t last();
};

template <typename t>
stack<t>::stack(int maxsize)
{
    stackPtr = new t[maxsize]; 
    size=0;
}
 

template <typename t>
stack<t>::~stack()
{
    delete [] stackPtr; 
}
 
template <typename t>
void stack<t>::push(t value)
{
    stackPtr[++size] = value; 
}

template <typename t>
t stack<t>::pop()
{
   if (size == 0)
        return 0; 
    return stackPtr[--size] ;  
}

template <typename t>
t stack<t>::last()
{
  return stackPtr[size];
}


template <typename t>
bool stack<t>::empty()
{
  if(size==0)
  return 1;
         else return 0;
}
