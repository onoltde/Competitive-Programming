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

const int mxn = 310;
int mx[mxn][mxn][mxn], dp[mxn][mxn];

int solve(int l, int r) {
	if(l > r) return 0;
	if(dp[l][r] != -1) return dp[l][r];
	dp[l][r] = 0;
	for(int i = l; i < r; i++) {
		mxx(dp[l][r], solve(l, i) + solve(i + 1, r));
	}
	for(int i = l; i <= r; i++) {
		mxx(dp[l][r], solve(l, i - 1) + solve(i + 1, r) + mx[l][r][i]);
	}
	return dp[l][r];
}

void go() {
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>> g(n + 1);
	for(int j = 1; j <= m; j++) {
		int w, l, r;
		cin >> w >> l >> r;
		g[l].pb({r, w});
	}
	for(int i = 1; i <= n; i++) {
		sort(all(g[i]));
		for(int j = 1; j <= n; j++) {
			dp[i][j] = -1;
		}
	}
	for(int l = 1; l <= n; l++) {
		vector<int> mx(n + 1, 0);
		for(int k = l; k <= n; k++) {
			for(auto it : g[k]) {
				mxx(mx[it.ff], it.ss);
			}
			int tmp = 0;
			for(int r = k; r <= n; r++) {
				mxx(tmp, mx[r]);
				mxx(::mx[l][r][k], tmp);
			}
		}
	}
	cout << solve(1, n) << '\n';
}

signed main() {
	#ifndef ONO
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}