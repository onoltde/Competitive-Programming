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

const int mxn = 3010;
vector<int> g[mxn * mxn];
vector<pair<int, int>> t;
int mx[mxn * mxn], par[mxn * mxn], ans[mxn * mxn], a[mxn][mxn];
int n, m, now, mm;

int get(int x) {
	return par[x] == x ? x : par[x] = get(par[x]);
}

void unite(int x1, int y1, int x2, int y2) {
	int t1 = m * (x1 - 1) + y1;
	int t2 = m * (x2 - 1) + y2;
	t1 = get(t1);
	t2 = get(t2);
	if(t1 == t2) return;
	if(mx[t1] > mx[t2]) {
		while(g[t2].size()) {
			ans[g[t2].back()] = mx[t2] - now;
			g[t2].pop_back();
		}
	}
	if(mx[t2] > mx[t1]) {
		while(g[t1].size()) {
			ans[g[t1].back()] = mx[t1] - now;
			g[t1].pop_back();
		}
	}
	if(g[t1].size() < g[t2].size()) swap(t1, t2);
	par[t2] = t1;
	mxx(mx[t1], mx[t2]);
	while(g[t2].size()) {
		g[t1].pb(g[t2].back());
		g[t2].pop_back();
	}
}

void go() {
	cin >> n >> m;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j];
			par[m * (i - 1) + j] = m * (i - 1) + j;
			mx[m * (i - 1) + j] = a[i][j];
			g[m * (i - 1) + j].pb(m * (i - 1) + j);
			mxx(mm, a[i][j]);
			t.pb({i, j});
		}
	}
	sort(all(t), [&](pair<int, int> a, pair<int, int> b) {
		return ::a[a.ff][a.ss] > ::a[b.ff][b.ss];
	});
	for(auto [x, y] : t) {
		for(auto [dx, dy] : {make_pair(0, 1), make_pair(0, -1), make_pair(1, 0), make_pair(-1, 0)}) {
			int nx = x + dx;
			int ny = y + dy;
			if(a[x][y] == mm) {
				ans[m * (x - 1) + y] = mm;
				g[m * (x - 1) + y].clear();
			}
			if(nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] < a[x][y]) continue;
			now = a[x][y];
			unite(x, y, nx, ny);
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cout << ans[m * (i - 1) + j] << ' ';
		}
		cout << '\n';
	}
}
 
signed main() {
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}