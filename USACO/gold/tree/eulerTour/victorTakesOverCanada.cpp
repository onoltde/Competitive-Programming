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

const int mxn = 5e5 + 10;
int id[mxn], c[mxn], sp[mxn][30], in[mxn], out[mxn], tt, dth[mxn];
vector<int> g[mxn];
set<int> s[mxn];

struct BIT {
	vector<int> fn;
	int sz;

	BIT() {
		sz = 0;
	}

	BIT(int n, int val = 0) {
		sz = n;
		fn.resize(n + 1, val);
	}

	void resize(int n, int val = 0) {
		sz = n;
		fn.clear();
		fn.resize(n + 1, val);
	}

	int sum(int l) {
		int ret = 0;
		for(; l; l -= (l & -l)) {
			ret += fn[l];
		}
		return ret;
	}
	int rangeSum(int l, int r) {
		if(l > r) swap(l, r);
		l--;
		return sum(r) - sum(l);
	}
	void add(int l, int val) {
		for(; l <= sz; l += (l & -l)) {
			fn[l] += val;
		}
	}
	void update(int l, int val) {
		int tmp = rangeSum(l, l);
		add(l, val - tmp);
	}
};

void dfs(int to, int fr) {
	dth[to] = dth[fr] + 1;
	sp[to][0] = fr;
	for(int i = 1; i <= 20; i++) {
		sp[to][i] = sp[sp[to][i - 1]][i - 1];
	}
	in[to] = ++tt;
	id[tt] = to;
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs(x, to);
	}
	out[to] = tt;
}

int getAnc(int x, int d) {
	for(int i = 20; i >= 0; i--) {
		if(d & (1 << i)) {
			x = sp[x][i];
		}
	}
	return x;
}

int lca(int x, int y) {
	if(dth[x] < dth[y]) swap(x, y);
	x = getAnc(x, dth[x] - dth[y]);
	if(x == y) return x;
	for(int i = 20; i >= 0; i--) {
		if(sp[x][i] != sp[y][i]) {
			x = sp[x][i];
			y = sp[y][i];
		}
	}
	return sp[x][0];
}

void go() {
	int n, k, q;
	cin >> n >> k >> q;
	for(int i = 1; i <= n; i++) {
		cin >> c[i];
	}
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; i++) {
		s[c[i]].in(in[i]);
	}
	BIT fn(n);
	for(int i = 1; i <= k; i++) {
		int ls = -1;
		for(int x : s[i]) {
			int node = id[x];
			fn.add(x, 1);
			if(ls != -1) {
				fn.add(in[lca(ls, node)], -1);
			}
			ls = node;
		}
	}



	auto add = [&](int col, int x) {
		int l = -1, r = -1;
		auto it = s[col].lower_bound(in[x]);
		if(it != s[col].end()) {
			r = *it;
		}
		if(it != s[col].begin()) {
			it--;
			l = *it;
		}
		if(l != -1) l = id[l];
		if(r != -1) r = id[r];
		if(l != -1) {
			fn.add(in[lca(l, x)], -1);
		}
		if(r != -1) {
			fn.add(in[lca(r, x)], -1);
		}
		if(l != -1 && r != -1) {
			fn.add(in[lca(l, r)], 1);
		}
		s[col].in(in[x]);
	};

	auto rem = [&](int col, int x) {
		int l = -1, r = -1;
		s[col].erase(in[x]);
		auto it = s[col].lower_bound(in[x]);
		if(it != s[col].end()) {
			r = *it;
		}
		if(it != s[col].begin()) {
			it--;
			l = *it;
		}
		if(l != -1) l = id[l];
		if(r != -1) r = id[r];
		if(l != -1) {
			fn.add(in[lca(l, x)], 1);
		}
		if(r != -1) {
			fn.add(in[lca(r, x)], 1);
		}
		if(l != -1 && r != -1) {
			fn.add(in[lca(l, r)], -1);
		}
	};

	while(q--) {
		int tp, x;
		cin >> tp >> x;
		if(tp == 1) {
			int y;
			cin >> y;
			rem(c[x], x);
			add(y, x);
			c[x] = y;
		} else {
			cout << fn.rangeSum(in[x], out[x]) << '\n';
		}
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