#pragma once

using namespace std;

bool check_operand(char oper);
bool check_operator(char oper);
int priority(char oper);
int choise_priority(char oper1, char oper2);
string sourceToFinal(string exp);
void calculate(string input);


#include "calc.tpp"
