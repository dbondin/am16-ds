#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "EncodeTables.h"
#include "dispersionOfSymbol.h"

int identify_encoding(unsigned char* text)
{
    int i, j;
    double koi8_val = 0;
    double win1251_val = 0;

    for(i=0; i<strlen(text); ++i)

    {
        if(text[i] > 190)
        {
            for(j=0; j<64; ++j)
            {
                if(text[i] == koi8_key[j])
                {
                    koi8_val += koi8_dispers[j];
                }
                else if(text[i] == win1251_key[j])
                {
                    win1251_val += win1251_dispers[j];
                }
            }
        }
    }
    if(koi8_val > win1251_val && koi8_val/strlen(text) > 0.033) return 8;
    else if(win1251_val > koi8_val && win1251_val/strlen(text) > 0.033) return 1251;
    else return 0;
}

void koi8_to_win1251(unsigned char* koi8, unsigned char* win1251)
{
    int i;
    for(i=0; i<strlen(koi8); ++i)
    {
        if(koi8[i] > 191) {
            win1251[i] = koi8ToWin1251[koi8[i]-192];
        }
        else {
            win1251[i] = koi8[i];
        }
    }
}

void win1251_to_koi8(unsigned char* win1251, unsigned char* koi8)
{
    int i;
    for(i=0; i<strlen(win1251); ++i)
    {
        if(win1251[i] > 191)
        {
            koi8[i] = win1251ToKoi8[win1251[i]-192];
        }
        else {
            koi8[i] = win1251[i];
        }
    }
}

void win1251_to_utf8(unsigned char* win1251, unsigned int **utf8)
{
    int i;
    for(i=0; i<strlen(win1251); ++i)
    {
        if(win1251[i] > 191)
        {
            utf8[i][0] = ((win1251ToUtf8[win1251[i]-192] & 65280) >> 8);
            utf8[i][1] = (win1251ToUtf8[win1251[i]-192] & 255);
        }
        else {
            utf8[i][0] = win1251[i];
        }
    }
}

void koi8_to_utf8(unsigned char* koi8, unsigned int **utf8)
{
    int i;
    for(i=0; i<strlen(koi8); ++i)
    {
        if(koi8[i] > 191)
        {
            utf8[i][0] = ((koi8ToUtf8[koi8[i]-192] & 65280) >> 8);
            utf8[i][1] = (koi8ToUtf8[koi8[i]-192] & 255);
        }
        else {
            utf8[i][0] = koi8[i];
        }
    }
}

int decode(unsigned char* source, unsigned int** utf8, int deep)
{
    int encK = identify_encoding(source);
    if(encK == 8)
    {
        koi8_to_utf8(source, utf8);
        return 1;
    }
    else if(encK == 1251)
    {
        win1251_to_utf8(source, utf8);
        return 1;
    }
    int encW = encK;
    if(deep > 3) return 0;
    int lenOfText = strlen(source);
    unsigned char* koi = (unsigned char*)malloc(sizeof(unsigned char)*lenOfText);
    unsigned char* win = (unsigned char*)malloc(sizeof(unsigned char)*lenOfText);

    koi8_to_win1251(source, win);
    encK = identify_encoding(win);

    win1251_to_koi8(source, koi);
    encW = identify_encoding(koi);
    if(encK == 8 || encW == 8)
    {
        koi8_to_utf8(win, utf8);
        return 1;
    }
    else if(encW == 1251 || encK == 1251)
    {
        win1251_to_utf8(koi, utf8);
        return 1;
    }
    else if(encK == 0 && encW == 0)
    {
        ++deep;
        if(decode(win, utf8, deep)) return 1;
        if(decode(koi, utf8, deep)) return 1;
    }
}


int main(int argc, char* argv[])
{
    char inputFile[32];
    char outFile[32];
    if(argc == 3)
    {
        strcpy(inputFile, argv[1]);
        strcpy(outFile, argv[2]);

    }
    else if(argc == 2)
    {
        strcpy(inputFile, argv[1]);
        printf("Default output file is <out.txt>\n");
        strcpy(outFile, "out.txt");
    }
    else {
        printf("Enter input file: ");
        scanf("%s", inputFile);
        printf("Default output file is <out.txt>\n");
        strcpy(outFile, "out.txt");
    }

    unsigned char text[5000];
    FILE *ftxt = fopen(inputFile, "r");
    FILE *out = fopen(outFile, "w");
    int i;
    unsigned int **utf = (unsigned int**)malloc(sizeof(unsigned int*)*sizeof(text));
    for(i=0; i<sizeof(text); i++)
    {
        utf[i] = (unsigned int*)malloc(sizeof(unsigned int)*2);
    }
    int p;
    while(!feof(ftxt)) {
        for(p=0; p<sizeof(text)-1; ++p)
        {
            if(feof(ftxt)) break;
            text[p] = getc(ftxt);
        }

        int deep = 0;
        if(decode(text, utf, deep))
        {
            for(i=0; i<p-1; ++i)
            {
                printf("%c%c", utf[i][0], utf[i][1]);
                fputc(utf[i][0], out);
                fputc(utf[i][1], out);
            }
        }
        else {
            perror("Error! Unrecognizable encoding");
        }
    }
}