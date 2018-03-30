#include <iostream>
#include <fstream>
#include <sstream>
#include "bin_tree.h"

int index_of_min (Node ** arr);
Node * merge_all_trees (Node **forest);
void fill_codes_from_Huffman_tree (Node * node_of_Huffman_tree, std::string *codes, std::string current_code = "");
void print_bitwise (std::string & remaining, std::string code, std::ofstream &output);
void read_bitwise_and_print_outside (Node * Huffman_tree, std::ifstream &input, std::ofstream &output, std::string * codes);
Node *uncode_by_huffman_tree (Node * Huffman_tree, std::string sequence);

int main ()
{
	#ifdef _WIN32
	system ("chcp 1251"); // для отладки в винде.
	#endif

	std::string input_name;
	std::string output_name;
	int mode = -1;
	std::cout << "Введите, пожалуйста, названия двух файлов и режим работы. Первый файл будет перекодирован во второй. Режимы работы: 0 - упаковка, 1 - распаковка." << std::endl;

	getline (std::cin, input_name, ' ');
	//std::cout << input_name.data () << " ";
	getline (std::cin, output_name, ' ');
	//std::cout << output_name.data () << " ";
	std::cin >> mode;
	//std::cout << mode << std::endl;

	std::ifstream in (input_name.data (), std::ifstream::binary);
	switch (mode) {
		case 0: {
			int statistics[256] = {};
			char c;
			while (in.get (c)) {
				++statistics[(unsigned char)c];
			}
			Node * forest[256];
			for (int i = 0; i < 256; ++i) {
				forest[i] = new Node (statistics[i], (char)i);
			}

			Node * Huffman_tree = merge_all_trees (forest);
			std::string codes[256];
			fill_codes_from_Huffman_tree (Huffman_tree, codes);

			//in.seekg (0, in.beg); // Почему это не работает????
			in.close ();
			in.open (input_name.data (), std::ifstream::binary);
			std::ofstream out (output_name.data (), std::ofstream::binary);
			out << "HF16";
			for (int i = 0; i < 256; ++i) {
				unsigned int stat = (unsigned int)statistics[i];
				out.put ((char)(unsigned char)(stat & 0xFF000000) >> 24);
				out.put ((char)(unsigned char)(stat & 0x00FF0000) >> 16);
				out.put ((char)(unsigned char)(stat & 0x0000FF00) >> 8 );
				out.put ((char)(unsigned char)(stat & 0x000000FF)      );
			}
			std::string remaining;
			while (in.get (c)) {
				print_bitwise (remaining, codes[(unsigned char)c], out); //читаем и пихаем
			}
			std::string zeros = "0000000"; // 7 штук, чтобы напечатать весь остаток наверняка
			print_bitwise (remaining, zeros, out);
			out.close ();
		} 
		break;
		case 1: {
			char c;
			std::string HF16 = "HF16";
			for (int i = 0; i < 4; ++i) {
				in.get (c);
				if (c != HF16[i]) {
					std::cerr << "Это твой файл, - говорили они. Распакуй, - просили они. Я такое не распаковываю!\n";
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

			Node * Huffman_tree = merge_all_trees (forest);
			std::string codes[256];
			fill_codes_from_Huffman_tree (Huffman_tree, codes);

			std::ofstream out (output_name.data (), std::ofstream::binary);
			read_bitwise_and_print_outside (Huffman_tree, in, out, codes);
			out.close ();
		}
		break;
		default: {
			std::cerr << "Ошибка! Mode не 1 и не 2.\n";
		}
	}

	//getline (std::cin, output_name, ' '); для отладки

	in.close ();


	return 0;
}

int index_of_min (Node ** arr) // заранее знаем, что
{
	int result = 0;
	int min = -1;
	for (int i = 0; i < 256; ++i) {
		if (arr[i] && ((arr[i]->get_weight () < min) || (min == -1))) {
			result = i;
			min = arr[i]->get_weight ();
		}
	}
	return result;
}

Node * merge_all_trees (Node **forest) {
	int min = 0;

	for (int trees = 256; trees > 1; --trees) {
		min = index_of_min (forest);
		Node * left_subtree = forest[min];
		for (int i = min; i < 255; ++i) {
			forest[i] = forest[i + 1];
		}
		forest[255] = NULL;
		min = index_of_min (forest);
		Node *right_subtree = forest[min];
		for (int i = min; i < 255; ++i) {
			forest[i] = forest[i + 1];
		}
		forest[255] = left_subtree->merge_as_left_subtree_with (right_subtree);	
	}
	std::cout << "file_size = " << forest[255]->get_weight () << std::endl;
	return forest[255];
}

void fill_codes_from_Huffman_tree (Node * node_of_Huffman_tree, std::string *codes, std::string current_code)
{
	if (node_of_Huffman_tree->get_lchild ()) {
		current_code.push_back ('0');
		fill_codes_from_Huffman_tree (node_of_Huffman_tree->get_lchild (), codes, current_code);
		current_code.pop_back ();
	}
	if (node_of_Huffman_tree->get_rchild ()) {
		current_code.push_back ('1');
		fill_codes_from_Huffman_tree (node_of_Huffman_tree->get_rchild (), codes, current_code);
		current_code.pop_back ();
	}
	else if (node_of_Huffman_tree->is_leaf ()) {
		codes[(unsigned char)node_of_Huffman_tree->get_letter ()] = current_code;
	}
}

void print_bitwise (std::string & remaining, std::string code, std::ofstream &output)
{
	if (remaining.size () >= 8) {
		std::cerr << "wtf? remaining size is > 8.\n";
		return;
	}
	remaining += code;

	if (remaining.size () < 8) {		
		return;
	}

	int bytes = remaining.size () / 8; // сколько бутесов выводим
	unsigned char output_byte = 0;
	for (int i = 0; i < bytes; ++i) {	
		for (unsigned int j = 0; j < 8; ++j) {
			output_byte |= remaining[j] - '0';
			if (j < 7) {
				output_byte <<= 1;
			}
		}
		output.put ((char)output_byte);
		
		remaining.erase (0, 8);
		output_byte = 0;
	}
}

void read_bitwise_and_print_outside (Node * Huffman_tree, std::ifstream &input, std::ofstream &output, std::string * codes)
{
	std::string remaining;
	int file_size = Huffman_tree->get_weight ();
	char c;
	int size = 0;
	std::string new_byte;
	while (input.get (c)) {
		if (size >= file_size) {
			break;
		}
		for (int i = 7; i >= 0; --i) {
			new_byte.push_back ((c & (0x1 << i)) ? '1' : '0');
		}
		
		remaining += new_byte;
		new_byte.clear ();
		Node * uncoding;
		while (uncoding = uncode_by_huffman_tree (Huffman_tree, remaining)) { // выводим, пока в остатке хватает на раскодирование буквы.
			char letter = uncoding->get_letter ();
			output.put (letter);
			++size;
			if (size == file_size) {
				break;
			}
			remaining.erase (0, codes[(unsigned char)letter].size ()); // не хочется передавать путь в uncoding_..., поэтому делаем через codes
		}
	}

}

Node *uncode_by_huffman_tree (Node * Huffman_tree, std::string sequence)
{
	Node * counter = Huffman_tree;
	for (unsigned int i = 0; i < sequence.size (); ++i) {
		if (sequence[i] == '0') {
			counter = counter->get_lchild ();
			if (counter->is_leaf ()) {
				return counter;
			}
		}
		else {
			counter = counter->get_rchild ();
			if (counter->is_leaf ()) {
				return counter;
			}
		}
	}
	return NULL;
}
