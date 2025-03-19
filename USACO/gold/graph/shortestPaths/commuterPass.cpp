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
int vis[mxn], mn[mxn][4], n, cnt[mxn][3], dp[mxn][3];
vector<pair<int, int>> g[mxn];

void dfs(int x) {
	vis[x] = 1;
	for(auto [y, t] : g[x])  {
		if(mn[y][0] + t == mn[x][0] && !vis[y]) {
			dfs(y);
		}
	}
}

void bfs(int st, int tp) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	for(int i = 1; i <= n; i++) {
		mn[i][tp] = inf;
	}
	mn[st][tp] = 0;
	q.push({0, st});
	while(q.size()) {
		int cs = q.top().ff, x = q.top().ss; q.pop();
		if(mn[x][tp] != cs) continue;
		for(auto [y, t] : g[x]) {
			if(mn[y][tp] > cs + t) {
				mn[y][tp] = cs + t;
				q.push({mn[y][tp], y});
			}
		}
	}
}

void topsort(int st, int tp) {
	queue<int> q;
	q.push(st);
	while(q.size()) {
		int x = q.front(); q.pop();
		for(auto [y, t] : g[x]) {
			if(tp == 0 && mn[y][0] + t == mn[x][0] && vis[y]) {
				cnt[y][tp]--;
				mnn(dp[y][tp], dp[x][tp]);
				if(cnt[y][tp] == 0) q.push(y);
			}
			if(tp == 1 && mn[y][0] == mn[x][0] + t && vis[y]) { 
				cnt[y][tp]--;
				mnn(dp[y][tp], dp[x][tp]);
				if(cnt[y][tp] == 0) q.push(y);
			}
		}
	}
}

void go() {
	int m;
	cin >> n >> m;
	int s, t, u, v;
	cin >> s >> t >> u >> v;
	for(int i = 1; i <= m; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		g[x].pb({y, c});
		g[y].pb({x, c});
	}
	bfs(s, 0);
	dfs(t);
	bfs(u, 1);
	bfs(v, 2);
	for(int i = 1; i <= n; i++) {
		if(vis[i]) {
			for(auto [y, t] : g[i]) {
				if(mn[y][0] + t == mn[i][0] && vis[y]) cnt[y][0]++;
				if(mn[y][0] == mn[i][0] + t && vis[y]) cnt[y][1]++;
			}
		}
		dp[i][0] = dp[i][1] = mn[i][1];
	}
	topsort(s, 1);
	topsort(t, 0);
	int ans = inf;
	for(int i = 1; i <= n; i++) {
		mnn(ans, min(dp[i][0], dp[i][1]) + mn[i][2]);
	}
	cout << ans << '\n';
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