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

const int mxn = 310, inf = 1e18;
int k[mxn], dp[mxn][mxn][mxn][2], pos;

int solve(int l, int r, int d, int tp) {
	if(dp[l][r][d][tp] != inf) return dp[l][r][d][tp];
	if(l == r) return 0;
	if(tp && r - 1 >= pos) mnn(dp[l][r][d][tp], min(solve(l, r - 1, d, tp) + (d - (r - l)) * (k[r] - k[r - 1]),
													solve(l, r - 1, d, 1 ^ tp) + (d - (r - l)) * (k[r] - k[l])));
	else if(!tp && l + 1 <= pos) mnn(dp[l][r][d][tp], min(solve(l + 1, r, d, 1 ^ tp) + (d - (r - l)) * (k[r] - k[l]),
													solve(l + 1, r, d, tp) + (d - (r - l)) * (k[l + 1] - k[l])));
	return dp[l][r][d][tp];
}

void go() {
	int n, m;
	cin >> n >> m;
	bool did = 0;
	for(int i = 1; i <= n; i++) {
		cin >> k[i];
		if(k[i] == 0) did = 1;
	}
	if(!did) k[++n] = 0;
	sort(k + 1, k + n + 1);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			for(int k = 1; k <= n; k++) {
				dp[i][j][k][0] = dp[i][j][k][1] = inf;
			}
		}
	}
	int ans = 0;
	pos = lower_bound(k + 1, k + n + 1, 0ll) - k;
	for(int i = 1; i <= pos; i++) {
		for(int j = pos; j <= n; j++) {
			mxx(ans, m * (j - i + 1) - min(solve(i, j, j - i + 1, 0), solve(i, j, j - i + 1, 1)));
		}
	}
	if(!did) ans -= m;
	cout << ans << '\n';
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