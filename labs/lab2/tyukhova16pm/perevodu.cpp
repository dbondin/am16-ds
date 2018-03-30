#include "func.h"
#include "tablici.h"
using namespace std;


void win_koi()
{

    ofstream out("text.txt",ios_base::binary);
    ifstream in("posrednik.txt", ios_base::binary);
        unsigned int simvol;
        
            while(in.good())
            {
                simvol=in.get();
                if(in.eof())
                    break;
                out.write((char*)(&_win_koi[simvol]),sizeof(char));
                
            }
            
in.close();
out.close();

    remove("posrednik.txt");
    rename("text.txt","posrednik.txt");
}

void koi_win()
{
   
    ofstream out("text.txt",ios_base::binary);
    ifstream in("posrednik.txt", ios_base::binary);
        unsigned int simvol;
        
            while(in.good())
            {
                simvol=in.get();
                if(in.eof())
                    break;
                out.write((char*)(&_koi_win[simvol]),sizeof(char));
                
            }
            
in.close();
out.close();

    remove("posrednik.txt");
    rename("text.txt","posrednik.txt");
}
