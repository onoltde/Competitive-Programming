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

template<typename T, typename U>
ostream & operator << (ostream &out, const pair<T, U> &c) {
	out << c.first << ' ' << c.second;
    return out;
}

template<typename T>
ostream & operator << (ostream &out, vector<T> &v) {
	const int sz = v.size();
	for (int i = 0; i < sz; i++) {
		if (i) out << ' ';
		out << v[i];
	}
    return out;
}

template<typename T>
istream & operator >> (istream &in, vector<T> &v) {
	for (T &x : v) in >> x;
    return in;
}


template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

const int mxn = 2e5 + 10, inf = 1e18 + 10;
int v[mxn], vis[mxn], n, ans[mxn], id[mxn], par[mxn], anc[mxn], dth[mxn];
vector<pair<int, int>> g[mxn];
vector<tuple<int, int, int>> edges;

void bfs(int st, vector<int> &dp) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	for(int i = 1; i <= n; i++) {
		vis[i] = 0;
	}
	q.push({0, st});
	dp[st] = 0;
	par[st] = 0;
	while(q.size()) {
		int my = q.top().ff;
		int x = q.top().ss;
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(auto it : g[x]) {
			if(dp[it.ff] > my + it.ss) {
				dp[it.ff] = my + it.ss;
				par[it.ff] = x;
				q.push({dp[it.ff], it.ff});
			}
		}
	}
}

void dfs(int to) {
	for(auto it : g[to]) {
		int x = it.ff;
		if(par[x] == to) {
			dth[x] = dth[to] + 1;
			dfs(x);
		}
	}
}

int lca(int x, int y) {
	while(dth[x] > dth[y]) {
		x = par[x];
	}
	while(dth[y] > dth[x]) {
		y = par[y];
	}
	while(x != y) {
		y = par[y];
		x = par[x];
	}
	return x;
}

void go() {
	int m, a, b;
	cin >> n >> m >> a >> b;
	vector<int> dp1(n + 10, inf), dp2(n + 10, inf);
	for(int i = 1; i <= m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		edges.pb({x, y, d});
		edges.pb({y, x, d});
		g[x].pb({y, d});
		g[y].pb({x, d});
	}
	bfs(b, dp2);
	bfs(a, dp1);
	int k;
	cin >> k;
	for(int i = 1; i <= k; i++) {
		cin >> v[i];
		id[v[i]] = i;
		if(i - 1) par[v[i]] = v[i - 1];		
	}
	dfs(a);
	for(int i = 1; i <= n; i++) {
		anc[i] = lca(i, b);
	}
	for(int i = 1; i < k; i++) {
		ans[i] = inf;
	}
	for(auto it : edges) {
		int x, y, d;
		tie(x, y, d) = it;
		if(par[x] == y || par[y] == x) continue;
		int l = id[anc[x]];
		int r = id[anc[y]];
		for(int i = l; i < r; i++) {
			mnn(ans[i], dp1[x] + dp2[y] + d);
		}
	}
	for(int i = 1; i < k; i++) {
		if(ans[i] == inf) ans[i] = -1;
		cout << ans[i] << '\n';
	}
}

signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}