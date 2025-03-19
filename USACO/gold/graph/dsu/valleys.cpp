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

const vector<pair<int, int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, **a;
int *par, *hole, comp;


int con(int x, int y) {
	return (x - 1) * n + y;
}

int get(int x) {
	return par[x] < 0 ? x : par[x] = get(par[x]);
}

void unite(int x, int y) {
	x = get(x);
	y = get(y);
	if(x == y) return;
	if(par[x] < par[y]) swap(x, y);
	par[x] += par[y];
	hole[x] += hole[y];
	par[y] = x;
	comp--;
}

void go() {
	cin >> n;
	a = new int*[n + 10];
	par = new int[n * n + 10];
	hole = new int[n * n + 10];
	vector<pair<int, int>> v;
	for(int i = 1; i <= n; i++) {
		a[i] = new int[n + 10];
		for(int j = 1; j <= n; j++) {
			cin >> a[i][j];
			v.pb({i, j});
			par[con(i, j)] = -1;
			hole[con(i, j)] = 0;
		}
	}
	par[n * n + 1] = -1;
	vector<int> w;
	w.pb(1);
	comp = 1;
	sort(all(v), [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
		return ::a[a.ff][a.ss] > ::a[b.ff][b.ss];
	});
	for(int i = 0; i < n * n; i++) {
		comp++;
		for(int dx = -1; dx <= 1; dx++) {
			for(int dy = -1; dy <= 1; dy++) {
				int x = v[i].ff + dx;
				int y = v[i].ss + dy;
				if(x < 1 || x > n || y < 1 || y > n) unite(con(v[i].ff, v[i].ss), n * n + 1);
				else if(a[v[i].ff][v[i].ss] < a[x][y]) unite(con(v[i].ff, v[i].ss), con(x, y));
			}
		}
		w.pb(comp);
	}
	reverse(all(w));
	for(int i = 1; i <= n * n + 1; i++) {
		par[i] = -1;
		hole[i] = 0;
	}
	reverse(all(v));
	int ans = 0;
	for(int i = 0; i < n * n; i++) {
		for(auto [dx, dy] : dir) {
			int x = v[i].ff + dx;
			int y = v[i].ss + dy;
			if(x < 1 || x > n || y < 1 || y > n || a[x][y] > a[v[i].ff][v[i].ss]) continue;
			unite(con(v[i].ff, v[i].ss), con(x, y));
		}
		int idx = get(con(v[i].ff, v[i].ss));
		hole[idx] += w[i + 1] - w[i];
		if(hole[idx] == 0)
			ans -= par[idx];
	}
	cout << ans << '\n';
}

signed main() {
	fast;
	#ifndef ONO
	freopen("valleys.in", "r", stdin);
	freopen("valleys.out", "w", stdout);
	#endif
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}