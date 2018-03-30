#pragma once
#include <iostream>
#include "Ochered.h"

using namespace std;

class Stack_number
{
	float *mem;
	int size;
	int ind;
public:
	Stack_number(int n);
	bool IsFull();
	bool IsEmpty();
	void push(float v);
	float pop();
	float GiveValue();
	void Print();
	~Stack_number(void);
};

