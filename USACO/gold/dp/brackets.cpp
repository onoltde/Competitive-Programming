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

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 710;
const int inf = 1e18;

int dp[mxn][mxn];
int v[mxn], a[mxn];
int n, k;

int solve(int l, int r) {
	if(dp[l][r] != -inf) {
		return dp[l][r];
	}
	if(l > r) {
		return 0;
	}
	int ret = max(0LL, solve(l + 1, r));
	for(int i = l + 1; i <= r; i++) {
		if(a[i] == a[l] + k) {
			ret = max(ret, solve(l + 1, i - 1) + solve(i + 1, r) + v[l] + v[i]);
		}
	}
	return dp[l][r] = ret;
}

signed main() {
	fast;
	// #ifndef ONO
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	// #endif
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			dp[i][j] = -inf;
		}
	}
	cout << solve(1, n) << '\n';
	return 0;
}