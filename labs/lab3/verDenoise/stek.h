template <typename T>
class stek
{
private:
    T *data;
    int size;
public:
    stek(int _size);
    T pop();
    T top();
    bool IsEmpty();
    void push(T value);
    ~stek();
};
template <typename T>
stek<T>::stek(int _size)
{
    data = new T[_size];
    size = 0;
}

template <typename T>
stek<T>::~stek()
{
    delete []data;
}
template <typename T>
T stek<T>::pop()
{
   if (size == 0){
        return false;
   }
   else {
       return data[--size];
   }
}
template <typename T>
T stek<T>::top()
{
    return data[size];
}
template <typename T>
bool stek<T>::IsEmpty()
{
    if(size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
template <typename T>
void stek<T>::push(T value)
{
    data[++size] = value;
}
