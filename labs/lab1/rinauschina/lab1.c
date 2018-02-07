#include <stdio.h>

void ftb(float in) {
	int* _in = (int *)&in;
	int i;
	char arr[32];
    for(i=31;i>-1;--i){
        arr[i] = (*(_in) & 1) + '0';
       *(_in) >>=1;
    }
    printf("Result:\n");
    for(i=0;i<32;++i){
        printf("%c",arr[i]);
    }
	printf("\n");
}

void btf(char arr[32]) {
    int out = 0;
    float _out;
    int i;
    for(i = 0; i<32; i++) {
        out <<= 1;
        out |= (arr[i] - '0');
    }
    _out = *(float*)&out;
    printf("%f\n", _out);
}
int main() {
    int key;
    printf("1. Float to binary;\n2. Binary to float;\n3. Exit.\n");
    scanf("%d", &key);
    switch(key){
        case 1: {
            float in;
            printf("Enter a number: \n");
            scanf("%f", &in);
            ftb(in);
        break;
        }
        case 2: {
            char arr[32];
            printf("Enter a number in bynary form:\n");
            scanf("%s", arr);
            btf(arr);
        break;
        }
        case 3:
            return 0;
        default:
         break;
    }
    return 0;
}

