#include "stack.h"

//Actually stack
string Replacement(string term)
{
  int T =term.length();
	Stack<char> N(T);
	string post = "";
	for(int i = 0;i< T;i++) {

		if(term[i] == ' ') 
		continue; 
            if(term[i] == '.')
            post+=".";
                else if(symb(term[i])) 
                {
                post+=" ";
                
                    while(!N.empty() && N.top() != '(' && Use_priority(N.top(),term[i]))
                    {
                    post+= N.top();
                    post+=" ";
                    N.pop();
                    }
                N.push(term[i]);
                }

        else if(numb(term[i]))
		{
			post+=term[i];

		}
 
		else if (term[i] == '(') 
		{
			N.push(term[i]);
		}
 
		else if(term[i] == ')') 
		{
			while(!N.empty() && N.top() !=  '(') {
        post+=" ";
				post+= N.top();
				N.pop();
			}
			N.pop();
		}
	}
 
	while(!N.empty()) {
    post+=" ";
		post+= N.top();
		N.pop();
	}
 
	return post;
}

//The process
void Proc(string ingoing)
{
 int T =ingoing.length();
 
 Stack<float> N(T);
 float res=0;
    for (int i = 0; i < T; i++)
      {
        if(ingoing[i]==' ') 
        continue;
             switch(ingoing[i])
        {
            case '+':
            {
                float sym1=N.top();
                N.pop();
                float sym2=N.top();
                N.pop();
                 res=sym2 + sym1;
                N.push(res);
            }
            break;
            
            case '-':
            { 
                float sym1=N.top();
                N.pop();
                float sym2=N.top();
                N.pop();
                 res=sym2 - sym1;
                N.push(res);
            }
            break;
            
            case '*':
            { 
                float sym1=N.top();
                N.pop();
                float sym2=N.top();
                N.pop();
                 res=sym2 * sym1;
                N.push(res);
            }
            break;
                  
            case '/':
            { 
                float sym1=N.top();
                N.pop();
                float sym2=N.top();
                N.pop();
                if(sym1!=0)
                 res=sym2 / sym1;
                else 
                  {
                  cout<<"Pls don't do like that: any number/zero"<<endl;
                  break;
                  }
                  
                N.push(res);
            }
            break;
            
            default:
               {
                 float numeral=0;
                 float rank=10;
                 char f=0;
                 int j;
                 for(j=0; ;j++)
                 {

                   if(ingoing[i+j]=='.')
                   {
                     f=1;
                     continue;
                   }
                    if((ingoing[i+j]>='0')&&(ingoing[i+j]<='9'))
                    {
                      if(!f)
                      {
                        numeral*=10;
                        numeral+=(float)(ingoing[i+j]-'0');
                      }
                      else
                      {
                        numeral+=(ingoing[i+j]-'0')/rank;
                         rank*=10;
                      }

                    }
                    else break;
                 }
                 i+=j;
                 
                 N.push(numeral);
        }
      }
    }
    cout << res << endl;
}
