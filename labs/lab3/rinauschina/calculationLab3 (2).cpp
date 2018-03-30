#include <iostream>
#include <string>
using namespace std;

template <typename T>
class stack{
		T *mExpr;
		int size;
	public:
		stack(int maxSize);
		~stack();
		void push(T value);
		T pop();
		T last();
		bool empty();
};


template <typename T>
stack<T>::stack(int maxSize)
{
    mExpr = new T[maxSize]; 
    size = 0; 
}

template <typename T>
stack<T>::~stack()
{
    delete [] mExpr; 
}
 
template <typename T>
void stack<T>::push(T value)
{
   
    mExpr[++size] = value; 
}

template <typename T>
T stack<T>::pop()
{
   if (size == 0)
        return false; 
    return mExpr[--size] ;  
}

template <typename T>
T stack<T>::last()
{
  return mExpr[size];
}


template <typename T>
bool stack<T>::empty()
{
  if(size==0)
  return 1;
         else return 0;
}



int operand_OR_operator(char _expr)
{
	if(_expr >= '0' && _expr <= '9') 
	{
		return 1;
	}else
		if(_expr == '+' || _expr == '-' || _expr == '*' || _expr == '/')
		{
			return 2;
	    } else return 0;
}


int priorOperator(char _op)
{
	int flag = 0;
	if(_op == '*' || _op == '/')
	{
		flag = 1;
	}else if(_op == '+' || _op == '-')
			{
				flag = 2;
			}
	return flag;
}


bool compareOperator(char _op1, char _op2)
{
	if(priorOperator(_op1) < priorOperator(_op2))
	{
		return true;
	}else return false;
	
}

string _postfix(string mathExpression)
{
	int len = mathExpression.length();
	stack <string> st1(len);
	string postf = ""; 
	
	for(int i = 0;i< len;i++) 
	{
		if(mathExpression[i] == ' ') continue;
		if(operand_OR_operator(mathExpression[i]) == 0) 
		{
      		postf += " "; 
			while(!st1.empty() && (st1.last() != '(') && compareOperator(st1.last(), mathExpression[i]))
			{
				postf += st1.last();
        		postf += " ";
				st1.pop();
			}
			st1.push(mathExpression[i]);
		}else if(operand_OR_operator(mathExpression))
		{
			postf += mathExpression[i];

		}else if(mathExpression[i] == '(') 
		{
			st1.push(mathExpression[i]);
		}else if(mathExpression[i] == ')') 
		{
			while(!st1.empty() && st1.last() !=  '(') 
			{
        		postf += " ";
				postf += st1.last();
				st1.pop();
			}
			st1.pop();
		}
	}
 
	while(!st1.empty()) {
    postf += " ";
		postf += st1.last();
		st1.pop();
	}
	
	return postf;
}

void calcExpression(string mathExpression) 
{
	int len = mathExpression.length();
	stack <int> st2(len);
 	int numb = 0;
 	int res = 0;
 	
    for (int i = 0; i < len; i++)
    {
        if(mathExpression[i]==' ') continue;
        switch(mathExpression[i])
        {
            case '+':
			{ 
                int op1 = st2.last();
                st2.pop();
                int op2 = st2.last();
                st2.pop();
                res = op2 + op1;
                st2.push(res);
            }break;
            
            case '-':
			{ 
                int op1 = st2.last();
                st2.pop();
                int op2 = st2.last();
                st2.pop();
                res = op2 - op1;
                st2.push(res);
            }break;
            
            case '*':
			{ 
                int op1 = st2.last();
                st2.pop();
                int op2 = st2.last();
                st2.pop();
                res = op2 * op1;
                st2.push(res);
            }break;
            
            case '/':
			{ 
                int op1 = st2.last();
                st2.pop();
                int op2 = st2.last();
                st2.pop();
                try
				{
					if(op1!=0)
						{
                 			res = op2 / op1;
                 		}	
                		else 
                		{
					throw 123;
                		}
            	}
            	catch(int i)
            	{
            		cout << "Error ¹" << i << " - division by zero!";
		}
                st2.push(res);
            }break;
            
            default: 
               {
                	int num = 0;
                	int grade = 10;
                	char flag = 0;

                	for(int j=0; ;j++)
                	{
						if(mathExpression[i+j]=='.')
                   		{
                     		flag=1;
                    		continue;
                   		}
                    	if((mathExpression[i+j] >= '0')&&(mathExpression[i+j] <= '9'))
                    	{
                      		if(!flag)
                      		{
                        		num *= 10;
                        		num += (int)(mathExpression[i+j] - '0');
                      		}else
                      			{
                        			num += (mathExpression[i+j] - '0')/grade;
                         			grade *= 10;
                      			}
						}else break;
                	}
                	i += j;
                	st2.push(num);
        		}
      }
    }
    cout << res << endl;
}


int main()
{
	string expression;
	cout << "Enter your expression: ";
	getline(cin, expression);
	cout << endl;
	
	cout << "Your expression in usual form:" << expression << endl;
	cout << "Your expression in postfix form: " << _postfix(expression) << endl;
	
	cout << "Result of your expression: ";
	calcExpression(expression);
	cout << endl;
		
	return 0;
}












