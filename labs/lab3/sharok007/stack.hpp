#ifndef STACK_HPP
#define STACK_HPP

#include<iostream>

using namespace std;

template <typename T>
class Stack
{
private:
    T *stack;
    int size; // размер стека
    int top; // вершина стека
public:
    Stack(int _size);
    ~Stack();
    void push(const T); // поместить элемент в стек
    bool pop(); // удалить из стека элемент
    void printStack();
    bool empty();
    T Top();
};

#endif // STACK_HPP
#include "stack.tpp"
