#include <iostream>
#include <fstream>
#include <string>
#include "node.h"

using namespace std;


int calc_min (Node** arr)
{
	int result = 0;
	int min = -1;
	for (int i = 0; i < 256; ++i) {
		if (arr[i] && ((arr[i]->get_wt() < min) || (min == -1))) {
			result = i;
			min = arr[i]->get_wt();
		}
	}
	return result;
}

Node* link_all (Node **forest) {
	int min = 0;
	for (int trees = 256; trees > 1; --trees) {
		min = calc_min(forest);
		Node* left_t = forest[min];
		for (int i = min; i < 255; ++i) {
			forest[i] = forest[i + 1];
		}
		forest[255] = NULL;
		min = calc_min(forest);
		Node *right_t = forest[min];
		for (int i = min; i < 255; ++i) {
			forest[i] = forest[i + 1];
		}
		forest[255] = left_t->link(right_t);	
	}
	return forest[255];
}

void fill_Huffman(Node* Huffman, string* codes, string code)
{
	if (Huffman->get_left()) 
	{
		code.push_back('0');
		fill_Huffman(Huffman->get_left(), codes, code);
		code.erase(code.end() - 1);
	}
	if (Huffman->get_right()) 
	{
		code.push_back ('1');
		fill_Huffman(Huffman->get_right(), codes, code);
		code.erase(code.end() - 1);
	}
	else if (Huffman->check_leaf ()) {
		codes[(unsigned char)Huffman->get_data()] = code;
	}
}

void write_bit(string& remain, string code, ofstream &output)
{
	if (remain.size() >= 8) 
	{
		cerr << "Size is > 8.\n";
		return;
	}
	remain+= code;
	if (remain.size() < 8) 
	{		
		return;
	}

	int bytes = remain.size() / 8;
	unsigned char output_byte = 0;
	for (int i = 0; i < bytes; ++i) 
	{	
		for (unsigned int j = 0; j < 8; ++j) 
		{
			output_byte |= remain[j] - '0';
			if (j < 7) 
			{
				output_byte <<= 1;
			}
		}
		output.put ((char)output_byte);
		remain.erase (0, 8);
		output_byte = 0;
	}
}

Node* uncode(Node* Huffman, string seq)
{
	Node* t = Huffman;
	for (unsigned int i = 0; i < seq.size (); ++i) {
		if (seq[i] == '0') {
			t = t->get_left ();
			if (t->check_leaf ()) {
				return t;
			}
		}
		else {
			t = t->get_right ();
			if (t->check_leaf ()) {
				return t;
			}
		}
	}
	return NULL;
}

void read_bit_write(Node* Huffman, ifstream& input, ofstream& output, string* codes)
{
	string remain;
	int f_size = Huffman->get_wt();
	char c;
	int size = 0;
	string n_byte;
	while (input.get (c)) {
		if (size >= f_size) 
		{
			break;
		}
		for (int i = 7; i >= 0; --i) {
			n_byte.push_back((c & (0x1 << i)) ? '1' : '0');
		}
		remain+= n_byte;
		n_byte.clear();
		Node* uncoding;
		while (uncoding = uncode(Huffman, remain)) 
		{ 
			char data = uncoding->get_data ();
			output.put(data);
			++size;
			if (size == f_size) 
			{
				break;
			}
			remain.erase(0, codes[(unsigned char)data].size ());
		}
	}

}


int main ()
{
	string input;
	string output;
	int mode = -1;
	cout << "Введите название исходного файла: ";
	cin >> input;
	cout << "Введите название файла в который исходный будет перекодирован: ";
	cin >> output;
	cout << "Выберите режим работы (0 - упаковать, 1 - распаковать): ";
	cin >> mode;
	ifstream in(input.data(), ifstream::binary);
	switch (mode) {
		case 0: {
			int stst[256] = {};
			char c;
			while (in.get(c)) {
				++stst[(unsigned char)c];
			}
			Node* forest[256];
			for (int i = 0; i < 256; ++i) {
				forest[i] = new Node (stst[i], (char)i);
			}
			Node* Huffman = link_all(forest);
			string codes[256];
			fill_Huffman (Huffman, codes, "");
			in.clear();
			in.seekg(0, ios_base::beg);
			ofstream out(output.data(), ofstream::binary);
			out << "HF16";
			for (int i = 0; i < 256; ++i) {
				unsigned int stat = (unsigned int)stst[i];
				out.put((char)(unsigned char)(stat & 0xFF000000) >> 24);
				out.put((char)(unsigned char)(stat & 0x00FF0000) >> 16);
				out.put((char)(unsigned char)(stat & 0x0000FF00) >> 8 );
				out.put((char)(unsigned char)(stat & 0x000000FF)      );
			}
			string remain;
			while (in.get (c)) 
			{
				write_bit(remain, codes[(unsigned char)c], out);
			}
			string zeros = "0000000";
			write_bit(remain, zeros, out);
			out.close ();
		} 
		break;
		case 1: {
			char c;
			string HF16 = "HF16";
			for (int i = 0; i < 4; ++i) {
				in.get(c);
				if (c != HF16[i]) 
				{
					cerr << "Невозможно распаковать!\n";
				}
			}

			Node * forest[256];
			for (int i = 0; i < 256; ++i) {
				unsigned int stat = 0;
				for (int j = 0; j < 4; ++j) {
					in.get (c);
					stat |= (unsigned char)c;
					stat <<= 8;
				}
				stat >>= 8;
				forest[i] = new Node (stat, (char)i);
			}
			Node* Huffman = link_all(forest);
			string codes[256];
			fill_Huffman(Huffman, codes, "");
			ofstream out (output.data (), ofstream::binary);
			read_bit_write (Huffman, in, out, codes);
			out.close ();
		}
		break;
		default: {
			std::cerr << "Ошибка! Mode не 0 и не 1.\n";
		}
	}
	in.close ();
	return 0;
}
