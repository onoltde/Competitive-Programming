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
int v[mxn], vis[mxn], n, ans[mxn], id[mxn];
vector<pair<int, int>> g[mxn];
vector<tuple<int, int, int>> edges;

void bfs(int st, vector<pair<int, int>> &dp) {
	priority_queue<pair<pii, int>, vector<pair<pii, int>>, greater<pair<pii, int>>> q;
	for(int i = 1; i <= n; i++) {
		vis[i] = 0;
	}
	for(int i = 1; i <= n; i++) {
		if(dp[i].ff != inf) {
			q.push({dp[i], i});
		}
	}
	while(q.size()) {
		auto my = q.top().ff;
		int x = q.top().ss;
		q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(auto it : g[x]) {
			my.ff += it.ss;
			if(dp[it.ff] > my) {
				dp[it.ff] = my;
				q.push({dp[it.ff], it.ss});
			}
			my.ff -= it.ss;
		}
	}
}

void go() {
	int m, a, b;
	cin >> n >> m >> a >> b;
	vector<pair<int, int>> dp1(n + 10, {inf, inf}), dp2(n + 10, {inf, inf});
	for(int i = 1; i <= m; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		edges.pb({x, y, d});
		edges.pb({y, x, d});
		g[x].pb({y, d});
		g[y].pb({x, d});
	}
	sort(all(edges));
	int k;
	cin >> k;
	for(int i = 1; i <= n; i++) {
		id[i] = -1;
	}
	for(int i = 1; i <= k; i++) {
		cin >> v[i];
		id[v[i]] = i;
	}
	v[0] = v[k + 1] = 0;
	for(int i = 1; i <= k; i++) {
		dp1[v[i]] = {0, i};
		if(i > 1) {
			auto it = lower_bound(all(edges), make_tuple(v[i - 1], v[i], 0));
			if(it == edges.end()) while(1);
			dp1[v[i]].ff = dp1[v[i - 1]].ff + get<2>(*it);
		}
	}
	for(int i = k; i >= 1; i--) {
		dp2[v[i]] = {0, k - i + 1};
		if(i < k) {
			auto it = lower_bound(all(edges), make_tuple(v[i + 1], v[i], 0));
			if(it == edges.end()) while(1);
			dp2[v[i]].ff = dp2[v[i + 1]].ff + get<2>(*it);
		}
	}
	bfs(a, dp1);
	bfs(b, dp2);
	for(int i = 1; i < k; i++) {
		ans[i] = inf;
	}
	for(auto it : edges) {
		int x, y, d;
		tie(x, y, d) = it;
		int l = dp1[x].ss;
		int r = dp1[y].ss;
		if(r == inf || l == inf) continue;
		if(id[x] + 1 == id[y]) continue;
		if(id[y] + 1 == id[x]) continue;
		for(int i = l; i < r; i++) {
			mnn(ans[i], dp1[x].ff + dp2[y].ff + d);
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