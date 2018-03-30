#include <conio.h>
#include <iostream>
#include <fstream>
#include "Ochered.h"
#include "Stack_sign.h"
#include "Stack_number.h"

void main()
{

	setlocale(LC_ALL, "Russian");

	
	char *str;
	int n = 0;
	str = new char[100];

	char c;
	c = getchar();
	while (c != '\n') {
		if (c != 32) {
			str[n] = c;
			n++;
		}
		c = getchar();
	}
	str[n] = '\0';

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	cout << "строка: " << endl;
	for (int i = 0; i < n; i++)
		cout << str[i];
	cout << endl;
	cout << "размер строки= " << n << endl;

	////////////////////////////////////////////////////////////////////////////////////////////////////

	Stack_sign str_st(n);//можно помен€ть n

	for (int i = 0; i < n; i++)
		if (str[i] == '(') str_st.push(str[i]);
		else if (str[i] == ')')
			if (!str_st.IsEmpty()) str_st.pop();
			else { cout << "  оличество закрывающихс€ скобок > открывающихс€, неверное выражение"; break; }
			if (!str_st.IsEmpty()) { cout << "  оличество открывающихс€ скобок > закрывающихс€, неверное выражение"; }

			/////////////////////////////////////////////////////////////

			Ochered str_och(n + 3);

			str_och.TakeType(operation);
			str_och.push('|');

			int l = 0, d = 1, v = 0;
			for (int i = 0; i < n + 2; i++)
			{

				if ((str[i] >= 48) && (str[i] <= 57)) { l++; if (l > 1) d = d * 10; }
				else
					if (((str[i] >= 40) && (str[i] <= 43)) || (str[i] == 45) || (str[i] == 47))
					{
						if (l != 0) {
							while (l != 0) {
								v = v + ((str[i - l]) - '0') * d;
								l--;
								if (d != 1) d = d / 10;
							}
							str_och.TakeType(number);
							str_och.push(v);
							v = 0;
						}
						str_och.TakeType(operation);
						str_och.push(str[i]);
					}
				/*else if (str[i]==32) {
									  if (l != 0) {
												   while (l != 0) {
																   v = v + ((str[i - l])-'0') * d;
																   l--;
																   if (d!=1) d = d / 10;
																  }
												   str_och.TakeType(number);
												   str_och.push(v);
												   v = 0;
												  }
									  }*/
					else if (str[i] == '\0') {
						if (l != 0) {
							while (l != 0) {
								v = v + ((str[i - l]) - '0') * d;
								l--;
								if (d != 1) d = d / 10;
							}
							str_och.TakeType(number);
							str_och.push(v);
						}
						//добавим в конец очереди знак,обозначающий конец, его значнеие 124
						str_och.TakeType(operation);
						str_och.push('|');
						break;
					}
					else { cout << "¬ы ввели недопустимые символы" << endl; break; }
			}


			cout << "ќчередь строки: " << endl;
			str_och.Print();


			enum STATE
			{
				STATE_Empty = 0,
				STATE_start = 124,
				STATE_opening_bracket = 40,
				STATE_closing_bracket = 41,
				STATE_Operations_division = 42,
				STATE_Operations_sum = 43,
				STATE_Operations_subtracrion = 45,
				STATE_Operations_increase = 47
			};

			//////////////////////////////////////////////

			bool t = 1;
			STATE state = STATE_Empty;
			Ochered och_pz(n + 1);
			Stack_sign stack_op(n + 1);
			my_type kt = str_och.GetType();
			int k = str_och.pop();

			while (t == 1)
			{
				if (kt == number) { och_pz.TakeType(number); och_pz.push(k); kt = str_och.GetType(); k = str_och.pop(); }
				else {
					switch (k)
					{
					case 40: {   // в любом случае
						stack_op.push(k);
						state = (STATE)stack_op.GiveValue();
						kt = str_och.GetType();
						k = str_och.pop();
						break;
					}
					case 41: {   if ((state == 43) || (state == 45) || (state == 42) || (state == 47)) // если +, - , /, *
					{
						och_pz.TakeType(operation);
						och_pz.push(stack_op.pop());
						state = (STATE)stack_op.GiveValue();
					}
							 else if (state == 40) // если (
							 {
								 kt = str_och.GetType();
								 k = str_och.pop();
								 stack_op.pop();
								 state = (STATE)stack_op.GiveValue();
							 }
							 else if (state == 124) // если |
							 {
								 cout << "Error:" << endl;
								 t = 0;
							 }
							 break;
					}
					case 42: {
						if ((state == 124) || (state == 43) || (state == 45) || (state == 40)) // если начало строки, +, - , (
						{
							stack_op.push(k);
							state = (STATE)stack_op.GiveValue();
							kt = str_och.GetType();
							k = str_och.pop();
						}
						else //если *, /
						{
							och_pz.TakeType(operation);
							och_pz.push(stack_op.pop());
							state = (STATE)stack_op.GiveValue();
						}
						break;
					}
					case 43: {
						if ((state == 45) || (state == 43) || (state == 42) || (state == 47)) // если +, -, *, /
						{
							och_pz.TakeType(operation);
							och_pz.push(stack_op.pop());
							state = (STATE)stack_op.GiveValue();
						}
						else //то есть когда начало строки или (
						{
							stack_op.push(k);
							state = (STATE)stack_op.GiveValue();
							kt = str_och.GetType();
							k = str_och.pop();
						}
						break;
					}
					case 45: {
						if ((state == 45) || (state == 43) || (state == 42) || (state == 47)) // если +, -, *, /
						{
							och_pz.TakeType(operation);
							och_pz.push(stack_op.pop());
							state = (STATE)stack_op.GiveValue();
						}
						else //то есть когда начало строки или (
						{
							stack_op.push(k);
							state = (STATE)stack_op.GiveValue();
							kt = str_och.GetType();
							k = str_och.pop();
						}
						break;
					}
					case 47: {
						if ((state == 124) || (state == 43) || (state == 45) || (state == 40)) // если начало строки, +, - , (
						{
							stack_op.push(k);
							state = (STATE)stack_op.GiveValue();
							kt = str_och.GetType();
							k = str_och.pop();
						}
						else //если *, /
						{
							och_pz.TakeType(operation);
							och_pz.push(stack_op.pop());
							state = (STATE)stack_op.GiveValue();
						}
						break;
					}
					case 124: {
						if ((state == 45) || (state == 43) || (state == 42) || (state == 47)) // если +, -, *, /
						{
							och_pz.TakeType(operation);
							och_pz.push(stack_op.pop());
							state = (STATE)stack_op.GiveValue();
						}
						else
							if (state == 40) {
								cout << "Error:" << endl;
							}
							else
								if (state == 124) {
									cout << "ѕольска€ запись: " << endl;
									och_pz.Print();
									cout << endl;
									t = 0;
								}
								else
									if (state == 0)
									{
										stack_op.push(k);
										state = (STATE)stack_op.GiveValue();
										kt = str_och.GetType();
										k = str_och.pop();
									}
						break;
					}
					}
				}
			}

			//////////////////////////////////////////////////////////////////////////

			Stack_number itog(n);
			float a, b;
			while (!och_pz.IsEmpty())
			{
				kt = och_pz.GetType();
				k = och_pz.pop();
				if (kt == number) itog.push(k);
				else {
					switch (k)
					{
					case 43: itog.push(itog.pop() + itog.pop());
						break;
					case 45:a = itog.pop();
						b = itog.pop();
						itog.push(b - a);
						break;
					case 42:itog.push(itog.pop()*itog.pop());
						break;
					case 47: a = itog.pop();
						b = itog.pop();
						itog.push(b / a);
						break;
					}
				}
				cout << "—тек дл€ подсчета значени€ выражени€: ";
				itog.Print();
			}

			////////////////////////////////////////////////////////////////////////

			cout << endl;
			cout << "«начение выражени€ = ";
			itog.Print();




}