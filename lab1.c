#include <stdio.h>
#include <string.h>

/* bintodec:  переводит строку s из двоичной системы в десятичную */
float bintodec(char *s)
{
    long n;
        
    while (*s == '0')
        s++;
    if (strlen(s) > 32)
        return EOF;
    else if (*s == '\0')
        return 0;
    for (n = 0; *s != '\0'; s++) {
        if (*s == '0')
            continue;
        else if (*s != '1')
            return EOF;
        n += 01 << (strlen(s)-1);
    }
    float *val =  (float*)&n;
    return *val;    
}



/* dectobin:  переводит число n из десятичной системы в двоичную */
void dectobin (float n)
  	{
  		int i, j;
  		char *s;
 		 
 		s = (char*)&n;
 		for (i=3; i>=0; i--)
 			for (j=7; j>=0; j--)
 				printf("%d", (s[i] >> j) & 1);
 		printf("\n");
 	}


int main()
{
    
     
    char *bin = "11000001000101100110011001100110";
    dectobin(13.45);
        
    printf("%f\n", bintodec(bin));
    
    return 0;
}
