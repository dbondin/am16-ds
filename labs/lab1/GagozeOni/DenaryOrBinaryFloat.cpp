#include "stdio.h" 
#include <fstream> 
#include <iostream> 
#include <string> 
#include <conio.h>
using namespace std;

void BinaryToDenary(bool mas[32],bool flag);

void DenaryToBinary(float var, bool flag){
	float *p = &var;
	long *number = (long*)p;
	bool *mas = new bool[32];
	for (int i = 31; i >= 0; i--){
		long mask = 1 << i;
		if ((mask & *number) == 0)
			mas[31 - i] = 0;
		else
			mas[31 - i] = 1;
	}
	for (int i = 0; i < 32; i++){
		if ((i == 1) || (i == 9)) cout << "|";
		cout << mas[i];
	}
	if (flag == 0) return;
	int choise;
	cout << endl << "Invert the result?" << endl << "1 - Yes" << endl << "Enter - exit"<< endl << "Any key - menu" << endl;
	choise = _getch();
	switch (choise){
		case '1':{
		BinaryToDenary(mas,0); 
		system("pause");
		break;
	}
	case 13:exit(0);
	default:break;
	}
}
void BinaryToDenary(bool mas[32],bool flag){
	int mask = 0;
	for (int i = 0; i<32; i++) {
		mask <<= 1;
		mask |= mas[i];
	}
	int *_flt = &mask;
	float *flt = (float*)_flt;
	cout << *flt << endl;
	if (flag == 0) return;
	int choise;	
	cout << endl << "Invert the result?" << endl << "1 - Yes" << endl << "Enter - exit"<< endl << "Any key - menu" << endl;
	choise = _getch();
	switch (choise){
	case '1':{
		DenaryToBinary(*flt,0);
		system("pause");
		break;
	}
	case 13:exit(0);
	default:break;
	}
}
void main()
{	
	setlocale(LC_ALL, "Russian");
	float var;	
	int choise=0;
	while (true){
		cout << "Select please:" << endl << "1 - denary float -> binaty float" << endl << "2) binaty float -> denaty float" << endl<<"Enter - exit" << endl;
		choise=_getch();		
		switch (choise){
		case '1':{
			cout << "Set denaty float" << endl;
			cin >> var;
			DenaryToBinary(var,1);
			break;
		}
		case '2':{
			bool mas[32];
			cout << "Set binaty float" << endl;
			string bin;
			cin >> bin;
			if (bin.length() < 32){
				cout << "Incorrect binary float" << endl;
				break;
			}
			for (int i = 0; i < 32; i++) mas[i] = bin[i]-'0';
			BinaryToDenary(mas,1);
			break;
		}
		case 13: exit(0); break;
		default: {
			cout << "Incorrect option, try again" << endl;
			break;
		}
		}	
		system("cls");
	}	
	return;
}