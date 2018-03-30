#ifndef STACK
#define STACK

template <typename T>
class Stack {
private:
    T *stack_arr;
    int size;
public:
    Stack(int stack_size);
    ~Stack();

    T pop(); //удаление
    T peek();//получение верхнего элемента без удаления
    bool is_empty();//проверка на пустоту
    void push(const T); //добавление
};

//конструктор
template <typename T>
Stack<T>::Stack(int stack_size)
{
    stack_arr = new T[stack_size];
    size = 0;
}

//деструктор
template <typename T>
Stack<T>::~Stack() {
    delete [] stack_arr;
}

template <typename T>
T Stack<T>::pop() {
   if (size == 0)
        return false;
    return stack_arr[--size] ;
}

template <typename T>
T Stack<T>::peek() {
    return stack_arr[size];
}

template <typename T>
bool Stack<T>::is_empty() {
    if(size == 0) return 1;
    else          return 0;
}

template <typename T>
void Stack<T>::push(T value) {
    stack_arr[++size] = value;
}

#endif // STACK
