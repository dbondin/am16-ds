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
        point () {};
        point (int x, int y) : x(x), y(y) {}
        bool operator< (const point & p) const {
                return (x < p.x || (x == p.x && y < p.y));
        }
        bool operator== (const point &p) const {
                return (x == p.x && y == p.y);
        }
};
 
struct mp {
        point player, hash;
        vector <point> boxes;
        mp () {};
        mp (point player, vector <point> boxes) : player(player), boxes(boxes) {
                hash = point(player.x - 1, player.y - 1);
                sort(boxes.begin(), boxes.end());
                for (int i = 0; i < boxes.size(); i++) {
                        hash = point(hash.x * 10 + boxes[i].x - 1, hash.y * 10 + boxes[i].y - 1);
                }
        }
        bool operator< (const mp &m) const {
                return hash < m.hash;
        }
};
 
int ans = 87654321;
queue <mp> q;
map <mp, int> dist;
int n, m;
vector <vector <char> > clearMap, readMap;
 
int empty (point p, mp &MAP) {
        if (p.x >= 1 && p.x <= n && p.y >= 1 && p.y <= m) {
                for (int i = 0; i < MAP.boxes.size(); i++) {
                        if (p == MAP.boxes[i]) {
                                return 2;
                        }
                }
                if (clearMap[p.x][p.y] == '.' || clearMap[p.x][p.y] == 'x') {
                        return 1;
                }
        }
        return 3;
}
 
bool check (mp &v) {
        for (int i = 0; i < v.boxes.size(); i++) {
                if (clearMap[v.boxes[i].x][v.boxes[i].y] != 'x') {
                        return false;                  
                }
        }
        return true;
}
 
void bfs (mp v) {
        q.push(v);
        while (!q.empty()) {
                v = q.front();
                int d = dist[v];
                if (check(v)) {
                        ans = min(ans, d);
                }
                point to = point(v.player.x - 1, v.player.y);
                int em = empty(to, v);
                mp newMap;
                //up
                if (em == 1) {
                        newMap = mp(to, v.boxes);
                        if (dist[newMap] == 0) {
                                dist[newMap] = d + 1;
                                q.push(newMap);
                        }
                }
                if (em == 2) {
                        if (empty(point(v.player.x - 2, v.player.y), v) == 1) {
                                for (int i = 0; i < v.boxes.size(); i++) {
                                        if (to == v.boxes[i]) {
                                                v.boxes[i].x--;
                                        }
                                }
                                v.player.x--;
                                newMap = mp(v.player, v.boxes);
                                if (dist[newMap] == 0) {
                                        dist[newMap] = d + 1;
                                        q.push(newMap);
                                }
                                v = q.front();
                        }
                }
                //right
                to = point(v.player.x, v.player.y + 1);
                em = empty(to, v);
                if (em == 1) {
                        newMap = mp(to, v.boxes);
                        if (dist[newMap] == 0) {
                                dist[newMap] = d + 1;
                                q.push(newMap);
                        }
                }
                if (em == 2) {
                        if (empty(point(v.player.x, v.player.y + 2), v) == 1) {
                                for (int i = 0; i < v.boxes.size(); i++) {
                                        if (to == v.boxes[i]) {
                                                v.boxes[i].y++;
                                        }
                                }
                                v.player.y++;
                                newMap = mp(v.player, v.boxes);
                                if (dist[newMap] == 0) {
                                        dist[newMap] = d + 1;
                                        q.push(newMap);
                                }
                                v = q.front();
                        }
                }
                //down
                to = point(v.player.x + 1, v.player.y);
                em = empty(to, v);
                if (em == 1) {
                        newMap = mp(to, v.boxes);
                        if (dist[newMap] == 0) {
                                dist[newMap] = d + 1;
                                q.push(newMap);
                        }
                }
                if (em == 2) {
                        if (empty(point(v.player.x + 2, v.player.y), v) == 1) {
                                for (int i = 0; i < v.boxes.size(); i++) {
                                        if (to == v.boxes[i]) {
                                                v.boxes[i].x++;
                                        }
                                }
                                v.player.x++;
                                newMap = mp(v.player, v.boxes);
                                if (dist[newMap] == 0) {
                                        dist[newMap] = d + 1;
                                        q.push(newMap);
                                }
                                v = q.front();
                        }
                }
                //left
                to = point(v.player.x, v.player.y - 1);
                em = empty(to, v);
                if (em == 1) {
                        newMap = mp(to, v.boxes);
                        if (dist[newMap] == 0) {
                                dist[newMap] = d + 1;
                                q.push(newMap);
                        }
                }
                if (em == 2) {
                        if (empty(point(v.player.x, v.player.y - 2), v) == 1) {
                                for (int i = 0; i < v.boxes.size(); i++) {
                                        if (to == v.boxes[i]) {
                                                v.boxes[i].y--;
                                        }
                                }                      
                                v.player.y--;
                                newMap = mp(v.player, v.boxes);
                                if (dist[newMap] == 0) {
                                        dist[newMap] = d + 1;
                                        q.push(newMap);
                                }
                                v = q.front();
                        }
                }
                q.pop();
        }
}
 
int main () {
        freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
        cin >> n >> m;
        readMap.resize(n + 2, vector <char> (m + 2, '*'));
        clearMap.resize(n + 2, vector <char> (m + 2, '*'));
        mp init;
        for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                        cin >> readMap[i][j];
                        clearMap[i][j] = readMap[i][j];
                        if (clearMap[i][j] == '$' || clearMap[i][j] == '%') {
                                clearMap[i][j] = 'x';
                        }
                        if (clearMap[i][j] == '#' || clearMap[i][j] == '@') {
                                clearMap[i][j] = '.';
                        }
                        if (readMap[i][j] == '@' || readMap[i][j] == '%') {
                                init.player = point(i, j);
                        }
                        if (readMap[i][j] == '#' || readMap[i][j] == '$') {
                                init.boxes.push_back(point(i, j));
                        }      
 
                }
        }
        init = mp(init.player, init.boxes);
        bfs(init);
        if (ans == 87654321) {
                ans = -1;
        }
        cout << ans << "\n";
 
}