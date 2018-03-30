#include <iostream>
#include <string>
#include "stack.h"

using namespace std;
// Ищем наиболее приоритетную операцию
int priority(char symbol) {
    int prior = 0;
    switch(symbol) {
        case '+':
        case '-':
            prior = 1;
        break;
        case '*':
        case '/':
            prior = 2;
        break;
    }
    return prior;
}

bool most_priority(char symbol1, char symbol2)
{
    return priority(symbol1) >= priority(symbol2) ? true: false;
}

//Строим анализатор входящего выражения и переводим его в postfix-версию
string infix_to_postfix(string infix) {
    string postfix = "";
    int len = infix.length();
    Stack<char> buff(len);
    for(int i = 0; i < len; i++) {
        switch(infix[i]) {
            case ' ':
            break;

            case '.':
                postfix += ".";
            break;
//принимаем на вход число
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                postfix += infix[i];
            break;
//принимаем на вход математический символ
            case '-':
            case '/':
            case '+':
            case '*': {
                postfix += " ";
                while(!buff.is_empty() && buff.peek() != '(' && most_priority(buff.peek(),infix[i])) {
                    postfix += buff.peek();
                    postfix += " ";
                    buff.pop();
                }
                buff.push(infix[i]);
            } break;

            case '(':
                buff.push(infix[i]);
            break;

            case ')': {
                while(!buff.is_empty() && buff.peek() != '(') {
                    postfix += " ";
                    postfix += buff.peek();
                    buff.pop();
                }
                buff.pop();
            } break;
        }
    }
    while(!buff.is_empty()) {
        postfix += " ";
        postfix += buff.peek();
        buff.pop();
    }
    return postfix;
}

//Сам калькулятор
void calculate(string in) {
    int len = in.length();
    Stack<float> st(len);
    float result = 0;
    float digit1 = 0;
    float digit2 = 0;
    for (int i = 0; i < len; ++i) {
        if(in[i]==' ') continue;
        switch(in[i]) {
            case '+': {
                digit1 = st.peek();
                st.pop();
                digit2 = st.peek();
                st.pop();
                result = digit2 + digit1;
                st.push(result);
            } break;
            case '-': {
                digit1 = st.peek();
                st.pop();
                digit2 = st.peek();
                st.pop();
                result = digit2 - digit1;
                st.push(result);
            } break;
            case '*': {
                digit1 = st.peek();
                st.pop();
                digit2 = st.peek();
                st.pop();
                result = digit2*digit1;
                st.push(result);
            } break;
            case '/':{
                digit1 = st.peek();
                st.pop();
                digit2 = st.peek();
                st.pop();
                if(digit1 != 0)
                result = digit2/digit1;
                else {
                    cout << "Деление на ноль. Ошибка." << endl;
                    return;
                }
                st.push(result);
            } break;

            default: {
                float digit = 0;
                float grade = 10;
                char flag = 0;
                int j;
                for(j=0; ;j++) {
                    if(in[i+j] == '.') {
                        flag = 1;
                        continue;
                    }
                    if((in[i+j] >= '0') && (in[i+j] <= '9')) {
                        if(!flag) {
                            digit *= 10;
                            digit += (float)(in[i+j] - '0');
                        }
                        else {
                            digit += (in[i+j]-'0')/grade;
                            grade *= 10;
                        }
                    }
                    else break;
                 }
                 i += j;
                 st.push(digit);
            }
        }
    }
    cout << result << endl;
}

int main() {
    string in;
    cout << "Введите выражение:" << endl;
    getline(cin, in);
    calculate(infix_to_postfix(in));
    return 0;
}
