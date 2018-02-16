#include <iostream>
#include <fstream>
#include <vector>
#include "codes.h"

enum encoding {
	UNKNOWN = 0,
	KOI = 1,
	WIN = 2
};

enum transcoding {
	NONE = 0,
	KOI_TO_WIN = 1,
	WIN_TO_KOI = 2
};

char koi8[256];
char win1251[256];
char utf8[65536];
#ifndef CODES_HEADER_
unsigned char codesKoiToWin[256];
unsigned char codesWinToKoi[256];
unsigned short int codesKoiToUTF[256];
unsigned short int codesWinToUTF[256];
#endif

encoding IdentifyEncoding (const std::vector<unsigned char> input); // 0 - unknown, 1 - koi8, 2 - win1251
unsigned char most_frequent_symbol    (const std::vector<unsigned char> input);

std::vector<unsigned char> * ConvertFromWin1251ToKoi8 (const std::vector<unsigned char> win_input);
std::vector<unsigned char> * ConvertFromKoi8ToWin1251 (const std::vector<unsigned char> koi_input);


void convert_to_UTF_and_print_into_file (std::ifstream & input, std::ofstream & out, encoding encod, transcoding * trans);

int main ()
{
	/////------------------------------| Подготовочная часть |------------------------------/////

	#ifdef _WIN32
	system ("chcp 1251"); // для отладки в винде.
	#endif

	for (int i = 0; i < 256; ++i) {
		koi8[i] = 0;
		win1251[i] = 0;
	}
	for (int i = 0; i < 65536; ++i) {
		utf8[i] = 0;
	}

	koi8[0xA3] = 'ё';	koi8[0xB3] = 'Ё';

	koi8[0xC0] = 'ю'; 	koi8[0xC1] = 'а';	koi8[0xC2] = 'б';	koi8[0xC3] = 'ц';
	koi8[0xC4] = 'д';	koi8[0xC5] = 'е';	koi8[0xC6] = 'ф';	koi8[0xC7] = 'г';
	koi8[0xC8] = 'х';	koi8[0xC9] = 'и';	koi8[0xCA] = 'й';	koi8[0xCB] = 'к';
	koi8[0xCC] = 'л';	koi8[0xCD] = 'м';	koi8[0xCE] = 'н';	koi8[0xCF] = 'о';
	koi8[0xD0] = 'п';	koi8[0xD1] = 'я';	koi8[0xD2] = 'р';	koi8[0xD3] = 'с';
	koi8[0xD4] = 'т';	koi8[0xD5] = 'у';	koi8[0xD6] = 'ж';	koi8[0xD7] = 'в';
	koi8[0xD8] = 'ь';	koi8[0xD9] = 'ы';	koi8[0xDA] = 'з';	koi8[0xDB] = 'ш';
	koi8[0xDC] = 'э';	koi8[0xDD] = 'щ';	koi8[0xDE] = 'ч';	koi8[0xDF] = 'ъ';

	koi8[0xE0] = 'Ю';	koi8[0xE1] = 'А';	koi8[0xE2] = 'Б';	koi8[0xE3] = 'Ц';
	koi8[0xE4] = 'Д';	koi8[0xE5] = 'Е';	koi8[0xE6] = 'Ф';	koi8[0xE7] = 'Г';
	koi8[0xE8] = 'Х';	koi8[0xE9] = 'И';	koi8[0xEA] = 'Й';	koi8[0xEB] = 'К';
	koi8[0xEC] = 'Л';	koi8[0xED] = 'М';	koi8[0xEE] = 'Н';	koi8[0xEF] = 'О';
	koi8[0xF0] = 'П';	koi8[0xF1] = 'Я';	koi8[0xF2] = 'Р';	koi8[0xF3] = 'С';
	koi8[0xF4] = 'Т';	koi8[0xF5] = 'У';	koi8[0xF6] = 'Ж';	koi8[0xF7] = 'В';
	koi8[0xF8] = 'Ь';	koi8[0xF9] = 'Ы';	koi8[0xFA] = 'З';	koi8[0xFB] = 'Ш';
	koi8[0xFC] = 'Э';	koi8[0xFD] = 'Щ';	koi8[0xFE] = 'Ч';	koi8[0xFF] = 'Ъ';

	win1251[0xA8] = 'Ё'; win1251[0xB8] = 'ё';
	for (int i = 0; i < 32; ++i) {
		win1251[0xC0 + i] = 'Б' + i - 1;
		win1251[0xE0 + i] = 'б' + i - 1;
	}

	utf8[0xD001] = 'Ё'; utf8[0xD191] = 'ё';
	for (int i = 0; i < 16; ++i) {
		utf8[0xD090 + i] = 'Б' + i - 1;
		utf8[0xD0B0 + i] = 'б' + i - 1;
	}
	for (int i = 0; i < 16; ++i) {
		utf8[0xD090 + i + 16] = 'Р' + i;
		utf8[0xD180 + i] = 'р' + i; // т.к. маленькие буквы лежат неровно, делаем два цикла
	}
	//------------------| Заполнение codes.h |------------------

#ifndef CODES_HEADER_

	std::ofstream header ("codes.h", std::ofstream::binary);
	header << "#ifndef CODES_HEADER_\n" << "#define CODES_HEADER_\n\n";										

	header << "unsigned char codesKoiToWin[256] = {";
	for (int i = 0; i < 0xC0; ++i) { // символы ASCII и нерусскую часть остального не меняем, т.к. хз во что.
		if (0xA3 == i) {
			header << 0xB8 << ", ";
		}
		else if (0xB3 == i) {
			header << 0xA8 << ", ";
		}
		else {
			header << i << ", ";
		}
		if (i % 32 == 31) {
			header << "\n" << "\t\t\t\t\t\t\t\t\t";
		}
	}
	for (int i_koi = 0xC0; i_koi <= 0xFF; ++i_koi) { // составляем таблицу перевода KOI в Win и обратно
		for (int i_win = 0xC0; i_win <= 0xFF; ++i_win) {
			if (koi8[i_koi] == win1251[i_win]) {
				header << i_win;
				if (i_koi != 0xFF) {
					header << ", ";
					if (i_koi % 32 == 31) {
						header << "\n" << "\t\t\t\t\t\t\t\t\t";
					}
				}			
			}
		}
	}
	header << "};\n";
	
	header << "unsigned char codesWinToKoi[256] = {";
	for (int i = 0; i < 0xC0; ++i) { // символы ASCII и нерусскую часть остального не меняем, т.к. хз во что.
		if (0xB8 == i) {
			header << 0xA3 << ", ";
		}
		else if (0xA8 == i) {
			header << 0xB3 << ", ";
		}
		else {
			header << i << ", ";
		}
		if (i % 32 == 31) {
			header << "\n" << "\t\t\t\t\t\t\t\t\t";
		}
	}
	for (int i_win = 0xC0; i_win <= 0xFF; ++i_win) { // составляем таблицу перевода KOI в Win и обратно
		for (int i_koi = 0xC0; i_koi <= 0xFF; ++i_koi) {
			if (koi8[i_koi] == win1251[i_win]) {
				header << i_koi;
				if (i_win != 0xFF) {
					header << ", ";
					if (i_win % 32 == 31) {
						header << "\n" << "\t\t\t\t\t\t\t\t\t";
					}
				}
			}
		}
	}
	header << "};\n";

	header << "unsigned short int codesKoiToUTF[256] = {";
	for (int i = 0; i < 0xC0; ++i) { // символы ASCII не меняем, не забываем про букву ё
		if (0xA3 == i) {
			header << 0xD191 << ", ";
		}
		else if (0xB3 == i) {
			header << 0xD001 << ", ";
		}
		else {
			header << i << ", ";
		}
		if (i % 32 == 31) {
			header << "\n" << "\t\t\t\t\t\t\t\t\t";
		}
	}
	for (int i_koi = 0xC0; i_koi <= 0xFF; ++i_koi) { // составляем таблицу перевода в UTF-8
		for (int i_utf = 0xD090; i_utf <= 0xD18F; ++i_utf) {
			if (utf8[i_utf] == koi8[i_koi]) {
				header << i_utf;
				if (i_koi != 0xFF) {
					header << ", ";
					if (i_koi % 16 == 15) {
						header << "\n" << "\t\t\t\t\t\t\t\t\t";
					}
				}
			}
		}
	}
	header << "};\n";

	header << "unsigned short int codesWinToUTF[256] = {";
	for (int i = 0; i < 0xC0; ++i) { // символы ASCII не меняем, не забываем про букву ё
		if (0xB8 == i) {
			header << 0xD191 << ", ";
		}
		else if (0xA8 == i) {
			header << 0xD001 << ", ";
		}
		else {
			header << i << ", ";
		}
		if (i % 32 == 31) {
			header << "\n" << "\t\t\t\t\t\t\t\t\t";
		}
	}
	for (int i_win = 0xC0; i_win <= 0xFF; ++i_win) { // составляем таблицу перевода в UTF-8
		for (int i_utf = 0xD090; i_utf <= 0xD18F; ++i_utf) {
			if (utf8[i_utf] == win1251[i_win]) {
				header << i_utf;
				if (i_win != 0xFF) {
					header << ", ";
					if (i_win % 16 == 15) {
						header << "\n" << "\t\t\t\t\t\t\t\t\t";
					}
				}
			}
		}
	}
	header << "};\n";
	header << "\n" << "#endif";

	header.close ();
	//////------------------------------| Подготовочная часть закончена |------------------------------/////
#else // если header есть.
	std::ifstream text ("disp.txt", std::ifstream::binary);
	if (!text.is_open()) {
		throw std::runtime_error ("нет файла со вводом");
	}
	std::ofstream output ("result.txt", std::ofstream::binary);
	std::vector<unsigned char> input;
	std::string fromfile;

	char c;
	while (text.get (c) && fromfile.size () < 1000) {
		if ((unsigned char)c > 0x80) {
			fromfile.push_back (c); // читаем в строку только русские символы Больше 1000 нам особо не понадобится
		}
	}
	const char * chars = fromfile.data ();
	const unsigned char* data_bytes = reinterpret_cast<const unsigned char*>(chars); // переводим эту строку в unsigned char

	for (int i = 0; i < fromfile.size (); ++i) {
		input.push_back (data_bytes[i]); // для перекодировок хочу векторы.
	}
	std::vector<unsigned char> * converted;
	std::vector<unsigned char> * new_inputKoiToWin;
	std::vector<unsigned char> * new_inputWinToKoi;

	transcoding transKoiToWin[3] = {NONE, NONE, NONE};
	transcoding transWinToKoi[3] = {NONE, NONE, NONE};
	encoding encod = IdentifyEncoding (input);
	if (encod != UNKNOWN) { // сходу определили кодировку
		convert_to_UTF_and_print_into_file (text, output, encod, transKoiToWin); // неважно какой тут trans, они оба в начале нулевые.
	}
	else {
		new_inputKoiToWin = &input;
		new_inputWinToKoi = &input;
		for (int i = 0; i < 3; ++i) {
			transKoiToWin[i] = KOI_TO_WIN;
			converted = ConvertFromKoi8ToWin1251 (*new_inputKoiToWin);
			if (i > 0) { // обычный input удалять не хотим
				delete new_inputKoiToWin;
			}
			new_inputKoiToWin = converted;
			encod = IdentifyEncoding (*new_inputKoiToWin);
			if (encod != UNKNOWN) {
				convert_to_UTF_and_print_into_file (text, output, encod, transKoiToWin);
				if (i > 0) {
					delete new_inputKoiToWin;
				}
				break;
			}

			transWinToKoi[i] = WIN_TO_KOI;
			converted = ConvertFromWin1251ToKoi8 (*new_inputWinToKoi);
			if (i > 0) { // обычный input удалять не хотим
				delete new_inputWinToKoi;
			}
			new_inputWinToKoi = converted;
			encod = IdentifyEncoding (*new_inputWinToKoi);
			if (encod != UNKNOWN) {
				convert_to_UTF_and_print_into_file (text, output, encod, transWinToKoi);
				if (i > 0) {
					delete new_inputWinToKoi;
				}
				break;
			}
		}
	}

	text.close ();
	output.close ();
	std::cin >> c;

#endif
	return 0;
}

