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

const int mxn = 2e5 + 10, inf = 1e18;
int n, f[mxn], g[mxn], ans;
vector<pair<int, int>> adj[mxn];

void dfs1(int to, int fr) {
	f[to] = 0;
	g[to] = -inf;
	int mx1 = -inf;
	for(auto it : adj[to]) {
		if(it.ff == fr) continue;
		int x = it.ff;
		dfs1(x, to);
		f[to] += max(f[x], g[x] + it.ss);
		mxx(mx1, f[x] + it.ss - max(f[x], g[x] + it.ss));
	}
	mxx(g[to], f[to] + mx1);
}

void dfs2(int to, int fr, int pf, int pg) {
	int sumf = pf + f[to];
	int mx1 = pg - pf, mx2 = -inf;
	mxx(ans, sumf);
	for(auto it : adj[to]) {
		if(it.ff == fr) continue;
		int x = it.ff;
		int tmp = f[x] + it.ss - max(g[x] + it.ss, f[x]);
		if(tmp > mx1) {
			mx2 = mx1;
			mx1 = tmp;
		} else if(tmp > mx2) {
			mx2 = tmp;
		}
	}
	for(auto it : adj[to]) {
		if(it.ff == fr) continue;
		int x = it.ff;
		sumf -= max(g[x] + it.ss, f[x]);
		int ll = (f[x] + it.ss - max(g[x] + it.ss, f[x]) == mx1 ? mx2 : mx1);
		dfs2(x, to, max(sumf, it.ss + sumf + ll), sumf + it.ss);
		sumf += max(g[x] + it.ss, f[x]);
	}
}

void go() {
	cin >> n;
	for(int i = 1; i < n; i++) {
		int x, y, c;
		cin >> x >> y >> c;
		adj[x].eb(y, c);
		adj[y].eb(x, c);
	}
	dfs1(1, 0);
	dfs2(1, 0, 0, -inf);
	cout << ans << '\n';
}
 
signed main() {
	// #ifndef ONO
	// freopen("beads.in", "r", stdin);
	// freopen("beads.out", "w", stdout);
	// #endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}