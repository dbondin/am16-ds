#include "stack.h"

int Priority(char znak)
{
	int prior = 0; 
	switch(znak)
	{
	case '+':
	case '-':
		prior = 1;
    break;
	case '*':
	case '/':
        prior = 2;
	}
	return prior;
}

int Use_priority(char sym1, char sym2)
{
	int sym1Prior = Priority(sym1);
	int sym2Prior = Priority(sym2);
	return sym1Prior >= sym2Prior ?  true: false;
}