std::vector<unsigned char> * ConvertFromKoi8ToWin1251 (const std::vector<unsigned char> koi_input) {
	std::vector<unsigned char> * result = new std::vector<unsigned char>;
	for (int i = 0; i < koi_input.size (); ++i) {
		result->push_back (codesKoiToWin[koi_input[i]]);
	}
	return result;
}

std::vector<unsigned char> * ConvertFromWin1251ToKoi8 (const std::vector<unsigned char> win_input)
{
	std::vector<unsigned char> * result = new std::vector<unsigned char>;
	for (int i = 0; i < win_input.size (); ++i) {
		result->push_back (codesWinToKoi[win_input[i]]);
	}
	return result;
}

encoding IdentifyEncoding (const std::vector<unsigned char> input) { // 0 - unknown, 1 - koi8, 2 - win1251
	unsigned char mfs = most_frequent_symbol (input);
	if ('о' == koi8[mfs]) {
		//std::cout << "koi\n";
		return KOI;
	}
	else if ('о' == win1251[mfs]) {
		//std::cout << "win\n";
		return WIN;		
	}
	else {
		//std::cout << "unknown\n";
		return UNKNOWN;		
	}	
}

unsigned char most_frequent_symbol (const std::vector<unsigned char> input) {
	int symb_count[256];
	unsigned char most_frequent_one = 0xC0;
	
	for (int i = 0; i < 0xFF; ++i) {
		symb_count[i] = 0;		
	}
	for (int i = 0; i < input.size (); ++i) {
		if (input[i] < 0x80) { // символы ASCII нас не интересуют
			continue;		
		}
		++symb_count[input[i]];		
	} // собираем статистику
	
	for (int i = 0xC0; i < 0xFF; ++i) {
		if (symb_count[i] > symb_count[most_frequent_one]) {
			most_frequent_one = i;			
		}		
	}
	return most_frequent_one;
}

