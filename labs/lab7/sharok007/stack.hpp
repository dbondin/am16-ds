#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>

template<class T>
class Stack{
private:
    int size;
    int capacity;
    void expand();
public:
    T *data;
    Stack();
    ~Stack();
    T top();
    T pop();
    void push(T new_data);
    int getSize();
};


#include "stack.tpp"
#endif // STACK_HPP

