#include "Ochered.h"


Ochered::Ochered(int n)
{
	this->n=n;
	p=new Value[n]; 
	si=0;
	ei=0;
}

bool Ochered::IsEmpty()
{
	return (ei==si);
}

bool Ochered::IsFull()
{
	return (ei+1)%n==si;
}

void Ochered::push(float _v)
{
	if (IsFull()) cout<<"Î÷åðåäü çàïîëíåíà, îïåðàöèÿ push íåâîçìîæíà";
	p[ei].v=_v;
	ei=(ei+1)%n;
}

my_type Ochered::GetType()
{ 
	return p[si].type;
}

float Ochered::pop()
{
	if (IsEmpty()) cout<<"Î÷åðåäü ïóñòà, îïåðàöèÿ pop íåâîçìîæíà";
	si=(si+1)%n;
	return p[si-1].v;
}

Ochered::~Ochered(void)
{
	delete []p;
}

void Ochered::TakeType(my_type t)
{
	p[ei].type=t;                //ÓÑÒÀÍÀÂËÈÂÀÅÒ ÒÈÏ ÏÐÈÍÈÌÀÅÌÎÃÎ ÇÍÀ×ÅÍÈß.   
}

float Ochered::GiveValue()
{
	return p[si].v;
}

void Ochered::Print()
{
	for (int i=si; i!=ei; i=(i+1)%n) 
		if (p[i].type==number) cout<<p[i].v;
		else cout<<(char)p[i].v;
	cout<<endl;
}