#include <stdio.h>

void float2bin(float in) {
    int i;
    int *buff = (int *)&in;
    printf("Число: %f\n", in);
    printf("Знак: %d| Экспонента: ", (buff[0]>>31)&1);
    for(i = 30; i > 22; i--) {
    	printf("%d", (buff[0]>>i)&1);
    }
    printf("| Мантисса: ");
    for(i = 22; i >= 0; i--) {
        printf("%d", (buff[0]>>i)&1);
    }
    printf("|\n");
}

void bin2float(char bin_str[32]) {
    int out = 0;
    int i;
    for(i = 0; i<32; i++) {
        out <<= 1;
        out |= (bin_str[i] - '0');
    }
    printf("%f\n", *(float*)&out);
}
int main() {
    int key;
    printf("Выберите действие:\n1. Вывод знака|экспоненты|мантиссы числа;\n2. Перевод двоичного числа в десятичное;\n3. Выход.\n");
    scanf("%d", &key);
    switch(key){
        case 1: {
            float in;
            printf("Введите число: \n");
            scanf("%f", &in);
            float2bin(in);
        break;
        }
        case 2: {
            char bin_str[32];
            printf("Введите число в двоичной форме: \n");
            scanf("%s", bin_str);
            bin2float(bin_str);
        break;
        }
        case 3:
            return 0;
        default:
            printf("Ошибка. Неверный пункт меню.\n");
        break;
    }
    return 0;
}

