#include "Stack_sign.h"


Stack_sign::Stack_sign(int n)
{
	size=n;
	mem= new int[n];
	ind=-1;
}

bool Stack_sign::IsEmpty()
{
	return (ind<=-1);
}

bool Stack_sign::IsFull()
{
	return (ind>=size-1);
}

void Stack_sign::push(int v)
{
	if (IsFull()) cout<<"Стек полный,нельзя вставить элемент";
	ind++;
	mem[ind]=v;
}

int Stack_sign::pop()
{
	if (IsEmpty()) cout<<"Стек пуст,нельзя извлечь элемент";
	ind--;
	return mem[ind+1];
}

int Stack_sign::GiveValue()
{
	return mem[ind];
}

void Stack_sign::Print()
{
	cout<<"Stack_operation:  ";
	for (int i=ind;i>=0;i--)
		cout<<mem[i];
	cout<<endl;	
}

Stack_sign::~Stack_sign(void)
{
	delete []mem;
}
