#include "func.h"
#include "tablici.h"

    void doshatatel(char mass[3]) {
        for(int i = 0; i < 3; ++i) {
            if(mass[i] == 'k') {
                koi_win();
            }
            else if(mass[i] == 'w') {
                win_koi();
            }
        }
    }

    int shatatel_simvolov(int ashot[500], char mass[3], int iterazia)
    {
        if (iterazia >= 3) return 0;
        int win_ashot[500];
        int koi_ashot[500];
        
        for(int i=0; i<500; ++i)
        {
        win_ashot[i]=_koi_win[ashot[i]];
        koi_ashot[i]=_win_koi[ashot[i]];
        }

        int a, b;
        a=opredelenie(win_ashot);
        b=opredelenie(koi_ashot);

     if(((a>=230)&&(a<=239))){
      mass[iterazia] = 'k';//koi->win
    doshatatel(mass);
      win_utf();
      return 1;
     }
     else if((b>=230)&&(b<=239)){
        mass[iterazia] = 'w';//win->koi
        doshatatel(mass);
        win_utf();
        return 1;
     }
     else if((a>=200)&&(a<=209)) {
        mass[iterazia] = 'k';
        doshatatel(mass);
        koi8r_utf();
        return 1;
     }
     else if((b>=200)&&(b<=209)) {
         mass[iterazia] = 'w';
         doshatatel(mass);
         koi8r_utf();
         return 1;
     }
     else if(a< 200 || (a > 209 && a<230) || a > 239) {
         mass[iterazia] = 'k';
         ++iterazia;
         shatatel_simvolov(win_ashot, mass, iterazia);
     }
     else if(b< 200 || (b > 209 && b<230) || b > 239) {
         mass[iterazia-1] = 'w';
         shatatel_simvolov(win_ashot, mass, iterazia);
     }
     return 0;
    }
