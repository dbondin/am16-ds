#include<iostream>
#include<string>
 
using namespace std;
template <typename s>
class stack
{
	public:
	int size;
	s *st; 
	stack(int size);
	~stack();
	void push(const s);
	s pop();
	s top();	
	bool empty();



};
template <typename s>

stack<s>::stack(int size1)
{
	st = new s[size1]; 
	size=0;
}
template <typename s>
stack<s>::~stack()
{
    delete [] st; 
}
template <typename s>
void stack<s>::push(s x)
{
    st[++size] = x; 
}
template <typename s>
s stack<s>::pop()
{
   if (size == 0)
        return 0; 
   return st[--size] ;  
}

template <typename s>
s stack<s>::top()
{
  return st[size];
}


template <typename s>
bool stack<s>::empty()
{
  if(size==0)
  return 1;
         else return 0;
}

