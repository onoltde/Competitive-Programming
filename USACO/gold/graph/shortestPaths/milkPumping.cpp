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

const int mxn = 1010, inf = 1e9 + 10, add = 1e6;
vector<array<int, 3>> g[mxn];
int mn[mxn], vis[mxn];


void go() {
	int n, m;
	cin >> n >> m;
	int mx = 0;
	for(int i = 1; i <= m; i++) {
		int x, y, c, f;
		cin >> x >> y >> c >> f;
		mxx(mx, f);
		g[x].pb({y, c, f});
		g[y].pb({x, c, f});
	}
	int ans = 0;
	for(int i = 1; i <= mx; i++) {
		for(int j = 1; j <= n; j++)
			mn[j] = inf, vis[j] = 0;
		priority_queue<pair<int, int>> q;
		q.push({0, 1});
		mn[1] = 0;
		while(q.size()) {
			int x = q.top().ss; q.pop();
			if(vis[x]) continue;
			vis[x] = 1;
			for(auto [y, c, f] : g[x]) {
				if(f < i) continue;
				if(mn[y] <= mn[x] + c) continue;
				mn[y] = mn[x] + c;
				q.push({-mn[y], y});
			}
		}
		if(mn[n] != inf)
			mxx(ans, i * add / mn[n]);
	}
	cout << ans << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("pump.in", "r", stdin);
	freopen("pump.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}