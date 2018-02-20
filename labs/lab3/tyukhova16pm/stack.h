#ifndef STACK_H
#define STACK_H
#include<iostream>
#include<string>
 
using namespace std;

//symb_oper.cpp
bool numb(char chislo);
bool symb(char znak);

//queue_work.cpp
int Priority(char znak);
int Use_priority(char sym1, char sym2);

//process.cpp 
string Replacement(string term);
void Proc(string ingoing);

template <typename S>
class Stack
{
private:
    S *ptr; 
    int size; 
public:
    Stack(int size);
    ~Stack(); 
    bool empty();
    void push(const S); 
    S pop(); 
    S top();
};

template <typename S>
Stack<S>::Stack(int full)
{
    ptr = new S[full]; 
    size=0;
}
 
template <typename S>
Stack<S>::~Stack()
{
    delete [] ptr; 
}
 
template <typename S>
void Stack<S>::push(S val)
{
    ptr[++size] = val; 
}

template <typename S>
S Stack<S>::pop()
{
   if (size == 0)
        return false; 
    return ptr[--size] ;  
}

template <typename S>
S Stack<S>::top()
{
  return ptr[size];
}


template <typename S>
bool Stack<S>::empty()
{
  if(size==0)
  return 1;
         else return 0;
}
#endif
