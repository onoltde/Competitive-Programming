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

const int mxn = 510;
int lol[mxn][mxn], a[mxn][mxn];

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
	vector<array<int, 3>> g;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
			lol[i][j] = (i - 1) * n + j;
			if(i - 1 > 0) g.pb({abs(a[i][j] - a[i - 1][j]), lol[i][j], lol[i - 1][j]});
			if(j - 1 > 0) g.pb({abs(a[i][j] - a[i][j - 1]), lol[i][j], lol[i][j - 1]});
		}
	}
	sort(all(g));
	int ans = 0;
	int mx = 1;
	DSU ds(n * n);
	for(auto [c, x, y] : g) {
		if(mx >= (n * n + 1) / 2) break;
		if(ds.get(x) == ds.get(y)) continue;
		ans = c;
		ds.unite(x, y);
		mx = max(ds.getSize(x), mx);
	}
	cout << ans << '\n';
}
 
signed main() {
	fast;
	#ifndef ONO
	freopen("tractor.in", "r", stdin);
	freopen("tractor.out", "w", stdout);
	#endif

	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}