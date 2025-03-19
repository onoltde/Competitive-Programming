#include<bits/stdc++.h>
using namespace std;
 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define in insert
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define move2D for(auto [dx, dy] : dl)

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

vector<pair<int, int>> dl = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

const int mxn = 510;
int a[mxn][mxn], l[mxn][mxn], ans[mxn * mxn], par[mxn * mxn], t, cnt[mxn * mxn];
vector<int> g[mxn * mxn];

int get(int x) {
	return par[x] == x ? x : par[x] = get(par[x]);
}

void unite(int x, int y, int p) {
	x = get(x);
	y = get(y);
	if(x == y) return;
	if(g[x].size() < g[y].size()) swap(x, y);
	par[y] = x;
	cnt[x] += cnt[y];
	g[x].insert(g[x].end(), g[y].begin(), g[y].end());
	g[y].clear();
	if(cnt[x] >= t) {
		for(int id : g[x]) {
			ans[id] = p;
		}
		g[x].clear();
	}
}

void go() {
	int n, m;
	cin >> n >> m >> t;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> a[i][j];
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			l[i][j] = m * (i - 1) + j;
			par[l[i][j]] = l[i][j];
			cnt[l[i][j]] = 1;
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int x;
			cin >> x;
			if(x) g[l[i][j]].pb(l[i][j]);
		}
	}
	vector<array<int, 3>> mp;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			move2D {
				int fi = i + dx;
				int fj = j + dy;
				if(fi < 1 || fi > n || fj < 1 || fj > m) continue;
				int dif = abs(a[i][j] - a[fi][fj]);
				mp.pb({dif, l[i][j], l[fi][fj]});
			}
		}
	}
	sort(all(mp));
	for(auto [p, x, y] : mp) {
		unite(x, y, p);
	}
	ll sum = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			sum += (ll)ans[l[i][j]];
		}
	}
	cout << sum << '\n';
}
 
signed main() {
	fast;
	#ifndef ONO
	freopen("skilevel.in", "r", stdin);
	freopen("skilevel.out", "w", stdout);
	#endif

	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}