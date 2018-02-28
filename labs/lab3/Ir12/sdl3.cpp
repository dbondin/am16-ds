#include<iostream>
#include<string>
#include"stek.h"

int priorityop(char operation1, char operation2);
string transformation(string primer);
void operate(string str);

int main() 
{
	string primers; 
	cout<<"Введите выражение:"<<endl;
	cin>> primers;
	string primer=primers; 
	cout<<"Вы ввели выражение= "<<primers<<endl;
	string postf = transformation(primer);
	cout<<"В постфиксной записи это выражение = "<<postf<<endl;
	cout<<"Результат вычислений = ";
	operate(postf);
    
}





