#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

#define int long long
 
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;
typedef multiset<int> msi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 510, inf = 1e18 + 10;
int g[mxn][mxn];
int mn[mxn][mxn][3];
int vis[mxn][mxn][3];
int n, m;

bool check(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= m);
}

void go() {
	cin >> n >> m;
	int stx, sty, enx, eny;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			char ch;
			cin >> ch;
			if(ch == 'C')
				stx = i, sty = j;
			else if(ch == 'D')
				enx = i, eny = j;
			else if(ch == '#')
				g[i][j] = 1;
			mn[i][j][0] = mn[i][j][1] = inf;
		}
	}
	priority_queue<array<int, 4>> q;
	q.push({0, stx, sty, 1});
	mn[stx][sty][1] = 0;
	while(q.size()) {
		int x = q.top()[1];
		int y = q.top()[2];
		int dir = q.top()[3];
		q.pop();
		if(vis[x][y][dir]) continue;
		vis[x][y][dir] = 1;
		int del = (dir == 1 ? 1 : -1);
		if(!check(x + del, y)) continue;
		if(g[x + del][y] == 0 && mn[x + del][y][dir] > mn[x][y][dir]) {
			mn[x + del][y][dir] = mn[x][y][dir];
			q.push({-mn[x + del][y][dir], x + del, y, dir});
			continue;
		}
		if(g[x + del][y] == 0) continue;
		if(check(x, y - 1) && g[x][y - 1] == 0 && mn[x][y - 1][dir] > mn[x][y][dir]) {
			mn[x][y - 1][dir] = mn[x][y][dir];
			q.push({-mn[x][y - 1][dir], x, y - 1, dir});
		}
		if(check(x, y + 1) && g[x][y + 1] == 0 && mn[x][y + 1][dir] > mn[x][y][dir]) {
			mn[x][y + 1][dir] = mn[x][y][dir];
			q.push({-mn[x][y + 1][dir], x, y + 1, dir});
		}
		if(mn[x][y][dir ^ 1] > mn[x][y][dir] + 1) {
			mn[x][y][dir ^ 1] = mn[x][y][dir] + 1;
			q.push({-mn[x][y][dir ^ 1], x, y, dir ^ 1});
		}
	}
	int mm = min(mn[enx][eny][0], mn[enx][eny][1]);
	if(mm == inf) mm = -1;
	cout << mm << '\n';
}

signed main() {
	#ifndef ONO
	freopen("gravity.in", "r", stdin);
	freopen("gravity.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}