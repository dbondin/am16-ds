#include "func.h"
using namespace std;

int opredelenie(int ashot[500])
{

    int summa=0;
    int diapazon=NULL;
    int i=0; //prosto mister schetchik
    
    unsigned  char mainsimvol=NULL;
    
       for(int z=0; z<500; ++z)
        {
            if((ashot[i]>127)&&(ashot[i]<255))
            {
            summa+=ashot[i];
            ++i;
            }
        }
        
        
        diapazon=summa/i;
        
return diapazon;
}
