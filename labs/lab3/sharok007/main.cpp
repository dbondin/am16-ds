#include <iostream>
#include <stdexcept>
#include <cmath>

#include "stack.hpp"

using namespace std;

string InfixToPostfix(string infix);
int Precedence(char symbol);
int Result(string postfix);
int calculate(int a,int b, char operation);

int main()
{
    string infix, postfix;
    int result;
    cout<<"Enter the expression in the infix: ";
    getline(cin,infix);
    postfix =InfixToPostfix(infix);
    cout<<endl<<"Infix Expression: "<<infix<<endl;
    cout<<"Postfix Expression: "<<postfix<<endl;
    result = Result(postfix);
    cout<<endl<<"Result is: "<<result<<endl;
    return 0;
}

string InfixToPostfix(string infix){
    string postfix = "";
    int size = infix.length();
    Stack <char> stack(size);
    char symbol;
    for(int i=0;i<size;++i){
        symbol = infix[i];
        if(symbol == '('){
            stack.push(symbol);
        }
        else if(symbol == ')'){
            while(!stack.empty() && stack.Top() !='('){
                postfix+=stack.Top();
                stack.pop();
            }
            if(!stack.empty() && stack.Top() == '('){
                stack.pop();
            }
        }
        else
        {
            int priority = Precedence(symbol);
            if(0==priority){
                postfix+=symbol;
            }
            else{
                if(stack.empty()){
                    stack.push(symbol);
                }
                else
                {
                    while(!stack.empty() && stack.Top()!='('
                          && priority<=Precedence(stack.Top()))
                    {
                        postfix = postfix + stack.Top();
                        stack.pop();
                    }
                    stack.push(symbol);
                }

            }
        }
    }

    while(!stack.empty())
    {
        postfix += stack.Top();
        stack.pop();
    }

    return postfix;
}
int Result(string postfix)
{
    int size = postfix.length();
    Stack <char> stack(size);
    char symbol;
    for(int i=0;i<size;++i)
    {
        symbol = postfix[i];
        if(symbol>='0' && symbol<='9'){
           stack.push(symbol-'0');
        }
        else
        {
            int a,b;
            b = stack.Top();
            stack.pop();

            a = stack.Top();
            stack.pop();
            stack.push(calculate(a,b,symbol));
        }
    }

    return stack.Top();
}

int calculate(int a, int b, char operation)
{
    switch (operation) {
    case '+':
        return a+b;
    case '-':
         return a-b;
    case '*':
         return a*b;
    case '/':
        if(0!=b){
           return a/b;
        }
        else{
            throw invalid_argument("Division by zero!");
        }
    case '^':
        return pow(a,b);
    default:
        break;
    }
}

int Precedence(char symbol)
{
   switch(symbol){
   case '^':
        return 3;
   case'*':
   case'/':
       return 2;
   case'+':
   case'-':
       return 1;
   default:
       return 0;
  }

}
