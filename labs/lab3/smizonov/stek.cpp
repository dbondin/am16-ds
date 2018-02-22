#include "stek.h"




int weigh(char ch);
bool in_what_stek(char ch);
float calcul(string st);



float calcul(string st)
{
    stek<char> st_1(st.length()*2);
    stek<char> st_2(st.length());

    for(int i=0;i<st.length();i++)
    {
        switch (st[i]) {

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
        case '.':
           { st_1.push(st[i]);
            break;
           }
        case '(':
            {
            st_2.push(st[i]);
            break;
             }
        case ')':
        {

           while(st_2.show()!='(')
           {
               st_1.push(st_2.pop());
           }
           st_2.pop();
           break;
        }
        case'*':
        case'/':
        case'+':
        case'-':
        case'^':
    {
        if (weigh(st[i])<=weigh(st_2.show()))
        {
            st_1.push(st_2.pop());
            st_2.push(st[i]);
            st_1.push(' ');
            break;
        } else {
              st_2.push(st[i]);
              st_1.push(' ');
              break;
        }
    }
        default:
            break;
        }
    }

      while (st_2.get_num())
        {
        st_1.push(st_2.pop());
        }

      stek<float> st_4(st_1.get_num());


  double f1, f2, result;
  char str[60];
  int index=0;

    for (int i=0; i<st_1.get_size(); )
    {
        switch(st_1.show(i))
        {
        case'*':
        {
            f1=st_4.pop();
            f2=st_4.pop();
            result=f2*f1;
            st_4.push(result);
            i++;
            break;
        }
        case'/':
        {
            f1=st_4.pop();
            f2=st_4.pop();
            result=f2/f1;
            st_4.push(result);
            i++;
            break;
        }
        case'+':
        {
            f1=st_4.pop();
            f2=st_4.pop();
            result=f1+f2;
            st_4.push(result);
            i++;
            break;
        }
        case'-':
        {
            f1=st_4.pop();
            f2=st_4.pop();
            result=f2-f1;
            st_4.push(result);
            i++;
            break;
        }
        case'^':
        {
            f1=st_4.pop();
            f2=st_4.pop();
            result=pow(f2,f1);
            st_4.push(result);
            i++;
            break;
        }
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
        case '.':
        {
        while (st_1.show(i)!=' ' && st_1.show(i)!='*' && st_1.show(i)!='/'
              && st_1.show(i)!='+' && st_1.show(i)!='-' &&st_1.show(i)!='^' )
            {
                str[index]=st_1.show(i);
                i++;
                index++;
            }

            f1=atof(str);
            st_4.push(f1);
            index++;
            while (index!=0)
            {

                index--;
                str[index]=' ';

            }
            break;
        }
        default:
        {
            i++;
            break;
        }
        }
    }

    return st_4.pop();
}



int weigh(char ch)
{
                int weig;
                switch (ch) {
            case '^':
                {
                    weig = 4;
                    break;
                }
            case '*':
            case'/':
               {
                    weig = 3;
                    break;
                }
            case'+':
            case'-':
               {
                    weig=2;
                    break;
                }
            case'(':
            case')':
                {
                     weig=1;
                     break;
                }
            default:
                break;
        }
                return weig;
        }


int main()
{
 string s;
 cout<<"Enter the arithmetic expression: ";

 getline(cin,s);

 float t=calcul(s);
 cout<<endl<<"Result ="<<t<<endl;
}


