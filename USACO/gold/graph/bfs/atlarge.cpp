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

const int mxn = 2e5 + 10, inf = 1e9 + 10;
vector<int> g[mxn];
int ans, par[mxn], d1[mxn], d2[mxn], can[mxn];

void dfs(int to, int fr) {
	d2[to] = d2[fr] + 1;
	d1[to] = inf;
	par[to] = fr;
	if(g[to].size() == 1)
		d1[to] = 1;
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs(x, to);
		mnn(d1[to], d1[x] + 1);
	}
	if(d1[to] <= d2[to])
		can[to] = 1;
}

void col(int to, int fr) {
	for(int x : g[to]) {
		if(x == fr) continue;
		can[x] |= can[to];
		col(x, to);
	}
}

void go() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	dfs(k, 0);
	col(k, 0);
	for(int i = 1; i <= n; i++)
		if(can[i] && !can[par[i]])
			ans++;
	cout << ans << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("atlarge.in", "r", stdin);
	freopen("atlarge.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}