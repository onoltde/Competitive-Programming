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

#define ll long long

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 510;
int dp[mxn][mxn];
int a[mxn];

int solve(int l, int r) {
	if(l == r) {
		return 1;
	}
	if(l > r) {
		return 0;
	}
	if(~dp[l][r]) {
		return dp[l][r];
	}
	int res = solve(l + 1, r) + 1;
	if(a[l] == a[l + 1]) {
		mnn(res, solve(l + 2, r) + 1);
	}
	for(int i = l + 2; i <= r; i++) {
		if(a[l] == a[i]) {
			mnn(res, solve(l + 1, i - 1) + solve(i + 1, r));
		}
	}
	return dp[l][r] = res;
}

signed main() {
	fast;
	// #ifndef ONO
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	// #endif
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = 0; i < mxn; i++) {
		for(int j = 0; j < mxn; j++) {
			dp[i][j] = -1;
		}
	}
	cout << solve(1, n) << '\n';
	return 0;
}