#include "stack.h"

bool symb(char znak)
{
	if(znak == '+' || znak == '-' || znak == '*' || znak == '/')
		return true;
 
	return false;
}

bool numb(char chislo) 
{
	if(chislo >= '0' && chislo <= '9') return true;

	return false;
}
 

