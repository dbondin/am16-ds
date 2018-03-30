#include <iostream>
#include <string>
#include <cmath>

#include "stack.h"
#include "calc.h"


int main() 
{
	string exp ="(8-2)*2+3.5*4^2";
	cout << "Infix = " << exp << endl;
	string postfix = infixToPostfix(exp);
	cout << "Postfix = " << postfix << endl;
	calculate(postfix);
}
