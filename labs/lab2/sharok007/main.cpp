#include"tables.hpp"

void Win_to_Utf();//перекодировка Win1251 в UTF-8
void Koi_to_Utf();//перекодировка Koi-8R в UTF-8

vector<unsigned int> loading(char (&name_file)[32]);//считываем данные из файла
int identify(vector<unsigned int> &in);//определяем кодировку
int decode(vector<unsigned int> input, int (&win_way)[3], int num);//определение кол-ва изменений
void decryptor(int way[3]);//промежуточная запись

void file_Koi_to_Win();//промежуточная запись перекодировки из Koi-8R в Win1251 в файл
void file_Win_to_Koi();//промежуточная запись перекодировки из Win1251 в Koi-8R в файл

void Koi_to_Win(vector<unsigned int> input, vector<unsigned int> &win);//перекодировка из Koi-8R в Win1251
void Win_to_Koi(vector<unsigned int> input, vector<unsigned int> &koi);//перекодировка из Win1251 в Koi-8R

vector<unsigned int> loading(char (&name_file)[32]) {
  vector<unsigned int> input;
  unsigned char symbol;
  int quantity = 0;
  ifstream fin(name_file);
  if(!fin){
      cout<<"Файл не найден :("<<endl;
  }
  while(fin.good()) {
      fin >> symbol;
      quantity++;
      input.push_back((unsigned int)symbol);
      if (quantity == 1000) break;
  }
  rename(name_file,"text.txt");
  fin.close();
  return input;
}

int identify(vector<unsigned int> &in) {
    unsigned int i;
    int symbol = 0;
    int quantity = 0;
    int result = 0;
    for(i = 0; i < in.size(); ++i) {
        if(in[i] > 191 && in[i] < 256) {
            symbol += in[i];
            quantity++;
        }
    }
    result = symbol/quantity;
    if(result > 231 && result < 243)      return 1251;
    else if(result > 200 && result < 212) return 8;
    else                                    return 0;
}

int decode(vector<unsigned int> input, int (&win_way)[3], int num) {
  int key = identify(input);
  if(key == 8)
  {
      Koi_to_Utf();
      return 0;
 }
  else if(key == 1251)
  {
      Win_to_Utf();
      return 0;
  }
  if(num > 3) return -1;

  int win_key;
  int koi_key;
  vector<unsigned int> koi8;
  vector<unsigned int> win1251;
  int koi_way[3];

  Koi_to_Win(input, win1251);
  win_key = identify(win1251);
  win_way[num] = 1251;

  if(win_key == 8)
  {
      decryptor(win_way);
      Koi_to_Utf();
      return 0;
  }
  else if(win_key == 1251)
  {
      decryptor(win_way);
      Win_to_Utf();
      return 0;
  }
  else if(win_key == 0)
  {
      ++num;
      decode(win1251, win_way, num);
      return 0;
  }

  Win_to_Koi(input, koi8);
  koi_key = identify(koi8);
  koi_way[num] = 8;

  if(koi_key == 8)
  {
      decryptor(koi_way);
      Koi_to_Utf();
      return 0;
  }
  else if(koi_key == 1251)
  {
      decryptor(koi_way);
      Win_to_Utf();
      return 0;
  }
  else if(koi_key == 0)
  {
      decode(koi8, koi_way, num);
      return 0;
  }
}

void decryptor(int way[3]) {
  int i;
  for(i = 0; i < 3; i++){
      if(way[i] == 1251)      file_Koi_to_Win();
      else if(way[i] == 8)    file_Win_to_Koi();
  }
}


void file_Koi_to_Win() {
    ofstream fout("intermediate.txt", ios_base::binary);
    ifstream fin("text.txt", ios_base::binary);
    unsigned int symbol;
    while(fin.good())
    {
      symbol=fin.get();
      if(fin.eof())
          break;
      fout.write((char*)(&koi_to_win[symbol]),sizeof(char));
    }
    fin.close();
    fout.close();
    remove("text.txt");
    rename("intermediate.txt","text.txt");
}

void file_Win_to_Koi() {
    ofstream fout("intermediate.txt", ios_base::binary);
    ifstream fin("text.txt", ios_base::binary);
    unsigned int symbol;
    while(fin.good())
    {
      symbol=fin.get();
      if(fin.eof())
          break;
      fout.write((char*)(&win_to_koi[symbol]),sizeof(char));
    }
    fin.close();
    fout.close();
    remove("text.txt");
    rename("intermediate.txt","text.txt");
}

void Koi_to_Win(vector<unsigned int> input, vector<unsigned int> &win) {
    unsigned  int i;
    for(i = 0; i < input.size(); ++i) {
        win.push_back(koi_to_win[input[i]]);
    }
}

void Win_to_Koi(vector<unsigned int> input, vector<unsigned int> &koi) {
    unsigned  int i;
    for(i = 0; i < input.size(); ++i) {
        koi.push_back(win_to_koi[input[i]]);
    }
}

void Koi_to_Utf() {
    ofstream fout("koi_utf8.txt", ios_base::binary);
    ifstream fin("text.txt", ios_base::binary);
    unsigned int symbol;
    while(fin.good())
    {
      symbol=fin.get();
      if(fin.eof())
          break;
      if(symbol < 128)
      {
        fout.write((char*)(&koi_to_utf[symbol][0]),sizeof(char));
      }
      else
      {
        fout.write((char*)(&koi_to_utf[symbol][0]),sizeof(char));
        fout.write((char*)(&koi_to_utf[symbol][1]),sizeof(char));
      }
    }
    system("clear");
    cout<<"Результат записан в фаил koi_utf8.txt :)"<<endl;
    fin.close();
    fout.close();
}

void Win_to_Utf() {
    ofstream fout("win_utf8.txt", ios_base::binary);
    ifstream fin("text.txt", ios_base::binary);
    unsigned int symbol;
    while(fin.good())
    {
      symbol=fin.get();
      if(fin.eof())
          break;
      if(symbol < 128)
      {
        fout.write((char*)(&win_to_utf[symbol][0]),sizeof(char));
      }
      else
      {
        fout.write((char*)(&win_to_utf[symbol][0]),sizeof(char));
        fout.write((char*)(&win_to_utf[symbol][1]),sizeof(char));
      }
    }
    system("clear");
    cout<<"Результат записан в фаил win_utf8.txt :)"<<endl;
    fin.close();
    fout.close();
}

int main()
{
    char name_file[32];
    cout<<"Введите название файла:";
    cin>>name_file;
    vector<unsigned int> input = loading(name_file);
    int way[3] = { 0, 0, 0 };
    decode(input, way, 0);
    input.clear();
    return 0;
}

