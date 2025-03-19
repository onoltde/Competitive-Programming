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

struct tree {
	int n, lg, t;
	vector<int> dep, in, out;
	vector<vector<int>> jump, g;
	bool did;

	tree(int _n) : n(_n) {
		g.resize(n + 1);
		in.resize(n + 1);
		out.resize(n + 1);
		dep.resize(n + 1);
		did = 0;
		lg = t = 0;
		while((1 << lg) <= n) lg++;
		jump.resize(n + 1, vector<int>(lg));
	}

	void build(int to = 1, int fr = 0) {
		dep[to] = dep[fr] + 1;
		jump[to][0] = fr;
		in[to] = ++t;
		for(int x : g[to]) {
			if(x == fr) continue;
			build(x, to);
		}
		out[to] = t;
	}

	void add(int x, int y) {
		g[x].pb(y);
		g[y].pb(x);
	}

	void buildLCA() {
		if(did) return;
		did = 1;
		for(int j = 1; j < lg; j++) {
			for(int i = 1; i <= n; i++) {
				jump[i][j] = jump[jump[i][j - 1]][j - 1];
			}
		}
	}

	int lca(int x, int y) {
		if(dep[x] < dep[y]) swap(x, y);
		int dff = dep[x] - dep[y];
		for(int i = 0; i < lg; i++) {
			if((dff >> i) & 1) x = jump[x][i];
		}
		if(x == y) return x;
		for(int i = lg - 1; i >= 0; i--) {
			if(jump[x][i] != jump[y][i]) {
				x = jump[x][i];
				y = jump[y][i];
			}
		}
		return jump[x][0];
	}

	int distance(int x, int y) {
		return dep[x] + dep[y] - dep[lca(x, y)] * 2;
	}

	bool isAnc(int x, int y) {
		return in[x] <= in[y] && out[x] >= out[y]; 
	}

	bool isOn(int x, int y, int z) {
		int p = lca(x, y);
		if(dep[p] > dep[z]) return 0;
		return (isAnc(z, x) || isAnc(z, y));
	}

	~tree() {
		jump.clear();
		dep.clear();
		g.clear();
		in.clear();
		out.clear();
	}
};

const int mxn = 1e6 + 10;
int dis1[mxn], dis2[mxn];
bool vis[mxn];
vector<pair<int, int>> adj1[mxn], adj2[mxn];

void dfs1(int to, int dis) {
	dis1[to] = dis;
	vis[to] = 1;
	for(auto it : adj1[to]) {
		if(vis[it.ff]) continue;
		dfs1(it.ff, dis + it.ss);
	}
}

void dfs2(int to, int dis) {
	dis2[to] = dis;
	vis[to] = 1;
	for(auto it : adj2[to]) {
		if(vis[it.ff]) continue;
		dfs2(it.ff, dis + it.ss);
	}
}

int main() {
	fast;
	int n, k, q, t; cin >> n >> k >> q >> t;
	tree tr1(n), tr2(n);
	int root1, root2;
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		if(~x) tr1.add(x, i);
		else root1 = i;
	}
	for(int i = 1; i <= n; i++) {
		int x; cin >> x;
		if(~x) tr2.add(x, i);
		else root2 = i;
	}

	tr1.build(root1); tr1.buildLCA();
	tr2.build(root2); tr2.buildLCA();

	vector<int> ks;
	for(int i = 1; i <= n; i++) {
		if(tr1.in[i] <= k) ks.pb(i);
	}
	sort(all(ks), [&](int x, int y) {
		return tr2.in[x] < tr2.in[y];
	});

	for(int i = 0; i < k; i++) {
		cout << ks[i] << ' ';
	}
	cout << endl;
	for(int i = 0; i + 1 < k; i++) {
		cout << "? " << ks[i] << ' ' << ks[i + 1] << endl;
	}
	cout << "!" << endl;
	for(int i = 0; i + 1 < k; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		int lc1 = tr1.lca(ks[i], ks[i + 1]);
		int lc2 = tr2.lca(ks[i], ks[i + 1]);
		adj1[ks[i]].eb(lc1, -a);
		adj1[lc1].eb(ks[i + 1], b);
		adj2[ks[i]].eb(lc2, -c);
		adj2[lc2].eb(ks[i + 1], d);
	}
	dfs1(ks[0], 0);
	for(int i = 0; i < k; i++) {
		vis[ks[i]] = 0;
	}
	dfs2(ks[0], 0);
	vector<pair<int, int>> ans;
	for(int i = 0; i < t; i++) {
		int x, y; cin >> x >> y;
		ans.eb(dis1[x] + dis1[y] - dis1[tr1.lca(x, y)] * 2, dis2[x] + dis2[y] - dis2[tr2.lca(x, y)] * 2);
	}
	for(auto &it : ans) {
		cout << it << endl;
	}
	return 0;
}