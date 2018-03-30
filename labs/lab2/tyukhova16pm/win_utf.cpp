#include "func.h"
using namespace std;

void win_utf()
{

    int d0=0xD0;
    int d1=0xD1;
    
    unsigned int simvol_win;
        ifstream in("text.txt", ios::out|ios::binary );
        ofstream out("UTF8.txt", ios::out|ios::binary);//bez binarnosti vse ploho   
            
        while(in.good())
        {
        
        simvol_win=in.get();
        
        if(in.eof()) break;
        
        if(simvol_win<128)
            {
        out.write((char*)&simvol_win,sizeof(char));
            }
     else 
     {
      if(simvol_win==168)//strashnaya Ё
     {
     simvol_win=simvol_win+0xCFD9;
     out.write((char*)d0,sizeof(char));
     }
     
     else if(simvol_win==184)//strashnaya ё
     {
     simvol_win=simvol_win+0xCFD9;
     out.write((char*)&d1,sizeof(char));
     }
     
     else if((simvol_win>=128)&&(simvol_win<=239))//ostalnyue norm bukvu
     {
     simvol_win=simvol_win+0xCF90;
     out.write((char*)&d1,sizeof(char));
     }
     out.write((char*)&simvol_win,sizeof(char));
          }    
         }
         
     in.close();
     out.close();
}     
        
        

