#include <iostream>
#include <fstream>
#include <string>
#include "currency.h"

#define CURRENCIES 18

void build_all_indexes ();
void search_test ();
void search_test2 ();
currency * get_currency (std::ifstream & in);

int main ()
{
	// Под каждую тварь нужна отдельная папка вида AUD_date или AUD_rate, где AUD - название валюты, иначе файлы не создаются
	// Просто сделаем вид, что они есть.

	// Вход просить не хотим, тем более строить нужно только один раз, поэтому если нужно, комментим test и разкомментим build
	// По идее можно запросто добавлять свежие данные в уже построенное дерево, если заменить input.txt файлом с правильным форматом 
	// (строго 18 валют, упорядоченно по дате без перемешивания и отсутствующий строк)
	// --- part1 ---
	//build_all_indexes ();
	// --- end   ---

	// --- part2 ---
	search_test ();
	search_test2 ();
	// --- end   ---

	return 0;
}

currency * get_currency (std::ifstream & in)
{
	currency * new_currency = new currency;

	int dd = 0;
	int mm = 0;
	int yyyy = 0;

	char c;
	for (int i = 0; i < 2; ++i) {
		in.get (c);
		dd = dd * 10 + c - '0';
	}
	in.get(c);
	for (int i = 0; i < 2; ++i) {
		in.get (c);
		mm = mm * 10 + c - '0';
	}
	in.get(c);
	for (int i = 0; i < 4; ++i) {
		in.get (c);
		yyyy = yyyy * 10 + c - '0';
	}
	in.get(c);

	new_currency->date = yyyy * 10000 + mm * 100 + dd;

	std::getline (in, new_currency->name, ' ');
	in >> new_currency->rub_amount_equals;
	in >> new_currency->curr_amount_equals;
	std::getline (in, new_currency->full_name, '\n');
	new_currency->rate = new_currency->curr_amount_equals / (double)new_currency->rub_amount_equals;

	return new_currency;
}

void build_all_indexes ()
{
	std::ifstream in ("input.txt", std::ifstream::binary);
	bnode<int, currency *> * roots1[CURRENCIES];
	bnode<double, currency *> * roots2[CURRENCIES];
	for (int i = 0; i < CURRENCIES; ++i) {
		roots1[i] = NULL;
		roots2[i] = NULL;
	}

	char c;
	while (in.get (c)) {
		in.putback (c);
		for (int i = 0; i < CURRENCIES; ++i) {
			currency * curr = get_currency (in);
			if (roots1[i]) {
				roots1[i]->insert (curr->date, curr);
				roots1[i]->load_myself ();
				if (roots1[i]->has_parent ()) { // храним только рутов
					bnode <int, currency *> * temp = roots1[i];
					roots1[i] = roots1[i]->load_parent (); 
					delete temp;
				}
			}
			else {
				roots1[i] = new bnode<int, currency *> (curr->date, curr, curr->name + "_date");
			}

			if (roots2[i]) {
				roots2[i]->insert (curr->rate, curr);
				if (roots2[i]->has_parent ()) { // храним только рутов
					bnode <double, currency *> * temp = roots2[i];
					roots2[i] = roots2[i]->load_parent (); 
					delete temp;
				}
			}
			else {
				roots2[i] = new bnode<double, currency *> (curr->rate, curr, curr->name + "_rate");
			}
		}
	} // читаем все, пихаем в наши 36 индексов (18 по дате, 18 по курсу)


	std::ofstream out;
	for (int i = 0; i < CURRENCIES; ++i) {
		if (roots1[i]) {
			std::string filename = roots1[i]->directory_name + "\\root.txt";
			out.open (filename.data (), std::ofstream::binary);
			out << roots1[i]->my_tag; // записываем коды всех рутов
			out.close ();
			delete roots1[i];
		}
		if (roots2[i]) {
			std::string filename = roots2[i]->directory_name + "\\root.txt";
			out.open (filename.data (), std::ofstream::binary);
			out << roots2[i]->my_tag; // записываем коды всех рутов
			out.close ();
			delete roots2[i];
		}
	}

	in.close ();
}

void search_test ()
{
	std::ifstream in ("AUD_date\\root.txt", std::ifstream::binary);
	int root_tag;
	in >> root_tag;
	in.close ();

	bnode<int, currency *> * root = new bnode<int, currency *> ((std::string)"AUD_date", root_tag, 0);
	root->load_myself ();

	std::ofstream out ("output.txt", std::ofstream::binary);
	root->search_from_to (out, 20070101, root->no_key ());
	delete root;
	out.close ();
}

void search_test2 ()
{
	std::ifstream in ("AUD_date\\root.txt", std::ifstream::binary);
	int root_tag;
	in >> root_tag;
	in.close ();

	bnode<int, currency *> * root = new bnode<int, currency *> ((std::string)"AUD_date", root_tag, 0);
	root->load_myself ();

	std::ofstream out ("output2.txt", std::ofstream::binary);
	root->search_from_to (out, 20070101, 20070103);
	delete root;
	out.close ();
}
