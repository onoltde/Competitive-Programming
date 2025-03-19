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

const int mxn = 1e5 + 10, mod = 1e9 + 7;
int dp[mxn][4], col[mxn];
vector<int> g[mxn];

void dfs(int to, int fr) {
	if(col[to]) dp[to][col[to]] = 1;
	else {
		dp[to][1] = dp[to][2] = dp[to][3] = 1;
	}
	for(int x : g[to]) {
		if(x == fr) continue;
		dfs(x, to);
		int sum = dp[x][1] + dp[x][2] + dp[x][3];
		for(int i = 1; i <= 3; i++) {
			dp[to][i] = (dp[to][i] * (sum - dp[x][i])) % mod;
		}
	}
}

void go() {
	int n, k;
	cin >> n >> k;
	for(int i = 1; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[x].pb(y);
		g[y].pb(x);
	}
	for(int i = 1; i <= k; i++) {
		int b, c;
		cin >> b >> c;
		col[b] = c;
	}
	dfs(1, 0);
	cout << (dp[1][1] + dp[1][2] + dp[1][3]) % mod << '\n';
}
 
signed main() {
	#ifndef ONO
	freopen("barnpainting.in", "r", stdin);
	freopen("barnpainting.out", "w", stdout);
	#endif
	fast;
	int t = 1;
	// cin >> t;
	while(t--) {
		go();
	}
	return 0;
}