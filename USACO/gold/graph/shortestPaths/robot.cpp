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

const int mxn = 1e5 + 10, inf = 1e18 + 10;
int dp[mxn];
map<int, int> mn[mxn], sum[mxn];
map<int, vector<pair<int, int>>> adj[mxn];
vector<array<int, 3>> g[mxn];

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int a, b, c, p;
		cin >> a >> b >> c >> p;
		g[a].pb({b, c, p});
		g[b].pb({a, c, p});
		adj[a][c].pb({b, p});
		adj[b][c].pb({a, p});
		sum[a][c] += p;
		sum[b][c] += p;
	}
	for(int i = 1; i <= n; i++) {
		dp[i] = inf;
	}
	dp[1] = 0;
	priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>>> q;
	q.push({0, 1, 0});
	while(q.size()) {
		auto tmp = q.top();
		int my = tmp[0];
		int to = tmp[1];
		int tp = tmp[2];
		q.pop();
		if(tp) {
			if(my != mn[to][tp]) continue;
			for(auto it : adj[to][tp]) {
				int x = it.ff;
				int p = it.ss;
				int kk = sum[to][tp]; 
				if(my + kk - p < dp[x]) {
					dp[x] = my + kk - p;
					q.push({dp[x], x, 0});
				}
			}
			continue;
		}
		if(my != dp[to]) continue;
		for(auto it : g[to]) {
			int x = it[0];
			int c = it[1];
			int p = it[2];
			int kk = sum[to][c];
			if(my + kk - p < dp[x]) {
				dp[x] = my + kk - p;
				q.push({dp[x], x, 0});
			}
			if(my + p < dp[x]) {
				dp[x] = my + p;
				q.push({dp[x], x, 0});
			}
			if(!mn[x].count(c) || mn[x][c] > my) {
				mn[x][c] = my;
				q.push({my, x, c});
			}
		}
	}
	if(dp[n] == inf) dp[n] = -1;
	cout << dp[n] << '\n';
}

signed main() {
	#ifndef ONO
	freopen("file.in", "r", stdin);
	freopen("file.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}