#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <regex>
#include <tuple>
#include <set>
#include <array>
#include <fstream>
using namespace std;

class Board
{
public:
    Board(ifstream & f);
    void Solve(); 
    bool isSolved(const vector<vector<char>> &d) const;
    string FindWay();
    bool move(int x, int y, int dx, int dy, vector<vector<char>> &);
    bool push(int x, int y, int dx, int dy, vector<vector<char>> &);
    void display_move(int x, int y, int dx, int dy);
    void display_push(int x, int y, int dx, int dy);
    void Run();
    void print(const vector<vector<char>> &) const;

private:
    vector<vector<char>> Data; 
    vector<vector<char>> EmptyMatix; 
    vector<vector<char>> Matix; 
    int px, py;
    string RightWay;
    static ofstream of;
};

ofstream Board::of("result.txt");

Board::Board(ifstream & f)
{

    
    string b = "";
    string str;
    while (getline(f, str))
    {
        b += str;  b += '\n';  // Data записана линейно построчно с разделителями '\n'
        vector<char> temp;
        for (int i = 0; i < str.size(); i++) temp.push_back(str[i]);
        Data.push_back(temp);  //Data как матрица
    }

    regex p("([^\\n]+)\\n?");
    sregex_iterator end, iter(b.begin(), b.end(), p);

    int max = 0;
    vector<string> data;
    for (; iter != end; ++iter) {
        data.push_back((*iter)[1]);
        if (max < (*iter)[1].length())
            max = (*iter)[1].length();
    }
    
    //создаем EmptyMatix ;
    for (int _y = 0; _y < data.size(); ++_y) {
        vector<char> T1, T2;
        for (int _x = 0; _x < max; ++_x) {
            if (_x > data[_y].size()){ T1.push_back(' '); T2.push_back(' '); }
            else {
                char a = ' ', b = ' ', val = data[_y][_x];
                switch(val){
                  case '#': a = '#'; break;
                  case '_':
                  case '1':
                  case '$': a = '_'; break;
                  case '@':
                  case '+': b = '@'; px = _x; py = _y; break;
                  case '0':
                  case '1': b = '1'; break;
                }
                T1.push_back(a); T2.push_back(b);
            }
        }
        EmptyMatix.push_back(T1);
        Matix.push_back(T2);
    }
}

void Board::Solve()
{
    RightWay = FindWay();
    if ((RightWay == "No Rezult") || (RightWay.size() == 0)){
        print(Data);
        cout << "No Rezult" << endl;
        Board::of << "No Rezult" << endl;
        return;
    }
    Run();
};

bool Board::isSolved(const vector<vector<char>> &data) const
{
    for (int v = 0; v < data.size(); ++v)
        for (int u = 0; u < data[v].size(); ++u)
            if ((EmptyMatix[v][u] == '_') ^ (data[v][u] == '1'))
                return false;
    return true;
}

string Board::FindWay()
{
    set<vector<vector<char>>> visited; // уже просмотренные позиции, чтобы мы не ходили по кругу
    queue<tuple<vector<vector<char>>, string, int, int>> open; 

    open.push(make_tuple(Matix, "", px, py));
    visited.insert(Matix);

    array<tuple<int, int, char>, 4> dirs; //координаты для перемещения
    dirs[0] = make_tuple(0, -1, 'u');	// up
    dirs[1] = make_tuple(1, 0, 'r');	//  right
    dirs[2] = make_tuple(0, 1, 'd');	// down
    dirs[3] = make_tuple(-1, 0, 'l');	// left

    while (open.size() > 0) { 
        vector<vector<char>> temp, cur = get<0>(open.front());
        string cSol = get<1>(open.front());
        int x = get<2>(open.front()); 
        int y = get<3>(open.front()); 
        open.pop();

        for (int i = 0; i < 4; ++i) {
            temp = cur;
            int dx = get<0>(dirs[i]);
            int dy = get<1>(dirs[i]);

            if (temp[y + dy][x + dx] == '1') {
                if (push(x, y, dx, dy, temp) && (visited.find(temp) == visited.end())) {
                    if (isSolved(temp))
                        return cSol + get<2>(dirs[i]);
                    open.push(make_tuple(temp, cSol + get<2>(dirs[i]), x + dx, y + dy));
                    visited.insert(temp);
                }
            }
            else if (move(x, y, dx, dy, temp) && (visited.find(temp) == visited.end())) {
                if (isSolved(temp))
                    return cSol + get<2>(dirs[i]);
                open.push(make_tuple(temp, cSol + get<2>(dirs[i]), x + dx, y + dy));
                visited.insert(temp);
            }
        }
    }
    return "No Rezult";
}

