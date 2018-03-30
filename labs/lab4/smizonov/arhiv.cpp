#include "arhiv.h"


using namespace std;

int num_min(tree **tre, unsigned char size);
void quant_every(unsigned int *arr, ifstream &file);
void build_tree(unsigned int *arr, tree** tre, string *s, string t);
void take_codes(tree* tre, string* mass, string code);
void put_bin_to_file(string *mass, unsigned int *arr, ofstream &file1, ifstream &file);
void uncod(tree *tre, string &str, unsigned int &weigh, ofstream &file);
void write_to_file(tree* tre, ofstream &file1, ifstream &file);
tree* create(tree* left1, tree* right1);

int main()
{
    ifstream file;
    ofstream file1;
    int key;
    cout<<"Выберите действие:\n1)Закодировать файл\n2)Раскодировать файл ";
    cin>>key;
    tree *tre[255];
    string mass[255];
    string code;
    string name1, name2;
    switch (key) {
    case 1:
    {
        cout<<"Введите имя файла: ";
        cin>>name1;
        cout<<endl<<"Введите имя второго файла(в него будут записанны закодированные данные) ";
        cin>>name2;
        file.open(name1, ios::in);
        file1.open(name2, ios::binary);
        unsigned int arr[255];
       quant_every(arr, file);
       build_tree(arr, tre, mass, code);
       file.close();
       file.open(name1, ios::in);
       put_bin_to_file(mass,arr,file1,file);
       file.close();
       file1.close();
    }
      //  break;
    case 2:
    {
        cout<<"Введите имя закодированного файла: ";
        cin>>name1;
        cout<<endl<<"Введите имя второго файла(в него будут записанны раскодированные данные) ";
        cin>>name2;

        file.open(name1, ios::binary);
        file1.open(name2, ios::out);
        string pass;
        char ch;
        unsigned int arr[255];
        for(int i=0;i<4;i++)
          {  file>>ch;
           pass+=ch;  }
        if(pass!="HF16")
           { cout<<"ОШИБКА, Такой файл не подходит для раскодирования"<<endl;
            break; }
        for(int i=0;i<255;i++)
            file.read((char*)&arr[i],sizeof(arr[i]));
        build_tree(arr, tre,mass,code);
        write_to_file(tre[0],file1,file);
        file.close();
        file1.close();
    }
 //   break;
    default:
    {
        cout<<"Введите 1 или 2"<<endl;
    }
      //  break;
    }
}

void quant_every(unsigned int *arr, ifstream &file)
{
    unsigned char ch;
    for(int i=0;i<255;i++)
         arr[i]=0;

  while (!file.eof())
  {
      file>>ch;
      arr[ch]++;
  }
  arr[ch]--;
}



void build_tree(unsigned int *arr, tree** tre, string *mass, string code)
{
  unsigned int num=0;
  for (unsigned char i = 0; i < 255; i++) {
         if(arr[i]!=0)
         {
             tre[num]= new tree (arr[i],i);
         num++;
         }
      }
num--;

for (int i=0; i<num;)
{
    unsigned int min1=num_min(tre, num);
    tree *tre1= new tree(tre[min1]->get_weigh(),tre[min1]->get_ch(),tre[min1]->get_left(),tre[min1]->get_right());
    for(int t=min1; t<255; t++)
        tre[t]=tre[t+1];
    tre[255]=NULL;
   num--;
   int min2=num_min(tre, num);
   tree *tre2= new tree(tre[min2]->get_weigh(),tre[min2]->get_ch(),tre[min2]->get_left(),tre[min2]->get_right());
   for(int t=min2;t<255; t++)
       tre[t]=tre[t+1];
   tre[255]=NULL;
   tre[num]=create(tre1,tre2);
}

  take_codes(*tre,mass,code);
}

tree* create(tree* left1, tree* right1)
{
    unsigned int weig=(left1->get_weigh())+(right1->get_weigh());
    tree *new_tree= new tree(weig);
    new_tree->put_left(left1);
    new_tree->put_right(right1);
    return new_tree;
}

void take_codes(tree* tre, string* mass, string code)
{
    if(tre->get_left()!=NULL)
    {
       code+='0';
       take_codes(tre->get_left(),mass,code);
       code.pop_back();
    }
    if(tre->get_right()!=NULL)
    {
        code+='1';
        take_codes(tre->get_right(),mass,code);
        code.pop_back();
    }
    if(tre->get_left()==NULL && tre->get_right()==NULL)
    {
        mass[tre->get_ch()]=code;
    }
}

void put_bin_to_file(string *mass, unsigned int *arr, ofstream &file1, ifstream &file)
{
    string str;
    int last_part;
    char ch, byte;
    file1<<"HF16";
    for(int i=0;i<255;i++)
    {
        file1.write((char*)&arr[i],sizeof(arr[i]));
    }
    while (file.get(ch))
    {
        str+=mass[ch];
        while(str.length()>=8)
        {
            byte=0;
            for(char i=0;i<8;i++)
            {
                byte|=str[i]-'0';
               if(i<7) byte<<=1;
            }
            file1<<byte;
            str.erase(0,8);
        }
        byte=0;
        last_part=8-str.length()%8;
        for(char i=0;i<str.length();i++)
        {
            byte|=str[i]-'0';
           if(i<7) byte<<=1;
        }
        byte<<=(last_part-1);
    }

   file1<<byte;

}

void write_to_file(tree* tre, ofstream &file1, ifstream &file)
{
    char bin;
    string str;
    unsigned int weigh=tre->get_weigh();
    while (file.get(bin) && weigh)
    {
         for(char i=7;i>=0;i--)
        {
             if(bin &(0x1<<i))
             {
                 str+='1';
             } else { str+='0';}
        }
         uncod(tre,str, weigh, file1);

    }
}

void uncod(tree *tre, string &str, unsigned int &weigh,ofstream &file)
{
    tree *tr=tre;
    for(int i=0;i<str.length();i++)
    {
        if(weigh<1)
            break;

        if (str[i]=='0' && tr->get_left()!=NULL)
        {
            tr=tr->get_left();
        }
        if(str[i]=='1' && tr->get_right()!=NULL)
        {
            tr=tr->get_right();
        }
        if(tr->get_left()==NULL && tr->get_right()==NULL)
        {
            file<<tr->get_ch();
            str.erase(0,i+1);
            i=-1;
            tr=tre;
            weigh--;
        }
    }
}

int num_min(tree **tre, unsigned char size)
{
    int num=0;
    int min=tre[0]->get_weigh();
    for (int i=0; i<size+1; i++)
    {
       if(min>tre[i]->get_weigh())
         {  min=tre[i]->get_weigh();
            num=i;}
    }
    return num;
}

