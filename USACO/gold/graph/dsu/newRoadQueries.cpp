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
int par[mxn], n, m, q, x[mxn], y[mxn], ans[mxn];
vector<pair<int, int>> g[mxn];

int get(int x) {
	return par[x] == x ? x : par[x] = get(par[x]);
}

void unite(int x, int y, int t) {
	x = get(x);
	y = get(y);
	if(x == y) return;
	if(g[x].size() < g[y].size()) swap(x, y);
	par[y] = x;
	for(auto [to, id] : g[y]) {
		if(get(to) == get(y)) {
			if(ans[id] == -1 || ans[id] > t) ans[id] = t;
		}
		else {
			g[x].pb({to, id});
		}
	}
}

void go() {
	cin >> n >> m >> q;
	for(int i = 1; i <= m; i++) {
		cin >> x[i] >> y[i];
	}
	for(int i = 1; i <= q; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb({y, i});
		g[y].pb({x, i});
		ans[i] = -1;
		if(x == y) ans[i] = 0;
	}
	for(int i = 1; i <= n; i++) {
		par[i] = i;
	}
	for(int i = 1; i <= m; i++) {
		unite(x[i], y[i], i);
	}
	for(int i = 1; i <= q; i++) {
		cout << ans[i] << '\n';
	}
}
 
signed main() {
	fast;
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}