void convert_to_UTF_and_print_into_file (std::ifstream & input, std::ofstream & out, encoding encod, transcoding * trans)
{
	input.seekg (0, input.beg);
	char c;

	//std::cout << trans[0] << ", " << trans[1] << ", " << trans[2] << ";\n";

	switch (encod) {
		case 1:
			while (input.get(c)) {
				if (codesKoiToUTF[(unsigned char)c] <= 0xFF) { // однобайтовое == ASCII
					out.put (c);
				}
				else { // двухбайтовые символы
					for (int i = 0; i < 3; ++i) { // перекодируем букву в нормальную кодировку (которую умеем переводить в UTF8).
						//std::cout << trans[i] << ";\n";
						if (WIN_TO_KOI == trans[i]) {
							c = (char)codesWinToKoi[(unsigned char)c];
						}
						else if (KOI_TO_WIN == trans[i]) {
							c = (char)codesKoiToWin[(unsigned char)c];
						}
						else {
							break;
						}
					}
					out.put ((char)((codesKoiToUTF[(unsigned char)c] & 0xFF00) >> 8)); // первый байт
					out.put ((char)((codesKoiToUTF[(unsigned char)c] & 0x00FF))); // второй байт
				}
			}
			break;
		case 2:
			while (input.get (c)) {
				if (codesWinToUTF[(unsigned char)c] <= 0xFF) { // однобайтовое == ASCII
					out.put (c);
				}
				else { // двухбайтовые символы
					for (int i = 0; i < 3; ++i) { // перекодируем букву в нормальную кодировку (которую умеем переводить в UTF8).
						//std::cout << trans[i] << ";\n";
						if (WIN_TO_KOI == trans[i]) {
							c = (char)codesWinToKoi[(unsigned char)c];
						}
						else if (KOI_TO_WIN == trans[i]) {
							c = (char)codesKoiToWin[(unsigned char)c];
						}
						else {
							break;
						}
					}
					out.put ((char)((codesWinToUTF[(unsigned char)c] & 0xFF00) >> 8)); // первый байт
					out.put ((char)((codesWinToUTF[(unsigned char)c] & 0x00FF))); // второй байт
				}
			}
			break;
		default:
			return; // кидаться ничем не буду, потому что больно
	}
}
