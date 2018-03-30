#include "calc.h"

bool is_operand(char operand);
bool is_operator(char op);
 int higherPrecedence(char op1, char op2);
 string sourceToFinal(string expression);
void calculate(string input);


string sourceToFinal(string expression)
{
  int len =expression.length();
	stack<char> wut(len);
	string postfix = ""; 
	for(int i = 0;i< len;i++) {

		if(expression[i] == ' ') continue; 
     if(expression[i] == '.')
        postfix+=".";
		else if(is_operator(expression[i])) 
		{
      postfix+=" "; 
			while(!wut.empty() && wut.last() != '(' && higherPrecedence(wut.last(),expression[i]))
			{
				postfix+= wut.last();
        postfix+=" ";
				wut.pop();
			}
			
			wut.push(expression[i]);
		}

		else if(is_operand(expression[i]))
		{
			postfix +=expression[i];

		}
 
		else if (expression[i] == '(') 
		{
			wut.push(expression[i]);
		}
 
		else if(expression[i] == ')') 
		{
			while(!wut.empty() && wut.last() !=  '(') {
        postfix+=" ";
				postfix += wut.last();
				wut.pop();
			}
			wut.pop();
		}
	}
 
	while(!wut.empty()) {
    postfix+=" ";
		postfix += wut.last();
		wut.pop();
	}
 
	return postfix;
}
 

bool is_operand(char operand) 
{
	if(operand >= '0' && operand <= '9') return true;

	return false;
}
 

bool is_operator(char op)
{
	if(op == '+' || op == '-' || op == '*' || op == '/')
		return true;
 
	return false;
}
 
int firstUse(char op)
{
	int weight = 0; 
	switch(op)
	{
	case '+':
	case '-':
		weight = 1;
    break;
	case '*':
	case '/':
    weight = 2;
	}
	return weight;
}

int higherPrecedence(char op1, char op2)
{
	int op1First = firstUse(op1);
	int op2First = firstUse(op2);
	return op1First >= op2First ?  true: false;
}



void calculate(string input) 
{
  int len =input.length();
 stack<float> wut(len);
 float digit=0;
 float result=0;
    for (int i = 0; i < len; i++)
      {
        if(input[i]==' ') continue;
             switch(input[i])
        {
            case '+':{ // if +
                float op1=wut.last();
                wut.pop();
                float op2=wut.last();
                wut.pop();
                 result=op2 + op1;
                wut.push(result);
            }break;
              case '-':{ 
                float op1=wut.last();
                wut.pop();
                float op2=wut.last();
                wut.pop();
                 result=op2 - op1;
                wut.push(result);
            }break;
                case '*':{ 
                float op1=wut.last();
                wut.pop();
                float op2=wut.last();
                wut.pop();
                 result=op2 * op1;
                wut.push(result);
            }break;
                  case '/':{ 
                float op1=wut.last();
                wut.pop();
                float op2=wut.last();
                wut.pop();
                if(op1!=0)
                 result=op2 / op1;
                else 
                  {cerr<<"Division by zero!"<<endl;
                 }
                wut.push(result);
            }break;
            
            default: 
               {
                 float digit=0;
                 float grade=10;
                 char flag=0;
                 int j;
                 for(j=0; ;j++)
                 {

                   if(input[i+j]=='.')
                   {
                     flag=1;
                     continue;
                   }
                    if((input[i+j]>='0')&&(input[i+j]<='9'))
                    {
                      if(!flag)
                      {
                        digit*=10;
                        digit+=(float)(input[i+j]-'0');
                      }
                      else
                      {
                        digit+=(input[i+j]-'0')/grade;
                         grade*=10;
                      }

                    }

                    else break;
                 }
                 i+=j;
                 wut.push(digit);
        }
      }
    }
    cout << result << endl;
}


int main() 
{
    string expression ="35.98*55.5";
    cout<<"Source expression = "<<expression<<endl;
    string postfix = sourceToFinal(expression);
    cout<<"Final expression = "<<postfix<<endl;
    calculate( postfix);
    
}
