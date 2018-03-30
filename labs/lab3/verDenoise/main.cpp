#include <iostream>
#include <string>
#include "stek.h"
using namespace std;
bool IsOperator(char symbol)
{
    if((symbol=='+') || (symbol=='-') || (symbol =='*') || (symbol=='/'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool IsNumber(char symbol)
{
    if((symbol>='0') && (symbol<='9'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int PriorityOperation(char symbol)
{
    int key = 0;
    switch(symbol)
    {
        case '+':
        case '-':
            key = 0;
        break;
        case '*':
        case '/':
            key = 1;
        break;
    }
    return key;
}

int MostPrior(char sym1, char sym2)
{
    if(PriorityOperation(sym1) >= PriorityOperation(sym2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string toPostfix(string infix)
{
    string postfix = "";
    int n = infix.length();
    stek<char> postf(n);
    for(int i = 0; i < n; i++)
    {
        if(infix[i] == ' ')
        {
            continue;
        }
        switch(infix[i])
        {
            case '.':
                postfix += ".";
            break;

            case '(':
                postf.push(infix[i]);
            break;

            case ')':
            {
                while(!postf.IsEmpty() && postf.top() != '(')
                {
                    postfix += " ";
                    postfix += postf.top();
                    postf.pop();
                }
                postf.pop();
            }
            break;
        }
        if(IsNumber(infix[i]))
        {
            postfix += infix[i];
            continue;
        }
        if(IsOperator(infix[i]))
        {
            postfix += " ";
            while(!postf.IsEmpty() && postf.top() != '(' && MostPrior(postf.top(),infix[i]))
            {
                postfix += postf.top();
                postfix += " ";
                postf.pop();
            }
            postf.push(infix[i]);
            continue;
        }
    }
    while(!postf.IsEmpty())
    {
        postfix += " ";
        postfix += postf.top();
        postf.pop();
    }
    return postfix;
}

void calc(string in)
{
    int n = in.length();
    stek<float> st(n);
    float res = 0;
    float num1 = 0;
    float num2 = 0;
    for (int i = 0; i < n; ++i)
    {

        if(IsOperator(in[i]))
        {
            switch(in[i])
            {
                case '+':
                {
                    num1 = st.top();
                    st.pop();
                    num2 = st.top();
                    st.pop();
                    res = num2 + num1;
                    st.push(res);
                }
                break;
                case '-':
                {
                    num1 = st.top();
                    st.pop();
                    num2 = st.top();
                    st.pop();
                    res = num2 - num1;
                    st.push(res);
                }
                break;
                case '*':
                {
                    num1 = st.top();
                    st.pop();
                    num2 = st.top();
                    st.pop();
                    res = num2*num1;
                    st.push(res);
                }
                break;
                case '/':
                {
                    num1 = st.top();
                    st.pop();
                    num2 = st.top();
                    st.pop();
                    if(num1 != 0)
                    res = num2/num1;
                    else {
                        cout << "Error" << endl;
                        return;
                    }
                    st.push(res);
                }
                break;
            }
        }
        else
        {
            float num = 0;
            float gr = 10;
            int StopFlag = 0;
            int j;
            for(j=0; ;j++)
            {
                if(in[i+j] == '.') 
                {
                    StopFlag = 1;
                    continue;
                }
                if(IsNumber(in[i+j]))
                {
                    if(!StopFlag)
                    {
                        num *= 10;
                        num += (float)(in[i+j] - '0');
                    }
                    else
                    {
                        num += (in[i+j]-'0')/gr;
                        gr *= 10;
                    }
                }
                else break;
             }
             i += j;
             st.push(num);
        }
    }
    cout << res << endl;
}

int main()
{
    string in;
    cout << "Vvedite primer\n";
    getline(cin, in);
    calc(toPostfix(in));
    return 0;
}
