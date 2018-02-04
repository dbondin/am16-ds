#include <stdio.h>
#include <math.h>

float BinToFloat (char *bin) {
  int i;
  float result=0.0;
  for (i=0; i<32; i++) {
    result=(result<<1);
    if (strcmp(bin[i], "1")!=0)
      result+=1;
  }
  return result;
}

//For using this function you must have a 32byte array of chars

char *FloatToBin (float fl) {
  int i;
  char bin[32];
  int *serv=&fl;
   for(i=0; i<32; i++) {
     if ((serv >> (32-(i+1)))=1) {
       bin[i]="1";
       serv = serv - pow(2, 32-(i+1));
     } else bin[i]="0";
   }
  return bin;
}

main() {
  float fl;
  char bin[32];
  int menu;
  int i;
  printf('Select 1 or 2:\n\t1) from Binary to Float \n\t2) from Float to Binary\n');
  scanf('%d', &menu);
  switch(menu) {
    case 1: {
      printf("Write 0 and 1 bit by bit 32 times\n");
      for (i=0, i<32, i++) {
        scanf('%c', &bin[i]);
      }
      fl=BinToFloat (*bin);
      printf('%f', fl);
      break;
    }
    case 2: {
      printf ("Write a number with the floating point\n");
      scanf ('%f', &fl);
      bin = FloatToBin(fl);
      for (i=0; i<32; i++) {
        printf('%c', bin[i]);
      }
      break;
    }
    default: {
      break;
    }
  }
  return 0;
}
