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
 
struct tchk
{
	int x, y;
	tchk() {};
	tchk(int x, int y) : x(x), y(y) {};
	bool operator< (const tchk & t) const 
	{
		return (x < t.x || (x == t.x && y < t.y));
	}
	bool operator== (const tchk &t) const 
	{
		return (x == t.x && y == t.y);
	}
};
 
struct mp
{
	tchk men, hash;
	vector <tchk> box;
	mp() {};
	mp(tchk men, vector <tchk> box) : men(men), box(box) 
	{
		hash = tchk(men.x - 1, men.y - 1);
		sort(box.begin(), box.end());
		for (int i = 0; i < box.size(); i++) 
		{
			hash = tchk(hash.x * 10 + box[i].x - 1, hash.y * 10 + box[i].y - 1);
		}
	}
	bool operator< (const mp &m) const 
	{
		return hash < m.hash;
	}
};
 
int ans = 87654321;
queue <mp> q;
map <mp, int> dis;
int n, m;
vector <vector <char> > clear, read;
 
int empty(tchk t, mp &map) 
{
	if (t.x >= 1 && t.x <= n && t.y >= 1 && t.y <= m) 
	{
		for (int i = 0; i < map.box.size(); i++) 
		{
			if (t == map.box[i]) 
			{
				return 2;
			}
		}
		if (clear[t.x][t.y] == '.' || clear[t.x][t.y] == 'x') 
		{
			return 1;
		}
	}
	return 3;
}
 
bool check(mp &v) 
{
	for (int i = 0; i < v.box.size(); i++) 
	{
		if (clear[v.box[i].x][v.box[i].y] != 'x') 
		{
			return false;                  
		}
	}
	return true;
}
 
void actions(mp v) 
{
	q.push(v);
	while (!q.empty()) 
	{
		v = q.front();
		int d = dis[v];
		if (check(v)) 
		{
			ans = min(ans, d);
		}
		tchk to = tchk(v.men.x - 1, v.men.y);
		int em = empty(to, v);
		mp newmp;
                
		if (em == 1) 
		{
			newmp = mp(to, v.box);
			if (dis[newmp] == 0) 
			{
				dis[newmp] = d + 1;
				q.push(newmp);
			}
		}
		if (em == 2) 
		{
			if (empty(tchk(v.men.x - 2, v.men.y), v) == 1) 
			{
				for (int i = 0; i < v.box.size(); i++) 
				{
					if (to == v.box[i]) 
					{
						v.box[i].x--;
					}
				}
				v.men.x--;
				newmp = mp(v.men, v.box);
				if (dis[newmp] == 0) 
				{
					dis[newmp] = d + 1;
					q.push(newmp);
				}
				v = q.front();
			}
		}
                
		to = tchk(v.men.x, v.men.y + 1);
		em = empty(to, v);
		if (em == 1) 
		{
			newmp = mp(to, v.box);
			if (dis[newmp] == 0) 
			{
				dis[newmp] = d + 1;
				q.push(newmp);
			}
		}
		if (em == 2) 
		{
			if (empty(tchk(v.men.x, v.men.y + 2), v) == 1) 
			{
				for (int i = 0; i < v.box.size(); i++) 
				{
					if (to == v.box[i]) 
					{
						v.box[i].y++;
					}
				}
                                v.men.y++;
				newmp = mp(v.men, v.box);
				if (dis[newmp] == 0) 
				{
					dis[newmp] = d + 1;
					q.push(newmp);
				}
				v = q.front();
			}
		}
            
		to = tchk(v.men.x + 1, v.men.y);
		em = empty(to, v);
		if (em == 1) 
		{
			newmp = mp(to, v.box);
			if (dis[newmp] == 0) 
			{
				dis[newmp] = d + 1;
				q.push(newmp);
			}
		}
		if (em == 2) 
		{
			if (empty(tchk(v.men.x + 2, v.men.y), v) == 1) 
			{
				for (int i = 0; i < v.box.size(); i++) 
				{
					if (to == v.box[i]) 
					{
						v.box[i].x++;
					}
				}
				v.men.x++;
				newmp = mp(v.men, v.box);
				if (dis[newmp] == 0) 
				{
					dis[newmp] = d + 1;
					q.push(newmp);
				}
				v = q.front();
			}
		}
               
		to = tchk(v.men.x, v.men.y - 1);
		em = empty(to, v);
		if (em == 1) 
		{
			newmp = mp(to, v.box);
			if (dis[newmp] == 0) 
			{
				dis[newmp] = d + 1;
				q.push(newmp);
			}
		}
		if (em == 2) 
		{
			if (empty(tchk(v.men.x, v.men.y - 2), v) == 1) 
			{
				for (int i = 0; i < v.box.size(); i++) 
				{
					if (to == v.box[i]) 
					{
						v.box[i].y--;
					}
				}                      
				v.men.y--;
				newmp = mp(v.men, v.box);
				if (dis[newmp] == 0) 
				{
					dis[newmp] = d + 1;
					q.push(newmp);
				}
				v = q.front();
			}
		}
		q.pop();
	}
}
 
int main () 
{
	char filename[32];
	cout<<"Введите название файла:";
	cin>>filename;
	freopen( filename, "r", stdin);
	freopen("resylt.txt", "w", stdout);
	cin >> n >> m;
	read.resize(n + 2, vector <char> (m + 2, '*'));
	clear.resize(n + 2, vector <char> (m + 2, '*'));
	mp init;
	for (int i = 1; i <= n; i++) 
	{
		for (int j = 1; j <= m; j++) 
		{
			cin >> read[i][j];
			clear[i][j] = read[i][j];
			if (clear[i][j] == '$' || clear[i][j] == '%') 
			{
				clear[i][j] = 'x';
			}
			if (clear[i][j] == '#' || clear[i][j] == '@') 
			{
				clear[i][j] = '.';
			}
			if (read[i][j] == '@' || read[i][j] == '%') 
			{
				init.men = tchk(i, j);
			}
			if (read[i][j] == '#' || read[i][j] == '$') 
			{
				init.box.push_back(tchk(i, j));
			}      
 
		}
	}
	init = mp(init.men, init.box);
	actions(init);
	if (ans == 87654321) 
	{
		ans = -1;
	}
	cout << ans << "\n";
 
}
