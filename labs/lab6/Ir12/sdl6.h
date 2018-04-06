#pragma once
#include "sdl6btree.h"
#include <string>
using namespace std;

struct money 
{
	int date;
	string name;
	int rubl;
	double sym;
	string fullname;
	double rate;
};
bool btree<double, money *>::little (double key1, double key2) 
{
	return (key2 - key1 < 1e-150)? true : false;
}

double btree<double, money *>::nokey ()
{
	return -1.5e308;
};


money * btree<double, money *>::novalue ()
{
	return NULL;
}

double btree<double, money *>::readkey (ifstream & in)
{
	double result;
	in >> result;
	return result;
}

money * btree<double, money *>::readvalue (ifstream & in)
{
	money * newmoney = new money;

	in >> newmoney->date;
	char c;
	in.get(c);
	getline (in, newmoney->name, ' ');
	in >> newmoney->rubl;
	in >> newmoney->sym;
	in.get(c);
	getline (in, newmoney->fullname, '\n');
	newmoney->rate = newmoney->sym / (double)newmoney->rubl;

	return newmoney;
}

void btree<double, money *>::writekey (ofstream & out, double key)
{
	out << key;
}

void btree<double, money *>::writevalue (ofstream & out, money * value)
{
	out << value->date;
	out << " ";
	out << value->name.data ();
	out << " ";
	out << value->rubl;
	out << " ";
	out << value->sym;
	out << " ";
	out << value->fullname;
}



bool btree<int, money *>::little (int key1, int key2) 
{
	return (key1 < key2)? true : false;
}

int btree<int, money *>::nokey ()
{
	return -1;
};


money * btree <int, money *>::novalue ()
{
	return NULL;
}
int btree <int, money *>::readkey (ifstream & in)
{
	int result;
	in >> result;
	return result;
}

money * btree <int, money *>::readvalue (ifstream & in)
{
	money * newmoney = new money;

	in >> newmoney->date;
	char c;
	in.get(c);
	getline (in, newmoney->name, ' ');
	in >> newmoney->rubl;
	in >> newmoney->sym;
	in.get(c);
	getline (in, newmoney->full_name, '\n');
	newmoney->rate = newmoney->sym / (double)newmoney->rubl;

	return newmoney;
}


void btree<int, money *>::writekey (ofstream & out, int key)
{
	out << key;
}

void btree<int, money *>::writevalue (ofstream & out, money * value)
{
	out << value->date;
	out << " ";
	out << value->name.data ();
	out << " ";
	out << value->rubl;
	out << " ";
	out << value->sym;
	out << " ";
	out << value->fullname;
}
