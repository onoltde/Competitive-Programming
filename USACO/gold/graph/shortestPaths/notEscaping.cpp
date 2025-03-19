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

const int mxn = 1e5 + 10, inf = 1e18;
int x[mxn];
vector<int> d[mxn];
vector<pair<int, int>> g[mxn];
vector<array<int, 4>> adj[mxn];

void go() {
	int n, m, k;
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i++) {
		cin >> x[i];
		d[i].clear();
		g[i].clear();
		adj[i].clear();
	}
	for(int i = 1; i <= k; i++) {
		int a, b, c, d, h;
		cin >> a >> b >> c >> d >> h;
		::d[c].pb(d);
		::d[a].pb(b);
		adj[a].pb({b, c, d, h});
	}
	d[1].pb(1);
	d[n].pb(m);
	vector<int> dp(k + n + m + 3, -inf);
	int t = 0;
	for(int i = 1; i <= n; i++) {
		sort(all(d[i]));
		d[i].erase(unique(all(d[i])), d[i].end());

	}
	dp[1] = 0;

	for(int i = 1; i <= n; i++) {
		for(int it : d[i]) {
			g[i].pb({it, ++t});
		}
	}

	for(int i = 1; i <= n; i++) {
		multiset<int> s1, s2;
		for(auto it : g[i]) {
			s1.in(dp[it.ss] - it.ff * x[i]);
		}
		for(auto it : g[i]) {
			s2.in(dp[it.ss] + it.ff * x[i]);
			int mx1 = *s1.rbegin();
			int mx2 = *s2.rbegin();
			s1.erase(s1.find(dp[it.ss] - it.ff * x[i]));
			mxx(dp[it.ss], max(mx1 + it.ff * x[i], mx2 - it.ff * x[i]));
		}
		sort(all(adj[i]));
		int idx = 0;
		for(auto it : g[i]) {
			while(idx < adj[i].size() && adj[i][idx][0] < it.ff) idx++;
			while(idx < adj[i].size() && adj[i][idx][0] == it.ff) {
				auto val = adj[i][idx];
				int pos = lower_bound(all(g[val[1]]), make_pair(val[2], 0LL)) -  g[val[1]].begin();
				int id = g[val[1]][pos].ss;
				mxx(dp[id], dp[it.ss] + val[3]);
				idx++;
			}
		}
	}
	// for(int i = 0; i <= t; i++) {
	// 	cout << dp[i] << " \n"[i == t];
	// }
	int pos = g[n].back().ss;
	if(dp[pos] <= -1e17) cout << "NO ESCAPE\n";
	else cout << -dp[pos] << '\n';
}
 
signed main() {
	// #ifndef ONO
	// freopen("file.in", "r", stdin);
	// freopen("file.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	cin >> t;
	while(t--) {
		go();
	}
	return 0;
}