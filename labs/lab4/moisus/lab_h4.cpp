#include <iostream>
#include <fstream>
#include <sstream>
#include "bin_tree.h"

using namespace std;
const int SYMBOLS = 256;

int num_mznach (Node ** forest);
Node *build_htree(int *per);
void huff_codes(Node *huffcodes, string *codes, string znach_code = "");
void write_znach(ofstream &out, string & leftznach, string znach_code);
Node *uncode_znach(Node *hufftree, string sequence);
string readByte(ifstream &in);
void uncode_text(ifstream &in, ofstream &out, Node *huffman_tree, string *codes);
void pack();
void unpack();

int num_mznach (Node ** forest) 
{
	int result = 0;
	int min = -1;
	for (int i = 0; i < SYMBOLS; ++i) {
		if (forest[i] && ((forest[i]->quan () < min) || (min == -1))) {
			result = i;
			min = forest[i]->quan ();
		}
	}
	return result;
}

Node *build_htree(int *per)
{
	Node *forest[SYMBOLS] = {};

	for (int i = 0;i < SYMBOLS;i++){
		forest[i] = new Node(NULL, NULL, NULL, per[i],(char)i);}
	
	int min = 0;

	for (int j = 0; j < SYMBOLS - 1; j++) 
	{
		min = num_mznach(forest);
		Node * first = forest[min];

		for (int i = min; i < SYMBOLS - 1; ++i){ 
			forest[i] = forest[i + 1];}

		forest[SYMBOLS - 1] = NULL;
		min = num_mznach(forest);
		Node * second = forest[min];

		for (int i = min; i < SYMBOLS - 1; ++i){ 
			forest[i] = forest[i + 1];}

		forest[SYMBOLS - 1] = merge(first, second);	
	}
	return forest[SYMBOLS - 1];
}


void huff_codes(Node *huffcodes, string *codes, string znach_code)
{
	if (huffcodes->get_leftchild ()) {
		znach_code.push_back ('0');
		huff_codes (huffcodes->get_leftchild (), codes, znach_code);
		znach_code.pop_back ();
	}
	if (huffcodes->get_rightchild ()) {
		znach_code.push_back ('1');
		huff_codes (huffcodes->get_rightchild (), codes, znach_code);
		znach_code.pop_back ();
	}
	else if (huffcodes->leaf ()) {
		codes[(unsigned char)huffcodes->sym ()] = znach_code;
	}
}


void write_znach(ofstream &out, string & leftznach, string znach_code)
{
	leftznach += znach_code;

	if (leftznach.length() < 8) 
	return;

	int bytes = leftznach.length() / 8;
	for (int i = 0;i < bytes;i++) 
	{	
		leftznach[0] -= '0';
		for (int j = 1;j < 8;j++)
			leftznach[j] = (leftznach[j - 1] << 1) | (leftznach[j] - '0');
		out.put(leftznach[7]);
		
		leftznach.erase(0, 8);
	}
}

Node *uncode_znach(Node *hufftree, string sequence)
{

	Node * counter = hufftree;
	for (unsigned int i = 0; i < sequence.length(); ++i) {
		if (sequence[i] == '0') {
			counter = counter->get_leftchild();
			if (counter->leaf()) {
				return counter;
			}
		}
		else {
			counter = counter->get_rightchild();
			if (counter->leaf()) {
				return counter;
			}
		}
	}
	return NULL;

}


string readByte(ifstream &in)
{
	char count;
	in.get(count);
	
	string new_b;

	for (int i = 0;i < 8;i++)
	{
		if (count & 128)
			new_b += '1';
		else
			new_b += '0';
		count <<= 1;
	}
	return new_b;
}


void uncode_text(ifstream &in, ofstream &out, Node *huffman_tree, string *codes)
{
	string remaining;
	int file_size = huffman_tree->quan ();
	string thing;
	while((thing = readByte(in)).length() > 0) {
		if (file_size == 0) 
		break;

		remaining += thing;
		while (Node *value = uncode_znach(huffman_tree, remaining))
		{		
			out << value->sym();
			--file_size;
			remaining.erase(0, codes[(unsigned char)value->sym()].length());
			if (file_size == 0) 
				break;
		}
	}
}

void pack()
{
	string input_file; 
	string output_file;
	int frequency[SYMBOLS] = {};
	ifstream in (input_file.data(), ifstream::binary);
	ofstream out(output_file.data(), ofstream::binary);
	char count;
	while (in.get (count))
	{
		++frequency[(unsigned char)count];
	}
	Node *huffman_tree = build_htree (frequency);
	string codes[SYMBOLS] = {};
	huff_codes (huffman_tree, codes);
	in.close();
	
	cout << "HF16";
	for (int i = 0;i < 256;++i) {
		unsigned int freq = (unsigned int)frequency[i];
		for (int j = 0;j < 4; j++)
			out.put ((char)(unsigned char)(freq & (0xFF << 8*(3-j))) >> 8*(3-j));
	}
	in.open(input_file.data(), ifstream::binary);

	string remaining;
	while(in.get(count)) 
	write_znach(out, remaining, codes[(unsigned char)count]); 

	in.close();

	while(remaining.length() % 8 != 0) 
		remaining += "0";
	write_znach(out, remaining, "");

	out.close();
}
void unpack()
{
	string input_file; 
	string output_file;
	ifstream in (input_file.data(), ifstream::binary);
	ofstream out(output_file.data(), ofstream::binary);

	char count;
	for (int i = 0;i < 4;i++)
	{
		in.get(count);
		if (count!= "HF16"[i]) 
			return;
	}

	int frequency[SYMBOLS] = {};
	for (int i = 0;i < SYMBOLS;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			in.get(count);
			frequency[i] = (frequency[i] << 8) | (unsigned char)count;
		}
	}
	Node *huffman_tree = build_htree(frequency);
	string codes[SYMBOLS] = {};
	huff_codes(huffman_tree, codes);
	uncode_text(in, out, huffman_tree, codes);
	in.close();
	out.close();
}


int main()
{
	int mode =0;
	while (mode !=3)
	{
		cout << "Choose mode: \n 1. Packing \n 2.Unpacking \n 3.Exit" << endl;
		cin >> mode;
		switch (mode)
		{
			case 1: 
			{
				pack();
				break;
			}

			case 2:
			{
				unpack();
				break;
			}

			case 3:
			{
				break;
			}

			default:
			{
				cout << "Error" << endl;
				break;
			}
			
		}

	}
	return 0;
}
