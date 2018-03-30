#include "Stack.h"


Stack::Stack(int n)
{
	size=n;
	mem= new Value[n];
	ind=-1;
}

bool Stack::IsEmpty()
{
	return (ind<=-1);
}

bool Stack::IsFull()
{
	return (ind>=size-1);
}

void Stack::push(float _v)
{
	if (IsFull()) cout<<"Стек полный,нельзя вставить элемент";
	ind++;
	mem[ind].v=_v;
}

float Stack::pop()
{
	if (IsEmpty()) cout<< "Стек пуст,нельзя извлечь элемент";
	ind--;
	return mem[ind+1].v;
}

void Stack::TakeType(my_type t)
{
	mem[ind+1].type=t; ////////// не проверяла
}

my_type Stack::GetType()
{ 
	return mem[ind].type;
}

void Stack::Print()
{
	cout<<"Stack_pol_zap:  ";
	for (int i=ind;i>=0;i--)
		cout<<mem[i].v;
	cout<<endl;
}

Stack::~Stack(void)
{
	delete []mem;
}
