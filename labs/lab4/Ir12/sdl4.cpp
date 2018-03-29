#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "sdl4.h"

int sort (Tree ** array);
Tree * mergetrees (Tree **sym);
void codesHuff (Tree * nodeHuff, string *codes, string codeHuff = "");
void bin (string & remainder, string code, ofstream &resfile);
void readbin (Tree * Huffmantree, ifstream &filename, ofstream &resfile, string * codes);
Tree *uncodeHuff (Tree * Huffmantree, string row);
void Packaging();
void Unpacking();

int main ()
{
	int menu = 0;
	while(menu != 3)
	{
		cout<< "1 - Упаковать файл \n 2 - Распокавать файл \n 3 - Выход" << endl;
		cin >> menu;
		switch (menu) 
		{
			case 1: 
			{
				Packaging();
				break;
			} 
			case 2: 
			{
				Unpacking();
				break;
			}
			case 3: 
				break;
			default: 
			{
				cout << "Не найдено. Ошибка.\n";
				break;
			}
		}
	}

	return 0;
}


void Packaging()
{
	string filename;
	string resfile;
	cout << "Введите, пожалуйста, названия файла, который надо упаковать: " << endl;
	cin >> filename;
	cout << "Введите, пожалуйста, названия файла-результата: " << endl;
	cin >> resfile;
	ifstream in (filename.data (), ifstream::binary);
	int statistics[256] = {};
	char c;
	while (in.get (c)) 
	{
		++statistics[(unsigned char)c];
	}
	Tree * sym[256];
	for (int i = 0; i < 256; ++i) 
	{
		sym[i] = new Tree (statistics[i], (char)i);
	}
	Tree * Huffmantree = mergetrees (sym);
	string codes[256];
	codesHuff (Huffmantree, codes);
	in.close ();
	in.open (filename.data (), ifstream::binary);
	ofstream out (resfile.data (), ofstream::binary);
	out << "HF16";
	for (int i = 0; i < 256; ++i) 
	{
		unsigned int stat = (unsigned int)statistics[i];
		out.put ((char)(unsigned char)(stat & 0xFF000000) >> 24);
		out.put ((char)(unsigned char)(stat & 0x00FF0000) >> 16);
		out.put ((char)(unsigned char)(stat & 0x0000FF00) >> 8 );
		out.put ((char)(unsigned char)(stat & 0x000000FF)      );
	}
			string remainder;
			while (in.get (c)) 
			{
				bin (remainder, codes[(unsigned char)c], out); 
			}
			string zeros = "0000000";
			bin (remainder, zeros, out);
			out.close ();
	in.close ();
	cout << "Файл упакован " << endl;
}

void Unpacking()
{
	string filename;
	string resfile;
	cout << "Введите, пожалуйста, названия файла, который надо распаковать: " << endl;
	cin >> filename;
	cout << "Введите, пожалуйста, названия файла-результата: " << endl;
	cin >> resfile;
	ifstream in (filename.data (), ifstream::binary);
	char c;
	string HF16 = "HF16";
	for (int i = 0; i < 4; ++i) 
	{
		in.get (c);
		if (c != HF16[i]) 
		{
			cout << "Файл другого формата. Распаковка не возможна.\n";
		}
	}

	Tree * sym[256];
	for (int i = 0; i < 256; ++i) 
	{
		unsigned int stat = 0;
		for (int j = 0; j < 4; ++j) 
		{
			in.get (c);
			stat |= (unsigned char)c;
			stat <<= 8;
		}
		stat >>= 8;
		sym[i] = new Tree (stat, (char)i);
	}

	Tree * Huffmantree = mergetrees (sym);
	string codes[256];
	codesHuff (Huffmantree, codes);
	ofstream out (resfile.data (), ofstream::binary);
	readbin (Huffmantree, in, out, codes);
	out.close ();
	in.close ();
	cout << "Файл распакован " << endl;
}

int sort (Tree ** array) 
{
	int result = 0;
	int min = -1;
	for (int i = 0; i < 256; ++i) 
	{
		if (array[i] && ((array[i]->getfrequency () < min) || (min == -1))) 
		{
			result = i;
			min = array[i]->getfrequency ();
		}
	}
	return result;
}

Tree * mergetrees (Tree **sym) 
{
	int min = 0;
	for (int trees = 256; trees > 1; --trees) 
	{
		min = sort (sym);
		Tree * leftbranch = sym[min];
		for (int i = min; i < 255; ++i) 
		{
			sym[i] = sym[i + 1];
		}
		sym[255] = NULL;
		min = sort (sym);
		Tree *rightbranch = sym[min];
		for (int i = min; i < 255; ++i) 
		{
			sym[i] = sym[i + 1];
		}
		sym[255] = leftbranch->mergeleftbranch (rightbranch);	
	}
	cout << "Размер файла = " << sym[255]->getfrequency () << endl;
	return sym[255];
}

void codesHuff (Tree * nodeHuff, string *codes, string codeHuff)
{
	if (nodeHuff->getleftleaf ()) 
	{
		codeHuff.push_back ('0');
		codesHuff (nodeHuff->getleftleaf (), codes, codeHuff);
	}
	if (nodeHuff->getrighleaf ()) 
	{
		codeHuff.push_back ('1');
		codesHuff (nodeHuff->getrighleaf (), codes, codeHuff);
	}
	else if (nodeHuff->leaf ()) 
	{
		codes[(unsigned char)nodeHuff->getsymbol ()] = codeHuff;
	}
}

void bin (string & remainder, string code, ofstream &resfile)
{

	remainder += code;

	if (remainder.size () < 8) 
	{		
		return;
	}

	int bytes = remainder.size () / 8;
	unsigned char resfilebyte = 0;
	for (int i = 0; i < bytes; ++i) 
	{			
		for (unsigned int j = 0; j < 8; ++j) 
		{
			resfilebyte |= remainder[j] - '0';
			if (j < 7) 
			{
				resfilebyte <<= 1;
			}
		}
		resfile.put ((char)resfilebyte);
		
		remainder.erase (0, 8);
		resfilebyte = 0;

	}
}

void readbin (Tree * Huffmantree, ifstream &filename, ofstream &resfile, string * codes)
{
	string remainder;
	int filesize = Huffmantree->getfrequency ();
	char c;
	int size = 0;
	string newbyte;
	while (filename.get (c)) 
	{
		if (size >= filesize) 
		{
			break;
		}
		for (int i = 7; i >= 0; --i) 
		{
			newbyte.push_back ((c & (0x1 << i)) ? '1' : '0');
		}
		
		remainder += newbyte;
		newbyte.clear ();
		Tree * uncoding;
		while (uncoding = uncodeHuff (Huffmantree, remainder)) 
		{ 
			char symbol = uncoding->getsymbol ();
			resfile.put (symbol);
			++size;
			if (size == filesize) 
			{
				break;
			}
			remainder.erase (0, codes[(unsigned char)symbol].size ()); 
		}
	}

}

Tree *uncodeHuff (Tree * Huffmantree, string row)
{
	Tree * kolvo = Huffmantree;
	for (unsigned int i = 0; i < row.size (); ++i) 
	{
		if (row[i] == '0') 
		{
			kolvo = kolvo->getleftleaf ();
			if (kolvo->leaf ()) 
			{
				return kolvo;
			}
		}
		else 
		{
			kolvo = kolvo->getrighleaf ();
			if (kolvo->leaf ()) 
			{
				return kolvo;
			}
		}
	}
	return NULL;
}

