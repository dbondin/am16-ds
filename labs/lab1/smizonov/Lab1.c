#include <stdio.h>

void float_to_bin()
{
    char buf[32];
    float qw;
    printf("Введите число: ");
    scanf("%f", &qw);   
    int x=*(int*)&qw;
    if (x>=0)
    buf[0]='0';
    else {buf[0]='1';
        x=-x;}
   // printf("(%c | ", buf[0]);
    for(int i=1;i<32;i++)
    {
      if(((x>>(31-i)) << 31)==0)
          buf[i]='0';
      else buf[i]='1';
    }
  printf("\n (знак|порядок|мантисса) ");
    for(int i=0;i<32;i++)
    {  printf("%c",buf[i]);
  if(i==0 || i==8)
      printf("|");
  }
  printf("\n");
}


void bin_to_float()
{
    char buf[33];
    printf("Введите число: ");
    scanf("%s", buf);
    int res=0;
    for (int a=0; a<32; a++)
        {
            res <<= 1;
            res |= (buf[a] - '0');
        }

    printf ("\nОтвет: %f\n", *(float*)&res);
}

    int main()
    {
        printf("Выберите действие: \n 1)Из float в двоичный код \n 2)Из двоичного кода в float\n");

        int key;
        scanf("%d", &key);
        switch (key) {
        case 1:
           { float_to_bin();
            break;
        }
        case 2:
        {bin_to_float();
            break;
        }
        default:
            break;
        }



    }
