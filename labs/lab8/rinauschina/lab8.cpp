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
 
struct PT{
        int x, y;
        PT() {};
        PT(int x, int y) : x(x), y(y) {};
        bool operator< (const PT & p) const 
		{
                return (x < p.x || (x == p.x && y < p.y));
        }
        bool operator== (const PT &p) const 
		{
                return (x == p.x && y == p.y);
        }
};
 
struct MP{
        PT PLAYMEN, HASH;
        vector <PT> boxs;
        MP() {};
        MP(PT PLAYMEN, vector <PT> boxs) : PLAYMEN(PLAYMEN), boxs(boxs) {
                HASH = PT(PLAYMEN.x - 1, PLAYMEN.y - 1);
                sort(boxs.begin(), boxs.end());
                for (int i = 0; i < boxs.size(); i++) {
                        HASH = PT(HASH.x * 10 + boxs[i].x - 1, HASH.y * 10 + boxs[i].y - 1);
                }
        }
        bool operator< (const MP &m) const {
                return HASH < m.HASH;
        }
};
 
int ans = 87654321;
queue <MP> q;
map <MP, int> dist;
int n, m;
vector <vector <char> > CLEARMP, READMP;
 
int EMPTY(PT p, MP &MAP) {
        if (p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= m) {
                for (int i = 0; i < MAP.boxs.size(); i++) {
                        if (p == MAP.boxs[i]) {
                                return 2;
                        }
                }
                if (CLEARMP[p.x][p.y] == '.' || CLEARMP[p.x][p.y] == 'x') {
                        return 1;
                }
        }
        return 3;
}
 
bool CHECK(MP &v) {
        for (int i = 0; i < v.boxs.size(); i++) {
                if (CLEARMP[v.boxs[i].x][v.boxs[i].y] != 'x') {
                        return false;                  
                }
        }
        return true;
}
 
void BF(MP v) {
        q.push(v);
        while (!q.empty()) {
                v = q.front();
                int d = dist[v];
               if (CHECK(v)) {
                        ans = min(ans, d);
                }
                PT to = PT(v.PLAYMEN.x - 1, v.PLAYMEN.y);
                int em = EMPTY(to, v);
                MP NEWMP;
                
                if (em == 1) {
                        NEWMP = MP(to, v.boxs);
                        if (dist[NEWMP] == 0) {
                                dist[NEWMP] = d + 1;
                                q.push(NEWMP);
                        }
                }
                if (em == 2) {
                        if (EMPTY(PT(v.PLAYMEN.x - 2, v.PLAYMEN.y), v) == 1) {
                                for (int i = 0; i < v.boxs.size(); i++) {
                                        if (to == v.boxs[i]) {
                                                v.boxs[i].x--;
                                        }
                                }
                                v.PLAYMEN.x--;
                                NEWMP = MP(v.PLAYMEN, v.boxs);
                                if (dist[NEWMP] == 0) {
                                        dist[NEWMP] = d + 1;
                                        q.push(NEWMP);
                                }
                                v = q.front();
                        }
                }
                
                to = PT(v.PLAYMEN.x, v.PLAYMEN.y + 1);
				em = EMPTY(to, v);
                if (em == 1) {
                        NEWMP = MP(to, v.boxs);
                        if (dist[NEWMP] == 0) {
                                dist[NEWMP] = d + 1;
                                q.push(NEWMP);
                        }
                }
                if (em == 2) {
                        if (EMPTY(PT(v.PLAYMEN.x, v.PLAYMEN.y + 2), v) == 1) {
                                for (int i = 0; i < v.boxs.size(); i++) {
                                        if (to == v.boxs[i]) {
                                                v.boxs[i].y++;
                                        }
                                }
                                v.PLAYMEN.y++;
                                NEWMP = MP(v.PLAYMEN, v.boxs);
                                if (dist[NEWMP] == 0) {
                                        dist[NEWMP] = d + 1;
                                        q.push(NEWMP);
                                }
                                v = q.front();
                        }
                }
            
                to = PT(v.PLAYMEN.x + 1, v.PLAYMEN.y);
                em = EMPTY(to, v);
                if (em == 1) {
                        NEWMP = MP(to, v.boxs);
                        if (dist[NEWMP] == 0) {
                                dist[NEWMP] = d + 1;
                                q.push(NEWMP);
                        }
                }
                if (em == 2) {
                        if (EMPTY(PT(v.PLAYMEN.x + 2, v.PLAYMEN.y), v) == 1) {
                                for (int i = 0; i < v.boxs.size(); i++) {
                                        if (to == v.boxs[i]) {
                                                v.boxs[i].x++;
                                        }
                                }
                                v.PLAYMEN.x++;
                                NEWMP = MP(v.PLAYMEN, v.boxs);
                                if (dist[NEWMP] == 0) {
                                        dist[NEWMP] = d + 1;
                                        q.push(NEWMP);
                                }
                                v = q.front();
                        }
                }
               
                to = PT(v.PLAYMEN.x, v.PLAYMEN.y - 1);
                em = EMPTY(to, v);
                if (em == 1) {
                        NEWMP = MP(to, v.boxs);
                        if (dist[NEWMP] == 0) {
                                dist[NEWMP] = d + 1;
                                q.push(NEWMP);
                        }
                }
                if (em == 2) {
                        if (EMPTY(PT(v.PLAYMEN.x, v.PLAYMEN.y - 2), v) == 1) {
                                for (int i = 0; i < v.boxs.size(); i++) {
                                        if (to == v.boxs[i]) {
                                                v.boxs[i].y--;
                                        }
                                }                      
                                v.PLAYMEN.y--;
                                NEWMP = MP(v.PLAYMEN, v.boxs);
                                if (dist[NEWMP] == 0) {
                                        dist[NEWMP] = d + 1;
                                        q.push(NEWMP);
                                }
                                v = q.front();
                        }
                }
                q.pop();
        }
}
 
int main () {
        freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
        cin >> n >> m;
        READMP.resize(n + 2, vector <char> (m + 2, '*'));
        CLEARMP.resize(n + 2, vector <char> (m + 2, '*'));
        MP init;
        for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                        cin >> READMP[i][j];
                        CLEARMP[i][j] = READMP[i][j];
                        if (CLEARMP[i][j] == '$' || CLEARMP[i][j] == '%') {
                                CLEARMP[i][j] = 'x';
                        }
                        if (CLEARMP[i][j] == '#' || CLEARMP[i][j] == '@') {
                                CLEARMP[i][j] = '.';
                        }
                        if (READMP[i][j] == '@' || READMP[i][j] == '%') {
                                init.PLAYMEN = PT(i, j);
                        }
                        if (READMP[i][j] == '#' || READMP[i][j] == '$') {
                                init.boxs.push_back(PT(i, j));
                        }      
 
                }
        }
        init = MP(init.PLAYMEN, init.boxs);
        BF(init);
        if (ans == 87654321) {
                ans = -1;
        }
        cout << ans << "\n";
 
}
