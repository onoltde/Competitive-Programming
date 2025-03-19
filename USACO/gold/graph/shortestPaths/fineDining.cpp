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

const int mxn = 5e4 + 10, inf = 1e18;
int dp1[mxn], dp2[mxn], vis[mxn];
vector<pair<int, int>> g[mxn];

void go() {
	int n, m, k;
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++) {
		int x, y, t;
		cin >> x >> y >> t;
		g[x].pb({y, t});
		g[y].pb({x, t});
	}
	for(int i = 1; i <= n; i++) {
		dp1[i] = dp2[i] = inf;
	}
	priority_queue<pair<int, int>> q;
	dp1[n] = 0;
	q.push({0, n});
	while(q.size()) {
		int x = q.top().ss; q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(auto [y, t] : g[x]) {
			if(dp1[y] > dp1[x] + t) {
				dp1[y] = dp1[x] + t;
				q.push({-dp1[y], y});
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		vis[i] = 0;
	}
	for(int i = 1; i <= k; i++) {
		int id, t;
		cin >> id >> t;
		dp2[id] = dp1[id] - t;
		q.push({-dp2[id], id});
	}
	while(q.size()) {
		int x = q.top().ss; q.pop();
		if(vis[x]) continue;
		vis[x] = 1;
		for(auto [y, t] : g[x]) {
			if(dp2[y] > dp2[x] + t) {
				dp2[y] = dp2[x] + t;
				q.push({-dp2[y], y});
			}
		}
	}
	for(int i = 1; i < n; i++) {
		cout << (dp2[i] <= dp1[i]) << '\n';
	}
}
 
signed main() {
	#ifndef ONO
	freopen("dining.in", "r", stdin);
	freopen("dining.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}