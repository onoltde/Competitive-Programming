#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second

// #define int long long
 
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

const int mxn = 2e5 + 10;
vector<vector<int>> g;
int mn[mxn], par[mxn], ans[mxn];
queue<int> q;

int get(int x) {
	return par[x] == x ? x : par[x] = get(par[x]);
}

void unite(int x, int y) {
	x = get(x);
	y = get(y);
	if(x == y) return;
	if(g[x].size() < g[y].size()) swap(x, y);
	par[y] = x;
	mnn(mn[x], mn[y]);
	g[x].insert(g[x].end(), g[y].begin(), g[y].end());
	g[y].clear();
	if(g[x].size() > 1) q.push(x);
}

void go() {
	int n, m;
	cin >> n >> m;
	g.resize(n + 10);
	for(int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
	}
	for(int i = 1; i <= n; i++) {
		mn[i] = par[i] = i;
		if(g[i].size() > 1) q.push(i);
	}
	while(q.size()) {
		int x = q.front(); q.pop();
		if(g[x].size() <= 1) continue;
		while(g[x].size() > 1) {
			int lol = g[x].back();
			g[x].pop_back();
			unite(lol, g[x].back());
		}
	}
	int t = 0;
	for(int i = 1; i <= n; i++) {
		if(mn[get(i)] == i)
			ans[i] = ++t;
	}
	for(int i = 1; i <= n; i++) {
		cout << ans[mn[get(i)]] << '\n';
	}
}
 
signed main() {
	fast;
	#ifndef ONO
	freopen("fcolor.in", "r", stdin);
	freopen("fcolor.out", "w", stdout);
	#endif
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}