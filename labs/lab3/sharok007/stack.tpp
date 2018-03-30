using namespace std;

template <typename T>
Stack<T>::Stack(int _size)
{
    size = _size;
    stack = new T[size];
    top = -1;//-1,чтобы stack начинался с 0
}


template <typename T>
Stack<T>::~Stack()
{
    delete [] stack;
}

template <typename T>
void Stack<T>::push(const T value)
{
    ++top;
    stack[top] = value; // помещаем элемент в стек
}

template <typename T>
bool Stack<T>::empty(){
    if(-1 == top){
        return true;
    }
    return false;

}

template <typename T>
bool Stack<T>::pop()
{
    if (-1 == top){
        return false; // стек пуст
    }
    stack[top]=0;
    --top;
    return true;
}

template <typename T>
void Stack<T>::printStack()
{
    for (int i = top;0<=i; --i)
        cout << stack[i] << endl;
}

template <typename T>
T Stack<T>::Top(){
    return stack[top];
}
