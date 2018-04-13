#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
 
using namespace std;
 
struct point {
	int x, y;
	point() {};
	point(int x, int y) : x(x), y(y) {}
	bool operator< (const point &p) const 
	{
		return (x < p.x || (x == p.x && y < p.y));
	}
	bool operator== (const point &p) const 
	{
		return (x == p.x && y == p.y);
	}
};
 
struct field {
	point player, hash;
	vector <point> boxes;
	field() {};
	field(point player, vector <point> boxes) : player(player), boxes(boxes) 
	{
		hash = point(player.x-1, player.y-1);
		sort(boxes.begin(), boxes.end());
		for (int i = 0; i < boxes.size(); i++) 
		{
			hash = point(hash.x*10 + boxes[i].x-1, hash.y*10 + boxes[i].y-1);
		}
	}
	bool operator< (const field &fld) const 
	{
	return hash < fld.hash;
	}
};
 
int ans = 87654321;
queue<field> q;
map<field, int> dist;
int n, m;
vector< vector<char> > clearField, readField;
 
int empty(point p, field &fld) 
{
        if (p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= m) 
	{
                for (int i = 0; i < fld.boxes.size(); i++) 
		{
                        if (p == fld.boxes[i]) 
			{
                                return 2;
                        }
                }
                if (clearField[p.x][p.y] == '.' || clearField[p.x][p.y] == 'x') 
		{
                        return 1;
                }
        }
        return 3;
}
 
bool check(field &fld) 
{
        for (int i = 0; i < fld.boxes.size(); i++) 
	{
                if (clearField[fld.boxes[i].x][fld.boxes[i].y] != 'x') 
		{
                        return false;                  
                }
        }
        return true;
}
 
void run(field fld) 
{
        q.push(fld);
        while (!q.empty()) 
	{
                fld = q.front();
                int d = dist[fld];
                if (check(fld)) 
		{
                        ans = min(ans, d);
                }
		field newField;                
		
		//Up
		point to = point(fld.player.x - 1, fld.player.y);
                int e = empty(to, fld);
                if (e == 1) 
		{
                        newField = field(to, fld.boxes);
                        if (dist[newField] == 0) 
			{
                                dist[newField] = d + 1;
                                q.push(newField);
                        }
                }
                if (e == 2) 
		{
                        if (empty(point(fld.player.x - 2, fld.player.y), fld) == 1) 
			{
                                for (int i = 0; i < fld.boxes.size(); i++) 
				{
                                        if (to == fld.boxes[i]) 
					{
                                                fld.boxes[i].x--;
                                        }
                                }
                                fld.player.x--;
                                newField = field(fld.player, fld.boxes);
                                if (dist[newField] == 0) 
				{
                                        dist[newField] = d + 1;
                                        q.push(newField);
                                }
                                fld = q.front();
                        }
                }
                

		//Right
                to = point(fld.player.x, fld.player.y + 1);
                e = empty(to, fld);
                if (e == 1) 
		{
                        newField = field(to, fld.boxes);
                        if (dist[newField] == 0) 
			{
                                dist[newField] = d + 1;
                                q.push(newField);
                        }
                }
                if (e == 2) 
		{
                        if (empty(point(fld.player.x, fld.player.y + 2), fld) == 1) 
			{
                                for (int i = 0; i < fld.boxes.size(); i++) 
				{
                                        if (to == fld.boxes[i]) 
					{
                                                fld.boxes[i].y++;
                                        }
                                }
                                fld.player.y++;
                                newField = field(fld.player, fld.boxes);
                                if (dist[newField] == 0) 
				{
                                        dist[newField] = d + 1;
                                        q.push(newField);
                                }
                                fld = q.front();
                        }
                }
                

		//Down
                to = point(fld.player.x + 1, fld.player.y);
                e = empty(to, fld);
                if (e == 1) 
		{
                        newField = field(to, fld.boxes);
                        if (dist[newField] == 0) 
			{
                                dist[newField] = d + 1;
                                q.push(newField);
                        }
                }
                if (e == 2) 
		{
                        if (empty(point(fld.player.x + 2, fld.player.y), fld) == 1) 
			{
                                for (int i = 0; i < fld.boxes.size(); i++) 
				{
                                        if (to == fld.boxes[i]) 
					{
                                                fld.boxes[i].x++;
                                        }
                                }
                                fld.player.x++;
                                newField = field(fld.player, fld.boxes);
                                if (dist[newField] == 0) 
				{
                                        dist[newField] = d + 1;
                                        q.push(newField);
                                }
                                fld = q.front();
                        }
                }
                

		//Left
                to = point(fld.player.x, fld.player.y - 1);
                e = empty(to, fld);
                if (e == 1) 
		{
                        newField = field(to, fld.boxes);
                        if (dist[newField] == 0) 
			{
                                dist[newField ] = d + 1;
                                q.push(newField );
                        }
                }
                if (e == 2) 
		{
                        if (empty(point(fld.player.x, fld.player.y - 2), fld) == 1) {
                                for (int i = 0; i < fld.boxes.size(); i++) 
				{
                                        if (to == fld.boxes[i]) 
					{
                                                fld.boxes[i].y--;
                                        }
                                }                      
                                fld.player.y--;
                                newField = field(fld.player, fld.boxes);
                                if (dist[newField] == 0) 
				{
                                        dist[newField] = d + 1;
                                        q.push(newField);
                                }
                                	fld = q.front();
                        }
                }
                q.pop();
        }
}
 
int main () 
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n >> m;
	readField.resize(n + 2, vector <char> (m + 2, '*'));
	clearField.resize(n + 2, vector <char> (m + 2, '*'));
	field init;
	for (int i = 1; i <= n; i++) 
	{
	for (int j = 1; j <= m; j++) 
		{
			cin >> readField[i][j];
			clearField[i][j] = readField[i][j];
			if (clearField[i][j] == '$' || clearField[i][j] == '%') 
			{
				clearField[i][j] = 'x';
			}
			if (clearField[i][j] == '#' || clearField[i][j] == '@') 
			{
				clearField[i][j] = '.';
			}
			if (readField[i][j] == '@' || readField[i][j] == '%') 
			{
				init.player = point(i, j);
			}
			if (readField[i][j] == '#' || readField[i][j] == '$') 
			{
				init.boxes.push_back(point(i, j));
			}      
		}
	}
	init = field(init.player, init.boxes);
	run(init);
	if (ans == 87654321) 
	{
		ans = -1;
	}
	cout << ans << "\n"; 
}
