#include"stek.h"

int priorityop(char operation1, char operation2);
string transformation(string primer);
void operate(string str);
 
using namespace std;
int priority(char operation)
{
	int znac=0;
	switch(operation)
	{
		case '*':
		znac=1;
		break;

		case '/':
		znac=1;
		break;

		case '^':
		znac=1;
		break;

		case '+':
		znac=2;
		break;

		case '-':
		znac=2;
		break;


		default: 
		return 0;
	}
}

int priorityop(char operation1, char operation2)
{
	int operation1First = priority(operation1);
	int operation2First = priority(operation2);
	return operation1First >= operation2First ?  true: false;
}

string transformation(string primer)
{
	int len =primer.length();
	stack<char> poi(len);
	string postf = ""; 
	for(int i = 0;i< len;i++) 
		{
			if(primer[i] == ' ') 
			continue; 
			if(primer[i] == '.')
			postf+=".";
			else if(primer[i] == '+' || primer[i] == '-' || primer[i] == '*' || primer[i] == '/') 
			{
				postf+=" "; 
				while(!poi.empty() && poi.top() != '(' && priorityop(poi.top(),primer[i]))
				{
				postf+= poi.top();
        postf+=" ";
				poi.pop();
			}
			
			poi.push(primer[i]);
		}

		else if(primer[i] >= '0' && primer[i] <= '9')
		{
			postf +=primer[i];

		}
 
		else if (primer[i] == '(') 
		{
			poi.push(primer[i]);
		}
 
		else if(primer[i] == ')') 
		{
			while(!poi.empty() && poi.top() !=  '(') 
			{
				postf+=" ";
				postf += poi.top();
				poi.pop();
			}
			poi.pop();
		}
	}
 
	while(!poi.empty()) 
	{
		postf+=" ";
		postf += poi.top();
		poi.pop();
	}
 
	return postf;
}

void operate(string str) 
{
int len =str.length();
stack<float> poi(len);
float chislo=0;
float res=0;
for (int i = 0; i < len; i++)
{
	if(str[i]==' ') 
	continue;
	switch(str[i])
        {
		case '+':
		{ 
                	float operation1=poi.top();
                	poi.pop();
                	float operation2=poi.top();
                	poi.pop();
                 	res=operation2 + operation1;
                	poi.push(res);
		}
		break;
		case '-':
		{ 
			float operation1=poi.top();
			poi.pop();
			float operation2=poi.top();
			poi.pop();
			res=operation2 - operation1;
			poi.push(res);
		}
		break;
		case '*':
		{ 
			float operation1=poi.top();
			poi.pop();
			float operation2=poi.top();
			poi.pop();
			res=operation2 * operation1;
			poi.push(res);
		}
		break;
		case '/':
		{ 
			float operation1=poi.top();
			poi.pop();
			float operation2=poi.top();
			poi.pop();
			if(operation1!=0)
			res=operation2 / operation1;
			else 
			{
				cout<<"На ноль делить нельзя!"<<endl;
			}
			poi.push(res);
		}
		break;
            
		default: 
		{
			float chislo=0;
			float gr=10;
			char flag=0;
			int j;
			for(j=0; ;j++)
			{

				if(str[i+j]=='.')
				{
					flag=1;
					continue;
				}
				if((str[i+j]>='0')&&(str[i+j]<='9'))
				{
					if(!flag)
					{
						chislo*=10;
						chislo+=(float)(str[i+j]-'0');
					}
					else
					{
						chislo+=(str[i+j]-'0')/gr;
						gr*=10;
					}

				}

				else break;
			}
			i+=j;
			poi.push(chislo);
		}
	}
}
	cout << res << endl;
}

