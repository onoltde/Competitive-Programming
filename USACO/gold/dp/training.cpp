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

const int mxn = 1010, mxm = 5010;
int n, m, dp[mxn][mxn + 40], d[mxn], par[mxn], pos[mxn], deg[mxn];
vector<tuple<int, int, int>> edges[mxn];
vector<int> g[mxn];

void dfs(int to, int fr) {
	if(fr) g[to].erase(find(all(g[to]), fr));
	d[to] = d[fr] + 1;
	par[to] = fr;
	for(int x : g[to]) {
		pos[x] = (1 << (deg[to]++));
		dfs(x, to);
	}
}

void solve(int to) {
	for(int x : g[to]) {
		solve(x);
	}
	for(int i = 0; i < (1 << deg[to]); i++) {
		for(int j = 0; j < deg[to]; j++) {
			if(!((i >> j) & 1)) dp[to][i] += dp[g[to][j]][0];
		}
	}
	for(auto it : edges[to]) {
		int x, y, w;
		tie(x, y, w) = it;
		int sum = w;
		int mask = 0;
		for(int now = 0; ; now = pos[x], x = par[x]) {
			if(x == to) {
				mask |= now;
				break;
			}
			sum += dp[x][now];
		}
		for(int now = 0; ; now = pos[y], y = par[y]) {
			if(y == to) {
				mask |= now;
				break;
			}
			sum += dp[y][now];
		}
		for(int i = 0; i < (1 << deg[to]); i++) {
			if(i & mask) continue;
			mxx(dp[to][i], sum + dp[to][i | mask]);
		}
	}
}

void go() {
	cin >> n >> m;
	int sum = 0;
	vector<tuple<int, int, int>> all;
	for(int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		sum += w;
		if(!w) {
			g[x].pb(y);
			g[y].pb(x);
		}
		else all.eb(x, y, w);
	}
	dfs(1, 0);
	for(auto it : all) {
		int x, y, w;
		tie(x, y, w) = it;
		if((d[x] + d[y]) & 1) continue;
		while(x != y) {
			if(d[x] > d[y]) x = par[x];
			else y = par[y];
		}
		edges[x].eb(it);
	}
	solve(1);
	cout << sum - dp[1][0] << '\n';
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