bool Board::move(int _x, int _y, int _dx, int _dy, vector<vector<char>> &data)
{
    if (EmptyMatix[_y + _dy][_x + _dx] == '#' || data[_y + _dy][_x + _dx] != ' ')
        return false;
    data[_y][_x] = ' ';
    data[_y + _dy][_x + _dx] = '@';
    return true;
}

bool Board::push(int x, int y, int dx, int dy, vector<vector<char>> &data)
{
    if (EmptyMatix[y + 2 * dy][x + 2 * dx] == '#' || data[y + 2 * dy][x + 2 * dx] != ' ')
        return false;

    data[y][x] = ' ';
    data[y + dy][x + dx] = '@';
    data[y + 2 * dy][x + 2 * dx] = '1';

    return true;
}


void Board::print(const vector<vector<char>> &_ob) const
{
    for(int i = 0; i < _ob.size(); i++){
        for (int j = 0; j < _ob[i].size(); j++){ cout << _ob[i][j];  Board::of << _ob[i][j]; }
        cout << endl;
        Board::of << endl;
    }
}

void Board::display_push(int x, int y, int dx, int dy )
{
    if(Data[x][y] == '$') Data[x][y] = '_';
    else                  Data[x][y] = ' ';
    Data[x + dx][y + dy] = '@';
    if(Data[x + 2 * dx][y + 2 * dy] == '_') Data[x + 2 * dx][y + 2 * dy] = '1';
    else                                    Data[x + 2 * dx][y + 2 * dy] = '0';
}

void Board::display_move(int x, int y, int dx , int dy )
{
            if(Data[x][y] == '$') Data[x][y] = '_';
            else                  Data[x][y] = ' ';
            if (Data[x + dx][y + dy] == '_') Data[x + dx][y + dy] = '$';
            else                             Data[x + dx][y + dy] = '@';
}

void Board::Run()
{
    print(Data);
    cout << Data[px][py]<<endl;
    for (int i = 0; i < Data.size(); i++)
        for (int j = 0; j < Data[i].size(); j++)
            if(Data[i][j] == '@'){ px = i; py = j; break; }
    for (int i = 0; i < RightWay.size(); i++){
        cout << endl << "____________" << i << " step" << "____________" << endl;
        of << endl << "____________" << i << " step" << "____________" << endl;

        switch (RightWay[i]){
          case 'u':
              if(Data[px - 1][py] == '0') display_push(px, py, -1,0);
              else                        display_move(px, py, -1,0);
              px--;
              print(Data); break;
          case 'r':
              if (Data[px][py+1] == '0') display_push(px, py, 0,1);
              else                       display_move(px, py, 0,1);
              py++;
              print(Data); break;
          case 'd':
              if(Data[px + 1][py] == '0') display_push(px, py, 1, 0);
              else                        display_move(px, py, 1, 0);
              px++;
              print(Data); break;
          case 'l':
              if (Data[px ][py - 1] == '0') display_push(px, py, 0, -1);
              else                          display_move(px, py, 0, -1);
              py--;
              print(Data); break;
          default: cout << "No Way";
        }
    }
}
int main()
{
    ifstream f("input.txt");

    Board b(f);

    b.Solve();
    return 0;
}
