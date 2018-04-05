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
    void Solve(); //решение
    bool isSolved(const vector<vector<char>> &d) const;
    string FindWay();
    bool move(int x, int y, int dx, int dy, vector<vector<char>> &);//движения человека
    bool push(int x, int y, int dx, int dy, vector<vector<char>> &);//перевести коробку
    void display_move(int x, int y, int dx, int dy);//отображение человека
    void display_push(int x, int y, int dx, int dy);//отображение коробку
    void Run()
    void print(const vector<vector<char>> &) const;

private:
    vector<vector<char>> Data;
    vector<vector<char>> Data1;
    vector<vector<char>> Data2;
    int px, py;// точка человека
    string ManWay;
    static ofstream of;
};

ofstream Board::of("result.txt");

Board::Board(ifstream & f)
{
    string b = "";
    string str;
    while (getline(f, str))
    {
        b += str;
        b += '\n';
        vector<char> temp;
        for (int i = 0; i < str.size(); i++)
            temp.push_back(str[i]);
        Data.push_back(temp);
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
    //----------------------------------------------------------------------------------





    for (int v = 0; v < data.size(); ++v) {
        vector<char> Temp1, Temp2;
        for (int u = 0; u < max; ++u) {
            if (u > data[v].size()) {
                Temp1.push_back(' ');
                Temp2.push_back(' ');
            }
            else {
                char a = ' ';
                char b = ' ';
                char val = data[v][u];
                if (val == '#') a = '#';
                else
                if (val == '_' || val == '1' || val == '$') a = '_';
                if (val == '@' || val == '+')
                 {
                    b = '@';
                    px = u;
                    py = v;
                 }
                else if (val == '0' || val == '1') b = '1';
                Temp1.push_back(a);
                Temp2.push_back(b);
            }
        }
        Data1.push_back(Temp1);
        Data2.push_back(Temp2);
    }
}

void Board::Solve()
{
    ManWay = FindWay();
    if ((ManWay == "No solution") || (ManWay.size() == 0))
    {
        print(Data);
        cout << "No solution" << endl;
        Board::of << "No solution" << endl;
        return;
    }
    Run();


};

bool Board::isSolved(const vector<vector<char>> &data) const
{
    for (int v = 0; v < data.size(); ++v)
        for (int u = 0; u < data[v].size(); ++u)
            if ((Data1[v][u] == '_') ^ (data[v][u] == '1'))
                return false;
    return true;
}

string Board::FindWay()
{
    set<vector<vector<char>>> visited;
    queue<tuple<vector<vector<char>>, string, int, int>> open;

    open.push(make_tuple(Data2, "", px, py));
    visited.insert(Data2);

    array<tuple<int, int, char>, 4> dirs;
    dirs[0] = make_tuple(0, -1, 'u');	//move up
    dirs[1] = make_tuple(1, 0, 'r');	// move right
    dirs[2] = make_tuple(0, 1, 'd');	//move down
    dirs[3] = make_tuple(-1, 0, 'l');	//move left

    while (open.size() > 0) { // по ширине
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

    return "No solution";
}

bool Board::move(int x, int y, int dx, int dy, vector<vector<char>> &data)
{
    if (Data1[y + dy][x + dx] == '#' || data[y + dy][x + dx] != ' ')
        return false;

    data[y][x] = ' ';
    data[y + dy][x + dx] = '@';

    return true;
}

bool Board::push(int x, int y, int dx, int dy, vector<vector<char>> &data)
{
    if (Data1[y + 2 * dy][x + 2 * dx] == '#' || data[y + 2 * dy][x + 2 * dx] != ' ')
        return false;

    data[y][x] = ' ';
    data[y + dy][x + dx] = '@';
    data[y + 2 * dy][x + 2 * dx] = '1';

    return true;
}


void Board::print(const vector<vector<char>> &ob) const
{
    for (int i = 0; i < ob.size(); i++)
    {
        for (int j = 0; j < ob[i].size(); j++)
        {
            cout << ob[i][j];
            Board::of << ob[i][j];
        }
        cout << endl;
        Board::of << endl;
    }
}
void Board::display_push(int x, int y, int dx, int dy )
{

            if (Data[x][y] == '$')
                Data[x][y] = '_';
            else
                Data[x][y] = ' ';
            Data[x + dx][y + dy] = '@';
            if (Data[x + 2 * dx][y + 2 * dy] == '_')
                Data[x + 2 * dx][y + 2 * dy] = '1';
            else
                Data[x + 2 * dx][y + 2 * dy] = '0';

}
void Board::display_move(int x, int y, int dx , int dy )
{
            if (Data[x][y] == '$')
                Data[x][y] = '_';
            else
                Data[x][y] = ' ';
            if (Data[x + dx][y + dy] == '_')
                Data[x + dx][y + dy] = '$';
            else
                Data[x + dx][y + dy] = '@';

}

void Board::Run()
{
    print(Data);
    cout << Data[px][py]<<endl;
    for (int i = 0; i < Data.size(); i++)
        for (int j = 0; j < Data[i].size(); j++)
            if (Data[i][j] == '@') {
                px = i; py = j;
                break;
            }
    for (int i = 0; i < ManWay.size(); i++)
    {
        cout << endl << "------------" << i << " step" << "------------" << endl;
        of << endl << "------------" << i << " step" << "------------" << endl;
        switch (ManWay[i])
        {
        case 'u':
        {

            if (Data[px - 1][py] == '0')
                display_push(px, py, -1,0);
            else
                display_move(px, py, -1,0);
            px--;
            print(Data);
            break;

        }
        case 'r':
        {

            if (Data[px][py+1] == '0')
                display_push(px, py, 0,1);
            else
                display_move(px, py, 0,1);
            py++;
            print(Data);
            break;
        }
        case 'd':
        {

            if (Data[px + 1][py] == '0')
                display_push(px, py, 1, 0);
            else
                display_move(px, py, 1, 0);
            px++;
            print(Data);
            break;
        }
        case 'l':
        {

            if (Data[px ][py - 1] == '0')
                display_push(px, py, 0, -1);
            else
                display_move(px, py, 0, -1);
            py--;
            print(Data);
            break;
        }
        default:
            cout << "No Way";
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
