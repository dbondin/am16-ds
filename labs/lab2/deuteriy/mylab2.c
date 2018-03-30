#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "table.h"
#include "encode_table.h"

int identify(unsigned char* unk_text)
{
	int i, j, len;
	double var_k, var_w;
	var_k = 0;
	var_w = 0;
	for(i = 0; i<strlen(unk_text); ++i)
	{
		if(unk_text[i] > 190)
		{
			for(j=0; j<64; ++j)
			{
				if(unk_text[i] == koi_t[j])
				{
					var_k += koiDec[j];
				}
				else 
				{
					if(unk_text[i] == win_t[j])
					{
						var_w += winDec[j];
					}
				}
			}
	
		}
	}
	
	if(var_k > var_w && var_k/strlen(unk_text) > 0.033)
	{	
		return 8;
	}
	else
	{
		if(var_w > var_k && var_w/strlen(unk_text) > 0.033) 
		{
			return 1251;
		}
		else 
		{
			return 0;
		}
	}
}

void recode_koi_to_win(unsigned char* koi, unsigned char* win)
{
	int i;
	for(i=0; i<strlen(koi); ++i)
	{
		if(koi[i] > 191) 
		{
			win[i] = koiToWin[koi[i]-192];
		}
		else 
		{
			win[i] = koi[i];
		}
	}
}

void recode_win_to_koi(unsigned char* win, unsigned char* koi)
{
	int i;
	for(i=0; i<strlen(win); ++i)
	{
		if(win[i] > 191)
		{
			koi[i] = winToKoi[win[i]-192];
		}
		else 
		{
			koi[i] = win[i];
		}
	}
}

void recode_win_to_utf(unsigned char* win, unsigned int **utf)
{
	int i;
	for(i=0; i<strlen(win); ++i)
	{
		if(win[i] > 191)
		{
			utf[i][0] = ((winToUtf[win[i]-192] & 65280) >> 8);
			utf[i][1] = (winToUtf[win[i]-192] & 255);
		}
		else 
		{
			utf[i][0] = win[i];
		}
	}
}

void recode_koi_to_utf(unsigned char* koi, unsigned int **utf)
{
	int i;
	for(i=0; i<strlen(koi); ++i)
	{
		if(koi[i] > 191)
		{
			utf[i][0] = ((koiToUtf[koi[i]-192] & 65280) >> 8);
			utf[i][1] = (koiToUtf[koi[i]-192] & 255);
		}
		else 
		{
			utf[i][0] = koi[i];
		}
	}
}

int decode(unsigned char* input_text, unsigned int** utf, int complexity)
{
	int decode_1, decode_2, len;
	len = strlen(input_text);
	unsigned char* koi = (unsigned char*)malloc(sizeof(unsigned char)*len);
	unsigned char* win = (unsigned char*)malloc(sizeof(unsigned char)*len);
	decode_1 = identify(input_text);
	if(decode_1 == 8)
	{
		recode_koi_to_utf(input_text, utf);
		return 1;
	}
	else 
	{
		if(decode_1 == 1251)
		{
			recode_win_to_utf(input_text, utf);
			return 1;
		}
	}
	if(complexity > 3) 
	{
		return 0;
	}
	recode_koi_to_win(input_text, win);
	decode_1 = identify(win);
	recode_win_to_koi(input_text, koi);
	decode_2 = identify(koi);
	if(decode_1 == 8 || decode_2 == 8)
	{
		recode_koi_to_utf(win, utf);
		return 1;
	}
	else 
	{
		if(decode_1 == 1251 || decode_2 == 1251)
		{
			recode_win_to_utf(koi, utf);
			return 1;
		}
		else 
		{
			if(decode_1 == 0 && decode_2 == 0)
			{
				++complexity;
				if(decode(win, utf, complexity)) 
				{
					return 1;
				}
				if(decode(koi, utf, complexity))
				{
					return 1;
				}
			}
		}
	}
}

int main()
{	
	int i, j, complexity;	
	unsigned char unk_text[1000];
	unsigned int **utf = (unsigned int**)malloc(sizeof(unsigned int*)*sizeof(unk_text));
	FILE *in = fopen("in.txt", "r");
	FILE *out = fopen("out.txt", "w");
	for(i=0; i<sizeof(unk_text); ++i)
	{
		utf[i] = (unsigned int*)malloc(sizeof(unsigned int)*2);
	}
	while(!feof(in)) 
	{
		for(j=0; j<sizeof(unk_text)-1; ++j)
		{
			if(feof(in))
			{
				for(j; j<sizeof(unk_text)-1; ++j)
				{
					unk_text[j]='\0';
				} 
				break;
			}
			unk_text[j] = getc(in);
		}
		complexity=0;
		if(decode(unk_text, utf, complexity))
		{
			for(i=0; i<strlen(unk_text); ++i)
			{
				fputc(utf[i][0], out);
				fputc(utf[i][1], out);
			}
		}
		else 
		{
			perror("Error! Unknown encoding!");
		}
	}
}


