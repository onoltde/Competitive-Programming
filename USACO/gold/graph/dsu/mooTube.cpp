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

template<typename T>
void mxx(T &a, T b){if(b > a) a = b;}
template<typename T>
void mnn(T &a, T b){if(b < a) a = b;}

struct DSU {
	int n, cmp;
	vector<int> par;
	vector<int> cnt;

	DSU(int _n) {
		n = _n;
		cmp = n;
		par.resize(n + 1, 0);
		cnt.resize(n + 1, 0);
		for(int i = 1; i <= n; i++) {
			par[i] = i;
			cnt[i] = 1;
		}
	}

	int get(int x) {
		return par[x] == x ? x : get(par[x]);
	}

	int getSize(int x) {
		return cnt[get(x)];
	}

	int getComp() {
		return cmp;
	}
	void unite(int x, int y) {
		x = get(x); y = get(y);
		if(x == y) {
			return;
		}
		cmp--;
		if(cnt[x] < cnt[y]) {
			swap(x, y);
		}
		par[y] = x;
		cnt[x] += cnt[y];
	}
};

void go() {
	int n, q;
	cin >> n >> q;
	vector<array<int, 4>> g;
	for(int i = 1, x, y, r; i < n; i++) {
		cin >> x >> y >> r;
		g.pb({r, 1, x, y});
	}
	vector<int> ans(q, 0);
	for(int i = 0, x, k; i < q; i++) {
		cin >> k >> x;
		g.pb({k, 0, x, i});
	}
	DSU ds(n);
	sort(all(g));
	reverse(all(g));
	int sz = g.size();
	for(int i = 0; i < sz; i++) {
		int tp = g[i][1];
		if(tp == 0) {
			ans[g[i][3]] = ds.getSize(g[i][2]);
		}
		else {
			ds.unite(g[i][2], g[i][3]);
		}
	}
	for(int i = 0; i < q; i++) {
		cout << ans[i] - 1 << '\n';
	}
}
 
signed main() {
	fast;
	#ifndef ONO
	freopen("mootube.in", "r", stdin);
	freopen("mootube.out", "w", stdout);
	#endif

	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}