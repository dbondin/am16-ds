#include <stdio.h>

union X {
  float fl;
  unsigned char binary[4];
  int integ;
};

void FloatToBin(char &bin[33], float f) {
  float result;
  union X x;
  int buf, n;
  x.fl=f;
  int i;

  for (i=0; i<32; i++) {
      buf = x.integ;
      buf>>=(31-i);
      if (buf) {
        bin[i]='1';
        x.integ = (x.integ^(1<<(31-i)));
      } else
        bin[i]='0';

  }
  bin[32]='\0';
}

float BinToFloat (float f, unsigned char bin[4]) {
  union X x;
  int i;
  for (i=0; i<4; i++)
    x.binary[i]=bin[i];
  f = x.fl;
  return f;
}

int main () {
  union X x;
  char bin[33];
  //printf ("Select 1 or 2:\n");
  //printf ("\t1)from Binary to Float \n");
  //printf ("\t2)from Float to Binary \n");



  return 0;
}
