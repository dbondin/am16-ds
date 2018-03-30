#include "Stack_number.h"


Stack_number::Stack_number(int n)
{
	size=n;
	mem= new float[n];
	ind=-1;
}

bool Stack_number::IsEmpty()
{
	return (ind<=-1);
}

bool Stack_number::IsFull()
{
	return (ind>=size-1);
}

void Stack_number::push(float v)
{
	if (IsFull()) cout<<"Стек полный,нельзя вставить элемент";
	ind++;
	mem[ind]=v;
}

float Stack_number::pop()
{
	if (IsEmpty()) cout<<"Стек пуст,нельзя извлечь элемент";
	ind--;
	return mem[ind+1];
}

float Stack_number::GiveValue()
{
	return mem[ind];
}

void Stack_number::Print()
{
	for (int i=ind;i>=0;i--)
		cout<<mem[i];
	cout<<endl;	
}

Stack_number::~Stack_number(void)
{
	delete []mem;
}
