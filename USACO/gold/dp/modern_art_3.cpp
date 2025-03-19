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

template<typename T>
void mxx(T &a, T b){if(b>a) a=b;}
template<typename T>
void mnn(T &a, T b){if(b<a) a=b;}

const int mxn = 310;

int dp[mxn][mxn];
int a[mxn];

signed main() {
	fast;
	int n;
	cin >> n;
	for(int i = 0; i < mxn; i++) {
		for(int j = i; j < mxn; j++) {
			dp[i][j] = 1e9;
		}
	}
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for(int i = n; i >= 1; i--) {
		for(int j = i; j <= n; j++) {
			if(i == j) {
				dp[i][j] = 1;
				continue;
			}
			for(int k = i; k < j; k++) {
				if(a[i] == a[j]) {
					mnn(dp[i][j], dp[i][k] + dp[k + 1][j] - 1);
				}
				else {
					mnn(dp[i][j], dp[i][k] + dp[k + 1][j]);
				}
			}
		}
	}
	cout << dp[1][n] << '\n';
	return 0;
}