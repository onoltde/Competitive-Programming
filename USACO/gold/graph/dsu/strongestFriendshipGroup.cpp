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

struct DSU {
	int n, cmp;
	vector<int> par, cnt, rnk;

	DSU(int _n) : n(_n) {
		cmp = n;
		par.resize(n + 1, 0);
		cnt.resize(n + 1, 1);
		rnk.resize(n + 1, 0);
		iota(all(par), 0);
	}

	int find(int x) {
		return par[x] == x ? x : par[x] = find(par[x]);
	}

	int getSize(int x) {
		return cnt[find(x)];
	}

	int getComp() {
		return cmp;
	}
	bool unite(int u, int v) {
		u = find(u); v = find(v);
		if(u == v) {
			return 0;
		}
		cmp--;
		if(rnk[u] < rnk[v]) swap(u, v);
		par[v] = u;
		cnt[u] += cnt[v];
		rnk[u] += (rnk[u] == rnk[v]);
		return 1;
	}
};

const int mxn = 2e5 + 10;
int deg[mxn];
bool is[mxn];
vector<int> g[mxn];

void go() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
		deg[x]++;
		deg[y]++;
	}
	vector<int> alive;
	for(int i = 1; i <= n; i++) {
		is[i] = 1;
		alive.pb(i);
	}
	int ans = 0;
	for(int d = 1; d * d <= m; d++) {
		DSU ds(n);
		queue<int> q;
		for(int x : alive) {
			if(deg[x] < d) q.push(x);
		}
		while(q.size()) {
			int x = q.front();
			q.pop();
			is[x] = 0;
			for(int y : g[x]) {
				if(!is[y]) continue;
				deg[y]--;
				if(deg[y] < d) q.push(y);
			}
			g[x].clear();
		}
		vector<int> tmp;
		for(int x : alive) {
			if(is[x]) tmp.pb(x);
		}
		swap(alive, tmp);
		for(int x : alive) {
			for(int y : g[x]) {
				if(is[y] && ds.unite(x, y)) mxx(ans, d * ds.getSize(x));
			}
		}
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