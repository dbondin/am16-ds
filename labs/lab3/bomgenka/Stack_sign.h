#pragma once
#include <iostream>
#include "Ochered.h"

using namespace std;

class Stack_sign
{
	int *mem;
	int size;
	int ind;
public:
	Stack_sign(int n);
	bool IsFull();
	bool IsEmpty();
	void push(int v);
	int pop();
	int GiveValue();
	void Print();
	~Stack_sign(void);
};

