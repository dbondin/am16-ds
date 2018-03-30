#pragma once
#include <iostream>

using namespace std;

//const int MAX_OCHERED_SIZE = 100;

    enum my_type
	{
		number,
		operation
	};

	struct Value
	{
		float  v;		
		my_type type;
	};


class Ochered
{
	Value *p;
	int si,ei,n;

	public:
	Ochered(int n);
	bool IsFull();
    bool IsEmpty();
	void push(float _v);
	my_type GetType();
	float pop();	
	void TakeType(my_type y);
	float GiveValue();
	void Print();
	~Ochered(void);
	// ввод-вывод
	//friend ostream &operator<<(ostream &ostr, const Ochered &bf);

   
};