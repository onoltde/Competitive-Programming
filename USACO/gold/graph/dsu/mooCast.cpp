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
	int n;
	cin >> n;
	vector<int> x(n), y(n);
	vector<array<int, 3>> g;
	for(int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
		for(int j = 0; j < i; j++) {
			int dx = x[i] - x[j];
			int dy = y[i] - y[j];
			g.pb({dx * dx + dy * dy, i + 1, j + 1});
		}
	}
	sort(all(g));
	int ans = 0;
	DSU ds(n);
	for(auto [c, x, y] : g) {
		if(ds.get(x) == ds.get(y)) continue;
		ans = c;
		ds.unite(x, y);
	}
	cout << ans << '\n';
}
 
signed main() {
	fast;
	#ifndef ONO
	freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);
	#endif

	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}