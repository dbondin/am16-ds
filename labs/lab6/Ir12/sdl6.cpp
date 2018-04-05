#include <iostream>
#include <fstream>
#include <string>
#include "sdl6.h"
using namespace std;

#define CURRENCIES 18

void build ();
void findt1 ();
void findt2 ();
money * getmoney (ifstream & in);

int main ()
{

	findt1 ();
	findt2 ();
	return 0;
}

money * getmoney (ifstream & in)
{
	money * newmoney = new money;

	int day = 0;
	int month = 0;
	int year = 0;

	char c;
	for (int i = 0; i < 2; ++i) 
	{
		in.get (c);
		day = day * 10 + c - '0';
	}
	in.get(c);
	for (int i = 0; i < 2; ++i) 
	{
		in.get (c);
		month = month * 10 + c - '0';
	}
	in.get(c);
	for (int i = 0; i < 4; ++i) 
	{
		in.get (c);
		year = year * 10 + c - '0';
	}
	in.get(c);

	newmoney->date = year * 10000 + month * 100 + day;

	getline (in, newmoney->name, ' ');
	in >> newmoney->rubl;
	in >> newmoney->sym;
	getline (in, newmoney->fullname, '\n');
	newmoney->rate = newmoney->sym / (double)newmoney->rubl;

	return newmoney;
}

void build ()
{
	ifstream in ("input.txt", ifstream::binary);
	btree<int, money *> * roots1[CURRENCIES];
	btree<double, money *> * roots2[CURRENCIES];
	for (int i = 0; i < CURRENCIES; ++i) 
	{
		roots1[i] = NULL;
		roots2[i] = NULL;
	}

	char c;
	while (in.get (c)) 
	{
		in.putback (c);
		for (int i = 0; i < CURRENCIES; ++i) 
		{
			money * mon = getmoney (in);
			if (roots1[i]) 
			{
				roots1[i]->add (mon->date, mon);
				roots1[i]->loadmyself ();
				if (roots1[i]->haveparent ()) 
				{ 
					btree <int, money *> * temp = roots1[i];
					roots1[i] = roots1[i]->loadparent (); 
					delete temp;
				}
			}
			else 
			{
				roots1[i] = new btree<int, money *> (mon->date, mon, mon->name + "_date");
			}

			if (roots2[i]) 
			{
				roots2[i]->add (mon->rate, mon);
				if (roots2[i]->haveparent ()) 
				{ 
					btree <double, money *> * temp = roots2[i];
					roots2[i] = roots2[i]->loadparent (); 
					delete temp;
				}
			}
			else 
			{
				roots2[i] = new btree<double, money *> (mon->rate, mon, mon->name + "_rate");
			}
		}
	} 


	ofstream out;
	for (int i = 0; i < CURRENCIES; ++i) 
	{
		if (roots1[i]) 
		{
			string filename = roots1[i]->wayname + "\\root.txt";
			out.open (filename.data (), ofstream::binary);
			out << roots1[i]->mylabel;
			out.close ();
			delete roots1[i];
		}
		if (roots2[i]) 
		{
			string filename = roots2[i]->wayname + "\\root.txt";
			out.open (filename.data (), ofstream::binary);
			out << roots2[i]->mylabel;
			out.close ();
			delete roots2[i];
		}
	}

	in.close ();
}

void findt1 ()
{
	ifstream in ("AUD_date\\root.txt", ifstream::binary);
	int rootlabel;
	in >> rootlabel;
	in.close ();

	btree<int, money *> * root = new btree<int, money *> ((string)"AUD_date", rootlabel, 0);
	root->loadmyself ();

	ofstream out ("output.txt", ofstream::binary);
	root->findfrom (out, 20070101, root->nokey ());
	delete root;
	out.close ();
}

void findt2 ()
{
	ifstream in ("AUD_date\\root.txt", ifstream::binary);
	int rootlabel;
	in >> rootlabel;
	in.close ();

	btree<int, money *> * root = new btree<int, money *> ((string)"AUD_date", rootlabel, 0);
	root->loadmyself ();

	ofstream out ("output2.txt", ofstream::binary);
	root->findfrom (out, 20070101, 20070103);
	delete root;
	out.close ();
}
