#include "func.h"
using namespace std;

int main()
{
    char simvol;
    int param;
    ifstream in("text.txt");
    int ashot[500];
    for(int z=0; z<500; ++z)
        {
        in>>simvol;
        ashot[z]=(int)simvol;
        }
    if(in.good())
    {
    param=opredelenie(ashot);
    
        if((param>=230)&&(param<=239))
        {
        cout<<"win->utf"<<endl;
        win_utf();
        }
        else if ((param>=200)&&(param<=209))
        {
        cout<<"koi->utf"<<endl;
        koi8r_utf();
        }
        else
        {
            int iterazia = 0;
            char ch[3] = {'n', 'n', 'n'};
            shatatel_simvolov(ashot, ch, iterazia);
        }
    }
    else
    {
    cout<<"???"<<endl;
    }
    return 0;
}
