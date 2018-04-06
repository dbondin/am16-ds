#pragma once
#include "btree.h"
#include <string>

struct currency {
	int date;
	std::string name;
	int rub_amount_equals;
	double curr_amount_equals;
	std::string full_name;
	double rate;
};

bool bnode<double, currency *>::less (double key1, double key2) // rate
{
	return (key2 - key1 < 1e-150)? true : false;
}

double bnode<double, currency *>::no_key ()
{
	return -1.5e308;
};


currency * bnode<double, currency *>::no_value ()
{
	return NULL;
}

double bnode<double, currency *>::read_key (std::ifstream & in)
{
	double result;
	in >> result;
	return result;
}

currency * bnode<double, currency *>::read_value (std::ifstream & in)
{
	currency * new_currency = new currency;

	in >> new_currency->date;
	char c;
	in.get(c);
	std::getline (in, new_currency->name, ' ');
	in >> new_currency->rub_amount_equals;
	in >> new_currency->curr_amount_equals;
	in.get(c);
	std::getline (in, new_currency->full_name, '\n');
	new_currency->rate = new_currency->curr_amount_equals / (double)new_currency->rub_amount_equals;

	return new_currency;
}


void bnode<double, currency *>::write_key (std::ofstream & out, double key)
{
	out << key;
}

void bnode<double, currency *>::write_value (std::ofstream & out, currency * value)
{
	out << value->date;
	out << " ";
	out << value->name.data ();
	out << " ";
	out << value->rub_amount_equals;
	out << " ";
	out << value->curr_amount_equals;
	out << " ";
	out << value->full_name;
}

///////////////////////////////////////////////////////////////////

bool bnode<int, currency *>::less (int key1, int key2) // rate
{
	return (key1 < key2)? true : false;
}

int bnode<int, currency *>::no_key ()
{
	return -1;
};


currency * bnode<int, currency *>::no_value ()
{
	return NULL;
}

int bnode<int, currency *>::read_key (std::ifstream & in)
{
	int result;
	in >> result;
	return result;
}

currency * bnode<int, currency *>::read_value (std::ifstream & in)
{
	currency * new_currency = new currency;

	in >> new_currency->date;
	char c;
	in.get(c);
	std::getline (in, new_currency->name, ' ');
	in >> new_currency->rub_amount_equals;
	in >> new_currency->curr_amount_equals;
	in.get(c);
	std::getline (in, new_currency->full_name, '\n');
	new_currency->rate = new_currency->curr_amount_equals / (double)new_currency->rub_amount_equals;

	return new_currency;
}


void bnode<int, currency *>::write_key (std::ofstream & out, int key)
{
	out << key;
}

void bnode<int, currency *>::write_value (std::ofstream & out, currency * value)
{
	out << value->date;
	out << " ";
	out << value->name.data ();
	out << " ";
	out << value->rub_amount_equals;
	out << " ";
	out << value->curr_amount_equals;
	out << " ";
	out << value->full_name;
}