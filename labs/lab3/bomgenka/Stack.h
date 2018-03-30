#pragma once
#include <iostream>
#include "Ochered.h"

using namespace std;


class Stack
{
	Value *mem;
	int size;
	int ind;
public:
	Stack(int n);
	bool IsFull();
	bool IsEmpty();
	void push(float _v);
	float pop();
	void TakeType(my_type t);
	my_type GetType();
	void Print();
	~Stack(void);
};

