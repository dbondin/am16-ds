#include "func.h"
using namespace std;

void koi8r_utf()
{
    int d0=0xD0;
    int d1=0xD1;
    
     unsigned int simvol_koi=0;
        ifstream in("text.txt", ios::out|ios::binary);
        ofstream out("UTF8.txt", ios::out|ios::binary);
       
        
unsigned int table[]=
  {0x00fe, 0x0020, 0x0021, 0x00f6, 0x0024,0x0025, 0x00f4, 0x0023, 
  0x00f5, 0x0028, 0x0029, 0x002a, 0x002b,0x002c, 0x002d, 0x002e, 
  0x002f, 0x00ff, 0x00f0, 0x00f1, 0x00f2,0x00f3, 0x0026, 0x0022,
  0x00fc, 0x00fb, 0x0027, 0x00f9, 0x00fd,0x00f9, 0x00f7, 0x00fa, 
  0x001e, 0x0000, 0x0001, 0x0016, 0x0004,0x0005, 0x0014, 0x0003,
  0x0015, 0x0008, 0x0009, 0x000a, 0x000b,0x000c, 0x000d, 0x000e, 
  0x000f, 0x001f, 0x0010, 0x0011, 0x0012,0x0013, 0x0006, 0x0002, 
  0x001c, 0x001b, 0x0007, 0x0019, 0x001d, 0x0019, 0x0017, 0x001a};
  
while (in.good()) {
    
simvol_koi=in.get();
if(in.eof())
break;
        
        if(simvol_koi<128)
            {
            out.write((char*)&simvol_koi,sizeof(char));
            }
            
            else
            {
            if(simvol_koi==179)
            {
            simvol_koi=simvol_koi+0xCFCE;
            out.write((char*)&d0,sizeof(char));
            }
            else if(simvol_koi==163)
            {
            simvol_koi=simvol_koi+0xD0EE;
            out.write((char*)&d1,sizeof(char));
            }
            else
            {
            simvol_koi=table[simvol_koi-0xc0]+0xd090;
            if(simvol_koi<0xd100)
            {
            out.write((char*)&d0,sizeof(char));
            }
            else
            {
            out.write((char*)&d1,sizeof(char));
            }
            }
            
            out.write((char*)&simvol_koi,sizeof(char));
            }
        }
  
  in.close();
  out.close();
}
