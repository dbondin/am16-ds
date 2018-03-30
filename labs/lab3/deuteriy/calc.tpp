bool check_operand(char oper)
{
	if(oper >= '0' && oper <= '9') 
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool check_operator(char oper)
{
	if(oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '^')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int priority(char oper)
{
	int prior = 0; 
	switch(oper)
	{
		case '+':
		case '-':
			prior = 1;
    			break;
		case '*':
		case '/':
			prior = 2;
			break;
		case '^':
			prior = 3;
			break; 
	}
	return prior;
}

int choise_priority(char oper1, char oper2)
{
	int oper1_v = priority(oper1);
	int oper2_v = priority(oper2);
	if(oper1_v >= oper2_v)
	{
		return 1;
	}
	else
	{
		return 0;	
	} 
}

string infixToPostfix(string exp)
{
	int len = exp.size();
	stack<char> infix;
	string postfix = ""; 
	for(int i = 0; i < len; ++i) 
	{
		if(exp[i] == ' ')
		{
			continue; 
		}
     		if(exp[i] == '.')
		{
		        postfix+=".";
		}
		else 
		{
			if(check_operator(exp[i])) 
			{
				postfix+=" "; 
				while(infix.size() != 0 && infix.last() != '(' && choise_priority(infix.last(), exp[i]))
				{
					postfix += infix.last();
					postfix += " ";
					infix.pop();
				}
			
				infix.push(exp[i]);
			}
			else 
			{
				if(check_operand(exp[i]))
				{
					postfix += exp[i];
				}
				else 
				{
					if (exp[i] == '(') 
					{
						infix.push(exp[i]);
					}
					else 
					{
						if(exp[i] == ')') 	
						{
							while(infix.size() != 0 && infix.last() !=  '(') 
							{
	       							postfix += " ";
								postfix += infix.last();
								infix.pop();
							}
							infix.pop();
						}
					}
				}
 			}
		}
	}
	while(infix.size() != 0) 
	{
		postfix += " ";
		postfix += infix.last();
		infix.pop();
	}
	return postfix;
}


void calculate(string postfix)
{
	int len =postfix.size();
	stack<float> s_result;
	float digit=0;
	float result=0;
	for (int i = 0; i < len; ++i)
	{
		if(postfix[i]==' ') 
			{
				continue;
			}
		switch(postfix[i])
		{
			case '+':
				{ 
					float oper1 = s_result.last();
					s_result.pop();
					float oper2 = s_result.last();
					s_result.pop();
					result = oper2 + oper1;
					s_result.push(result);
				}
				break;
			case '-':
				{ 
					float oper1 = s_result.last();
					s_result.pop();
					float oper2 = s_result.last();
					s_result.pop();
					result = oper2 - oper1;
					s_result.push(result);
				}
				break;
			case '*':
				{ 
					float oper1 = s_result.last();
					s_result.pop();
					float oper2 = s_result.last();
					s_result.pop();
					result = oper2 * oper1;
					s_result.push(result);
				}
				break;
			case '/':
				{ 
					float oper1 = s_result.last();
					s_result.pop();
					float oper2 = s_result.last();
					s_result.pop();
					if(oper1 != 0)
					{
						result = oper2 / oper1;
					}
					else 
					{
						cerr<<"You can't divide by zero!"<<endl;
					}
					s_result.push(result);
				}
				break;
			case '^':
				{ 
					float oper1 = s_result.last();
					s_result.pop();
					float oper2 = s_result.last();
					s_result.pop();
					result = pow(oper2, oper1);
					s_result.push(result);
				}
				break;
			default: 
				{
					float d = 0;
					float grade = 10;
					int flag = 0;
					int j;
					for(j = 0;; ++j)
					{
						if(postfix[i+j] == '.')
						{
							flag = 1;
							continue;
						}
						if((postfix[i+j]>='0') && (postfix[i+j]<='9'))
						{
							if(!flag)
							{
								d *= 10;
								d += (float)(postfix[i+j] - '0');
							}
							else
							{
								d += (postfix[i+j] - '0') / grade;
								grade *= 10;
							}
						}
						else 
						{
							break;
						}
					}	
					i += j;
					s_result.push(d);
					
				}
		}
	}
	cout << "Result = " << result << endl;
}

