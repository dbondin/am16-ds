#ifndef STACK_TPP
#define STACK_TPP
#include <stdexcept>

template<class T>
Stack<T>::Stack(){
    size = 0;
    capacity = 10;
    data = new T[capacity];
}

template<class T>
Stack<T>::~Stack(){
    delete[] data;
}

template<class T>
void Stack<T>::push(T new_data){
    if(size == capacity){
        expand();
    }
    data[size] = new_data;
    ++size;
}

template<class T>
T Stack<T>::top(){
    if(0 == size){
        throw std::underflow_error("Стэк пустой");
    }
    return data[size - 1];
}

template<class T>
T Stack<T>::pop(){
    if(0 == size){
        throw std::underflow_error("Нечего удалять,стэк пустой");
    }
    return data[--size];
}

template<class T>
void Stack<T>::expand(){
    capacity *=2;
    T *temp = new T[capacity];
    for(int i = 0;i < size;++i){
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
}

template<class T>
int Stack<T>::getSize(){
    return size;
}

#endif // STACK_TPP

