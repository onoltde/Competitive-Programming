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

const int mxn = 1 << 14;
vector<int> g[mxn];
map<int, int> gg;
int n, m, k, S;

bool is(int x, int bit) {
	return (x & (1 << bit)) > 0;
}

void build(int now, int ans, int bit) {
	if(bit - 2 >= 0 && !is(now, bit - 2)) return;
	if(bit == n) {
		if(now == (1 << n) - 1) g[S].pb(ans);
		return;
	}
	// 1 **
	//    *
	if(bit - 1 >= 0 && !is(now, bit) && !is(ans, bit) && !is(ans, bit - 1)) {
		build(now ^ (1 << bit), ans ^ (1 << bit) ^ (1 << (bit - 1)), bit + 1);
	}
	// 2 **
	//   *
	if(bit + 1 < n && !is(now, bit) && !is(ans, bit) && !is(ans, bit + 1)) {
		build(now ^ (1 << bit), ans ^ (1 << bit) ^ (1 << (bit + 1)), bit + 1);
	}
	// 3 *
	//   **
	if(bit - 1 >= 0 && !is(now, bit - 1) && !is(now, bit) && !is(ans, bit - 1)) {
		build(now ^ (1 << bit) ^ (1 << (bit - 1)), ans ^ (1 << (bit - 1)), bit + 1);
	}
	// 4  *
	//   **
	if(bit - 1 >= 0 && !is(now, bit - 1) && !is(now, bit) && !is(ans, bit)) {
		build(now ^ (1 << bit) ^ (1 << (bit - 1)), ans ^ (1 << bit), bit + 1);
	}
	// 5
	build(now, ans, bit + 1);
}

vector<vector<int>> get(vector<vector<int>> &a, vector<vector<int>> &b) {
	vector<vector<int>> ret(1 << n, vector<int>(1 << n));
	for(int k = 0; k < (1 << n); k++) {
		for(int i = 0; i < (1 << n); i++) {
			for(int j = 0; j < (1 << n); j++) {
				if(a[i][k] && b[k][j]) ret[i][j] = 1;
			}
		}
	}
	return ret;
}
 
vector<int> solve(vector<int> &prdp, int len, int pp) {
	vector<vector<int>> can(1 << n, vector<int>(1 << n)), tmp(1 << n, vector<int>(1 << n));
	for(int i = 0; i < (1 << n); i++) {
		for(int x : g[i]) {
			tmp[i][x] = 1;
		}
	} 
	for(int i = 0; i < (1 << n); i++) {
		can[i][i] = 1;
	}
	for(; len; len >>= 1) {
		if(len & 1) can = get(can, tmp);
		tmp = get(tmp, tmp);
	}
	vector<int> ret(1 << n);
	for(int i = 0; i < (1 << n); i++) {
		if(!prdp[i]) continue;
		for(int j = 0; j < (1 << n); j++) {
			if(j & pp) continue;
			if(can[i][j]) ret[j | pp] = 1;
		}
	}
	return ret;
}

void go() {
	cin >> n >> m >> k;
	for(int i = 0; i < k; i++) {
		int x, y; cin >> x >> y;
		gg[y] |= (1 << (x - 1));
	}
	for(int i = 0; i < (1 << n); i++) {
		S = i;
		build(i, 0, 0);
		sort(all(g[S]));
		g[S].erase(unique(all(g[S])), g[S].end());
	}
	int ls = 0;
	vector<int> dp(1 << n);
	dp[(1 << n) - 1] = 1;
	gg[m + 1] = (1 << n) - 1;
	if(k == 0) {
		if(n % 6 == 0) {
			if(m >= 2) cout << "YES\n";
			else cout << "NO\n";
		} else if(n % 2 == 0) {
			if(m % 3 == 0) cout << "YES\n";
			else cout << "NO\n";
		} else if(n == 3) {
			if(m % 2 == 0) cout << "YES\n";
			else cout << "NO\n";
		} else if(n == 9) {
			if(m != 1 && m != 3) cout << "YES\n";
			else cout << "NO\n";
		} else {
			if(m % 3 == 0 && m >= 6) cout << "YES\n";
			else cout << "NO\n";
		}
		return;
	}
	if(n <= 6) {
		for(auto it : gg) {
			dp = solve(dp, it.ff - ls, it.ss);
			ls = it.ff;
		}
		if(dp[(1 << n) - 1]) cout << "YES\n";
		else cout << "NO\n";
		return;
	}
	vector<pair<int, int>> v;
	for(auto it : gg) {
		if(it.ff == m + 1) continue;
		v.eb(it.ff, it.ss);
	}
	int l = 0;
	for(int i = 1; i <= m; i++) {
		int nxt = m, msk = 0;
		if(l < v.size()) nxt = v[l].ff;
		int kk = (nxt - i - 2) / 6;
		if(kk >= 0) i += kk * 6;
		if(l < v.size() && v[l].ff == i) {
			msk = v[l++].ss;
		}
		vector<int> nwdp(1 << n);
		for(int j = 0; j < (1 << n); j++) {
			if(!dp[j]) continue;
			for(int x : g[j]) {
				if(x & msk) continue;
				nwdp[x | msk] = 1;
			}
		}
		swap(nwdp, dp);
	}
	if(dp[(1 << n) - 1]) cout << "YES\n";
	else cout << "NO\n";
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